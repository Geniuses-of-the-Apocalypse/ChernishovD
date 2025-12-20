#include <iostream>
using namespace std;

template<typename T>
T gcd(T a, T b) {
    while (b != 0) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

template<typename T>
T lcm_two(T a, T b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

template<typename T>
T lcm(T a) {
    return a;
}

template<typename T, typename... Args>
T lcm(T first, T second, Args... args) {
    return lcm(lcm_two(first, second), args...);
}

int main() {
    cout << "lcm(2, 3) = " << lcm(2, 3) << endl;                    
    cout << "lcm(4, 6, 8) = " << lcm(4, 6, 8) << endl;             
    cout << "lcm(5, 10, 15) = " << lcm(5, 10, 15) << endl;         

    return 0;
}
