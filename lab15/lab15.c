#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char* cells;
    int size;
    int elementCount;
    int collisions;
} HashTable;

HashTable* createHashTable(int m) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = m;
    ht->elementCount = 0;
    ht->collisions = 0;
    ht->cells = (char*)malloc(m * sizeof(char));
    for (int i = 0; i < m; i++) {
        ht->cells[i] = ' ';
    }
    return ht;
}

int hashFunction(char symbol, int tableSize) {
    return (int)symbol % tableSize;
}

void insertLinear(HashTable* ht, char symbol) {
    int firstHash = hashFunction(symbol, ht->size);
    int currentIndex = firstHash;
    int attempt = 0;
    
    while (ht->cells[currentIndex] != ' ') {
        ht->collisions++;
        attempt++;
        currentIndex = (firstHash + attempt) % ht->size;
        if (attempt >= ht->size) {
            printf("Ошибка: таблица переполнена\n");
            return;
        }
    }
    ht->cells[currentIndex] = symbol;
    ht->elementCount++;
}

void insertQuadratic(HashTable* ht, char symbol) {
    int firstHash = hashFunction(symbol, ht->size);
    int currentIndex = firstHash;
    int attempt = 0;
    
    while (ht->cells[currentIndex] != ' ') {
        ht->collisions++;
        attempt++;
        currentIndex = (firstHash + attempt * attempt) % ht->size;
        if (attempt > ht->size / 2) {
            printf("Ошибка: не удалось вставить '%c'\n", symbol);
            return;
        }
    }
    ht->cells[currentIndex] = symbol;
    ht->elementCount++;
}

void printHashTable(HashTable* ht, const char* name) {
    printf("\n%s (размер = %d):\n", name, ht->size);
    printf("Всего элементов: %d\n", ht->elementCount);
    printf("Коллизий: %d\n", ht->collisions);
    printf("\n");
    
    printf("Индекс: ");
    for (int i = 0; i < ht->size; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    
    printf("Символ: ");
    for (int i = 0; i < ht->size; i++) {
        if (ht->cells[i] == ' ') {
            printf("   ");
        } else {
            printf(" %c ", ht->cells[i]);
        }
    }
    printf("\n");
}

void freeHashTable(HashTable* ht) {
    free(ht->cells);
    free(ht);
}

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void getUniqueSymbols(const char* input, char* result, int* count) {
    int len = strlen(input);
    int uniqueCount = 0;
    int maxLen = (len < 12) ? len : 12;
    
    for (int i = 0; i < maxLen; i++) {
        int duplicate = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (result[j] == input[i]) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            result[uniqueCount] = input[i];
            uniqueCount++;
        }
    }
    *count = uniqueCount;
}

void investigateCollisions(const char* data, int dataLen) {
    int primes[30];
    int primeCount = 0;
    
    for (int i = 11; i <= 101; i++) {
        if (isPrime(i)) {
            primes[primeCount] = i;
            primeCount++;
        }
    }
    
    printf("\n=== Исследование зависимости коллизий ===\n");
    printf("Символы: ");
    for (int i = 0; i < dataLen; i++) {
        printf("'%c' ", data[i]);
    }
    printf("\n\n");
    
    printf("Размер таблицы | Символов | Линейные | Квадратичные\n");
    printf("----------------------------------------------------\n");
    
    for (int i = 0; i < primeCount && primes[i] <= 101; i++) {
        int m = primes[i];
        
        HashTable* htLinear = createHashTable(m);
        for (int j = 0; j < dataLen; j++) {
            insertLinear(htLinear, data[j]);
        }
        int linearCollisions = htLinear->collisions;
        freeHashTable(htLinear);
        
        HashTable* htQuad = createHashTable(m);
        int allInserted = 1;
        for (int j = 0; j < dataLen; j++) {
            insertQuadratic(htQuad, data[j]);
            if (htQuad->elementCount < j + 1) {
                allInserted = 0;
            }
        }
        int quadCollisions = htQuad->collisions;
        freeHashTable(htQuad);
        
        if (!allInserted) {
            printf("     %3d     |    %3d    |    %3d     |     %3d*\n",
                   m, dataLen, linearCollisions, quadCollisions);
        } else {
            printf("     %3d     |    %3d    |    %3d     |     %3d\n",
                   m, dataLen, linearCollisions, quadCollisions);
        }
    }
    printf("\n* - не все элементы вставлены\n");
}

int main() {
    char fullName[] = "KONFEDERATOV";
    char uniqueSymbols[20];
    int uniqueCount;
    
    getUniqueSymbols(fullName, uniqueSymbols, &uniqueCount);
    
    printf("Уникальные символы: ");
    for (int i = 0; i < uniqueCount; i++) {
        printf("'%c' ", uniqueSymbols[i]);
    }
    printf("\n");
    printf("Количество символов: %d\n", uniqueCount);
    
    printf("\n=== Задание 2 ===\n");
    
    int m = uniqueCount;
    while (!isPrime(m)) {
        m++;
    }
    printf("Размер таблицы m = %d (простое число)\n", m);
    
    HashTable* htLinear = createHashTable(m);
    printf("\nВставка с линейными пробами:\n");
    for (int i = 0; i < uniqueCount; i++) {
        insertLinear(htLinear, uniqueSymbols[i]);
        printf("Вставлен '%c'\n", uniqueSymbols[i]);
    }
    printHashTable(htLinear, "Линейные пробы");
    
    HashTable* htQuad = createHashTable(m);
    printf("\nВставка с квадратичными пробами:\n");
    for (int i = 0; i < uniqueCount; i++) {
        insertQuadratic(htQuad, uniqueSymbols[i]);
    }
    printHashTable(htQuad, "Квадратичные пробы");
    
    printf("\nСравнение коллизий:\n");
    printf("Линейные пробы: %d\n", htLinear->collisions);
    printf("Квадратичные пробы: %d\n", htQuad->collisions);
    
    freeHashTable(htLinear);
    freeHashTable(htQuad);
    
    investigateCollisions(uniqueSymbols, uniqueCount);
    
    return 0;
}