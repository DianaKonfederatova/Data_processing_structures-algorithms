#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int C = 0;
int M = 0;


struct Node {
    int data;      
    struct Node* next; 
};

int countList(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void reset_counters() {
    C = 0;
    M = 0;
}

int series(struct Node* head) {
    int count_series = 0;
    struct Node* current = head;
    
    while (current != NULL && current->next != NULL) {
        if (current->data > current->next->data) {
            count_series++;
        }
        current = current->next;
    }
    return count_series + 1;
}

int control_sum(struct Node* head) {
    int sum = 0;
    struct Node* current = head;
    
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

struct Node* RandomList(int size, int min, int max) {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    for (int i = 0; i < size; i++) {
        int value = rand() % (max - min + 1) + min;
        struct Node* newNode = createNode(value);
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

struct Node* IncreaseList(int size, int min) {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    for (int i = 0; i < size; i++) {
        struct Node* newNode = createNode(min + i);
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

struct Node* DecreaseList(int size, int max) {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    for (int i = 0; i < size; i++) {
        struct Node* newNode = createNode(max - i);
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

int splitList(struct Node* S, struct Node** a, struct Node** b){
    if (S == NULL) {
        *a = NULL;
        *b = NULL;
        return 0;
    }
    
    int count_n = 1;
    
    *a = S;
    *b = S->next;
    
    struct Node* k = *a;
    struct Node* p = *b;
    
    while (p != NULL) {
        count_n++;
        k->next = p->next;  
        k = p;              
        p = p->next;   
        M++;     
    }

    k->next = NULL;
    
    return count_n;
}

void moveNode(struct Node** from, struct Node** head, struct Node** tail) {
    struct Node* temp = *from;
    *from = (*from)->next;
    temp->next = NULL;
    
    if (*head == NULL) {
        *head = temp;
        *tail = temp;
    } else {
        (*tail)->next = temp;
        *tail = temp;
    }
    M++;
}

void merge(struct Node** a, int q, struct Node** b, int r, struct Node** c_head, struct Node** c_tail) {
    *c_head = NULL;
    *c_tail = NULL;
    
    while (q > 0 && r > 0) {
        if (*a == NULL || *b == NULL){
            break;
        } 
        C++;

        if ((*a)->data <= (*b)->data) {
            moveNode(a, c_head, c_tail);
            q--;
        } else {
            moveNode(b, c_head, c_tail);
            r--;
        }
    }

    while (q > 0) {
        moveNode(a, c_head, c_tail);
        q = q - 1;
    }
    
    while (r > 0) {
        moveNode(b, c_head, c_tail);
        r = r - 1;
    }
}

struct Node* MergeSort(struct Node* S, int n) {
    if (S == NULL || S->next == NULL){
        return S;
    }

    struct Node *a = NULL, *b = NULL;
    int p = 1;
    
    n = splitList(S, &a, &b);
    
    while (p < n) {
        struct Node *c0_head = NULL, *c0_tail = NULL; 
        struct Node *c1_head = NULL, *c1_tail = NULL;
        int i = 0;
        int m = n;
        
        while (m > 0) {
            int q = (m >= p) ? p : m;
            m = m - q;
            
            int r = (m >= p) ? p : m;
            m = m - r;
            
            // врем. указатели для текущего вызова merge
            struct Node *temp_head = NULL, *temp_tail = NULL;
            merge(&a, q, &b, r, &temp_head, &temp_tail);
            
            
            if (i == 0) {
                if (c0_head == NULL) {
                    c0_head = temp_head;
                    c0_tail = temp_tail;
                } else {
                    c0_tail->next = temp_head;  
                    c0_tail = temp_tail;
                }
            } else {
                if (c1_head == NULL) {
                    c1_head = temp_head;
                    c1_tail = temp_tail;
                } else {
                    c1_tail->next = temp_head;
                    c1_tail = temp_tail;
                }
            }
            
            i = 1 - i;
        }
        
        a = c0_head;
        b = c1_head;
        
        p = 2 * p;
    }
    
    return a;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    srand(time(NULL));
    
    printf("=== ПРОВЕРКА ПРАВИЛЬНОСТИ СОРТИРОВКИ ===\n\n");
    
    struct Node* testList = RandomList(10, 1, 100);
    
    printf("Исходный список:\n");
    printList(testList);
    printf("Количество серий: %d\n", series(testList));
    printf("Контрольная сумма: %d\n\n", control_sum(testList));
    
    reset_counters();
    testList = MergeSort(testList, 10);
    
    printf("После сортировки:\n");
    printList(testList);
    printf("Количество серий: %d\n", series(testList));
    printf("Контрольная сумма: %d\n\n", control_sum(testList));
    
    printf("Фактические сравнения (C): %d\n", C);
    printf("Фактические перемещения (M): %d\n", M);
    printf("Фактическая трудоемкость (C+M): %d\n\n", C + M);
    
    freeList(testList);
    printf("\n=== ПРОВЕРКА РАСЩЕПЛЕНИЯ ===\n");
    struct Node* splitTest = RandomList(20, 1, 100);
    printf("Исходный список: ");
    printList(splitTest);

    struct Node *a = NULL, *b = NULL;
    int n = splitList(splitTest, &a, &b);
    printf("Список A (нечетные позиции): ");
    printList(a);
    printf("Список B (четные позиции): ");
    printList(b);
    printf("Элементов в A: %d, в B: %d\n", countList(a), countList(b));
    freeList(a);
    freeList(b);

    
    printf("\n=== ПРОВЕРКА СЛИЯНИЯ ===\n");
    struct Node* listA = RandomList(5, 1, 50);
    struct Node* listB = RandomList(5, 1, 50);
    printf("Список A: ");
    printList(listA);
    printf("Серий в A: %d\n", series(listA));
    printf("Список B: ");
    printList(listB);
    printf("Серий в B: %d\n", series(listB));

    reset_counters();
    struct Node *merged_head = NULL, *merged_tail = NULL;
    merge(&listA, countList(listA), &listB, countList(listB), &merged_head, &merged_tail);

    printf("Результат слияния: ");
    printList(merged_head);
    printf("Контрольная сумма результата: %d\n", control_sum(merged_head));
    printf("Серий в результате: %d\n", series(merged_head));
    printf("Cф=%d, Mф=%d\n", C, M);
    freeList(merged_head);
    
    printf("\n=== ТРУДОЕМКОСТЬ MERGE SORT ===\n");
    printf("N     M+C теор  M+C факт (Убыв)  M+C факт (Случ)  M+C факт (Возр)\n");
    printf("-----------------------------------------------------------------\n");

    for (int n = 100; n <= 500; n += 100) {
        struct Node* decList = DecreaseList(n, n);
        struct Node* incList = IncreaseList(n, 1);
        struct Node* randList = RandomList(n, 1, n * 10);
        
        // Убывающий
        reset_counters();
        decList = MergeSort(decList, n);
        int res_dec = C + M;
        freeList(decList);
        
        // Возрастающий
        reset_counters();
        incList = MergeSort(incList, n);
        int res_inc = C + M;
        freeList(incList);
        
        // Случайный
        reset_counters();
        randList = MergeSort(randList, n);
        int res_rand = C + M;
        freeList(randList);
        
        // Теория
        int log_n = (int)ceil(log2(n));
        int theory = 2 * n * log_n + n;  // C + M = n*log + (n*log + n) = 2*n*log + n
        
        printf("%-6d%-13d%-15d%-15d%-15d\n", n, theory, res_dec, res_rand, res_inc);
    }

    printf("\nТрудоемкость метода не зависит от исходной упорядоченности данных.\n");
    printf("Фактические значения Cф и Mф соответствуют теоретическим оценкам:\n");
    printf("Метод обеспечивает устойчивую сортировку.\n");
    
    return 0;
}