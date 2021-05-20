#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;          // значение, которое хранит узел
    struct node *next;  // ссылка на следующий элемент списка
} node;

typedef struct list {
    struct node *head;  // начало списка
    struct node *tail;
} list;

void init(list *l) { // инициализация пустого списка
    l->head = NULL;
    l->tail = NULL;
}

bool is_empty(list *l) { // проверка на пустоту списка
    if (l == NULL) {
        return true;
    }
    return l->head == NULL;
}

void clean(list *l) { // удалить все элементы из списка
    if (l == NULL) {
        return;
    }
    else if (!is_empty(l)) {
        node *NNextNode = l->head;
        node *NNode;
        while (NNextNode != NULL) {
            NNode = NNextNode;
            NNextNode = NNode->next;
            free(NNode);
        }
    }
}

node *find(list *l, int value) { // поиск элемента по значению. вернуть NULL если эжемент не найден
    if (l == NULL) {
        return NULL;
    }
    else if (is_empty(l)) {
        return NULL;
    }
    node *NNode = l->head;
    while (NNode) {
        if (NNode->value == value) {
            return NNode;
        }
        NNode = NNode->next;
    }
    return NULL;
}

int push_front(list *l, int value) { // вставка значения в начало списка, вернуть 0 если успешно
    if (l == NULL) {
        return -1;
    }
    node* NNode = (node*)malloc(sizeof(node));
    NNode->value = value;
    NNode->next = l->head;
    if (l->head == NULL) {
        l->tail = NNode;
    }
    l->head = NNode;
    return 0;
}

int push_back(list *l, int value) { // вставка значения в конец списка, вернуть 0 если успешно
    if (l == NULL) {
        return -1;
    }
    if (is_empty(l)) {
        return push_front(l, value);
    }
    node* NNode = (node*)malloc(sizeof(node));
    NNode->value = value;
    NNode->next = NULL;
    l->tail->next = NNode;
    l->tail = NNode;
    return 0;
}

int insert_after(node *n, int value) { // вставка значения после указанного узла, вернуть 0 если успешно
    if (n == NULL) {
        return -1;
    }
    node* NNode = (node*)malloc(sizeof(node));
    NNode->value = value;
    NNode->next = n->next;
    n->next = NNode;
    return 0;
}

int remove_node(list *l, int value) { // удалить первый элемент из списка с указанным значением, вернуть 0 если успешно
    if (l == NULL) {
        return -1;
    }
    else if (is_empty(l)) {
        return -1;
    }
    node *NNode = l->head;
    node *pPreNode = NNode;
    while (NNode != NULL) {
        if (NNode->value == value) {
            if (pPreNode == l->head) {
                l->head = NNode->next;
            } else if (!NNode->next) {
                l->tail = pPreNode;
            }
            pPreNode->next = NNode->next;
            free(NNode);
            return 0;
        }
        pPreNode = NNode;
        NNode = NNode->next;
    }
    return -1;
}

void print(list *l) { // вывести все значения из списка в прямом порядке через пробел, после окончания вывода перейти на новую строку
    if (l == NULL) {
        return;
    }
    else if (is_empty(l)) {
        return;
    }
    node *NNode = l->head;
    while (NNode != NULL) {
        printf("%d ", NNode->value);
        NNode = NNode->next;
    }
    printf("\n");
}

node* get(list* l, int index) {
    if (index == 0) {
        index = 1;
    }
    else if (l == NULL) {
        return NULL;
    }
    else if (is_empty(l)) {
        return NULL;
    }
    node* NNode = l->head;
    int i = 1;
    while (NNode != NULL) {
        if (i == index) {
            return NNode;
        }
        NNode = NNode->next;
        i++;
    }
    return NULL;
}

int
main () {
    unsigned int n;
    int args = scanf("%u", &n);
    if (args != 1 || n == 0) {
        return 1;
    }
    list *spis = (list *) malloc(sizeof(list));
    init(spis);
    int a;
    for (unsigned int i = 0; i < n; i++) {
        args = scanf("%d", &a);
        if (args != 1) {
            return 2;
        }
        push_back(spis, a);
    }
    print(spis);
    int k[3];
    for (unsigned int i = 0; i < 3; ++i) {
        args = scanf("%d", &k[i]);
        if (args != 1) {
            return 3;
        }
    }
    for (unsigned int i = 0; i < 3; i++) {
        printf("%d ", find(spis, k[i]) != NULL);
    }
    printf("\n");
    int m;
    args = scanf("%d", &m);
    if (args != 1) {
        return 4;
    }
    push_back(spis, m);
    print(spis);
    int t;
    args = scanf("%d", &t);
    if (args != 1) {
        return 5;
    }
    push_front(spis, t);
    print(spis);
    unsigned int j;
    args = scanf("%u", &j);
    if (args != 1) {
        return 6;
    }
    int x;
    args = scanf("%d", &x);
    if (args != 1) {
        return 7;
    }
    node *prevNode = get(spis, j);
    if (prevNode == NULL) {
        return 8;
    }
    insert_after(prevNode, x);
    if (prevNode == spis->tail) {
        spis->tail = prevNode->next;
    }
    print(spis);
    int z;
    args = scanf("%d", &z);
    if (args != 1) {
        return 9;
    }
    if (prevNode != NULL) {
        remove_node(spis, z);
    }
    print(spis);
    clean(spis);
    free(spis);
    return 0;
}