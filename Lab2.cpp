#include <iostream>
#include <string>

using namespace std;

// СПОСОБ 1

struct ModelWindow {
    string title;
    int x, y;               
    int width, height;      
    string color;
    bool isVisible;
    bool hasBorder;
};

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

void init(ModelWindow& window,
    const string& title = "Window",
    int x = 0, int y = 0,
    int width = 100, int height = 100,
    const string& color = "white",
    bool isVisible = true,
    bool hasBorder = true) {
    window.title = title;
    window.x = (x >= 0 && x < SCREEN_WIDTH) ? x : 0;
    window.y = (y >= 0 && y < SCREEN_HEIGHT) ? y : 0;
    window.width = (width > 0 && width <= SCREEN_WIDTH) ? width : 100;
    window.height = (height > 0 && height <= SCREEN_HEIGHT) ? height : 100;
    window.color = color;
    window.isVisible = isVisible;
    window.hasBorder = hasBorder;
}

// Ввод с клавиатуры
void read(ModelWindow& window) {
    cout << "Введите заголовок окна: ";
    getline(cin, window.title);

    cout << "Введите координату X (0-" << SCREEN_WIDTH - 1 << "): ";
    cin >> window.x;
    if (window.x < 0) window.x = 0;
    if (window.x >= SCREEN_WIDTH) window.x = SCREEN_WIDTH - 1;

    cout << "Введите координату Y (0-" << SCREEN_HEIGHT - 1 << "): ";
    cin >> window.y;
    if (window.y < 0) window.y = 0;
    if (window.y >= SCREEN_HEIGHT) window.y = SCREEN_HEIGHT - 1;

    cout << "Введите ширину окна (1-" << SCREEN_WIDTH << "): ";
    cin >> window.width;
    if (window.width <= 0) window.width = 1;
    if (window.width > SCREEN_WIDTH) window.width = SCREEN_WIDTH;

    cout << "Введите высоту окна (1-" << SCREEN_HEIGHT << "): ";
    cin >> window.height;
    if (window.height <= 0) window.height = 1;
    if (window.height > SCREEN_HEIGHT) window.height = SCREEN_HEIGHT;

    cout << "Введите цвет окна: ";
    cin.ignore();
    getline(cin, window.color);

    cout << "Видимое окно? (1 - да, 0 - нет): ";
    cin >> window.isVisible;

    cout << "Есть рамка? (1 - да, 0 - нет): ";
    cin >> window.hasBorder;
}

// Вывод на экран
void display(const ModelWindow& window) {
    cout << "\n=== Состояние окна ===" << endl;
    cout << "Заголовок: " << window.title << endl;
    cout << "Координаты: (" << window.x << ", " << window.y << ")" << endl;
    cout << "Размеры: " << window.width << "x" << window.height << endl;
    cout << "Цвет: " << window.color << endl;
    cout << "Видимость: " << (window.isVisible ? "видимое" : "невидимое") << endl;
    cout << "Рамка: " << (window.hasBorder ? "с рамкой" : "без рамки") << endl;

    // Проверка видимости окна на экране
    bool isOnScreen = (window.x + window.width <= SCREEN_WIDTH &&
        window.y + window.height <= SCREEN_HEIGHT);
    cout << "Окно в пределах экрана: " << (isOnScreen ? "да" : "нет") << endl;
    cout << "========================\n" << endl;
}

// Преобразование в строку
string toString(const ModelWindow& window) {
    string result = "Window '" + window.title + "'";
    result += " at (" + to_string(window.x) + "," + to_string(window.y) + ")";
    result += " size " + to_string(window.width) + "x" + to_string(window.height);
    result += " color: " + window.color;
    result += " " + string(window.isVisible ? "visible" : "invisible");
    result += " " + string(window.hasBorder ? "with border" : "borderless");
    return result;
}

void moveHorizontal(ModelWindow& window, int dx) {
    int newX = window.x + dx;
    if (newX >= 0 && newX + window.width <= SCREEN_WIDTH) {
        window.x = newX;
        cout << "Окно перемещено по горизонтали на " << dx << " пикселей" << endl;
    }
    else {
        cout << "Невозможно переместить окно: выходит за границы экрана" << endl;
    }
}

void moveVertical(ModelWindow& window, int dy) {
    int newY = window.y + dy;
    if (newY >= 0 && newY + window.height <= SCREEN_HEIGHT) {
        window.y = newY;
        cout << "Окно перемещено по вертикали на " << dy << " пикселей" << endl;
    }
    else {
        cout << "Невозможно переместить окно: выходит за границы экрана" << endl;
    }
}

void changeWidth(ModelWindow& window, int newWidth) {
    if (newWidth > 0 && window.x + newWidth <= SCREEN_WIDTH) {
        window.width = newWidth;
        cout << "Ширина изменена на " << newWidth << " пикселей" << endl;
    }
    else {
        cout << "Невозможно изменить ширину: недопустимое значение или выход за границы" << endl;
    }
}

void changeHeight(ModelWindow& window, int newHeight) {
    if (newHeight > 0 && window.y + newHeight <= SCREEN_HEIGHT) {
        window.height = newHeight;
        cout << "Высота изменена на " << newHeight << " пикселей" << endl;
    }
    else {
        cout << "Невозможно изменить высоту: недопустимое значение или выход за границы" << endl;
    }
}

void changeColor(ModelWindow& window, const string& newColor) {
    window.color = newColor;
    cout << "Цвет изменен на: " << newColor << endl;
}

void setVisibility(ModelWindow& window, bool visible) {
    window.isVisible = visible;
    cout << "Видимость изменена: " << (visible ? "видимое" : "невидимое") << endl;
}

void setBorder(ModelWindow& window, bool border) {
    window.hasBorder = border;
    cout << "Состояние рамки изменено: " << (border ? "с рамкой" : "без рамки") << endl;
}

bool isVisible(const ModelWindow& window) {
    return window.isVisible;
}

bool hasBorder(const ModelWindow& window) {
    return window.hasBorder;
}

void demoStructVersion() {
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ СТРУКТУРЫ ===" << endl;

    ModelWindow win1;
    init(win1, "Мое окно", 100, 150, 300, 200, "синий", true, true);
    display(win1);

    moveHorizontal(win1, 50);
    moveVertical(win1, -30);
    changeWidth(win1, 400);
    changeColor(win1, "красный");
    setVisibility(win1, false);

    display(win1);
    cout << "Строковое представление: " << toString(win1) << endl;
}

//  СПОСОБ 2

class ModelWindowClass {
private:
    string title;
    int x, y;
    int width, height;
    string color;
    bool visible;
    bool border;

    static const int SCREEN_WIDTH = 1920;
    static const int SCREEN_HEIGHT = 1080;

public:
    
    ModelWindowClass(const string& title = "Window",
        int x = 0, int y = 0,
        int width = 100, int height = 100,
        const string& color = "white",
        bool visible = true,
        bool border = true);
    void read();
    void display() const;
    string toString() const;
    void moveHorizontal(int dx);
    void moveVertical(int dy);
    void changeWidth(int newWidth);
    void changeHeight(int newHeight);
    void changeColor(const string& newColor);
    void setVisibility(bool isVisible);
    void setBorder(bool hasBorder);
    bool isVisible() const;
    bool hasBorder() const;
    string getTitle() const { return title; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    string getColor() const { return color; }

    // Статический метод для получения размеров экрана
    static pair<int, int> getScreenSize() {
        return make_pair(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
};



// Конструктор
ModelWindowClass::ModelWindowClass(const string& title,
    int x, int y,
    int width, int height,
    const string& color,
    bool visible,
    bool border) {
    this->title = title;
    this->x = (x >= 0 && x < SCREEN_WIDTH) ? x : 0;
    this->y = (y >= 0 && y < SCREEN_HEIGHT) ? y : 0;
    this->width = (width > 0 && width <= SCREEN_WIDTH) ? width : 100;
    this->height = (height > 0 && height <= SCREEN_HEIGHT) ? height : 100;
    this->color = color;
    this->visible = visible;
    this->border = border;
}

// Ввод с клавиатуры
void ModelWindowClass::read() {
    cout << "Введите заголовок окна: ";
    getline(cin, title);

    cout << "Введите координату X (0-" << SCREEN_WIDTH - 1 << "): ";
    cin >> x;
    if (x < 0) x = 0;
    if (x >= SCREEN_WIDTH) x = SCREEN_WIDTH - 1;

    cout << "Введите координату Y (0-" << SCREEN_HEIGHT - 1 << "): ";
    cin >> y;
    if (y < 0) y = 0;
    if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;

    cout << "Введите ширину окна (1-" << SCREEN_WIDTH << "): ";
    cin >> width;
    if (width <= 0) width = 1;
    if (width > SCREEN_WIDTH) width = SCREEN_WIDTH;

    cout << "Введите высоту окна (1-" << SCREEN_HEIGHT << "): ";
    cin >> height;
    if (height <= 0) height = 1;
    if (height > SCREEN_HEIGHT) height = SCREEN_HEIGHT;

    cout << "Введите цвет окна: ";
    cin.ignore();
    getline(cin, color);

    cout << "Видимое окно? (1 - да, 0 - нет): ";
    cin >> visible;

    cout << "Есть рамка? (1 - да, 0 - нет): ";
    cin >> border;
    cin.ignore(); 
}

// Вывод на экран
void ModelWindowClass::display() const {
    cout << "\n=== Состояние окна (класс) ===" << endl;
    cout << "Заголовок: " << title << endl;
    cout << "Координаты: (" << x << ", " << y << ")" << endl;
    cout << "Размеры: " << width << "x" << height << endl;
    cout << "Цвет: " << color << endl;
    cout << "Видимость: " << (visible ? "видимое" : "невидимое") << endl;
    cout << "Рамка: " << (border ? "с рамкой" : "без рамки") << endl;

    bool isOnScreen = (x + width <= SCREEN_WIDTH && y + height <= SCREEN_HEIGHT);
    cout << "Окно в пределах экрана: " << (isOnScreen ? "да" : "нет") << endl;
    cout << "==============================\n" << endl;
}

// Преобразование в строку
string ModelWindowClass::toString() const {
    string result = "Window '" + title + "'";
    result += " at (" + to_string(x) + "," + to_string(y) + ")";
    result += " size " + to_string(width) + "x" + to_string(height);
    result += " color: " + color;
    result += " " + string(visible ? "visible" : "invisible");
    result += " " + string(border ? "with border" : "borderless");
    return result;
}

void ModelWindowClass::moveHorizontal(int dx) {
    int newX = x + dx;
    if (newX >= 0 && newX + width <= SCREEN_WIDTH) {
        x = newX;
        cout << "Окно перемещено по горизонтали на " << dx << " пикселей" << endl;
    }
    else {
        cout << "Невозможно переместить окно: выходит за границы экрана" << endl;
    }
}

void ModelWindowClass::moveVertical(int dy) {
    int newY = y + dy;
    if (newY >= 0 && newY + height <= SCREEN_HEIGHT) {
        y = newY;
        cout << "Окно перемещено по вертикали на " << dy << " пикселей" << endl;
    }
    else {
        cout << "Невозможно переместить окно: выходит за границы экрана" << endl;
    }
}

void ModelWindowClass::changeWidth(int newWidth) {
    if (newWidth > 0 && x + newWidth <= SCREEN_WIDTH) {
        width = newWidth;
        cout << "Ширина изменена на " << newWidth << " пикселей" << endl;
    }
    else {
        cout << "Невозможно изменить ширину: недопустимое значение или выход за границы" << endl;
    }
}

void ModelWindowClass::changeHeight(int newHeight) {
    if (newHeight > 0 && y + newHeight <= SCREEN_HEIGHT) {
        height = newHeight;
        cout << "Высота изменена на " << newHeight << " пикселей" << endl;
    }
    else {
        cout << "Невозможно изменить высоту: недопустимое значение или выход за границы" << endl;
    }
}

void ModelWindowClass::changeColor(const string& newColor) {
    color = newColor;
    cout << "Цвет изменен на: " << newColor << endl;
}

void ModelWindowClass::setVisibility(bool isVisible) {
    visible = isVisible;
    cout << "Видимость изменена: " << (isVisible ? "видимое" : "невидимое") << endl;
}

void ModelWindowClass::setBorder(bool hasBorder) {
    border = hasBorder;
    cout << "Состояние рамки изменено: " << (hasBorder ? "с рамкой" : "без рамки") << endl;
}

bool ModelWindowClass::isVisible() const {
    return visible;
}

bool ModelWindowClass::hasBorder() const {
    return border;
}

void demoClassVersion() {
    cout << "\n ДЕМОНСТРАЦИЯ" << endl;

    ModelWindowClass win2("Окно класса", 200, 250, 400, 300, "зеленый", true, false);
    win2.display();

    win2.moveHorizontal(-50);
    win2.moveVertical(100);
    win2.changeHeight(350);
    win2.changeColor("желтый");
    win2.setBorder(true);

    win2.display();
    cout << "Строковое представление: " << win2.toString() << endl;
    // Проверка состояний
    cout << "Окно видимое? " << (win2.isVisible() ? "да" : "нет") << endl;
    cout << "Есть рамка? " << (win2.hasBorder() ? "да" : "нет") << endl;
}

// Главная функция для демонстрации обоих способов
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "ПРОГРАММА ДЛЯ РАБОТЫ С МОДЕЛЯМИ ЭКРАННЫХ ОКОН\n" << endl;

    // Демонстрация структуры
    demoStructVersion();

    // Демонстрация класса
    demoClassVersion();

    // Дополнительный пример с вводом с клавиатуры
    cout << "\nПРИМЕР С ВВОДОМ С КЛАВИАТУРЫ" << endl;

    ModelWindowClass userWindow;
    cout << "Введите данные для нового окна:" << endl;
    userWindow.read();
    userWindow.display();

    // Небольшие манипуляции
    userWindow.moveHorizontal(100);
    userWindow.changeColor("фиолетовый");
    userWindow.display();

    return 0;
}
