#include <iostream>
#include <cmath>

using namespace std;

struct Pair {
    int first;  
    int second;  

    void init(int a, int b);
    void read();
    void display();
    double ipart();
};

void Pair::init(int a, int b) {
    if (a < 0 || b <= 0) {
        cout << "Ошибка: числитель должен быть неотрицательным, знаменатель - положительным!" << endl;
        cout << "Значения по умолчанию (1, 1)" << endl;
        first = 1;
        second = 1;
        return;
    }
    first = a;
    second = b;
}

void Pair::read() {
    int a, b;
    cout << "Введите целое положительное число (числитель): ";
    cin >> a;
    cout << "Введите целое положительное число (знаменатель): ";
    cin >> b;
    init(a, b);
}

void Pair::display() {
    cout << "first = " << first << ", second = " << second;
    cout << " (дробь: " << first << "/" << second << ")";
}

double Pair::ipart() {
    if (second == 0) {
        cout << "Ошибка: знаменатель равен нулю!" << endl;
        return 0;
    }
    return static_cast<double>(first) / second;
}

Pair make_Pair(int a, int b) {
    if (a < 0 || b <= 0) {
        cout << "Ошибка: числитель должен быть неотрицательным, знаменатель - положительным!" << endl;
        cout << "Объект с значениями по умолчанию (1, 1)" << endl;
        Pair p;
        p.init(1, 1);
        return p;
    }
    Pair p;
    p.init(a, b);
    return p;
}


int main() {
    setlocale(LC_ALL, "Russian");
    cout << " Лабораторная работа 1 \n" << endl;
    cout << " Вариант 3: Выделение целой части дроби \n" << endl;

    cout << " Статический объект " << endl;
    Pair p1;
    p1.init(7, 3);
    p1.display();
    cout << "\nЦелая часть дроби: " << static_cast<int>(p1.ipart()) << endl;
    cout << "Десятичное значение: " << p1.ipart() << endl;

    cout << "\n Ввод с клавиатуры " << endl;
    Pair p2;
    p2.read();
    p2.display();
    cout << "\nЦелая часть дроби: " << static_cast<int>(p2.ipart()) << endl;
    cout << "Десятичное значение: " << p2.ipart() << endl;

    cout << "\n3. Внешняя функция make_Pair " << endl;
    Pair p3 = make_Pair(15, 4);
    p3.display();
    cout << "\nЦелая часть дроби: " << static_cast<int>(p3.ipart()) << endl;
    cout << "Десятичное значение: " << p3.ipart() << endl;

    cout << "\n Массив объектов " << endl;
    Pair arr[3];

    arr[0].init(8, 3);    
    arr[1].init(5, 2);    
    arr[2].init(1, 4);   

    for (int i = 0; i < 3; i++) {
        cout << "\nОбъект " << i + 1 << ": ";
        arr[i].display();
        cout << "\nЦелая часть: " << static_cast<int>(arr[i].ipart());
        cout << "\nДесятичное значение: " << arr[i].ipart() << endl;
    }

    cout << "\n Динамический объект " << endl;
    Pair* p4 = new Pair;
    p4->init(22, 7);  
    p4->display();
    cout << "\nЦелая часть дроби: " << static_cast<int>(p4->ipart()) << endl;
    cout << "Десятичное значение: " << p4->ipart() << endl;
    delete p4;

    cout << "\n Демонстрация обработки ошибок " << endl;

    cout << "Попытка создать объект с отрицательным числителем (-5, 3):" << endl;
    Pair p5;
    p5.init(-5, 3);
    p5.display();
    cout << "\nДесятичное значение: " << p5.ipart() << endl;

    cout << "\nПопытка создать объект с нулевым знаменателем (7, 0):" << endl;
    Pair p6 = make_Pair(7, 0);
    p6.display();
    cout << "\nДесятичное значение: " << p6.ipart() << endl;

    cout << "\nПопытка создать объект с отрицательным знаменателем (3, -2):" << endl;
    Pair p7;
    p7.init(3, -2);
    p7.display();
    cout << "\nДесятичное значение: " << p7.ipart() << endl;

    cout << "\n Демонстрация различных случаев " << endl;

    Pair case1 = make_Pair(0, 5);
    cout << "Нулевой числитель: ";
    case1.display();
    cout << "\nЦелая часть: " << static_cast<int>(case1.ipart());
    cout << "\nДесятичное значение: " << case1.ipart() << endl;

    Pair case2 = make_Pair(10, 1);
    cout << "\nЗнаменатель равен 1: ";
    case2.display();
    cout << "\nЦелая часть: " << static_cast<int>(case2.ipart());
    cout << "\nДесятичное значение: " << case2.ipart() << endl;

    Pair case3 = make_Pair(3, 2);
    cout << "\nЧислитель меньше знаменателя: ";
    case3.display();
    cout << "\nЦелая часть: " << static_cast<int>(case3.ipart());
    cout << "\nДесятичное значение: " << case3.ipart() << endl;

    Pair case4 = make_Pair(9, 9);
    cout << "\nЧислитель равен знаменателю: ";
    case4.display();
    cout << "\nЦелая часть: " << static_cast<int>(case4.ipart());
    cout << "\nДесятичное значение: " << case4.ipart() << endl;

    return 0;
}
