#include <iostream>
#include <string>
using namespace std;

const int MAX_WIDTH = 1920;
const int MAX_HEIGHT = 1080;

class ModelWindow {
private:
    string title;
    int x, y;
    int width, height;
    string color;
    bool isVisible;
    bool hasBorder;

public:
    void init(string t, int xPos, int yPos, int w, int h, string col, bool visible, bool border);
    void read();
    void display() const;
    string toString() const;
    void moveHorizontal(int dx);
    void moveVertical(int dy);
    void resize(int w, int h);
    void changeColor(string newColor);
    void toggleVisibility();
    void toggleBorder();
    bool getVisibility() const;
    bool getBorder() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    string getColor() const;
    string getTitle() const;
};

void ModelWindow::init(string t, int xPos, int yPos, int w, int h, string col, bool visible, bool border) {
    title = t;
    x = xPos;
    y = yPos;
    width = w;
    height = h;
    color = col;
    isVisible = visible;
    hasBorder = border;
}

void ModelWindow::read() {
    cout << "Введите заголовок: ";
    getline(cin, title);
    cout << "Введите координату X: ";
    cin >> x;
    cout << "Введите координату Y: ";
    cin >> y;
    cout << "Введите ширину: ";
    cin >> width;
    cout << "Введите высоту: ";
    cin >> height;
    cout << "Введите цвет: ";
    cin >> color;
    cout << "Видимое (1/0): ";
    cin >> isVisible;
    cout << "С рамкой (1/0): ";
    cin >> hasBorder;
    cin.ignore();
}

void ModelWindow::display() const {
    cout << "Окно: " << title << endl;
    cout << "Позиция: (" << x << ", " << y << ")" << endl;
    cout << "Размеры: " << width << "x" << height << endl;
    cout << "Цвет: " << color << endl;
    cout << "Видимое: " << (isVisible ? "Да" : "Нет") << endl;
    cout << "Рамка: " << (hasBorder ? "Да" : "Нет") << endl;
}

string ModelWindow::toString() const {
    string info = "Окно: " + title + "\n";
    info += "Позиция: (" + to_string(x) + ", " + to_string(y) + ")\n";
    info += "Размер: " + to_string(width) + "x" + to_string(height) + "\n";
    info += "Цвет: " + color + "\n";
    info += "Видимое: " + string(isVisible ? "Да" : "Нет") + "\n";
    info += "Рамка: " + string(hasBorder ? "Да" : "Нет") + "\n";
    return info;
}

void ModelWindow::moveHorizontal(int dx) {
    if (x + dx >= 0 && x + dx + width <= MAX_WIDTH) {
        x += dx;
    }
    else {
        cout << "Выход за границы экрана по горизонтали!" << endl;
    }
}

void ModelWindow::moveVertical(int dy) {
    if (y + dy >= 0 && y + dy + height <= MAX_HEIGHT) {
        y += dy;
    }
    else {
        cout << "Выход за границы экрана по вертикали!" << endl;
    }
}

void ModelWindow::resize(int w, int h) {
    if (w > 0 && h > 0 && x + w <= MAX_WIDTH && y + h <= MAX_HEIGHT) {
        width = w;
        height = h;
    }
    else {
        cout << "Недопустимый размер!" << endl;
    }
}

void ModelWindow::changeColor(string newColor) {
    color = newColor;
}

void ModelWindow::toggleVisibility() {
    isVisible = !isVisible;
}

void ModelWindow::toggleBorder() {
    hasBorder = !hasBorder;
}

bool ModelWindow::getVisibility() const {
    return isVisible;
}

bool ModelWindow::getBorder() const {
    return hasBorder;
}

int ModelWindow::getX() const {
    return x;
}

int ModelWindow::getY() const {
    return y;
}

int ModelWindow::getWidth() const {
    return width;
}

int ModelWindow::getHeight() const {
    return height;
}

string ModelWindow::getColor() const {
    return color;
}

string ModelWindow::getTitle() const {
    return title;
}

int main() {
    setlocale(LC_ALL, "Russian");
    ModelWindow window;
    window.init("Моё окно", 100, 100, 400, 300, "синий", true, true);
    window.display();

    cout << "\n Перемещение окна \n";
    window.moveHorizontal(50);
    window.moveVertical(-20);
    window.display();

    cout << "\n Изменение размера \n";
    window.resize(500, 400);
    window.display();

    cout << "\n Изменение цвета \n";
    window.changeColor("красный");
    window.display();

    cout << "\n Переключение видимости \n";
    window.toggleVisibility();
    window.display();

    cout << "\n Переключение рамки \n";
    window.toggleBorder();
    window.display();

    cout << "\n В строковом виде \n";
    cout << window.toString();

    return 0;
}
