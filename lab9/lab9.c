#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int C = 0;
int M = 0;

int count_series(int massive[], int size){
    int number_of_episodes = 0;
    
    for (int b = 0; b<size-1; b++){

        int current = massive[b];
        int next = massive[b+1];

        if (current > next) {
            number_of_episodes++;  
        }
    }
    return number_of_episodes + 1;
}

int control_sum(int massive[], int n){
    int control_sum_massive = 0;

    for (int d=0; d<n; d++){

        control_sum_massive += massive[d];
    }

    return control_sum_massive;
}

void Random_massive(int massive[], int size, int min, int max){
    for (int i=0; i<size; i++){
        massive[i] = rand() % (max - min + 1) + min;
    }
}

void Increase_massive(int massive[], int size, int min){
    for(int i = 0; i<size; i++){
        massive[i] = min + i;
    }
}

void Decrease_massive(int massive[], int size, int max){
    for(int i = 0; i<size; i++){
        massive[i] = max - i;
    }
}

void reset_counters() {
    C = 0;
    M = 0;
}

void heap(int a[], int L, int R){
    int x = a[L];
    int i = L;
    M++;

    while(1){
        int j = 2*i;

        C++;
        if(j>R){
            break;
        }
        
        C+=2;
        if(j<R && a[j+1] <= a[j]){
            j = j+1;
        }
        
        C++;
        if(x <= a[j]){
            break;
        }
        

        a[i] = a[j];
        M++;
        i = j;
    }

    a[i] = x;
    M++;
}

void HeapSort(int a[], int n){
    int L = n / 2 - 1;
    
    while(L>=0){
        heap(a, L, n-1);
        L = L-1;
    }

    int R = n-1;

    while(R > 0){
        int temp = a[0];
        a[0] = a[R];
        a[R] = temp;
        M += 3;
        R = R - 1;
        heap(a, 0, R);
    }

    for(int i = 0; i < n/2; i++){
        int temp = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = temp;
        M += 3;
    }
}

void check_sort_heap(char* name, int a[], int n) {
    printf("%s\n", name);
    
    printf("Массив до сортировки:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    int cs1 = control_sum(a, n);
    int s1 = count_series(a, n);
    printf("Контрольная сумма до сортировки: %d\n", cs1);
    printf("Количество серий до сортировки: %d\n", s1);
    
    printf("\n--------------------------------------------------\n");
    
    reset_counters();
    HeapSort(a, n);
    
    printf("После сортировки:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    int cs2 = control_sum(a, n);
    int s2 = count_series(a, n);
    printf("Контрольная сумма после сортировки: %d\n", cs2);
    printf("Количество серий после сортировки: %d\n", s2);
        
    printf("\n\n");
}


int main(){
    srand(time(NULL));
    
    // Задание 2
    printf("\n--- Построение пирамиды ---\n");
    printf("N     M+C теор   Убыв    Случ    Возр\n");
    printf("-------------------------------------\n");
    
    for (int n = 100; n <= 500; n += 100) {
        int* a_dec = malloc(n * sizeof(int));
        int* a_rand = malloc(n * sizeof(int));
        int* a_inc = malloc(n * sizeof(int));
        
        Decrease_massive(a_dec, n, n);
        Random_massive(a_rand, n, 1, n * 10);
        Increase_massive(a_inc, n, 1);
        
        double theor = 3.0 * log2(n) + 2.0;
        
        reset_counters();
        heap(a_dec, 0, n-1);
        int res_dec = C + M;
        
        reset_counters();
        heap(a_rand, 0, n-1);
        int res_rand = C + M;
        
        reset_counters();
        heap(a_inc, 0, n-1);
        int res_inc = C + M;
        
        printf("%-6d%-11.1f%-8d%-8d%-8d\n", n, theor, res_dec, res_rand, res_inc);
        
        free(a_dec);
        free(a_rand);
        free(a_inc);
    }
    
    // Задание 4
    printf("\n--- HeapSort ---\n");
    printf("N     Убыв    Возр    Случ\n");
    printf("--------------------------\n");
    
    for (int n = 100; n <= 500; n += 100) {
        int* a_dec = malloc(n * sizeof(int));
        int* a_rand = malloc(n * sizeof(int));
        int* a_inc = malloc(n * sizeof(int));
        
        Decrease_massive(a_dec, n, n);
        Random_massive(a_rand, n, 1, n * 10);
        Increase_massive(a_inc, n, 1);
        
        reset_counters();
        HeapSort(a_dec, n);
        int res_dec = C + M;
        
        reset_counters();
        HeapSort(a_inc, n);
        int res_inc = C + M;
        
        reset_counters();
        HeapSort(a_rand, n);
        int res_rand = C + M;
        
        printf("%-6d%-8d%-8d%-8d\n", n, res_dec, res_inc, res_rand);
        
        free(a_dec);
        free(a_rand);
        free(a_inc);
    }
    
    printf("\n=== ПРОВЕРКА ПРАВИЛЬНОСТИ СОРТИРОВКИ ===\n\n");
    
    int n_test = 10;
    
    // Случайный массив
    int* a_rand_test = malloc(n_test * sizeof(int));
    Random_massive(a_rand_test, n_test, 1, 10);
    check_sort_heap("СЛУЧАЙНЫЙ МАССИВ", a_rand_test, n_test);
    free(a_rand_test);
    
    // Убывающий массив
    int* a_dec_test = malloc(n_test * sizeof(int));
    Decrease_massive(a_dec_test, n_test, n_test);
    check_sort_heap("УБЫВАЮЩИЙ МАССИВ", a_dec_test, n_test);
    free(a_dec_test);
    
    // Возрастающий массив
    int* a_inc_test = malloc(n_test * sizeof(int));
    Increase_massive(a_inc_test, n_test, 1);
    check_sort_heap("ВОЗРАСТАЮЩИЙ МАССИВ", a_inc_test, n_test);
    free(a_inc_test);
    
    printf("\nВывод: HeapSort не зависит от упорядоченности массива,\n");
    printf("значения близкие для всех типов, рост O(n log n).\n");
    
    return 0;
}