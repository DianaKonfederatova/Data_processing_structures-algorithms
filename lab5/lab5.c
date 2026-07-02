#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void labor_intensity(const char* name, int n);

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

void ShellSort(int massive[], int n, int* cs, int* cc){
    int h[] =  {1,3,7,15,31,63,127,255};
    int num_otstyp = 8;
    
    for (int g = num_otstyp - 1; g >= 0; g--) {
        int k = h[g];
        
        for (int i = k; i < n; i++) {
            int t = massive[i];
            (*cs)++;
            int j = i - k;
            int flag = 0;
            
            while (j >= 0 && t < massive[j]) {
                (*cc)++;
                massive[j + k] = massive[j];
                (*cs)++;
                j -= k;
                flag = 1;
            }

            if(flag == 0 && j >= 0){
                (*cc)++;
            }
            
            massive[j + k] = t;
            (*cs)++;
        }
    }
}

void Test(const char* name, int massive[], int size){
    int counter_shipment = 0;   
    int counter_comparison = 0;
    printf("==============================");
    printf("%s\n", name);
    printf("Массив до сортировки:\n");
    for (int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }

    printf("\n");

    int control_sum_befor = control_sum(massive, size);
    printf("Контрольная сумма до сортировки: %d\n", control_sum_befor);
    int series_befor = count_series(massive, size);
    printf("Количество серий до сортировки: %d\n", series_befor);
    printf("\n\n");

    clock_t start_time = clock();
    ShellSort(massive, size, &counter_shipment, &counter_comparison);
    clock_t end_time = clock();

    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("--------------------------------------------------\n");
    printf("После сортировки:\n");
    for (int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }

    printf("\n");

    int control_sum_after = control_sum(massive, size);
    printf("Контрольная сумма после сортировки: %d\n", control_sum_after);
    int series_after = count_series(massive, size);
    printf("Количество серий после сортировки: %d\n", series_after);
    printf("\n\n");

    printf("ХАРАКТЕРИСТИКИ\n");
    printf("Фактическое количество сравнений: %d\n", counter_comparison);
    printf("Фактическое количество пересылок: %d\n", counter_shipment);
    int T_fact = counter_comparison + counter_shipment;
    printf("Трудоемкость фактическая: %d", T_fact);

    printf("\n\n");
    labor_intensity(name, size);
    printf("Время выполнения: %.6f сек (или %.3f мс)\n", time_spent, time_spent * 1000);
    printf("\n\n");
}

void labor_intensity(const char* name, int n) {
    if (strcmp(name, "ВОЗРАСТАЮЩИЙ МАССИВ") == 0) {
        // Количество проходов для шагов Кнута = log2(n)
        //Лучший случай: O(n log n)
        int passes = (int)(log2((double)n) + 1);
        if (passes < 1){
            passes = 1;
        }

        int C = n * passes;
        int M = 2 * C; 

        printf("Теоретическое количество сравнений: %d\n", C);
        printf("Теоретическое количество пересылок: %d\n", M);
        printf("Теоретическая трудоемкость: %d\n", C+M);
    }

    if (strcmp(name, "СЛУЧАЙНЫЙ МАССИВ") == 0) {
        // Средний случай: O(n^1.25)
        double n_125 = pow((double)n, 1.25);
        int C = (int)(0.35 * n_125);
        int M = (int)(0.70 * n_125);
        
        // Для малых n результат не должен быть меньше базовой вставки
        if (C < n - 1){
            C = n - 1;
        } 

        if (M < 2 * (n - 1)){
            M = 2 * (n - 1);
        } 

        printf("Теоретическое количество сравнений: %d\n", C);
        printf("Теоретическое количество пересылок: %d\n", M);
        printf("Теоретическая трудоемкость: %d\n", C+M);
    }

    if (strcmp(name, "УБЫВАЮЩИЙ МАССИВ") == 0) {
        // Худший случай: O(n^1.5)
        double n_15 = pow((double)n, 1.5);
        int C = (int)(0.50 * n_15);
        int M = (int)(1.00 * n_15);
        printf("Теоретическое количество сравнений: %d\n", C);
        printf("Теоретическое количество пересылок: %d\n", M);
        printf("Теоретическая трудоемкость: %d\n", C+M);
    }
}



int main(){
    srand(time(NULL));
    int size;
    int min;
    int max;


    printf("Введите количество элементов массива:\n");
    scanf("%d", &size);
    printf("Введите минимальное значаение массива:\n");
    scanf("%d", &min);
    printf("Введите максимально значаение массива:\n");
    scanf("%d", &max);
    int massive[size];
    printf("\n\n");

    Increase_massive(massive, size, min);
    Test("ВОЗРАСТАЮЩИЙ МАССИВ", massive, size);

    
    Decrease_massive(massive, size, max);
    Test("УБЫВАЮЩИЙ МАССИВ", massive, size);

    
    Random_massive(massive, size, min, max);
    Test("СЛУЧАЙНЫЙ МАССИВ", massive, size);

}