#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void Increase_massive(int massive[], int size, int min){
    for(int i = 0; i<size; i++){
        massive[i] = min + i;
    }
}

void print_array(int arr[], int n) {
    printf("Массив: [");
    for(int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if(i < n-1) printf(", ");
        if((i+1) % 20 == 0 && i < n-1) printf("\n          ");
    }
    printf("]\n");
}


void binary_search_1(int massive[], int n, int* cc, int* x){
    int L = 0;
    int R = n-1;
    int flag = 0;
    
    while(L <= R){
        int m = (L+R)/2;
        
        (*cc)++;
        if(massive[m] == *x){
            flag = 1;
            printf("Элемент %d найден, он на %d месте в массиве\n", *x, m+1);
            break;
        }

        (*cc)++;
        if(massive[m]<*x){
            L = m+1;
        }
        else{
            R = m-1;
        }

    }

    if (flag == 0) {
        printf("Элемент %d не найден\n", *x);
    }
}

void binary_search_2(int massive[], int n, int* cc, int* x){
    int L = 0;
    int R = n-1;
    int flag = 0;

    while(L < R){
        int m = (L+R) / 2;

        (*cc)++;
        if(massive[m] < *x){
            L = m+1;
        }else{
            R = m;
        }

    }

    (*cc)++;
    if(massive[R] == *x){
        printf("Элемент %d найден, он на %d месте в массиве\n", *x, R+1);
        flag = 1;
    }else{
        printf("Элемент %d не найден\n", *x);
    }

    if(flag!=1){
        printf("Элемент %d не найден\n", *x);
    }
}

int binary_search_1_quiet(int massive[], int n, int* cc, int x){
    int L = 0, R = n-1;
    while(L <= R){
        int m = (L+R)/2;
        (*cc)++;
        if(massive[m] == x) return m;
        (*cc)++;
        if(massive[m] < x) L = m+1;
        else R = m-1;
    }
    return -1;
}

int binary_search_2_quiet(int massive[], int n, int* cc, int x){
    int L = 0, R = n-1;
    while(L < R){
        int m = (L+R) / 2;
        (*cc)++;
        if(massive[m] < x) L = m+1;
        else R = m;
    }
    (*cc)++;
    if(massive[R] == x) return R;
    return -1;
}

int theoretical_C(int n) {
    return (int)(log2((double)n) + 1);
}

void run_verification_tests(){
    printf("=== ПРОВЕРКА РАБОТЫ АЛГОРИТМОВ ===\n\n");
    
    int n = 30;
    int* arr = malloc(n * sizeof(int));
    Increase_massive(arr, n, 1);
    
    printf("Размер массива: N = %d\n", n);
    print_array(arr, n);
    printf("\n");
    
    
    int c_theory = theoretical_C(n);
    
    
    int key = arr[0];
    int cc1 = 0, cc2 = 0;
    printf("1. Поиск первого элемента (%d):\n", key);
    binary_search_1(arr, n, &cc1, &key);
    printf("   Сф (версия 1) = %d, С (теор) = %d \n", cc1, c_theory);
    
    cc2 = 0;
    binary_search_2(arr, n, &cc2, &key);
    printf("   Сф (версия 2) = %d, С (теор) = %d \n\n", cc2, c_theory);
    
    
    key = arr[n-1];
    cc1 = 0; cc2 = 0;
    printf("2. Поиск последнего элемента (%d):\n", key);
    binary_search_1(arr, n, &cc1, &key);
    printf("   Сф (версия 1) = %d, С (теор) = %d \n", cc1, c_theory);
    
    cc2 = 0;
    binary_search_2(arr, n, &cc2, &key);
    printf("   Сф (версия 2) = %d, С (теор) = %d \n\n", cc2, c_theory);
    
    key = arr[n-1] + 100;
    cc1 = 0; cc2 = 0;
    printf("3. Поиск отсутствующего элемента (%d):\n", key);
    binary_search_1(arr, n, &cc1, &key);
    printf("   Сф (версия 1) = %d, С (теор) = %d \n", cc1, c_theory);
    
    cc2 = 0;
    binary_search_2(arr, n, &cc2, &key);
    printf("   Сф (версия 2) = %d, С (теор) = %d \n\n", cc2, c_theory);
    
    printf("Теоретическая оценка: С = ⌊log₂%d⌋ + 1 = %d\n", n, c_theory);
    
    free(arr);
}

int main(){
    run_verification_tests();
    
    printf("========================================================================\n");
    printf("              ТРУДОЕМКОСТЬ ДВОИЧНОГО ПОИСКА ЭЛЕМЕНТА\n");
    printf("========================================================================\n\n");
    
    printf("+--------+------------------+------------------+\n");
    printf("|   N    |  Сф 1 версия     |  Сф 2 версия    |\n");
    printf("+--------+------------------+------------------+\n");
    
    for (int n = 100; n <= 1000; n += 100) {
        int* arr = malloc(n * sizeof(int));
        Increase_massive(arr, n, 1);
        
        int key = n + 100;
        int cc1 = 0, cc2 = 0;
        
        
        binary_search_1_quiet(arr, n, &cc1, key);
        binary_search_2_quiet(arr, n, &cc2, key);
        
        
        printf("| %6d | %16d | %16d |\n", n, cc1, cc2);
        
        free(arr);
    }
    printf("+--------+------------------+------------------+\n");
     
    return 0;
}