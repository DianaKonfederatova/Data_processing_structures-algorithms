#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

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

void QuickSort(int a[], int L, int R) {
    int x = a[L];
    int i = L;
    int j = R;

    while(i <= j){

        C++;
        while(a[i] < x){
            C++;
            i = i+1;
        }

        C++;
        while(a[j] > x){
            C++;
            j = j-1;
        }

        C++;
        if(i <= j){
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            M += 3;
            i = i+1;
            j = j-1;
        }
    }

    C++;
    if(L < j){
        QuickSort(a, L, j);
    }

    C++;
    if(i < R){
        QuickSort(a, i, R);
    }
}

void check_sort(char* name, int a[], int n) {
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
    QuickSort(a, 0, n - 1);
    
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

void character(int C, int M, int n, char* type) {
    printf("\nХАРАКТЕРИСТИКИ (для N=%d, %s)\n", n, type);
    printf("Фактическое количество сравнений: %d\n", C);
    printf("Фактическое количество пересылок: %d\n", M);
    printf("Фактическая трудоемкость: %d\n\n", C + M);
    
    double theor_C, theor_M;
    
    if (strcmp(type, "СЛУЧАЙНЫЙ") == 0) {
        // Средний случай
        theor_C = 1.44 * n * log2(n);
        theor_M = 0.3 * n * log2(n);
        printf("Теоретическое количество сравнений (средний случай): %.0f\n", theor_C);
        printf("Теоретическое количество пересылок (средний случай): %.0f\n", theor_M);
    } 
    else if (strcmp(type, "УБЫВАЮЩИЙ") == 0) {
        // Худший случай
        theor_C = (n*n + 5*n + 4) / 2.0;
        theor_M = 3 * (n - 1);
        printf("Теоретическое количество сравнений (худший случай): %.0f\n", theor_C);
        printf("Теоретическое количество пересылок (худший случай): %.0f\n", theor_M);
    } 
    else {
        // Лучший случай (возрастающий)
        theor_C = n * log2(n);
        theor_M = n * log2(n) / 3.0;
        printf("Теоретическое количество сравнений (лучший случай): %.0f\n", theor_C);
        printf("Теоретическое количество пересылок (лучший случай): %.0f\n", theor_M);
    }
    
    printf("Теоретическая трудоемкость: %.0f\n", theor_C + theor_M);
}

int main(){
    srand(time(NULL));

    
    printf("\n--- Трудоемкость метода Хоара ---\n");
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
        QuickSort(a_dec, 0, n - 1); 
        int res_dec = C + M;

        reset_counters();
        QuickSort(a_inc, 0, n - 1);
        int res_inc = C + M;

        reset_counters();
        QuickSort(a_rand, 0, n - 1);
        int res_rand = C + M;
        
        printf("%-6d%-8d%-8d%-8d\n", n, res_dec, res_inc, res_rand);
        
        free(a_dec);
        free(a_rand);
        free(a_inc);
    }

    printf("\n=== ПРОВЕРКА ПРАВИЛЬНОСТИ СОРТИРОВКИ ===\n\n");
    
    int n_test = 10;
    
    int* a_rand_test = malloc(n_test * sizeof(int));
    Random_massive(a_rand_test, n_test, 1, 10);
    check_sort("СЛУЧАЙНЫЙ МАССИВ", a_rand_test, n_test);
    character(C, M, n_test, "СЛУЧАЙНЫЙ");
    free(a_rand_test);
    
    int* a_dec_test = malloc(n_test * sizeof(int));
    Decrease_massive(a_dec_test, n_test, n_test);
    check_sort("УБЫВАЮЩИЙ МАССИВ", a_dec_test, n_test);
    character(C, M, n_test, "УБЫВАЮЩИЙ");
    free(a_dec_test);
    
    int* a_inc_test = malloc(n_test * sizeof(int));
    Increase_massive(a_inc_test, n_test, 1);
    check_sort("ВОЗРАСТАЮЩИЙ МАССИВ", a_inc_test, n_test);
    character(C, M, n_test, "ВОЗРАСТАЮЩИЙ");
    free(a_inc_test);
}