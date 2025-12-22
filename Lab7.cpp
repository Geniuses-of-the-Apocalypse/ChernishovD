#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;


class TriangleExceptionEmpty {};
class TriangleExceptionWithData {
public:
    double side1, side2, side3;
    string message;

    TriangleExceptionWithData(double s1, double s2, double s3, const string& msg)
        : side1(s1), side2(s2), side3(s3), message(msg) {
    }
};

// Расширяет стандартное исключение
class TriangleExceptionStd : public exception {
private:
    double side1_, side2_, side3_;
    string message_;
    mutable string what_buffer_;

public:
    TriangleExceptionStd(double s1, double s2, double s3, const string& msg)
        : side1_(s1), side2_(s2), side3_(s3), message_(msg) {
    }

    // What() для вывода пользовательского сообщения
    const char* what() const noexcept override {
        what_buffer_ = "Исключение треугольника: " + message_ +
            " (стороны: " + to_string(side1_) + ", " +
            to_string(side2_) + ", " +
            to_string(side3_) + ")";
        return what_buffer_.c_str();
    }

    double getSide1() const { return side1_; }
    double getSide2() const { return side2_; }
    double getSide3() const { return side3_; }
};


bool isValidTriangle(double a, double b, double c) {
    return (a > 0 && b > 0 && c > 0) &&
        (a + b > c) &&
        (a + c > b) &&
        (b + c > a);
}

//Без спецификации исключений
double trianglePerimeterV1(double a, double b, double c) {
    if (!isValidTriangle(a, b, c)) {
        throw invalid_argument("Некорректные стороны треугольника");
    }
    return a + b + c;
}

// Со спецификацией throw()

double trianglePerimeterV2(double a, double b, double c) throw() {
    if (!isValidTriangle(a, b, c)) {
        throw invalid_argument("Некорректные стороны треугольника");
    }
    return a + b + c;
}

//С конкретной спецификацией
double trianglePerimeterV3(double a, double b, double c)
throw(invalid_argument, overflow_error) {

    if (!isValidTriangle(a, b, c)) {
        throw invalid_argument("Некорректные стороны треугольника");
    }
    // Дополнительная проверка на переполнение при вычислении суммы
    if (a > numeric_limits<double>::max() - b ||
        (a + b) > numeric_limits<double>::max() - c) {
        throw overflow_error("Переполнение при вычислении периметра");
    }

    return a + b + c;
}

// С собственным исключением

double trianglePerimeterV4a(double a, double b, double c) throw(TriangleExceptionEmpty) {
    if (!isValidTriangle(a, b, c)) {
        throw TriangleExceptionEmpty();
    }
    return a + b + c;
}

// С независимым классом с полями

double trianglePerimeterV4b(double a, double b, double c) throw(TriangleExceptionWithData) {
    if (!isValidTriangle(a, b, c)) {
        throw TriangleExceptionWithData(a, b, c, "Некорректные стороны треугольника");
    }
    return a + b + c;
}

// С наследником от std::exception

double trianglePerimeterV4c(double a, double b, double c) throw(TriangleExceptionStd) {
    if (!isValidTriangle(a, b, c)) {
        throw TriangleExceptionStd(a, b, c, "Некорректные стороны треугольника");
    }
    return a + b + c;
}


void demonstrateAllVariants() {
    struct TestCase {
        double a, b, c;                 
        bool shouldSucceed;          
        string description;            
    };

    TestCase testCases[] = {
        {3.0, 4.0, 5.0, true, "Правильный прямоугольный треугольник"},
        {1.0, 1.0, 3.0, false, "Некорректный треугольник (1, 1, 3)"},
        {-1.0, 2.0, 3.0, false, "Отрицательная сторона"},
        {0.0, 2.0, 3.0, false, "Нулевая сторона"},
        {1e308, 1e308, 1e308, false, "Возможное переполнение"},
        {5.0, 5.0, 5.0, true, "Правильный равносторонний треугольник"},
        {2.0, 3.0, 4.0, true, "Произвольный треугольник"}
    };

    cout << "ДЕМОНСТРАЦИЯ \n\n";
    cout << "В этом демо показываются 4 варианта реализации функции с разными спецификациями исключений:\n";
    cout << "1. Без спецификации исключений\n";
    cout << "2. Со спецификацией throw()\n";
    cout << "3. С конкретной спецификацией исключений\n";
    cout << "4. С пользовательскими исключениями (3 подварианта)\n\n";

    for (const auto& test : testCases) {
        cout << "\nТЕСТ: " << test.description
            << "\nСтороны: " << test.a << ", " << test.b << ", " << test.c << "\n";
        cout << string(60, '=') << "\n";

        cout << "\nБез спецификации исключений \n";
        try {
            double result = trianglePerimeterV1(test.a, test.b, test.c);
            cout << " Успех! Периметр = " << result << "\n";
        }
        catch (const invalid_argument& e) {
            cout << " Исключение invalid_argument: " << e.what() << "\n";
        }
        catch (...) {
            cout << " Неизвестное исключение\n";
        }


        cout << "\nСо спецификацией throw()\n";
        try {
            double result = trianglePerimeterV2(test.a, test.b, test.c);
            cout << " Успех! Периметр = " << result << "\n";
        }
        catch (const invalid_argument& e) {
            cout << " Исключение invalid_argument: " << e.what() << "\n";
        }
        catch (...) {
            cout << " Неизвестное исключение\n";
        }

        cout << "\nС конкретной спецификацией \n";
        try {
            double result = trianglePerimeterV3(test.a, test.b, test.c);
            cout << " Успех! Периметр = " << result << "\n";
        }
        catch (const invalid_argument& e) {
            cout << " Исключение invalid_argument: " << e.what() << "\n";
        }
        catch (const overflow_error& e) {
            cout << " Исключение overflow_error: " << e.what() << "\n";
        }
        catch (...) {
            cout << " Неизвестное исключение\n";
        }

        cout << "\nС пустым классом исключения \n";
        try {
            double result = trianglePerimeterV4a(test.a, test.b, test.c);
            cout << " Успех! Периметр = " << result << "\n";
        }
        catch (const TriangleExceptionEmpty&) {
            cout << " Исключение TriangleExceptionEmpty: пустое пользовательское исключение\n";
        }
        catch (...) {
            cout << " Неизвестное исключение\n";
        }

        cout << "\nС независимым классом с полями\n";
        try {
            double result = trianglePerimeterV4b(test.a, test.b, test.c);
            cout << " Успех! Периметр = " << result << "\n";
        }
        catch (const TriangleExceptionWithData& e) {
            cout << " Исключение TriangleExceptionWithData:\n";
            cout << "  Сообщение: " << e.message << "\n";
            cout << "  Стороны треугольника: " << e.side1 << ", " << e.side2 << ", " << e.side3 << "\n";
        }
        catch (...) {
            cout << " Неизвестное исключение\n";
        }

        cout << "\nС наследником от std::exception \n";
        try {
            double result = trianglePerimeterV4c(test.a, test.b, test.c);
            cout << " Успех! Периметр = " << result << "\n";
        }
        catch (const TriangleExceptionStd& e) {
            cout << " Исключение TriangleExceptionStd: " << e.what() << "\n";
        }
        catch (...) {
            cout << " Неизвестное исключение\n";
        }

        cout << "\n" << string(60, '-') << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    try {
        demonstrateAllVariants();
    }
    catch (const exception& e) {
        cerr << "\n!!! КРИТИЧЕСКАЯ ОШИБКА в main: " << e.what() << " !!!\n";
        cerr << "Программа завершена с ошибкой.\n";
        return 1;
    }

    catch (...) {
        cerr << "\n!!! НЕИЗВЕСТНАЯ КРИТИЧЕСКАЯ ОШИБКА в main !!!\n";
        cerr << "Программа завершена с неизвестной ошибкой.\n";
        return 1;
    }

    cout << "\nПрограмма успешно завершена.\n";
    return 0;
}
