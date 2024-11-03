#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct Telefon {
    char name[11];
    char surname[21];
    char n_phone[13];
};

const string FILE_OF_DATA = "phone.dat";
const int RESERVE_MAX = 20;

void addNote();
void deleteNote();
void findNote();
void showAllNote();
void saveNoteToFile();
void loadNoteFromFile();
void pressKey();

Telefon phoneBook[RESERVE_MAX];
int numberContact = 0;


int menu() {
    int choice = 0;
    do {
        cout << "1.Додати запис\n";
        cout << "2.Видалити запис\n";
        cout << "3.Знайти запис\n";
        cout << "4.Показати всі записи\n";
        cout << "5.Зберегти записи у файлі\n";
        cout << "6.Завантажити записи з файлу\n";
        cout << "7.Вийти із програми\n";
        cout << "Зробіть вибір: ";
        cin >> choice;
    } while (choice < 1 || choice > 7);
    return choice;
}

int main() {
    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Ukrainian");
    loadNoteFromFile();
        while(1)
            switch (menu()) {
            case 1: addNote(); break;
            case 2: deleteNote(); break;
            case 3: findNote(); break;
            case 4: showAllNote(); break;
            case 5: saveNoteToFile(); break;
            case 6: loadNoteFromFile(); break;
            case 7: return 0;
            default: cout << "Невірний вибір!" << endl;
            }
        
}

void addNote() {
    if (numberContact + 1 <= RESERVE_MAX) {
        numberContact++; 
        cout << "Введіть ім'я: ";
        cin >> phoneBook[numberContact - 1].name;
        cout << "Введіть прізвище: ";
        cin >> phoneBook[numberContact - 1].surname;
        cout << "Введіть номер телефону: ";
        cin >> phoneBook[numberContact - 1].n_phone;
        cout << "Запис успішно додано.\n";
    }
    else {
        cout << "Немає місця!\n";
    }
    pressKey();
}


void showAllNote() {
    if (numberContact > 0) {
        for (int i = 0; i < numberContact; i++) {
            cout << "Ім'я: " << phoneBook[i].name << " Прізвище: " << phoneBook[i].surname<< " Телефон: " << phoneBook[i].n_phone << '\n';
        }
    }
    else {
        cout << "Тут пусто!\n";
    }
    pressKey();
}

void pressKey() {
    cout << "Натисніть будь-яку клавішу для продовження...";
    cin.ignore();
    cin.get();
}

void deleteNote() {
    char n_phone[13];
    cout << "Введіть номер телефону для видалення: ";
    cin >> n_phone;
    bool your_num = 0;
    for (int i = 0; i < numberContact; i++) {
        if (strcmp(phoneBook[i].n_phone, n_phone) == 0) {
            your_num = 1;
            for (int j = i; j < numberContact - 1; j++) {
                phoneBook[j] = phoneBook[j + 1];
            }
            numberContact--;
            cout << "Запис видалено!\n";
            break;
        }
    }

    if (!your_num) {
        cout << "Такого запису немає!\n";
    }
    pressKey();
}

void findNote() {
    char surname[21];
    cout << "Введіть прізвище для пошуку: ";
    cin >> surname;

    bool your_sur = 0;

    for (int i = 0; i < numberContact; i++) {
        if (strcmp(phoneBook[i].surname, surname) == 0) {
            cout << "Ім'я: " << phoneBook[i].name << " Телефон: " << phoneBook[i].n_phone << '\n';
            your_sur = 1;
        }
    }
    if (!your_sur) {
        cout << "Запис не знайдено.\n";
    }
    pressKey();
}

void saveNoteToFile() {
    ofstream file(FILE_OF_DATA, ios::binary);
    file.write(reinterpret_cast<char*>(phoneBook), sizeof(Telefon) * numberContact);
    file.close();

    cout << "Записи успішно збережено у файл.\n";

    pressKey();
}

void loadNoteFromFile() {
    ifstream file(FILE_OF_DATA, ios::binary);
    if (file) {
        file.read(reinterpret_cast<char*>(phoneBook), sizeof(Telefon) * RESERVE_MAX);
        file.close();
        numberContact = file.gcount() / sizeof(Telefon);
        cout << "Записи успішно завантажено з файлу.\n";
    }
    else {
        cout << "Тут пусто, почнемо заповнювати\n";
    }
}