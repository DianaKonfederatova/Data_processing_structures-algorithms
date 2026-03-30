#include <stdio.h>
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


void SelectSort(int massive_orig[], int n){
    
    for (int i = 0; i<n; i++){

        int min_index = i;
        
        for(int j=i+1; j<n; j++){

            if(massive_orig[min_index]>massive_orig[j]){

                min_index = j; 
            }
        }

        int temp = massive_orig[i];
        massive_orig[i]=massive_orig[min_index];
        massive_orig[min_index] = temp;       
      
    }
}

void Random_massive(int massive[], int size, int min, int max){
    for (int i=0; i<size; i++){
        massive[i] = rand() % (max - min + 1) + min;
    }
}

int main(){
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

    printf("Массив до сортировки:\n");
    Random_massive(massive, size, min, max);
    for (int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }
    printf("\n");
    int control_sum_befor = control_sum(massive, size);
    printf("Контрольная сумма до сортировки: %d\n", control_sum_befor);
    int series_befor = count_series(massive, size);
    printf("Количество серий до сортировки: %d\n", series_befor);
    printf("\n\n");
    
    printf("Массив после SelectSort: \n");
    SelectSort(massive, size);
    for (int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }
    printf("\n");
    int control_sum_after = control_sum(massive, size);
    printf("Контрольная сумма после сортировки: %d\n", control_sum_after);
    int series_after = count_series(massive, size);
    printf("Количество серий после сортировки: %d\n", series_after);
    
}