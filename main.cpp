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
        cout << "1.������ �����\n";
        cout << "2.�������� �����\n";
        cout << "3.������ �����\n";
        cout << "4.�������� �� ������\n";
        cout << "5.�������� ������ � ����\n";
        cout << "6.����������� ������ � �����\n";
        cout << "7.����� �� ��������\n";
        cout << "������ ����: ";
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
            default: cout << "������� ����!" << endl;
            }
        
}

void addNote() {
    if (numberContact + 1 <= RESERVE_MAX) {
        numberContact++; 
        cout << "������ ��'�: ";
        cin >> phoneBook[numberContact - 1].name;
        cout << "������ �������: ";
        cin >> phoneBook[numberContact - 1].surname;
        cout << "������ ����� ��������: ";
        cin >> phoneBook[numberContact - 1].n_phone;
        cout << "����� ������ ������.\n";
    }
    else {
        cout << "���� ����!\n";
    }
    pressKey();
}


void showAllNote() {
    if (numberContact > 0) {
        for (int i = 0; i < numberContact; i++) {
            cout << "��'�: " << phoneBook[i].name << " �������: " << phoneBook[i].surname<< " �������: " << phoneBook[i].n_phone << '\n';
        }
    }
    else {
        cout << "��� �����!\n";
    }
    pressKey();
}

void pressKey() {
    cout << "�������� ����-��� ������ ��� �����������...";
    cin.ignore();
    cin.get();
}

void deleteNote() {
    char n_phone[13];
    cout << "������ ����� �������� ��� ���������: ";
    cin >> n_phone;
    bool your_num = 0;
    for (int i = 0; i < numberContact; i++) {
        if (strcmp(phoneBook[i].n_phone, n_phone) == 0) {
            your_num = 1;
            for (int j = i; j < numberContact - 1; j++) {
                phoneBook[j] = phoneBook[j + 1];
            }
            numberContact--;
            cout << "����� ��������!\n";
            break;
        }
    }

    if (!your_num) {
        cout << "������ ������ ����!\n";
    }
    pressKey();
}

void findNote() {
    char surname[21];
    cout << "������ ������� ��� ������: ";
    cin >> surname;

    bool your_sur = 0;

    for (int i = 0; i < numberContact; i++) {
        if (strcmp(phoneBook[i].surname, surname) == 0) {
            cout << "��'�: " << phoneBook[i].name << " �������: " << phoneBook[i].n_phone << '\n';
            your_sur = 1;
        }
    }
    if (!your_sur) {
        cout << "����� �� ��������.\n";
    }
    pressKey();
}

void saveNoteToFile() {
    ofstream file(FILE_OF_DATA, ios::binary);
    file.write(reinterpret_cast<char*>(phoneBook), sizeof(Telefon) * numberContact);
    file.close();

    cout << "������ ������ ��������� � ����.\n";

    pressKey();
}

void loadNoteFromFile() {
    ifstream file(FILE_OF_DATA, ios::binary);
    if (file) {
        file.read(reinterpret_cast<char*>(phoneBook), sizeof(Telefon) * RESERVE_MAX);
        file.close();
        numberContact = file.gcount() / sizeof(Telefon);
        cout << "������ ������ ����������� � �����.\n";
    }
    else {
        cout << "��� �����, ������� �����������\n";
    }
}