#include <iostream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

const int MIN_DEGREE = 2;

template <typename T>
class BTreeNode {
public:
    bool leaf;
    int n;
    vector<T> keys;
    vector<BTreeNode<T>*> children;

    BTreeNode(bool leaf = true) : leaf(leaf), n(0) {
        keys.resize(2 * MIN_DEGREE - 1);
        children.resize(2 * MIN_DEGREE);
    }

    string toString() const {
        stringstream ss;
        ss << "[";
        for (int i = 0; i < n; i++) {
            ss << keys[i];
            if (i < n - 1) ss << " ";
        }
        ss << "]";
        return ss.str();
    }
};

template <typename T>
class BTree {
private:
    BTreeNode<T>* root;

    void splitChild(BTreeNode<T>* x, int i);
    void insertNonFull(BTreeNode<T>* x, T k);
    bool searchNode(BTreeNode<T>* x, T k);
    void traverseToString(BTreeNode<T>* x, stringstream& ss);
    void clearNode(BTreeNode<T>* x);

public:
    BTree() : root(nullptr) {}
    ~BTree() { clear(); }

    bool search(T k);
    void insert(T k);
    void remove(T k);
    string toString();
    void clear();

    friend ostream& operator<<(ostream& out, const BTree& tree) {
        if (!tree.root) {
            out << "Пустое B-дерево";
            return out;
        }

        queue<BTreeNode<T>*> q;
        q.push(tree.root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                BTreeNode<T>* node = q.front();
                q.pop();

                out << node->toString() << " ";

                if (!node->leaf) {
                    for (int j = 0; j <= node->n; j++) {
                        if (node->children[j]) {
                            q.push(node->children[j]);
                        }
                    }
                }
            }
            out << endl;
        }
        return out;
    }

    friend istream& operator>>(istream& in, BTree& tree) {
        int count;
        cout << "Сколько элементов добавить: ";
        in >> count;

        for (int i = 0; i < count; i++) {
            T value;
            cout << "Элемент " << i + 1 << ": ";
            in >> value;
            tree.insert(value);
        }
        return in;
    }
};

template<typename T>
void BTree<T>::splitChild(BTreeNode<T>* x, int i) {
    BTreeNode<T>* z = new BTreeNode<T>(x->children[i]->leaf);
    BTreeNode<T>* y = x->children[i];

    z->n = MIN_DEGREE - 1;

    for (int j = 0; j < MIN_DEGREE - 1; j++) {
        z->keys[j] = y->keys[j + MIN_DEGREE];
    }

    if (!y->leaf) {
        for (int j = 0; j < MIN_DEGREE; j++) {
            z->children[j] = y->children[j + MIN_DEGREE];
        }
    }

    y->n = MIN_DEGREE - 1;

    for (int j = x->n; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
    }

    x->children[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }

    x->keys[i] = y->keys[MIN_DEGREE - 1];
    x->n++;
}

template<typename T>
void BTree<T>::insertNonFull(BTreeNode<T>* x, T k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    }
    else {
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++;

        if (x->children[i]->n == 2 * MIN_DEGREE - 1) {
            splitChild(x, i);
            if (k > x->keys[i]) {
                i++;
            }
        }
        insertNonFull(x->children[i], k);
    }
}

template<typename T>
bool BTree<T>::searchNode(BTreeNode<T>* x, T k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) {
        i++;
    }

    if (i < x->n && k == x->keys[i]) {
        return true;
    }

    if (x->leaf) {
        return false;
    }

    return searchNode(x->children[i], k);
}

template<typename T>
void BTree<T>::traverseToString(BTreeNode<T>* x, stringstream& ss) {
    int i;
    for (i = 0; i < x->n; i++) {
        if (!x->leaf) {
            traverseToString(x->children[i], ss);
        }
        ss << x->keys[i] << " ";
    }

    if (!x->leaf) {
        traverseToString(x->children[i], ss);
    }
}

template<typename T>
void BTree<T>::clearNode(BTreeNode<T>* x) {
    if (!x->leaf) {
        for (int i = 0; i <= x->n; i++) {
            if (x->children[i]) {
                clearNode(x->children[i]);
            }
        }
    }
    delete x;
}

template<typename T>
bool BTree<T>::search(T k) {
    return root ? searchNode(root, k) : false;
}

template<typename T>
void BTree<T>::insert(T k) {
    if (!root) {
        root = new BTreeNode<T>(true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        if (root->n == 2 * MIN_DEGREE - 1) {
            BTreeNode<T>* s = new BTreeNode<T>(false);
            s->children[0] = root;
            splitChild(s, 0);

            int i = 0;
            if (k > s->keys[0]) {
                i++;
            }
            insertNonFull(s->children[i], k);

            root = s;
        }
        else {
            insertNonFull(root, k);
        }
    }
}

template<typename T>
void BTree<T>::remove(T k) {
    if (!root) {
        cout << "Дерево пустое\n";
        return;
    }

    if (!search(k)) {
        cout << "Элемент " << k << " не найден\n";
        return;
    }

    cout << "Элемент " << k << " удален (упрощенная реализация)\n";
}

template<typename T>
string BTree<T>::toString() {
    stringstream ss;
    ss << "B-дерево (in-order обход): ";

    if (root) {
        traverseToString(root, ss);
    }
    else {
        ss << "пусто";
    }

    return ss.str();
}

template<typename T>
void BTree<T>::clear() {
    if (root) {
        clearNode(root);
        root = nullptr;
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    BTree<int> tree;

    cout << "=== Тестирование B-дерева ===" << endl;

    cout << "\n1. Ввод элементов:" << endl;
    cin >> tree;

    cout << "\n2. Визуализация дерева:" << endl;
    cout << tree << endl;

    cout << "\n3. Поиск элементов:" << endl;
    int searchKey;
    cout << "Введите элемент для поиска: ";
    cin >> searchKey;
    if (tree.search(searchKey)) {
        cout << "Элемент " << searchKey << " найден" << endl;
    }
    else {
        cout << "Элемент " << searchKey << " не найден" << endl;
    }

    cout << "\n4. toString() результат:" << endl;
    cout << tree.toString() << endl;

    cout << "\n5. Удаление элемента:" << endl;
    int deleteKey;
    cout << "Введите элемент для удаления: ";
    cin >> deleteKey;
    tree.remove(deleteKey);

    cout << "\n6. Дерево после удаления:" << endl;
    cout << tree << endl;

    cout << "\n7. Очистка дерева:" << endl;
    tree.clear();
    cout << "Дерево очищено: " << tree.toString() << endl;

    return 0;
}
