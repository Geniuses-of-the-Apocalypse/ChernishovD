#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

using namespace std;

class EmptyTriangleException {};

class TriangleException {
private:
    string message;
    double a_val, b_val, c_val;
public:
    TriangleException(const string& msg, double a, double b, double c)
        : message(msg), a_val(a), b_val(b), c_val(c) {
    }

    string getMessage() const { return message; }
    double getA() const { return a_val; }
    double getB() const { return b_val; }
    double getC() const { return c_val; }
};

class TriangleMathException : public runtime_error {
private:
    double a_val, b_val, c_val;
public:
    TriangleMathException(const string& msg, double a, double b, double c)
        : runtime_error(msg), a_val(a), b_val(b), c_val(c) {
    }

    double getA() const { return a_val; }
    double getB() const { return b_val; }
    double getC() const { return c_val; }
};

bool isValidTriangle(double a, double b, double c) {
    return (a > 0 && b > 0 && c > 0) &&
        (a + b > c) && (a + c > b) && (b + c > a);
}

double trianglePerimeter1(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw invalid_argument("Стороны треугольника должны быть положительными числами");
    }

    if (!isValidTriangle(a, b, c)) {
        throw domain_error("Треугольник с такими сторонами не существует: "
            "a=" + to_string(a) +
            ", b=" + to_string(b) +
            ", c=" + to_string(c));
    }

    return a + b + c;
}

double trianglePerimeter2(double a, double b, double c) throw() {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw invalid_argument("Стороны треугольника должны быть положительными числами");
    }

    if (!isValidTriangle(a, b, c)) {
        throw domain_error("Треугольник не существует");
    }

    return a + b + c;
}

double trianglePerimeter3(double a, double b, double c) throw(invalid_argument, domain_error) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw invalid_argument("Стороны треугольника должны быть положительными числами");
    }

    if (!isValidTriangle(a, b, c)) {
        throw domain_error("Треугольник с такими сторонами не существует");
    }

    return a + b + c;
}

double trianglePerimeter4(double a, double b, double c) throw(EmptyTriangleException, TriangleException, TriangleMathException) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw TriangleException("Сторона треугольника должна быть положительным числом", a, b, c);
    }

    if (a + b <= c) {
        throw TriangleException("Не выполняется неравенство треугольника: a + b <= c", a, b, c);
    }
    if (a + c <= b) {
        throw TriangleException("Не выполняется неравенство треугольника: a + c <= b", a, b, c);
    }
    if (b + c <= a) {
        throw TriangleException("Не выполняется неравенство треугольника: b + c <= a", a, b, c);
    }

    if (a > 1e100 || b > 1e100 || c > 1e100) {
        throw TriangleMathException("Возможное переполнение при вычислении", a, b, c);
    }

    if (a == b && b == c && a == 1.0) {
        throw EmptyTriangleException();  
    }

    return a + b + c;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа 1: Исключения" << endl;
    cout << "Вычисление периметра треугольника по трем сторонам" << endl << endl;

    double test_cases[][3] = {
        {3, 4, 5},
        {5, 5, 5},     
        {2, 2, 3},    
        {1, 1, 1},   
        {0, 4, 5},   
        {-1, 2, 3},    
        {1, 2, 10},    
        {1, 10, 2},   
        {10, 1, 2},     
        {1e150, 2, 3}  
    };

    const char* descriptions[] = {
        "Треугольник 3-4-5",
        "Равносторонний треугольник 5-5-5",
        "Равнобедренный треугольник 2-2-3",
        "Равносторонний треугольник 1-1-1",
        "Треугольник с нулевой стороной",
        "Треугольник с отрицательной стороной",
        "Не треугольник: 1-2-10",
        "Не треугольник: 1-10-2",
        "Не треугольник: 10-1-2",
        "Треугольник с очень большой стороной"
    };

    for (int variant = 1; variant <= 4; variant++) {
        cout << " Вариант " << variant << endl;

        for (int i = 0; i < 10; i++) {
            double a = test_cases[i][0];
            double b = test_cases[i][1];
            double c = test_cases[i][2];

            cout << "Треугольник: " << descriptions[i] << " ("
                << a << ", " << b << ", " << c << ") -> ";

            try {
                double result;

                switch (variant) {
                case 1:
                    result = trianglePerimeter1(a, b, c);
                    break;
                case 2:
                    result = trianglePerimeter2(a, b, c);
                    break;
                case 3:
                    result = trianglePerimeter3(a, b, c);
                    break;
                case 4:
                    result = trianglePerimeter4(a, b, c);
                    break;
                default:
                    result = 0;
                }

                cout << "P = " << result;

            }
            catch (const invalid_argument& e) {
                cout << "Ошибка (invalid_argument): " << e.what();
            }
            catch (const domain_error& e) {
                cout << "Ошибка (domain_error): " << e.what();
            }
            catch (const runtime_error& e) {
                cout << "Ошибка (runtime_error): " << e.what();
            }
            catch (const EmptyTriangleException&) {
                cout << "Ошибка (EmptyTriangleException): Особый случай равностороннего треугольника";
            }
            catch (const TriangleException& e) {
                cout << "Ошибка (TriangleException): " << e.getMessage()
                    << " (a=" << e.getA() << ", b=" << e.getB() << ", c=" << e.getC() << ")";
            }
            catch (const TriangleMathException& e) {
                cout << "Ошибка (TriangleMathException): " << e.what()
                    << " (a=" << e.getA() << ", b=" << e.getB() << ", c=" << e.getC() << ")";
            }
            catch (...) {
                cout << "Неизвестная ошибка";
            }

            cout << endl;
        }
        cout << endl;
    }

    cout << " Пример успешного вычисления " << endl;
    try {
        double p = trianglePerimeter4(7, 8, 9);
        cout << "Периметр треугольника со сторонами 7, 8, 9: " << p << endl;
        double s = (7 + 8 + 9) / 2.0;
        double area = sqrt(s * (s - 7) * (s - 8) * (s - 9));
        cout << "Площадь (по формуле Герона): " << area << endl;
    }
    catch (...) {
        cout << "Ошибка при вычислении" << endl;
    }

    return 0;
}
