#include "My_Tree.cpp"
//#include "Test.cpp"
int lrand() { return rand() << 16 | rand(); }

void test_sort() {
    int n;
    cout << "\nInput size ";
    cin >> n;

    BSTree< int, int >* tr = new BSTree< int, int >;
    int* m = new int[n];

    for (int i = 0; i < n; i++) {
        m[i] = i * 1000;
        tr->add(m[i], 1);
    }

    double I = 0;
    double D = 0;
    double S = 0;

    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0)
        {
            int k = lrand() % 1000;
            //k=k+!(k%2);
            tr->remove(k);
            //tree.deleteElem(k);
            D += tr->getOps();
            tr->add(m[lrand() % n], 1);
            //tree.add(m[lrand()%n],1);
            I += tr->getOps();
            k = lrand() % 1000;
            try {
                tr->find(k);
                S += tr->getOps();
            }
            catch (char* e) { S += tr->getOps(); }
        }
        else
        {
            int ind = lrand() % n;
            tr->remove(m[ind]);
            D += tr->getOps();
            int k = lrand() % (1000 * n);
            k = k + k % 2;
            tr->add(k, 1);
            I += tr->getOps();
            m[ind] = k;
            try {
                tr->find(m[lrand() % n]);
                S += tr->getOps();
            }
            catch (char* e) { S += tr->getOps(); }

        }
    }

    cout << "items count:" << tr->getSize() << endl;
    cout << "n/2=" << n / 2 << endl;
    cout << "Count insert: " << I / (n / 2) << endl;
    cout << "Count delete: " << D / (n / 2) << endl;
    cout << "Count search: " << S / (n / 2) << endl;
    delete[] m;
}

void test_rand() {

    int n;
    cout << "\nInput size ";
    cin >> n;

    BSTree< int, int >* tr = new BSTree< int, int >;
    int* m = new int[n];

    for (int i = 0; i < n; i++)
    {
        m[i] = lrand();
        tr->add(m[i], 1);
    }

    double I = 0;
    double D = 0;
    double S = 0;

    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0)
        {
            tr->remove(lrand());
            D += tr->getOps();
            tr->add(m[lrand() % n], 1);
            I += tr->getOps();
            try {
                tr->find(lrand());
                S += tr->getOps();
            }
            catch (char* a)
            {
                S += tr->getOps();
            }
        }
        else {
            int ind = lrand() % n;
            tr->remove(m[ind]);
            D += tr->getOps();
            int key = lrand();
            tr->add(key, 1);
            I += tr->getOps();
            m[ind] = key;
            try {
                tr->find(m[lrand() % n]);
                S += tr->getOps();
            }
            catch (char* a)
            {
                S += tr->getOps();
            }

        }

    cout << "items count:" << tr->getSize() << endl;
    cout << "1.39*log2(n)=" << 1.39 * log((double)n) / log(2.0) << endl;
    cout << "Count insert: " << I / (n / 2) << endl;
    cout << "Count delete: " << D / (n / 2) << endl;
    cout << "Count search: " << S / (n / 2) << endl;
    delete[] m;
}

int getNum() {
    /*int buf;
    cin >> buf;
    while (!cin.good()) {
        cout << "Неверный формат данных!" << endl;
        cout << "Введите другое значение: ";
        cin.clear();
        _flushall();
        cin >> buf;
    }
    return buf;*/
    int number;
    while (true) {
        cin >> number;
        if ((number >= 0) && (number <= 21) && (cin.peek() == '\n'))
            break;
        else {
            cout << "Введите корректный номер!" << endl;

            cin.clear();
            while (cin.get() != '\n') {
            }
        }
    }
    return number;
}

int cin_int(int min, int max) {
    int number = min - 1;
    while (true) {
        cin >> number;
        if ((number >= min) && (number <= max) && (cin.peek() == '\n'))
            break;
        else {
            cout << "Введите значение int" << endl;

            cin.clear();
            while (cin.get() != '\n') {
            }
        }
    }
    return number;
}

void cout_menu() {
    cout << "\n-------Выберите пункт меню-------" << endl;
    cout << "0 - Включение 10 данных" << endl;
    cout << "1 - Включение данных с заданным ключом" << endl; //+
    cout << "2 - Удаление данных с заданным ключом" << endl; //+
    cout << "3 - Чтение данных по заданному ключу" << endl; //+
    cout << "4 - Перезапись данных по заданному ключу" << endl; //-
    cout << "5 - Опрос размера дерева" << endl; //-
    cout << "6 - Проверка дерева на пустоту" << endl; //+
    cout << "7 - Очистка дерева" << endl; //+
    cout << "8 - Обход L->t->R" << endl; //+
    cout << "9 - Поиск данных по ключу" << endl; //+
    cout << "10 - Горизонтальная печать" << endl; //-
    cout << "-------Меню итератора-------" << endl; //-
    cout << "11 - Запрс прямого итератора на начало" << endl;
    cout << "12 - Следующий элемент" << endl;
    cout << "13 - Предыдущий элемент" << endl;
    cout << "14 - Запрс прямого итератора на конец" << endl;
    cout << "15 - Запрос обратного итератора на начало" << endl;
    cout << "16 - Следующий элемент" << endl;
    cout << "17 - Предыдущий элемент" << endl;
    cout << "18 - Запрос обратного итератора на конец" << endl;
    cout << "-------Меню тестирования-------" << endl; //-
    cout << "19 - Вырожденное дерево" << endl;
    cout << "20 - Случайно заполнение дерево" << endl;
    //cout << "11 - Меню итератора" << endl; //-
    cout << "-1 - Выход" << endl;
}

void mainMenu() {
    int data, key;
    BSTree<int, int> tree;
    BSTree<int, int>::Iterator iterator;
    BSTree<int, int>::Inverse_iterator iIterator;
    int val;
    int menu;

    while (1) {
        cout_menu();
        menu = getNum();
        switch (menu) {
        case 0: {
            int val, key;
            bool rezult;
            tree.add(5, 1);
            tree.add(3, 2);
            tree.add(6, 3);
            tree.add(8, 4);
            tree.add(7, 5);
            tree.add(4, 6);
            tree.add(2, 7);
            tree.add(9, 8);
            tree.add(-10, 9);
            tree.add(-5, 99);
            cout << "Было созданно 10 значений" << endl;
            //iter;
            getchar();
        }
              break;

        case 1: {
            int val, key;
            bool rezult;
            cout << "Введите данные: ";
            val = cin_int(-2147483647, 2147483647);
            cout << "Введите ключ: ";
            key = cin_int(-2147483647, 2147483647);
            rezult = tree.add(key, val);

            if (rezult == true)
                cout << "Узел с искомыми данными и ключом добавлен в дерево" << endl;
            else if (rezult == false)
                cout << "Узел дерева с таким ключом уже существует!" << endl;
            // iter;
            getchar();
        }
              break;
        case 2: {
            int key;
            bool rez;
            cout << "Введите ключ: " << endl;
            key = cin_int(-2147483647, 2147483647);
            rez = tree.remove(key);
            if (rez == true)
                cout << "Элемент удален успешно!" << endl;
            if (rez == false)
                cout << "Элемента с заданным ключом не существует!" << endl;
            // iter.setUndefined();
            getchar();
        };
              break;

        case 3: {
            int key;
            cout << "Введите ключ: ";
            key = cin_int(-2147483647, 2147483647);
            try {
                cout << "Значение узла: " << tree.find(key) << endl;
            }
            catch (int) {
                cout << "Данного ключа нет в дереве!" << endl;
            }
            catch (char* Error) {
                cout << Error << endl;
            }
            getchar();
        }
              break;
        case 4: {
            int key, data;
            cout << "Введите ключ: ";
            key = cin_int(-2147483647, 2147483647);
            cout << "Введите значение узла: ";
            data = cin_int(-2147483647, 2147483647);
            try {
                tree.rewriteData(key, data);
            }
            catch (int) {
                cout << "Данного ключа нет в дереве!" << endl;
            }
            catch (char* Error) {
                cout << Error << endl;
            }
            cout << "Успешно!" << endl;
            // iter.setUndefined();
            getchar();
        };
              break;


        case 5: {
            cout << "Размер дерева: " << tree.getSize() << endl;
            getchar();
        };
              break;

        case 6: {
            bool rez = tree.isClear();
            if (rez == true)
                cout << "Дерево пусто" << endl;
            else
                cout << "Дерево не пусто" << endl;
            getchar();
        };
              break;

        case 7: {
            tree.clearTree();
            cout << "Дерево очищено" << endl;
            // iter.setUndefined();
            getchar();
        };
              break;

        case 8: {
            try {
                tree.LTR(tree.getRoot());
            }
            catch (char* Error) {
                cout << Error << endl;
            };
            cout << endl;
            getchar();
        }
              break;

        case 9: {
            int key;
            int rez;
            cout << "Введите ключ: ";
            key = cin_int(-2147483647, 2147483647);
            try {
                rez = tree.find(key);
            }
            catch (char* Error) {
                cout << Error << endl;

                cout << "Введите пункт меню: ";
                break;
            }
            cout << "Данные узла: " << rez << endl;
            getchar();
        };
              break;

        case 10: {
            try {
                tree.print();
            }
            catch (char* Error) {
                cout << Error << endl;
            };
            getchar();
        };
               break;
        case 11:
        {
            iterator = BSTree<int, int>::Iterator(tree);
            iterator.begin();
            BSTree<int, int>::Node* node = *(iterator);
            cout << "Итератор установлен на ключ: " << node->key << endl;
           // tree.print();
            //allowedToGetBal = true;

        }

        break;
        case 12:
        {   try {
            iterator.operator++();
            BSTree<int, int>::Node* node = *(iterator);
            cout << "Итератор установлен на ключ: " << node->key << std::endl;
            
        }
        catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
        }
        }
        break;
        case 13:
        {
            try {
                iterator.operator--();
                BSTree<int, int>::Node* node = *(iterator);
                cout << "Итератор установлен на ключ: " << node->key << std::endl;
               // tree.print();
            }
            catch (std::runtime_error e) {
                std::cout << e.what() << std::endl;
            }
        }

        break;
        case 14:
        {
            iterator = BSTree<int, int>::Iterator(tree);
            iterator.end();
            BSTree<int, int>::Node* node = *(iterator);
            cout << "Итератор установлен на ключ: " << node->key << std::endl;
            
            //allowedToGetBal = true;
        }

        break;
        case 15:
        {

            iIterator = BSTree<int, int>::Inverse_iterator(tree);
            iIterator.rBegin();
            BSTree<int, int>::Node* node = *(iIterator);
            cout << "Итератор установлен на ключ: " << node->key << std::endl;
            
            break;
        }
        case 16:
        {
            try {
                iIterator.operator++();
                BSTree<int, int>::Node* node = *(iIterator);
                cout << "Итератор установлен на ключ: " << node->key << std::endl;
                
            }
            catch (std::runtime_error e) {
                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 17:
        {
            try {
                iIterator.operator--();
                BSTree<int, int>::Node* node = *(iIterator);
                cout << "Итератор установлен на ключ: " << node->key << std::endl;
                
            }
            catch (std::runtime_error e) {
                std::cout << e.what() << std::endl;
            }

        }
        break;
        case 18:
        {
            iIterator = BSTree<int, int>::Inverse_iterator(tree);
            iIterator.rEnd();
            BSTree<int, int>::Node* node = *(iIterator);
            cout << "Итератор установлен на ключ: " << node->key << std::endl;     
        }

        break;

        case 19: {
            test_sort();
        }
               break;
        case 20: {
            test_rand();
        }       
               break;

        case -1: {
            return;
        }
               break;
        default: {
            cout << "Неверно выбран пункт меню!" << endl;
            cout << "Введите верный пункт: ";
        };
        }
    }
}

int main() {
    srand(time(NULL));
    setlocale(0, "");
    mainMenu();
    return 0;
}