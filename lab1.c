#include <stdio.h>
#include <stdlib.h>

void SelectSort(){
    
}

void Random_massive(int massive[], int size, int min, int max){
    for (int i=0; i<size; i++){
        massive[i] = rand() % (max - min + 1) + min;
    }
    
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

    Random_massive(massive, size, min, max);

    
    
}