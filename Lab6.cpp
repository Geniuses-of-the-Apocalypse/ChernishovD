#include <iostream>
#include <cstring>

using namespace std;

class Array {
protected:
    static const int MAX = 100;
    unsigned char* arr;
    int len;

public:
    Array();
    Array(int n, unsigned char init = 0);
    virtual ~Array();

    int length() const;
    unsigned char& operator[](int index);
    virtual Array* operator+(Array& other) = 0;

    friend ostream& operator<<(ostream& out, const Array& a);
    friend istream& operator>>(istream& in, Array& a);
};

Array::Array() : arr(nullptr), len(0) {}

Array::Array(int n, unsigned char init) : len(n) {
    arr = new unsigned char[MAX];
    for (int i = 0; i < len; i++)
        arr[i] = init;
}

Array::~Array() {
    delete[] arr;
}

int Array::length() const {
    return len;
}

unsigned char& Array::operator[](int index) {
    if (index < 0 || index >= len) {
        cerr << "Ошибка индекса!" << endl;
        exit(1);
    }
    return arr[index];
}

ostream& operator<<(ostream& out, const Array& a) {
    for (int i = 0; i < a.len; i++)
        out << (int)a.arr[i] << " ";
    return out;
}

istream& operator>>(istream& in, Array& a) {
    cout << "Введите длину массива (1-" << a.MAX << "): ";
    in >> a.len;
    if (a.len <= 0 || a.len > a.MAX) {
        cerr << "Неверная длина!" << endl;
        exit(1);
    }
    delete[] a.arr;
    a.arr = new unsigned char[a.MAX];
    cout << "Введите элементы (числа 0-255): ";
    for (int i = 0; i < a.len; i++)
        in >> a.arr[i];
    return in;
}

class Decimal : public Array {
private:
    bool sign;

public:
    Decimal();
    Decimal(int n, bool s = false);

    Array* operator+(Array& other) override;

    friend ostream& operator<<(ostream& out, const Decimal& d);
    friend istream& operator>>(istream& in, Decimal& d);
};

Decimal::Decimal() : Array(), sign(false) {}

Decimal::Decimal(int n, bool s) : Array(n, 0), sign(s) {}

Array* Decimal::operator+(Array& other) {
    Decimal* res = new Decimal(len, false);
    for (int i = 0; i < len; i++)
        (*res)[i] = arr[i] + ((Decimal&)other)[i];
    return res;
}

ostream& operator<<(ostream& out, const Decimal& d) {
    out << (d.sign ? "-" : "");
    for (int i = 0; i < d.len; i++)
        out << (int)d.arr[i];
    return out;
}

istream& operator>>(istream& in, Decimal& d) {
    cout << "Длина десятичного числа: ";
    in >> d.len;
    delete[] d.arr;
    d.arr = new unsigned char[d.MAX];
    cout << "Введите цифры (0-9) через пробел: ";
    for (int i = 0; i < d.len; i++) {
        int tmp;
        in >> tmp;
        d.arr[i] = tmp;
    }
    cout << "Знак (0 = '+', 1 = '-'): ";
    in >> d.sign;
    return in;
}

class BitString : public Array {
public:
    BitString();
    BitString(int n);

    Array* operator+(Array& other) override;

    friend ostream& operator<<(ostream& out, const BitString& bs);
    friend istream& operator>>(istream& in, BitString& bs);
};

BitString::BitString() : Array() {}

BitString::BitString(int n) : Array(n, 0) {}

Array* BitString::operator+(Array& other) {
    BitString* res = new BitString(len);
    for (int i = 0; i < len; i++)
        (*res)[i] = arr[i] ^ ((BitString&)other)[i];
    return res;
}

ostream& operator<<(ostream& out, const BitString& bs) {
    out << "Битовая строка: ";
    for (int i = 0; i < bs.len; i++)
        out << (int)bs.arr[i];
    return out;
}

istream& operator>>(istream& in, BitString& bs) {
    cout << "Длина битовой строки: ";
    in >> bs.len;
    delete[] bs.arr;
    bs.arr = new unsigned char[bs.MAX];
    cout << "Введите биты (0 или 1) через пробел: ";
    for (int i = 0; i < bs.len; i++) {
        int tmp;
        in >> tmp;
        bs.arr[i] = tmp;
    }
    return in;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "вариант 3 (Decimal и BitString) \n\n";

    Decimal dec1, dec2;
    cout << "Введите первое десятичное число:\n";
    cin >> dec1;
    cout << "Введите второе десятичное число:\n";
    cin >> dec2;

    Array* sumDec = dec1 + dec2;
    cout << "Сумма (поэлементная): " << *sumDec << endl;
    delete sumDec;

    BitString bs1, bs2;
    cout << "\nВведите первую битовую строку:\n";
    cin >> bs1;
    cout << "Введите вторую битовую строку:\n";
    cin >> bs2;

    Array* sumBits = bs1 + bs2;
    cout << "Сумма (XOR): " << *sumBits << endl;
    delete sumBits;

    Array* arrPtr;
    arrPtr = &dec1;
    cout << "\nЧерез указатель на Array выводим Decimal: " << *arrPtr << endl;

    arrPtr = &bs1;
    cout << "Через указатель на Array выводим BitString: " << *arrPtr << endl;

    return 0;
}
