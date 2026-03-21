#include <stdio.h>
#include <stdlib.h>


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

    int control_sum_massive_sort = 0;
    for (int d=0; d<n; d++){
        control_sum_massive_sort += massive_orig[d];
        printf("%d", massive_orig[d]);
    }
    printf("\n");
    printf("Контрольная сумма после сортировки:\n");
    printf("%d\n", control_sum_massive_sort);
 
}

void Random_massive(int massive[], int size, int min, int max){
    for (int i=0; i<size; i++){
        massive[i] = rand() % (max - min + 1) + min;
    }

    int control_sum_orig = 0;
    for (int d=0; d<size; d++){
        control_sum_orig += massive[d];
    }
    printf("%d\n", control_sum_orig);
    
    printf("Исходный массив:\n");
    for (int j=0; j<size; j++){
        printf("%d", massive[j]);
    }
    printf("\n");
  
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

    printf("Контрольная сумма до сортировки:\n");
    Random_massive(massive, size, min, max);
    
    printf("Массив после SelectSort: \n");
    SelectSort(massive, size);
    
}