#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
#include <Windows.h> 
#include <cstring>
using namespace std;

// Структури даних
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

// Функція створення файлу
void CreateFile(const char* fname) {
    ofstream fout(fname, ios::binary);
    if (!fout) {
        cout << "Помилка відкриття файлу для запису!" << endl;
        return;
    }

    char ch;
    do {
        Institute institute;
        cin.ignore();
        cout << "Введіть назву інституту: ";
        cin.getline(institute.name, 50);

        cout << "Введіть план прийому: ";
        cin >> institute.admissionPlan;

        cout << "Введіть кількість факультетів: ";
        cin >> institute.facultyCount;

        for (int i = 0; i < institute.facultyCount; i++) {
            cin.ignore();
            cout << "Введіть назву факультету: ";
            cin.getline(institute.faculties[i].name, 50);

            cout << "Введіть кількість спеціальностей: ";
            cin >> institute.faculties[i].specialtyCount;

            for (int j = 0; j < institute.faculties[i].specialtyCount; j++) {
                cin.ignore();
                cout << "Введіть назву спеціальності: ";
                cin.getline(institute.faculties[i].specialties[j].name, 50);

                cout << "Введіть прохідний бал: ";
                cin >> institute.faculties[i].specialties[j].passingScore;
            }
        }

        fout.write((char*)&institute, sizeof(Institute));

        cout << "Продовжити введення? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "Файл успішно створено." << endl;
}

// Функція виведення файлу
void PrintFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "Помилка відкриття файлу для читання!" << endl;
        return;
    }

    Institute institute;
    while (fin.read((char*)&institute, sizeof(Institute))) {
        cout << "Інститут: " << institute.name << endl;
        cout << "План прийому: " << institute.admissionPlan << endl;
        cout << "Кількість факультетів: " << institute.facultyCount << endl;

        for (int i = 0; i < institute.facultyCount; i++) {
            cout << "  Факультет: " << institute.faculties[i].name << endl;
            cout << "  Кількість спеціальностей: " << institute.faculties[i].specialtyCount << endl;

            for (int j = 0; j < institute.faculties[i].specialtyCount; j++) {
                cout << "    Спеціальність: " << institute.faculties[i].specialties[j].name << endl;
                cout << "    Прохідний бал: " << institute.faculties[i].specialties[j].passingScore << endl;
            }
        }
        cout << endl;
    }

    fin.close();
}

// Функція доповнення файлу
void AppendToFile(const char* fname) {
    ofstream fout(fname, ios::binary | ios::app);
    if (!fout) {
        cout << "Помилка відкриття файлу для доповнення!" << endl;
        return;
    }

    char ch;
    do {
        Institute institute;
        cin.ignore();
        cout << "Введіть назву інституту: ";
        cin.getline(institute.name, 50);

        cout << "Введіть план прийому: ";
        cin >> institute.admissionPlan;

        cout << "Введіть кількість факультетів: ";
        cin >> institute.facultyCount;

        for (int i = 0; i < institute.facultyCount; i++) {
            cin.ignore();
            cout << "Введіть назву факультету: ";
            cin.getline(institute.faculties[i].name, 50);

            cout << "Введіть кількість спеціальностей: ";
            cin >> institute.faculties[i].specialtyCount;

            for (int j = 0; j < institute.faculties[i].specialtyCount; j++) {
                cin.ignore();
                cout << "Введіть назву спеціальності: ";
                cin.getline(institute.faculties[i].specialties[j].name, 50);

                cout << "Введіть прохідний бал: ";
                cin >> institute.faculties[i].specialties[j].passingScore;
            }
        }

        fout.write((char*)&institute, sizeof(Institute));

        cout << "Продовжити введення? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "Файл успішно доповнено." << endl;
}

// Функція заміни даних у файлі
void ReplaceInFile(const char* fname) {
    fstream file(fname, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Помилка відкриття файлу для редагування!" << endl;
        return;
    }

    Institute institute;
    char searchName[50];
    bool found = false;

    cout << "Введіть назву інституту, який потрібно змінити: ";
    cin.ignore();
    cin.getline(searchName, 50);

    while (file.read((char*)&institute, sizeof(Institute))) {
        if (strcmp(institute.name, searchName) == 0) {
            cout << "Знайдено інститут: " << institute.name << ". Введіть нові дані.\n";
            file.seekp(-static_cast<int>(sizeof(Institute)), ios::cur);

            cout << "Введіть нову назву інституту: ";
            cin.getline(institute.name, 50);

            cout << "Введіть новий план прийому: ";
            cin >> institute.admissionPlan;

            cout << "Введіть кількість факультетів: ";
            cin >> institute.facultyCount;

            for (int i = 0; i < institute.facultyCount; i++) {
                cin.ignore();
                cout << "Введіть назву факультету: ";
                cin.getline(institute.faculties[i].name, 50);

                cout << "Введіть кількість спеціальностей: ";
                cin >> institute.faculties[i].specialtyCount;

                for (int j = 0; j < institute.faculties[i].specialtyCount; j++) {
                    cin.ignore();
                    cout << "Введіть назву спеціальності: ";
                    cin.getline(institute.faculties[i].specialties[j].name, 50);

                    cout << "Введіть прохідний бал: ";
                    cin >> institute.faculties[i].specialties[j].passingScore;
                }
            }

            file.write((char*)&institute, sizeof(Institute));
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Інститут з назвою \"" << searchName << "\" не знайдено.\n";
    }

    file.close();
}

// Функція видалення даних із файлу
void DeleteFromFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    ofstream fout("temp.bin", ios::binary);

    if (!fin || !fout) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    Institute institute;
    char searchName[50];
    bool found = false;

    cout << "Введіть назву інституту, який потрібно видалити: ";
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
        cout << "Інститут успішно видалено.\n";
    }
    else {
        remove("temp.bin");
        cout << "Інститут з назвою \"" << searchName << "\" не знайдено.\n";
    }
}

// Меню програми
void Menu() {
    char fname[100];
    cout << "Введіть ім'я файлу: ";
    cin >> fname;

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1 - Створити файл\n";
        cout << "2 - Вивести вміст файлу\n";
        cout << "3 - Доповнити файл\n";
        cout << "4 - Змінити дані в файлі\n";
        cout << "5 - Видалити дані з файлу\n";
        cout << "0 - Вихід\n";
        cout << "Ваш вибір: ";
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
            cout << "Завершення програми.\n";
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);
}

// Головна функція
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Menu();
    return 0;
}
