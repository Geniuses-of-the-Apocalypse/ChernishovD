#include <iostream>
#include <string>

using namespace std;


class ModelWindow {
private:
    string title;      
    int x, y;         
    int width, height; 
    string color;      
    bool visible;     
    bool framed;       
    bool isWithinScreen(int newX, int newY, int newWidth, int newHeight) const;

public:
    ModelWindow(); 
    ModelWindow(string t, int posX, int posY, int w, int h, string c, bool v, bool f); 
    ModelWindow(const ModelWindow& other); 

    void moveHorizontal(int dx); 
    void moveVertical(int dy);   
    void resize(int newWidth, int newHeight); 
    void changeColor(const string& newColor); 
    void toggleVisibility(); 
    void toggleFrame();      


    bool isVisible() const;
    bool hasFrame() const;
    string getColor() const;
    string getTitle() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;


    ModelWindow operator+(const ModelWindow& other) const; 
    bool operator==(const ModelWindow& other) const; 
    bool operator!=(const ModelWindow& other) const; 


    friend ostream& operator<<(ostream& os, const ModelWindow& win);
    friend istream& operator>>(istream& is, ModelWindow& win);
};



bool ModelWindow::isWithinScreen(int newX, int newY, int newWidth, int newHeight) const {
    const int screenWidth = 1920;   
    const int screenHeight = 1080;  
    return newX >= 0 && newY >= 0 &&
        (newX + newWidth) <= screenWidth &&
        (newY + newHeight) <= screenHeight;
}


ModelWindow::ModelWindow()
    : title("Untitled"), x(0), y(0), width(100), height(100),
    color("white"), visible(true), framed(true) {
}

// Конструктор
ModelWindow::ModelWindow(string t, int posX, int posY, int w, int h,
    string c, bool v, bool f)
    : title(t), x(posX), y(posY), width(w), height(h),
    color(c), visible(v), framed(f) {
    if (!isWithinScreen(x, y, width, height)) {
        cout << "Окно выходит за границы экрана! Сброс до стандартных значений.\n";
        x = 0; y = 0; width = 100; height = 100;
    }
}

// Конструктор копирования
ModelWindow::ModelWindow(const ModelWindow& other)
    : title(other.title), x(other.x), y(other.y),
    width(other.width), height(other.height),
    color(other.color), visible(other.visible),
    framed(other.framed) {
}


void ModelWindow::moveHorizontal(int dx) {
    if (isWithinScreen(x + dx, y, width, height)) {
        x += dx;
    }
    else {
        cout << "Невозможно сдвинуть по горизонтали: выход за границы.\n";
    }
}


void ModelWindow::moveVertical(int dy) {
    if (isWithinScreen(x, y + dy, width, height)) {
        y += dy;
    }
    else {
        cout << "Невозможно сдвинуть по вертикали: выход за границы.\n";
    }
}

void ModelWindow::resize(int newWidth, int newHeight) {
    if (isWithinScreen(x, y, newWidth, newHeight)) {
        width = newWidth;
        height = newHeight;
    }
    else {
        cout << "Невозможно изменить размер: выход за границы.\n";
    }
}

// Изменение цвета окна
void ModelWindow::changeColor(const string& newColor) {
    color = newColor;
}

// Переключение видимости окна
void ModelWindow::toggleVisibility() {
    visible = !visible;
}

// Переключение рамки окна
void ModelWindow::toggleFrame() {
    framed = !framed;
}

// Геттеры
bool ModelWindow::isVisible() const { return visible; }
bool ModelWindow::hasFrame() const { return framed; }
string ModelWindow::getColor() const { return color; }
string ModelWindow::getTitle() const { return title; }
int ModelWindow::getX() const { return x; }
int ModelWindow::getY() const { return y; }
int ModelWindow::getWidth() const { return width; }
int ModelWindow::getHeight() const { return height; }

// Объединение окон
ModelWindow ModelWindow::operator+(const ModelWindow& other) const {
    int newX = (x + other.x) / 2;                   
    int newY = (y + other.y) / 2;                    
    int newWidth = width + other.width;             
    int newHeight = height + other.height;           
    string newColor = (color == other.color) ? color : "mixed"; 
    bool newVisible = visible && other.visible;      
    bool newFramed = framed && other.framed;        
    string newTitle = title + "+" + other.title;    

    return ModelWindow(newTitle, newX, newY, newWidth, newHeight, newColor, newVisible, newFramed);
}

// Оператор сравнения на равенство
bool ModelWindow::operator==(const ModelWindow& other) const {
    return (x == other.x && y == other.y &&
        width == other.width && height == other.height &&
        color == other.color && visible == other.visible &&
        framed == other.framed && title == other.title);
}

// Сравнение
bool ModelWindow::operator!=(const ModelWindow& other) const {
    return !(*this == other);
}

// Вывода 
ostream& operator<<(ostream& os, const ModelWindow& win) {
    os << "Окно: \"" << win.title << "\"\n";
    os << "Позиция: (" << win.x << ", " << win.y << ")\n";
    os << "Размер: " << win.width << "x" << win.height << "\n";
    os << "Цвет: " << win.color << "\n";
    os << "Видимость: " << (win.visible ? "видимое" : "невидимое") << "\n";
    os << "Рамка: " << (win.framed ? "с рамкой" : "без рамки") << "\n";
    return os;
}

// Ввод 
istream& operator>>(istream& is, ModelWindow& win) {
    cout << "Введите заголовок: ";
    getline(is, win.title);
    cout << "Введите x, y: ";
    is >> win.x >> win.y;
    cout << "Введите ширину и высоту: ";
    is >> win.width >> win.height;
    cout << "Введите цвет: ";
    is >> win.color;
    cout << "Видимость (1/0): ";
    is >> win.visible;
    cout << "Рамка (1/0): ";
    is >> win.framed;
    return is;
}

int main() {
    setlocale(LC_ALL, "Russian"); 

    ModelWindow win1("Main", 100, 100, 300, 200, "blue", true, true);
    ModelWindow win2("Dialog", 200, 200, 150, 150, "green", true, false);

    ModelWindow win3 = win1 + win2;

    cout << win1 << endl;
    cout << win2 << endl;
    cout << "Результат сложения окон:\n" << win3 << endl;

    cout << "win1 == win2? " << (win1 == win2 ? "да" : "нет") << endl;
    cout << "win1 != win2? " << (win1 != win2 ? "да" : "нет") << endl;

    win1.moveHorizontal(50);      
    win2.toggleVisibility();      
    win3.changeColor("red");     

    cout << "\nПосле изменений:\n";
    cout << win1 << endl;
    cout << win2 << endl;
    cout << win3 << endl;

    ModelWindow win4;
    cout << "\nВведите данные для нового окна:\n";
    cin.ignore();
    cin >> win4;
    cout << "\nСозданное окно:\n" << win4 << endl;

    return 0;
}
