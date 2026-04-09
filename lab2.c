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

    printf("Исследование BubbleSort (n = %d)\n", size);
    
    Increase_massive(massive, size, min);
    Test("ВОЗРАСТАЮЩИЙ", massive, size);

    Decrease_massive(massive, size, max);
    Test("УБЫВАЮЩИЙ", massive, size);

    Random_massive(massive, size, min, max);
    Test("ИЗ СЛУЧАЙНЫХ ЧИСЕЛ", massive, size);

}