#include <iostream>
#include <string>
using namespace std;

class ModelWindow {
private:
    string title;
    int x, y;
    int width, height;
    string color;
    bool isVisible;
    bool hasBorder;
    const int screenWidth = 1920;
    const int screenHeight = 1080;

public:
    ModelWindow();  
    ModelWindow(string t, int xPos, int yPos, int w, int h,
        string col, bool visible, bool border);
    ModelWindow(const ModelWindow& other); 

    void moveHorizontal(int dx);
    void moveVertical(int dy);
    void resize(int newWidth, int newHeight);
    void setColor(string newColor);
    void toggleVisibility();
    void toggleBorder();
    bool isVisibleStatus() const;
    bool hasBorderStatus() const;
    void display() const;
};

ModelWindow::ModelWindow()
    : title("Untitled"), x(0), y(0), width(100), height(100),
    color("white"), isVisible(true), hasBorder(true) {
}

ModelWindow::ModelWindow(string t, int xPos, int yPos, int w, int h,
    string col, bool visible, bool border)
    : title(t), x(xPos), y(yPos), width(w), height(h), color(col),
    isVisible(visible), hasBorder(border) {
}

ModelWindow::ModelWindow(const ModelWindow& other)
    : title(other.title), x(other.x), y(other.y), width(other.width),
    height(other.height), color(other.color), isVisible(other.isVisible),
    hasBorder(other.hasBorder) {
}

void ModelWindow::moveHorizontal(int dx) {
    if (x + dx >= 0 && x + dx + width <= screenWidth) {
        x += dx;
    }
    else {
        cout << "Движение по горизонтали выходит за границы экрана!" << endl;
    }
}

void ModelWindow::moveVertical(int dy) {
    if (y + dy >= 0 && y + dy + height <= screenHeight) {
        y += dy;
    }
    else {
        cout << "Движение по вертикали выходит за границы экрана!" << endl;
    }
}

void ModelWindow::resize(int newWidth, int newHeight) {
    if (newWidth > 0 && newHeight > 0 &&
        x + newWidth <= screenWidth && y + newHeight <= screenHeight) {
        width = newWidth;
        height = newHeight;
    }
    else {
        cout << "Недопустимые размеры окна!" << endl;
    }
}

void ModelWindow::setColor(string newColor) {
    color = newColor;
}

void ModelWindow::toggleVisibility() {
    isVisible = !isVisible;
}

void ModelWindow::toggleBorder() {
    hasBorder = !hasBorder;
}

bool ModelWindow::isVisibleStatus() const {
    return isVisible;
}

bool ModelWindow::hasBorderStatus() const {
    return hasBorder;
}

void ModelWindow::display() const {
    cout << "Окно: " << title << endl;
    cout << "Позиция: (" << x << ", " << y << ")" << endl;
    cout << "Размеры: " << width << "x" << height << endl;
    cout << "Цвет: " << color << endl;
    cout << "Видимость: " << (isVisible ? "да" : "нет") << endl;
    cout << "Рамка: " << (hasBorder ? "да" : "нет") << endl;
    cout << "-----------------------------" << endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    ModelWindow win1;
    ModelWindow win2("Main Window", 100, 150, 400, 300, "blue", true, false);
    ModelWindow win3(win2); 

    cout << "Исходные состояния окон:" << endl;
    win1.display();
    win2.display();
    win3.display();

    win2.moveHorizontal(50);
    win2.moveVertical(-30);
    win2.resize(500, 350);
    win2.setColor("green");
    win2.toggleBorder();
    win2.toggleVisibility();

    cout << "\nПосле изменений в win2:" << endl;
    win2.display();

    cout << "Видимость win2: " << (win2.isVisibleStatus() ? "да" : "нет") << endl;
    cout << "Рамка win2: " << (win2.hasBorderStatus() ? "да" : "нет") << endl;

    return 0;
}
