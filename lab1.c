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


void SelectSort(int massive_orig[], int n, int* cs, int* cc){
    
    
    for (int i = 0; i<n; i++){

        int min_index = i;
        
        for(int j=i+1; j<n; j++){
            (*cc)++;

            if(massive_orig[min_index]>massive_orig[j]){

                min_index = j; 
            }
        }
        /*
        //это условие убирать, если рассматривать не усовершенствованный код
        if (min_index != i) {
            (*cs)+=3;  
            
            int temp = massive_orig[i];
            massive_orig[i] = massive_orig[min_index];
            massive_orig[min_index] = temp;       
        }     
        */
        //эту часть добалять, если смотреть первоначальную, не усовершенствованную версию кода
        
        (*cs)+=3;
        
        int temp = massive_orig[i];
        massive_orig[i] = massive_orig[min_index];
        massive_orig[min_index] = temp;
        
      
    }
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

void Test(const char* name, int massive[], int size){
    int counter_shipment = 0;
    int counter_comparison = 0;

    printf("%s\n", name);
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

    SelectSort(massive, size, &counter_shipment, &counter_comparison);

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

    printf("ХАРАКТЕРИСТИКИ МЕТОДА ПРЯМОГО ВЫБОРА\n");
    printf("Фактическое количество сравнений: %d\n", counter_comparison);
    printf("Фактическое количество пересылок: %d\n", counter_shipment);
    int T_fact = counter_comparison + counter_shipment;
    printf("Трудоемкость фактическая: %d", T_fact);

    printf("\n\n");

    int M = 3*(size-1);
    int C = ((size*size) - size)/2;

    printf("Теоретическое количество сравнений: %d\n", C);
    printf("Теоретическое количество пересылок: %d\n", M);
    int T_teor = C + M;
    printf("Трудоемкость теоретическая: %d", T_teor);
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

    printf("Исследование SelectSort (n = %d)\n", size);
    
    Increase_massive(massive, size, min);
    Test("ВОЗРАСТАЮЩИЙ", massive, size);

    Decrease_massive(massive, size, max);
    Test("УБЫВАЮЩИЙ", massive, size);

    Random_massive(massive, size, min, max);
    Test("ИЗ СЛУЧАЙНЫХ ЧИСЕЛ", massive, size);    

    return 0;
}