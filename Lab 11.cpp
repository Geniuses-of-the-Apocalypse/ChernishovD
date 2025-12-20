#include <iostream>
#include <concepts>
using namespace std;

template<typename T>
concept Arithmetic = integral<T>;

template <Arithmetic T>
constexpr auto nod = [](T a, T b) constexpr
    {
        if (a < 0) a = -a;
        if (b < 0) b = -b;

        while (b != 0) {
            T temp = b;
            b = a % b;
            a = temp;
        }

        return a;
    };

template <Arithmetic T>
constexpr auto nok = [](T a, T b) constexpr
    {
        if (a == 0 && b == 0) {
            return static_cast<T>(0);
        }

        if (a < 0) a = -a;
        if (b < 0) b = -b;
        T gcd = nod<T>(a, b);

        if (gcd == 0) {
            return static_cast<T>(0);
        }

        if (a / gcd > numeric_limits<T>::max() / b) {
            return static_cast<T>(0);
        }

        return (a / gcd) * b;
    };

int main() {
    setlocale(LC_ALL, "RU");

  
    constexpr auto result1 = nod<int>(48, 18);   
    constexpr auto result2 = nod<int>(17, 13);    
    constexpr auto result3 = nod<int>(-36, 48);    
    int result4 = nod<int>(35, 15);              

    constexpr auto lcm1 = nok<int>(48, 18);       
    constexpr auto lcm2 = nok<int>(17, 13);       
    constexpr auto lcm3 = nok<int>(-36, 48);     
    constexpr auto lcm4 = nok<int>(35, 15);       
    constexpr auto lcm5 = nok<int>(12, 18);       
    constexpr auto lcm6 = nok<int>(0, 5);       
    constexpr auto lcm7 = nok<int>(0, 0);       
    int lcm8 = nok<int>(21, 6);                  

    cout << "Результаты НОД:" << endl;
    cout << "НОД(48, 18) = " << result1 << endl;
    cout << "НОД(17, 13) = " << result2 << endl;
    cout << "НОД(-36, 48) = " << result3 << endl;
    cout << "НОД(35, 15) = " << result4 << endl;

    cout << "\nРезультаты НОК:" << endl;
    cout << "НОК(48, 18) = " << lcm1 << endl;
    cout << "НОК(17, 13) = " << lcm2 << endl;
    cout << "НОК(-36, 48) = " << lcm3 << endl;
    cout << "НОК(35, 15) = " << lcm4 << endl;
    cout << "НОК(12, 18) = " << lcm5 << endl;
    cout << "НОК(0, 5) = " << lcm6 << endl;
    cout << "НОК(0, 0) = " << lcm7 << endl;
    cout << "НОК(21, 6) = " << lcm8 << endl;

    constexpr auto lcm_long = nok<long>(123456, 7890);
    cout << "\nНОК(123456, 7890) [long] = " << lcm_long << endl;

    return 0;
}
