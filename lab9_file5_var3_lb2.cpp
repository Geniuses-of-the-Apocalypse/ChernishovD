#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
class Triplet {
private:
    T elements[3];

public:
    Triplet();
    Triplet(const T& a, const T& b, const T& c);

    T& operator[](int index);
    const T& operator[](int index) const;

    void rotate();
    string toString() const;
    void clear();

    friend ostream& operator<<(ostream& out, const Triplet& t);
    friend istream& operator>>(istream& in, Triplet& t);
};

template<typename T>
Triplet<T>::Triplet() : elements{} {}

template<typename T>
Triplet<T>::Triplet(const T& a, const T& b, const T& c) {
    elements[0] = a;
    elements[1] = b;
    elements[2] = c;
}

template<typename T>
T& Triplet<T>::operator[](int index) {
    return elements[index];
}

template<typename T>
const T& Triplet<T>::operator[](int index) const {
    return elements[index];
}

template<typename T>
void Triplet<T>::rotate() {
    T temp = elements[2];
    elements[2] = elements[1];
    elements[1] = elements[0];
    elements[0] = temp;
}

template<typename T>
string Triplet<T>::toString() const {
    stringstream ss;
    ss << "(" << elements[0] << ", " << elements[1] << ", " << elements[2] << ")";
    return ss.str();
}

template<typename T>
void Triplet<T>::clear() {
    elements[0] = T{};
    elements[1] = T{};
    elements[2] = T{};
}

template<typename T>
ostream& operator<<(ostream& out, const Triplet<T>& t) {
    out << t.toString();
    return out;
}

template<typename T>
istream& operator>>(istream& in, Triplet<T>& t) {
    cout << "Введите три элемента: ";
    in >> t.elements[0] >> t.elements[1] >> t.elements[2];
    return in;
}

int main() {
    setlocale(LC_ALL, "ru");

    Triplet<int> t1(1, 2, 3);
    cout << "Исходный триплет: " << t1 << endl;

    t1.rotate();
    cout << "После rotate(): " << t1 << endl;

    t1[1] = 99;
    cout << "После изменения элемента [1]: " << t1 << endl;

    Triplet<double> t2;
    cout << "\nВведите значения для триплета double:" << endl;
    cin >> t2;
    cout << "Введённый триплет: " << t2 << endl;

    t2.clear();
    cout << "После clear(): " << t2 << endl;

    return 0;
}
