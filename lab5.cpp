#include <sstream>
#include <string>
#include <cstdlib>  
#include <ctime>    
#include <iostream>

using namespace std;

// Класс для представления IP-адреса
class IPv4 {
private:
    int p1, p2, p3, p4; // Части IP-адреса

public:
    // Метод для парсинга одной части IP-адреса в десятичной, восьмеричной и шестнадцатеричной системах
    bool ParsePart(const string& partStr, int& part) {
        int base = 10;

        if (partStr.size() > 1 && partStr[0] == '0') {
            if (partStr[1] == 'x' || partStr[1] == 'X') {
                base = 16;  // шестнадцатеричная система
            } else if (isdigit(partStr[1])) {
                base = 8;   // восьмеричная система
            }
        }

        try {
            part = stoi(partStr, nullptr, base);
        } catch (...) {
            return false; // Если ошибка парсинга, возвращаем false
        }

        // Проверка на допустимые значения для части IP (от 0 до 255)
        return (part >= 0 && part <= 255);
    }


    // Метод для проверки IP-адреса
    bool IsValid() {
        return (p1 >= 0 && p1 <= 255) && 
               (p2 >= 0 && p2 <= 255) && 
               (p3 >= 0 && p3 <= 255) && 
               (p4 >= 0 && p4 <= 255);
    }

    // Метод для парсинга IP-адреса из строки
    bool Parse(const string& ipStr) {
        istringstream ss(ipStr);
        string partStr;

        // Читаем и парсим 4 части IP-адреса
        if (!(getline(ss, partStr, '.') && ParsePart(partStr, p1))) return false;
        if (!(getline(ss, partStr, '.') && ParsePart(partStr, p2))) return false;
        if (!(getline(ss, partStr, '.') && ParsePart(partStr, p3))) return false;
        if (!(getline(ss, partStr) && ParsePart(partStr, p4))) return false;

        return true;
    }

    // Метод для преобразования IP-адреса в строку
    string ToString() {
        return to_string(p1) + "." + to_string(p2) + "." + to_string(p3) + "." + to_string(p4);
    }

    // Метод для генерации случайного IP-адреса, который может быть недействительным
    void GenerateRandomIP(bool valid = true) {
        p1 = rand() % 256;
        p2 = rand() % 256;
        p3 = rand() % 256;
        p4 = rand() % 256;

        // Если нужно создать недействительный IP-адрес, то модифицируем одну из частей
        if (!valid) {
            // Случайным образом увеличиваем одну из частей на большее значение, чем 255
            int invalidPart = rand() % 4;
            switch (invalidPart) {
                case 0: p1 = 256; break;
                case 1: p2 = 256; break;
                case 2: p3 = 256; break;
                case 3: p4 = 256; break;
            }
        }
    }
};

// Основное меню
int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    IPv4 ip; // создаем объект для IP-адреса
    string ipStr;

    while (true) {
        cout << "\n=== АРМ Системного Администратора ===\n";
        cout << "1. Проверить IP-адрес\n";
        cout << "2. Сгенерировать случайный IP и проверить\n";
        cout << "3. Выход\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Введите IP-адрес: ";
            getline(cin, ipStr);

            if (ip.Parse(ipStr)) {
                if (ip.IsValid()) {
                    cout << "IP-адрес действителен: " << ip.ToString() << endl;
                } else {
                    cout << "IP-адрес недействителен.\n";
                }
            } else {
                cout << "IP-адрес недействителен.\n";
            }
        } else if (choice == 2) {
            // Генерация случайного IP
            bool valid = rand() % 2; // случайным образом генерируем действительный или недействительный IP
            ip.GenerateRandomIP(valid);
            cout << "Сгенерированный IP: " << ip.ToString() << endl;

            if (ip.IsValid()) {
                cout << "IP-адрес действителен.\n";
            } else {
                cout << "Ошибка: сгенерированный IP-адрес недействителен!\n";
            }
        } else if (choice == 3) {
            cout << "Выход...\n";
            break;
        } else {
            cout << "Некорректный ввод, попробуйте снова.\n";
        }
    }

    return 0;
}
