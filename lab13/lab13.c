#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>


typedef struct Node {
    uint32_t data;
    struct Node* next;
} Node;


Node* DigitalSort(Node* S, int L_bytes, bool ascending, long long* M_fact) {
    Node Q_head[256];
    Node* Q_tail[256];
    *M_fact = 0;

    for (int j = 0; j < L_bytes; j++) {
        for (int i = 0; i < 256; i++) {
            Q_tail[i] = &Q_head[i];
            Q_head[i].next = NULL;
        }

        Node* p = S;
        while (p != NULL) {
            int d = (p->data >> (j * 8)) & 0xFF;
            Node* next_p = p->next;
            Q_tail[d]->next = p;
            Q_tail[d] = p;
            (*M_fact)++;
            p = next_p;
        }

        Node dummyS;
        p = &dummyS;

        if (ascending) {
            for (int i = 0; i < 256; i++) {
                if (Q_tail[i] != &Q_head[i]) {
                    p->next = Q_head[i].next;
                    p = Q_tail[i];
                }
            }
        } else {
            for (int i = 255; i >= 0; i--) {
                if (Q_tail[i] != &Q_head[i]) {
                    p->next = Q_head[i].next;
                    p = Q_tail[i];
                }
            }
        }

        p->next = NULL;
        S = dummyS.next;
    }

    return S;
}


uint64_t calculate_checksum(Node* head) {
    uint64_t sum = 0;
    while (head != NULL) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}


int count_series(Node* head, bool ascending) {
    if (head == NULL) return 0;
    int series = 1;
    Node* curr = head;
    while (curr->next != NULL) {
        if (ascending) {
            if (curr->data > curr->next->data) series++;
        } else {
            if (curr->data < curr->next->data) series++;
        }
        curr = curr->next;
    }
    return series;
}


Node* create_node(uint32_t data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}


Node* generate_list(int N, int type, int bytes) {
    Node dummy;
    Node* p = &dummy;
    uint32_t mask = (bytes == 2) ? 0xFFFF : 0xFFFFFFFF;

    for (int i = 0; i < N; i++) {
        uint32_t val;
        if (type == 1) val = i + 1;              // возрастающий: 1, 2, 3, ..., N
        else if (type == 2) val = N - i;         // убывающий: N, N-1, ..., 1
        else val = (rand() % N) + 1;             // случайный: 1, 2, 3, ..., N

        p->next = create_node(val & mask);
        p = p->next;
    }
    return dummy.next;
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}


void print_list(Node* head, int count) {
    int i = 0;
    while (head != NULL && i < count) {
        printf("%u ", head->data);
        head = head->next;
        i++;
    }
    if (head != NULL) printf("...");
    printf("\n");
}


Node* copy_list(Node* head) {
    if (head == NULL) return NULL;
    Node dummy;
    Node* p = &dummy;
    while (head != NULL) {
        p->next = create_node(head->data);
        p = p->next;
        head = head->next;
    }
    return dummy.next;
}


void run_experiment(int bytes) {
    printf("\n=== ТЕСТИРОВАНИЕ ДЛЯ %d-БАЙТОВЫХ ЧИСЕЛ ===\n", bytes);
    
    int sizes[] = {100, 200, 300, 400, 500};
    int max_show = 15;
    
    long long M_results[5][3];
    long long M_theory_values[5];

    for (int s = 0; s < 5; s++) {
        int N = sizes[s];
        long long M_theory = bytes * N;
        M_theory_values[s] = M_theory;
        
        printf("\n----------------------------------------\n");
        printf("N = %d\n", N);
        printf("----------------------------------------\n");

        printf("\nУБЫВАЮЩИЙ МАССИВ -> ПО ВОЗРАСТАНИЮ\n");
        Node* list = generate_list(N, 2, bytes);
        Node* list_copy = copy_list(list);
        
        printf("исходный массив: ");
        print_list(list_copy, max_show);
        printf("количество серий до сортировки: %d\n", count_series(list_copy, true));
        printf("контрольная сумма до: %llu\n", calculate_checksum(list_copy));
        
        long long M_fact;
        uint64_t sum_before = calculate_checksum(list);
        list = DigitalSort(list, bytes, true, &M_fact);
        M_results[s][0] = M_fact;
        
        printf("------------------------------------\n");
        printf("массив после сортировки (по возрастанию): ");
        print_list(list, max_show);
        printf("количество серий после сортировки: %d\n", count_series(list, true));
        printf("контрольная сумма после: %llu\n", calculate_checksum(list));
        printf("фактическое M: %lld\n", M_fact);
        
        if (calculate_checksum(list) != sum_before || count_series(list, true) != 1) {
            printf("ОШИБКА СОРТИРОВКИ!\n");
        }
        
        free_list(list_copy);
        free_list(list);

        printf("\nСЛУЧАЙНЫЙ МАССИВ -> ПО ВОЗРАСТАНИЮ\n");
        list = generate_list(N, 3, bytes);
        list_copy = copy_list(list);
        
        printf("исходный массив: ");
        print_list(list_copy, max_show);
        printf("количество серий до сортировки: %d\n", count_series(list_copy, true));
        printf("контрольная сумма до: %llu\n", calculate_checksum(list_copy));
        
        sum_before = calculate_checksum(list);
        list = DigitalSort(list, bytes, true, &M_fact);
        M_results[s][1] = M_fact;
        
        printf("------------------------------------\n");
        printf("массив после сортировки (по возрастанию): ");
        print_list(list, max_show);
        printf("количество серий после сортировки: %d\n", count_series(list, true));
        printf("контрольная сумма после: %llu\n", calculate_checksum(list));
        printf("фактическое M: %lld\n", M_fact);
        
        if (calculate_checksum(list) != sum_before || count_series(list, true) != 1) {
            printf("ОШИБКА СОРТИРОВКИ!\n");
        }
        
        free_list(list_copy);
        free_list(list);

        printf("\nВОЗРАСТАЮЩИЙ МАССИВ -> ПО ВОЗРАСТАНИЮ\n");
        list = generate_list(N, 1, bytes);
        list_copy = copy_list(list);
        
        printf("исходный массив: ");
        print_list(list_copy, max_show);
        printf("количество серий до сортировки: %d\n", count_series(list_copy, true));
        printf("контрольная сумма до: %llu\n", calculate_checksum(list_copy));
        
        sum_before = calculate_checksum(list);
        list = DigitalSort(list, bytes, true, &M_fact);
        M_results[s][2] = M_fact;
        
        printf("------------------------------------\n");
        printf("массив после сортировки (по возрастанию): ");
        print_list(list, max_show);
        printf("количество серий после сортировки: %d\n", count_series(list, true));
        printf("контрольная сумма после: %llu\n", calculate_checksum(list));
        printf("фактическое M: %lld\n", M_fact);
        
        if (calculate_checksum(list) != sum_before || count_series(list, true) != 1) {
            printf("ОШИБКА СОРТИРОВКИ!\n");
        }
        
        free_list(list_copy);
        free_list(list);

        printf("\nУБЫВАЮЩИЙ МАССИВ -> ПО УБЫВАНИЮ\n");
        list = generate_list(N, 2, bytes);
        list_copy = copy_list(list);
        
        printf("исходный массив: ");
        print_list(list_copy, max_show);
        printf("количество серий до сортировки: %d\n", count_series(list_copy, false));
        printf("контрольная сумма до: %llu\n", calculate_checksum(list_copy));
        
        sum_before = calculate_checksum(list);
        list = DigitalSort(list, bytes, false, &M_fact);
        
        printf("------------------------------------\n");
        printf("массив после сортировки (по убыванию): ");
        print_list(list, max_show);
        printf("количество серий после сортировки: %d\n", count_series(list, false));
        printf("контрольная сумма после: %llu\n", calculate_checksum(list));
        printf("фактическое M: %lld\n", M_fact);
        
        if (calculate_checksum(list) != sum_before || count_series(list, false) != 1) {
            printf("ОШИБКА СОРТИРОВКИ!\n");
        }
        
        free_list(list_copy);
        free_list(list);

        printf("\nСЛУЧАЙНЫЙ МАССИВ -> ПО УБЫВАНИЮ\n");
        list = generate_list(N, 3, bytes);
        list_copy = copy_list(list);
        
        printf("исходный массив: ");
        print_list(list_copy, max_show);
        printf("количество серий до сортировки: %d\n", count_series(list_copy, false));
        printf("контрольная сумма до: %llu\n", calculate_checksum(list_copy));
        
        sum_before = calculate_checksum(list);
        list = DigitalSort(list, bytes, false, &M_fact);
        
        printf("------------------------------------\n");
        printf("массив после сортировки (по убыванию): ");
        print_list(list, max_show);
        printf("количество серий после сортировки: %d\n", count_series(list, false));
        printf("контрольная сумма после: %llu\n", calculate_checksum(list));
        printf("фактическое M: %lld\n", M_fact);
        
        if (calculate_checksum(list) != sum_before || count_series(list, false) != 1) {
            printf("ОШИБКА СОРТИРОВКИ!\n");
        }
        
        free_list(list_copy);
        free_list(list);

        printf("\nВОЗРАСТАЮЩИЙ МАССИВ -> ПО УБЫВАНИЮ\n");
        list = generate_list(N, 1, bytes);
        list_copy = copy_list(list);
        
        printf("исходный массив: ");
        print_list(list_copy, max_show);
        printf("количество серий до сортировки: %d\n", count_series(list_copy, false));
        printf("контрольная сумма до: %llu\n", calculate_checksum(list_copy));
        
        sum_before = calculate_checksum(list);
        list = DigitalSort(list, bytes, false, &M_fact);
        
        printf("------------------------------------\n");
        printf("массив после сортировки (по убыванию): ");
        print_list(list, max_show);
        printf("количество серий после сортировки: %d\n", count_series(list, false));
        printf("контрольная сумма после: %llu\n", calculate_checksum(list));
        printf("фактическое M: %lld\n", M_fact);
        
        if (calculate_checksum(list) != sum_before || count_series(list, false) != 1) {
            printf("ОШИБКА СОРТИРОВКИ!\n");
        }
        
        free_list(list_copy);
        free_list(list);
    }
    
    printf("\n");
    printf("|  N  | M (теорет.) | M_факт Убыв. | M_факт Случ. | M_факт Возр. |\n");
    printf("|-----|-------------|--------------|--------------|--------------|\n");
    
    for (int s = 0; s < 5; s++) {
        printf("| %3d | %11lld | %12lld | %12lld | %12lld |\n",
               sizes[s], 
               M_theory_values[s],
               M_results[s][0],
               M_results[s][1],
               M_results[s][2]);
    }
}

int main() {
    srand(time(NULL));
    
    run_experiment(2);
    run_experiment(4);
    
    return 0;
}