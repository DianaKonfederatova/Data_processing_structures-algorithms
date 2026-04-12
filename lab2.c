#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

void BubbleSort(int massive_orig[], int n, int* cs, int* cc){
    for(int j = 0; j < n-1; j++){
        for(int i = n-1; i > j; i--){
            (*cc)++;

            if(massive_orig[i] < massive_orig[i-1]){
                
                int temp = massive_orig[i];
                massive_orig[i] = massive_orig[i-1];
                massive_orig[i-1] = temp;
                (*cs)++; 
            }
        }
    }  
}

void test_random(const char* name, int massive[], int size){
    int counter_shipment = 0;
    int counter_comparison = 0;

    printf("--------------------------\n");
    printf("=====%s=====\n", name);
    printf("--------------------------\n");
    printf("\n");
    printf("До сортировки:\n");
    for (int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }
    printf("\n");

    int control_sum_befor = control_sum(massive, size);
    printf("Контрольная сумма до сортировки: %d\n", control_sum_befor);
    int series_befor = count_series(massive, size);
    printf("Количество серий до сортировки: %d\n", series_befor);
    printf("\n\n");

    BubbleSort(massive, size, &counter_shipment, &counter_comparison);

    printf("--------------------\n");
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

    printf("Фактическое количество сравнений: %d\n", counter_comparison);
    printf("Фактическое количество пересылок: %d\n", counter_shipment);
    int T_fact = counter_comparison + counter_shipment;
    printf("Трудоемкость фактическая: %d", T_fact);

    printf("\n\n");

    int M = 3*((size*size)-size)/4;
    int C = ((size*size) - size)/2;

    printf("Теоретическое количество сравнений: %d\n", C);
    printf("Теоретическое количество пересылок: %d\n", M);
    int T_teor = C + M;
    printf("Трудоемкость теоретическая: %d\n", T_teor);

    printf("\n");
}

void test_increase(const char* name, int massive[], int size){
    int counter_shipment = 0;
    int counter_comparison = 0;
    
    printf("--------------------------\n");
    printf("=====%s=====\n", name);
    printf("--------------------------\n");
    printf("\n");
    printf("До сортировки:\n");
    for (int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }
    printf("\n");

    int control_sum_befor = control_sum(massive, size);
    printf("Контрольная сумма до сортировки: %d\n", control_sum_befor);
    int series_befor = count_series(massive, size);
    printf("Количество серий до сортировки: %d\n", series_befor);
    printf("\n\n");

    BubbleSort(massive, size, &counter_shipment, &counter_comparison);

    printf("--------------------\n");
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

    printf("Фактическое количество сравнений: %d\n", counter_comparison);
    printf("Фактическое количество пересылок: %d\n", counter_shipment);
    int T_fact = counter_comparison + counter_shipment;
    printf("Трудоемкость фактическая: %d", T_fact);

    printf("\n\n");

    int M = 0;
    int C = ((size*size) - size)/2;

    printf("Теоретическое количество сравнений: %d\n", C);
    printf("Теоретическое количество пересылок: %d\n", M);
    int T_teor = C + M;
    printf("Трудоемкость теоретическая: %d\n", T_teor);

    printf("\n");

}

void test_decrease(const char* name, int massive[], int size){
    int counter_shipment = 0;
    int counter_comparison = 0;

    printf("--------------------------\n");
    printf("=====%s=====\n", name);
    printf("--------------------------\n");
    printf("\n");
    printf("До сортировки:\n");

    for (int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }
    printf("\n");

    int control_sum_befor = control_sum(massive, size);
    printf("Контрольная сумма до сортировки: %d\n", control_sum_befor);
    int series_befor = count_series(massive, size);
    printf("Количество серий до сортировки: %d\n", series_befor);
    printf("\n\n");

    BubbleSort(massive, size, &counter_shipment, &counter_comparison);

    printf("--------------------\n");
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

    printf("Фактическое количество сравнений: %d\n", counter_comparison);
    printf("Фактическое количество пересылок: %d\n", counter_shipment);
    int T_fact = counter_comparison + counter_shipment;
    printf("Трудоемкость фактическая: %d", T_fact);

    printf("\n\n");
    
    int C = ((size*size) - size)/2;
    int M = 3*C;

    printf("Теоретическое количество сравнений: %d\n", C);
    printf("Теоретическое количество пересылок: %d\n", M);
    int T_teor = C + M;
    printf("Трудоемкость теоретическая: %d\n", T_teor);

    printf("\n");
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

    printf("Исследование BubbleSort (n = %d)\n", size);
    printf("\n");

    Random_massive(massive, size, min, max);
    test_random("МАССИВ ИЗ СЛУЧАЙНЫХ ЧИСЕЛ", massive, size);

    Increase_massive(massive, size, min);
    test_increase("МАССИВ ВОЗРАСТАЮЩИЙ", massive, size);

    Decrease_massive(massive, size, max);
    test_decrease("МАССИВ УБЫВАЮЩИЙ", massive, size);

    return 0;
}