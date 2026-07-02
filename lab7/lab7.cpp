#include <iostream>
#include <string>

struct Contact{
    std::string surname;
    std::string name;
    long phone;
    std::string group;
};

void print_phonebook(const Contact arr[], int count, const std::string& title){
    std::cout << "\n=== " << title << " ===\n";

    for(int i = 0; i < count; ++i){
        std::cout << arr[i].surname << " " << arr[i].name
        << " " << arr[i].phone << " " << arr[i].group << "\n";
    }
    std::cout << "\n";
}

int less(struct Contact X, struct Contact Y){
    if (X.surname < Y.surname){
        return 1;
    } 
    else if (X.surname > Y.surname){
        return 0;
    } 
    else if (X.name > Y.name){
        return  0;
    }
    else if (X.name < Y.name){
        return 1;
    }
    else{
        return 0;
    }
}
 

int less2(struct Contact X, struct Contact Y){
    if (X.group < Y.group) return 1;
    else if (X.group > Y.group) return 0;
    else if (X.surname < Y.surname) return 1;
    else return 0;
}


/*int less(struct Contact X, struct Contact Y){
    if (X.surname > Y.surname) return 1;  
    else if (X.surname < Y.surname) return 0;
    else if (X.name > Y.name) return 1;  
    else return 0;
}
*/

void SelectSort(Contact arr[], int n, int* cs, int* cc) {
    for (int i = 0; i < n; i++) {
        int min_index = i;
        
        for (int j = i + 1; j < n; j++) {
            (*cc)++; 
            
            if (less(arr[j], arr[min_index]) == 1) {
                min_index = j;
            }
        }
        
        (*cs) += 3;  
        
        Contact temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

void SelectSort2(Contact arr[], int n, int* cs, int* cc) {
    for (int i = 0; i < n; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            (*cc)++;
            if (less2(arr[j], arr[min_index]) == 1) {
                min_index = j;
            }
        }
        (*cs) += 3;
        Contact temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

int main(){
    
    Contact phonebook[] = {
        {"Иванов", "Иван", 79131111111, "ИА-331"},
        {"Конфедератова", "Диана", 79132222222, "ИП-514"},
        {"Конфедератова", "Анна", 79133333333, "ИП-514"},
        {"Рубцов", "Роман", 79134444444, "ИА-331"},
        {"Вовченко", "Олег", 79135555555, "ИВТ-327"} 
    };

    int count_contact = 5;
    print_phonebook(phonebook, count_contact, "ИСХОДНЫЙ ТЕЛЕФОННЫЙ СПРАВОЧНИК");

    int comparisons = 0;
    int swaps = 0;
    SelectSort(phonebook, count_contact, &swaps, &comparisons);
    print_phonebook(phonebook, count_contact, "ОТСОРТИРОВАННЫЙ СПРАВОЧНИК");

    std::cout << "Сравнений: " << comparisons << "\n";
    std::cout << "Перестановок: " << swaps / 3 << "\n";

    comparisons = 0; swaps = 0;
    SelectSort2(phonebook, count_contact, &swaps, &comparisons);
    print_phonebook(phonebook, count_contact, "ОТСОРТИРОВАН: Группа + Фамилия");
    return 0;
}