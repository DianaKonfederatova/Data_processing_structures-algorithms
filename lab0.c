#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void control_sum(int massive[], int n){
    int control_sum_massive = 0;

    for (int d=0; d<n; d++){

        control_sum_massive += massive[d];
    }

    printf("Контрольной сумма: %d\n", control_sum_massive);
    
}

void count_series(int massive[], int size){
    int number_of_episodes = 0;
    
    for (int b = 0; b<size-1; b++){

        int current = massive[b];
        int next = massive[b+1];

        if (current > next) {
            number_of_episodes++;  
        }
    }

    printf("Количество серий: %d\n", number_of_episodes + 1);
}

void Increase_massive(int massive[], int size, int min){
    for(int i = 0; i<size; i++){
        massive[i] = min + i;
    }

    printf("Задание 1\n");
    printf("Массив по возрастанию:\n");
    for(int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }

    printf("\n");

    control_sum(massive, size);
    count_series(massive, size);

    printf("\n\n");

}

void Decrease_massive(int massive[], int size, int max){
    for(int i = 0; i<size; i++){
        massive[i] = max - i;
    }

    printf("Задание 2\n");
    printf("Массив по убыванию:\n");
    for(int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }

    printf("\n");

    control_sum(massive, size);
    count_series(massive, size);

    printf("\n\n");
}

void Random_massive(int massive[], int size, int min, int max){
    for (int i=0; i<size; i++){
        massive[i] = rand() % (max - min + 1) + min;
    }

    printf("Задание 3\n");
    printf("Массив из случайных чисел:\n");
    for(int i = 0; i<size; i++){
        printf("%d ", massive[i]);
    }

    printf("\n");

    control_sum(massive, size);
    count_series(massive, size);

    printf("\n\n");
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

    Increase_massive(massive, size, min);
    Decrease_massive(massive, size, max);
    Random_massive(massive, size, min, max);

    return 0;
}
