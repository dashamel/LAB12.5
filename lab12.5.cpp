#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
#include <Windows.h> 
#include <cstring>
using namespace std;

// ��������� �����
struct Specialty {
    char name[50];
    float passingScore;
};

struct Faculty {
    char name[50];
    int specialtyCount;
    Specialty specialties[10]; 
};

struct Institute {
    char name[50];
    int admissionPlan;
    int facultyCount;
    Faculty faculties[10];
};
void CreateFile(const char* fname); 
void PrintFile(const char* fname); 
void AppendToFile(const char* fname);
void ReplaceInFile(const char* fname);
void DeleteFromFile(const char* fname);
void Menu();

// ������� ��������� �����
void CreateFile(const char* fname) {
    ofstream fout(fname, ios::binary);
    if (!fout) {
        cout << "������� �������� ����� ��� ������!" << endl;
        return;
    }

    char ch;
    do {
        Institute institute;
        cin.ignore();
        cout << "������ ����� ���������: ";
        cin.getline(institute.name, 50);

        cout << "������ ���� �������: ";
        cin >> institute.admissionPlan;

        cout << "������ ������� ����������: ";
        cin >> institute.facultyCount;

        for (int i = 0; i < institute.facultyCount; i++) {
            cin.ignore();
            cout << "������ ����� ����������: ";
            cin.getline(institute.faculties[i].name, 50);

            cout << "������ ������� ��������������: ";
            cin >> institute.faculties[i].specialtyCount;

            for (int j = 0; j < institute.faculties[i].specialtyCount; j++) {
                cin.ignore();
                cout << "������ ����� ������������: ";
                cin.getline(institute.faculties[i].specialties[j].name, 50);

                cout << "������ ��������� ���: ";
                cin >> institute.faculties[i].specialties[j].passingScore;
            }
        }

        fout.write((char*)&institute, sizeof(Institute));

        cout << "���������� ��������? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "���� ������ ��������." << endl;
}

// ������� ��������� �����
void PrintFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "������� �������� ����� ��� �������!" << endl;
        return;
    }

    Institute institute;
    while (fin.read((char*)&institute, sizeof(Institute))) {
        cout << "��������: " << institute.name << endl;
        cout << "���� �������: " << institute.admissionPlan << endl;
        cout << "ʳ������ ����������: " << institute.facultyCount << endl;

        for (int i = 0; i < institute.facultyCount; i++) {
            cout << "  ���������: " << institute.faculties[i].name << endl;
            cout << "  ʳ������ ��������������: " << institute.faculties[i].specialtyCount << endl;

            for (int j = 0; j < institute.faculties[i].specialtyCount; j++) {
                cout << "    ������������: " << institute.faculties[i].specialties[j].name << endl;
                cout << "    ��������� ���: " << institute.faculties[i].specialties[j].passingScore << endl;
            }
        }
        cout << endl;
    }

    fin.close();
}

// ������� ���������� �����
void AppendToFile(const char* fname) {
    ofstream fout(fname, ios::binary | ios::app);
    if (!fout) {
        cout << "������� �������� ����� ��� ����������!" << endl;
        return;
    }

    char ch;
    do {
        Institute institute;
        cin.ignore();
        cout << "������ ����� ���������: ";
        cin.getline(institute.name, 50);

        cout << "������ ���� �������: ";
        cin >> institute.admissionPlan;

        cout << "������ ������� ����������: ";
        cin >> institute.facultyCount;

        for (int i = 0; i < institute.facultyCount; i++) {
            cin.ignore();
            cout << "������ ����� ����������: ";
            cin.getline(institute.faculties[i].name, 50);

            cout << "������ ������� ��������������: ";
            cin >> institute.faculties[i].specialtyCount;

            for (int j = 0; j < institute.faculties[i].specialtyCount; j++) {
                cin.ignore();
                cout << "������ ����� ������������: ";
                cin.getline(institute.faculties[i].specialties[j].name, 50);

                cout << "������ ��������� ���: ";
                cin >> institute.faculties[i].specialties[j].passingScore;
            }
        }

        fout.write((char*)&institute, sizeof(Institute));

        cout << "���������� ��������? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "���� ������ ���������." << endl;
}

// ������� ����� ����� � ����
void ReplaceInFile(const char* fname) {
    fstream file(fname, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "������� �������� ����� ��� �����������!" << endl;
        return;
    }

    Institute institute;
    char searchName[50];
    bool found = false;

    cout << "������ ����� ���������, ���� ������� ������: ";
    cin.ignore();
    cin.getline(searchName, 50);

    while (file.read((char*)&institute, sizeof(Institute))) {
        if (strcmp(institute.name, searchName) == 0) {
            cout << "�������� ��������: " << institute.name << ". ������ ��� ���.\n";
            file.seekp(-static_cast<int>(sizeof(Institute)), ios::cur);

            cout << "������ ���� ����� ���������: ";
            cin.getline(institute.name, 50);

            cout << "������ ����� ���� �������: ";
            cin >> institute.admissionPlan;

            cout << "������ ������� ����������: ";
            cin >> institute.facultyCount;

            for (int i = 0; i < institute.facultyCount; i++) {
                cin.ignore();
                cout << "������ ����� ����������: ";
                cin.getline(institute.faculties[i].name, 50);

                cout << "������ ������� ��������������: ";
                cin >> institute.faculties[i].specialtyCount;

                for (int j = 0; j < institute.faculties[i].specialtyCount; j++) {
                    cin.ignore();
                    cout << "������ ����� ������������: ";
                    cin.getline(institute.faculties[i].specialties[j].name, 50);

                    cout << "������ ��������� ���: ";
                    cin >> institute.faculties[i].specialties[j].passingScore;
                }
            }

            file.write((char*)&institute, sizeof(Institute));
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "�������� � ������ \"" << searchName << "\" �� ��������.\n";
    }

    file.close();
}

// ������� ��������� ����� �� �����
void DeleteFromFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    ofstream fout("temp.bin", ios::binary);

    if (!fin || !fout) {
        cout << "������� �������� �����!" << endl;
        return;
    }

    Institute institute;
    char searchName[50];
    bool found = false;

    cout << "������ ����� ���������, ���� ������� ��������: ";
    cin.ignore();
    cin.getline(searchName, 50);

    while (fin.read((char*)&institute, sizeof(Institute))) {
        if (strcmp(institute.name, searchName) != 0) {
            fout.write((char*)&institute, sizeof(Institute));
        }
        else {
            found = true;
        }
    }

    fin.close();
    fout.close();

    if (found) {
        remove(fname);
        rename("temp.bin", fname);
        cout << "�������� ������ ��������.\n";
    }
    else {
        remove("temp.bin");
        cout << "�������� � ������ \"" << searchName << "\" �� ��������.\n";
    }
}

// ���� ��������
void Menu() {
    char fname[100];
    cout << "������ ��'� �����: ";
    cin >> fname;

    int choice;
    do {
        cout << "\n����:\n";
        cout << "1 - �������� ����\n";
        cout << "2 - ������� ���� �����\n";
        cout << "3 - ��������� ����\n";
        cout << "4 - ������ ��� � ����\n";
        cout << "5 - �������� ��� � �����\n";
        cout << "0 - �����\n";
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CreateFile(fname);
            break;
        case 2:
            PrintFile(fname);
            break;
        case 3:
            AppendToFile(fname);
            break;
        case 4:
            ReplaceInFile(fname);
            break;
        case 5:
            DeleteFromFile(fname);
            break;
        case 0:
            cout << "���������� ��������.\n";
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    } while (choice != 0);
}

// ������� �������
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Menu();
    return 0;
}
