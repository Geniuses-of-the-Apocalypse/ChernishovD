#include <iostream>
#include <string>


using namespace std;

class Liquid {
protected:
    string name;
    double density;

public:
    Liquid();
    Liquid(const string& n, double d);
    virtual ~Liquid();

    void setName(const string& n);
    string getName() const;
    void setDensity(double d);
    double getDensity() const;

    virtual string toString() const;

    friend ostream& operator<<(ostream& os, const Liquid& l);
    friend istream& operator>>(istream& is, Liquid& l);
};

Liquid::Liquid() : name("Unknown"), density(0) {}

Liquid::Liquid(const string& n, double d) : name(n), density(d) {
    if (density < 0) {
        cerr << "Ошибка: плотность не может быть отрицательной!" << endl;
        exit(1);
    }
}

Liquid::~Liquid() {}

void Liquid::setName(const string& n) {
    name = n;
}

string Liquid::getName() const {
    return name;
}

void Liquid::setDensity(double d) {
    if (d < 0) {
        cerr << "Ошибка: плотность не может быть отрицательной!" << endl;
        exit(1);
    }
    density = d;
}

double Liquid::getDensity() const {
    return density;
}

string Liquid::toString() const {
    return "Жидкость: " + name + ", плотность = " + to_string(density) + " кг/м³";
}

ostream& operator<<(ostream& os, const Liquid& l) {
    os << l.toString();
    return os;
}

istream& operator>>(istream& is, Liquid& l) {
    cout << "Введите название жидкости: ";
    getline(is, l.name);
    cout << "Введите плотность (кг/м³): ";
    is >> l.density;
    is.ignore();
    if (l.density < 0) {
        cerr << "Ошибка: плотность не может быть отрицательной!" << endl;
        exit(1);
    }
    return is;
}

class Alcohol : public Liquid {
private:
    double strength;

public:
    Alcohol();
    Alcohol(const string& n, double d, double s);

    void setStrength(double s);
    double getStrength() const;

    string toString() const override;

    friend ostream& operator<<(ostream& os, const Alcohol& a);
    friend istream& operator>>(istream& is, Alcohol& a);
};

Alcohol::Alcohol() : Liquid(), strength(0) {}

Alcohol::Alcohol(const string& n, double d, double s) : Liquid(n, d), strength(s) {
    if (strength < 0 || strength > 100) {
        cerr << "Ошибка: крепость должна быть в диапазоне 0..100%!" << endl;
        exit(1);
    }
}

void Alcohol::setStrength(double s) {
    if (s < 0 || s > 100) {
        cerr << "Ошибка: крепость должна быть в диапазоне 0..100%!" << endl;
        exit(1);
    }
    strength = s;
}

double Alcohol::getStrength() const {
    return strength;
}

string Alcohol::toString() const {
    return "Спирт: " + name + ", плотность = " + to_string(density) +
        " кг/м³, крепость = " + to_string(strength) + "%";
}

ostream& operator<<(ostream& os, const Alcohol& a) {
    os << a.toString();
    return os;
}

istream& operator>>(istream& is, Alcohol& a) {
    cout << "Введите название спирта: ";
    getline(is, a.name);
    cout << "Введите плотность (кг/м³): ";
    is >> a.density;
    cout << "Введите крепость (%): ";
    is >> a.strength;
    is.ignore();
    if (a.density < 0 || a.strength < 0 || a.strength > 100) {
        cerr << "Ошибка ввода данных!" << endl;
        exit(1);
    }
    return is;
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << " Создание объектов Liquid " << endl;
    Liquid liq1("Вода", 1000);
    Liquid liq2;
    liq2.setName("Масло");
    liq2.setDensity(900);
    cout << liq1 << endl;
    cout << liq2 << endl;

    cout << "\n Создание объектов Alcohol " << endl;
    Alcohol alc1("Водка", 950, 40);
    Alcohol alc2;
    alc2.setName("Виски");
    alc2.setDensity(940);
    alc2.setStrength(45);
    cout << alc1 << endl;
    cout << alc2 << endl;

    cout << "\n Принцип подстановки " << endl;
    Liquid* basePtr = &alc1;
    cout << "Через указатель на Liquid: " << basePtr->toString() << endl;

    cout << "\n Массив объектов " << endl;
    Alcohol alcohols[2] = {
        Alcohol("Ром", 920, 38),
        Alcohol("Джин", 930, 42)
    };
    for (int i = 0; i < 2; i++) {
        cout << alcohols[i] << endl;
    }

    cout << "\n Работа с вводом/выводом " << endl;
    Alcohol alc3;
    cout << "Введите данные для спирта:" << endl;
    cin >> alc3;
    cout << "Вы ввели: " << alc3 << endl;

    return 0;
}
