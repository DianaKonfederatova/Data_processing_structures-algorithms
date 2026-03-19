#include <stdio.h>
#include <stdlib.h>

//пока в процессе, не продуман момент сохранения прежнего значения
//стоит подумать над началом поиска элемента
//сразу не менять данные лучше
void SelectSort(int massive_orig[], int n){
    
    for (int i = 0; i<n; i++){
        int min_el = massive_orig[0];

        for(int j=1; j<n; j++){

            int temp = massive_orig[j];

            if(min_el>temp){
                
                min_el = temp;
                massive_orig[i] = massive_orig[j];
            }
        }        
    }

    for (int d=0; d<n; d++){
        printf("%d", massive_orig[d]);
    }
    
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

    printf("Массив после SelectSort: \n");
    SelectSort(massive, size);

    
    
}