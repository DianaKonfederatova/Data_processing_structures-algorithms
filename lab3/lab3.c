#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


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

void ShakerSort(int massive[], int n, int* cs, int* cc){
    int L = 0;
    int R = n-1;
    int f = n-1;

    while(L<R){

        for (int i = R; i>L; i--){
            (*cc)++;

            if(massive[i]<massive[i-1]){
                int temp = massive[i];
                massive[i] = massive[i-1];
                massive[i-1] = temp;
                (*cs)+=3;
                f = i;
            }
        }
        L=f;

        for (int j = L; j<R; j++){
            (*cc)++;
            if(massive[j]>massive[j+1]){
                int temp = massive[j];
                massive[j] = massive[j+1];
                massive[j+1] = temp;
                (*cs)+=3;
                f = j;
            }
        }
        R=f;   
    }
}

void labor_intensity(const char* name, int n) {
    if (strcmp(name, "ВОЗРАСТАЮЩИЙ МАССИВ") == 0) {
        int C = n-1;
        int M = 0;
        printf("Теоретическое количество сравнений: %d\n", C);
        printf("Теоретическое количество пересылок: %d\n", M);
        printf("Теоретическая трудоемкость: %d\n", C+M);
    }

    if (strcmp(name, "СЛУЧАЙНЫЙ МАССИВ") == 0) {
        int C = ((n*n)-n)/4;
        int M = (3*((n*n)-n))/4;
        printf("Теоретическое количество сравнений: %d\n", C);
        printf("Теоретическое количество пересылок: %d\n", M);
        printf("Теоретическая трудоемкость: %d\n", C+M);
    }

    if (strcmp(name, "УБЫВАЮЩИЙ МАССИВ") == 0) {
        int C = ((n*n)-n)/2;
        int M = (3*((n*n)-n))/2;
        printf("Теоретическое количество сравнений: %d\n", C);
        printf("Теоретическое количество пересылок: %d\n", M);
        printf("Теоретическая трудоемкость: %d\n", C+M);
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
    ShakerSort(massive, size, &counter_shipment, &counter_comparison);
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