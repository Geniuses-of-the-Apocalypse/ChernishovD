#include <iostream>
using namespace std;

struct Drob {
private:
    int first;
    int second;
public:
    void init(int f, int s);
    void read();
    void display() const;
    int ipart() const;
};

void Drob::init(int f, int s) {
    if (f <= 0 || s <= 0) {
        cout << "Ошибка: числитель и знаменатель должны быть положительными." << endl;
        exit(1);
    }
    first = f;
    second = s;
}

void Drob::read() {
    int f, s;
    cout << "Введите числитель (положительное целое): ";
    cin >> f;
    cout << "Введите знаменатель (положительное целое): ";
    cin >> s;

    if (f <= 0 || s <= 0) {
        cout << "Ошибка: числитель и знаменатель должны быть положительными." << endl;
        exit(1);
    }
    first = f;
    second = s;
}

void Drob::display() const {
    cout << first << "/" << second;
}

int Drob::ipart() const {
    if (second == 0) {
        throw runtime_error("Ошибка: знаменатель не может быть нулём.");
    }
    return first / second;
}


int main() {
    setlocale(LC_ALL, "Ru");
    Drob d1;
    d1.init(7, 3);
    cout << "Дробь D1: ";
    d1.display();
    cout << ", целая часть: " << d1.ipart() << endl;

    Drob d2;
    d2.read();
    cout << "Дробь D2: ";
    d2.display();
    cout << ", целая часть: " << d2.ipart() << endl;

    return 0;
}
