#include <stdio.h>
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

void ShakerSort(int massive[], int n, int* cs, int* cc){
    int cc = 0;
    int cs = 0;
    int L = 0;
    int R = n-1;
    while(L<R){

        for (int i = R; i>L; i--){
            (*cc)++;

            if(massive[i]<massive[i-1]){
                int temp = massive[i];
                massive[i] = massive[i-1];
                massive[i-1] = temp;
                (*cs)+=3;
            }
        }
        L++;

        for (int j = L; j<R; j++){
            (*cc)++;
            if(massive[j]>massive[j+1]){
                int temp = massive[j];
                massive[j] = massive[j+1];
                massive[j+1] = temp;
                (*cs)+=3; 
            }
        }
        R--;
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




}