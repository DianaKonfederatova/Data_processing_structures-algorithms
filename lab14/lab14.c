#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    char symbol;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    int size;
    int totalElements;
    int collisions;
} HashTable;

int hashFunction(const char* str, int m) {
    int h = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        h = (h * 256 + (unsigned char)str[i]) % m;
    }
    return h;
}

HashTable* createHashTable(int m) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = m;
    table->totalElements = 0;
    table->collisions = 0;
    table->buckets = (Node**)malloc(m * sizeof(Node*));
    for (int i = 0; i < m; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

Node* createNode(char symbol) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->symbol = symbol;
    newNode->next = NULL;
    return newNode;
}

void insertElement(HashTable* table, char symbol) {
    char str[2];
    str[0] = symbol;
    str[1] = '\0';
    
    int index = hashFunction(str, table->size);
    Node* newNode = createNode(symbol);
    
    if (table->buckets[index] == NULL) {
        table->buckets[index] = newNode;
    } else {
        table->collisions++;
        Node* current = table->buckets[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    table->totalElements++;
}

int searchElement(HashTable* table, char symbol) {
    char str[2];
    str[0] = symbol;
    str[1] = '\0';
    
    int index = hashFunction(str, table->size);
    Node* current = table->buckets[index];
    int position = 0;
    
    while (current != NULL) {
        if (current->symbol == symbol) {
            printf("Символ '%c' найден в списке %d на позиции %d\n", symbol, index, position);
            return 1;
        }
        current = current->next;
        position++;
    }
    printf("Символ '%c' не найден\n", symbol);
    return 0;
}

void printHashTable(HashTable* table) {
    printf("\nХеш-таблица (размер = %d):\n", table->size);
    printf("Всего элементов: %d\n", table->totalElements);
    printf("Коллизий: %d\n", table->collisions);
    printf("\nСписки:\n");
    for (int i = 0; i < table->size; i++) {
        printf("Список %d: ", i);
        Node* current = table->buckets[i];
        if (current == NULL) {
            printf("пуст");
        } else {
            while (current != NULL) {
                printf("'%c' ", current->symbol);
                current = current->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Node* current = table->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void getPrimes(int primes[], int* count) {
    *count = 0;
    for (int i = 11; i <= 101; i++) {
        if (isPrime(i)) {
            primes[*count] = i;
            (*count)++;
        }
    }
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
    int primeCount;
    getPrimes(primes, &primeCount);
    
    printf("\n=== Исследование зависимости коллизий ===\n");
    printf("Уникальные символы: ");
    for (int i = 0; i < dataLen; i++) {
        printf("'%c' ", data[i]);
    }
    printf("\n\n");
    
    printf("Размер таблицы | Кол-во символов | Коллизий\n");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < primeCount && primes[i] <= 101; i++) {
        int m = primes[i];
        HashTable* table = createHashTable(m);
        
        for (int j = 0; j < dataLen; j++) {
            insertElement(table, data[j]);
        }
        
        printf("      %3d      |       %3d       |    %3d\n", 
               m, dataLen, table->collisions);
        
        freeHashTable(table);
    }
    printf("\n");
}

int main() {
    char fullName[] = "KONFEDERATOV";
    char uniqueSymbols[20];
    int uniqueCount;
    
    getUniqueSymbols(fullName, uniqueSymbols, &uniqueCount);
    
    printf("Входные данные (первые 12 символов): ");
    for (int i = 0; i < 12 && i < strlen(fullName); i++) {
        printf("'%c' ", fullName[i]);
    }
    printf("\n");
    
    printf("Уникальные символы: ");
    for (int i = 0; i < uniqueCount; i++) {
        printf("'%c' ", uniqueSymbols[i]);
    }
    printf("\n");
    printf("Количество уникальных символов: %d\n", uniqueCount);
    
    printf("\n=== Задание 2 ===\n");
    
    int n = uniqueCount;
    double logN = log(n) / log(2);
    int minM = (int)(n / (2 * logN)) + 1;
    
    int m = minM;
    while (!isPrime(m)) {
        m++;
    }
    
    printf("Количество элементов n = %d\n", n);
    printf("log2(n) = %.2f\n", logN);
    printf("Необходимо m > %.2f\n", n / (2 * logN));
    printf("Выбран размер m = %d (простое число)\n", m);
    
    HashTable* table = createHashTable(m);
    
    printf("\nВставка элементов:\n");
    for (int i = 0; i < uniqueCount; i++) {
        insertElement(table, uniqueSymbols[i]);
        char str[2];
        str[0] = uniqueSymbols[i];
        str[1] = '\0';
        printf("Вставлен '%c' (хеш = %d)\n", 
               uniqueSymbols[i], hashFunction(str, m));
    }
    
    printHashTable(table);
    
    printf("Проверка поиска:\n");
    if (uniqueCount > 0) {
        searchElement(table, uniqueSymbols[0]);
        if (uniqueCount > 1) {
            searchElement(table, uniqueSymbols[uniqueCount-1]);
        }
    }
    searchElement(table, 'Z');
    
    printf("\nФактическое количество коллизий Kф = %d\n", table->collisions);
    
    printf("\n=== Задание 3 ===\n");
    investigateCollisions(uniqueSymbols, uniqueCount);
    
    freeHashTable(table);
    
    return 0;
}