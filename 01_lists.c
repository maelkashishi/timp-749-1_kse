#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
	struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
	struct node *tail;  // конец списка
} list;

// инициализация пустого списка
void init(list *l) {
    l->head = NULL;
    l->tail = NULL;
}

// проверка на пустоту списка
bool is_empty(list *l) {
    if (l->head == NULL) {
        return 1;
    }
    else
    return 0;
}

// удалить все элементы из списка
void clean(list *l){
    node* NNextNode = l->head;
    node* NNode;
    while (NNextNode->next != NULL){
        NNode = NNextNode;
        NNextNode = NNextNode->next;
        free(NNode);
    }
    free(NNextNode);
    init(l);
}

// поиск элемента по значению,
// вернуть NULL если эжемент не найден
node *find(list *l, int value){
    node* NNode = l->head;
    while (NNode->next != NULL){
        if (NNode->value == value)
            return NNode;
        NNode = NNode->next;
    }
    if (NNode->value == value)
        return NNode;
    return NULL;
}

node *findNode(list* l, int n){
    int i;
    node* NNode = l->head;
    for (i = 1; i < n; i++)
        NNode = NNode->next;
    return NNode;
}

// вставка значения в конец списка,
// вернуть 0 если успешно
int push_back(list *l, int value){
    node* NNode;
    NNode = (node*)malloc(sizeof(node));
    NNode->value = value;
    NNode->next = NULL;
    if (is_empty(l)){
        l->head = NNode;
        l->tail = NNode;
        NNode->prev = NULL;
    }
    else{
        NNode->prev = l->tail;
        l->tail->next = NNode;
        l->tail = NNode;
    }
    return 0;
}

// вставка значения в начало списка,
// вернуть 0 если успешно
int push_front(list *l, int value){
    node* NNode;
    NNode = (node*)malloc(sizeof(node));
    NNode->value = value;
    NNode->prev = NULL;
    if (is_empty(l)){
        l->head = NNode;
        l->tail = NNode;
        NNode->next = NULL;
    }
    else{
        NNode->next = l->head;
        l->head->prev = NNode;
        l->head = NNode;
    }
    return 0;
}

// вставка значения после указанного узла,
// вернуть 0 если успешно
int insert_after(list *l, node *n, int value){
    {
        node* NNode;
        NNode = (node*)malloc(sizeof(node));
        NNode->value = value;
        NNode->prev = n;
        if (n->next == NULL){
            NNode->next = NULL;
            n->next = NNode;
            l->tail = NNode;
        }
        else{
            NNode->next = n->next;
            NNode->next->prev = NNode;
            n->next = NNode;
        }
        return 0;
    }
}

// вставка значения перед указанным узлом,
// вернуть 0 если успешно
int insert_before(list *l, node *n, int value) {
    if (n->prev == NULL) {
        push_front(l, value);
        return 0;
    }
    node* NNode = (node*)malloc(sizeof(node));
    NNode->next = n;
    NNode->prev = n->prev;
    NNode->prev->next = NNode;
    n->prev = NNode;
    NNode->value = value;
    return 0;
}

// удалить первый элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_first(list *l, int value){
    node* NNextNode = l->head;
    node* NNode;
    while ((NNextNode->value != value)&&(NNextNode->next != NULL)){
        NNode = NNextNode;
        NNextNode = NNextNode->next;
    }
    if ((NNextNode->next == NULL)&&(NNextNode->value != value))
        return 1;
    else if ((NNextNode->next == NULL)&&(NNextNode->value == value)){
        NNode->next = NULL;
        l->tail = NNode;
    }
    else if (NNextNode == l->head) {
        l->head = NNextNode->next;
        NNextNode->next->prev = NULL;
    }
    else{
        NNode->next = NNextNode->next;
        NNextNode->next->prev = NNode;
    }
    free(NNextNode);
    return 0;
}

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list *l, int value) {
    node *NNextNode = l->tail;
    node *NNode;
    while ((NNextNode->value != value) && (NNextNode->prev != NULL)) {
        NNode = NNextNode;
        NNextNode = NNextNode->prev;
    }
    if ((NNextNode->prev == NULL) && (NNextNode->value != value))
        return 1;
    else if ((NNextNode->prev == NULL) && (NNextNode->value == value)){
        NNode->prev = NULL;
        l->head = NNode;
    }
    else if (NNextNode == l->tail){
        l->tail = NNextNode->prev;
        NNextNode->prev->next = NULL;
    }
    else {
        NNode->prev = NNextNode->prev;
        NNextNode->prev->next = NNode;
    }
    free(NNextNode);
    return 0;
}

// вывести все значения из списка в прямом порядке через пробел
// после окончания вывода перейти на новую строку
void print(list *l){
    node *NNode = l->head;
    while (NNode->next != NULL){
        printf("%d ", NNode->value);
        NNode = NNode->next;
    }
    printf("%d", NNode->value);
    printf("\n");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l){
    node *NNode = l->tail;
    while (NNode->prev != NULL){
        printf("%d ", NNode->value);
        NNode = NNode->prev;
    }
    printf("%d", NNode->value);
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

int main() {
    list spis;
    node* b;
    int n, i, input, k1, k2, k3;
    init(&spis);
    (void)scanf("%d", &n);
    for (i = 1; i <= n; i++){
        (void)scanf("%d", &input);
        push_back(&spis, input);
    }
    print(&spis);
    (void)scanf("%d %d %d", &k1, &k2, &k3);
    b = find(&spis, k1);
    if (b != NULL)
        k1 = 1;
    else
        k1 = 0;
    b = find(&spis, k2);
    if (b != NULL)
        k2 = 1;
    else
        k2 = 0;
    b = find(&spis, k3);
    if (b != NULL)
        k3 = 1;
    else
        k3 = 0;
    printf("%d %d %d\n", k1, k2, k3);
    (void)scanf("%d", &input);
    push_back(&spis, input);
    print_invers(&spis);
    (void)scanf("%d", &input);
    push_front(&spis, input);
    print(&spis);
    (void)scanf("%d %d", &n, &input);
    b = findNode(&spis, n);
    insert_after(&spis, b, input);
    print_invers(&spis);
    (void)scanf("%d %d", &n, &input);
    b = findNode(&spis, n);
    insert_before(&spis, b, input);
    print(&spis);
    (void)scanf("%d", &input);
    remove_first(&spis, input);
    print_invers(&spis);
    (void)scanf("%d", &input);
    remove_last(&spis, input);
    print(&spis);
    clean(&spis);
    return 0;
}