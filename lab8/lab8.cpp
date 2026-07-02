#include <iostream>
#include <string>

struct Contact{
    std::string surname;
    std::string name;
    long phone;
    std::string group;
};

void print_phonebook_by_index(const Contact arr[], const int index[], int count, const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
    for (int i = 0; i < count; ++i) {
        int idx = index[i];  
        std::cout << arr[idx].surname << " " << arr[idx].name
                  << " " << arr[idx].phone << " " << arr[idx].group << "\n";
    }
    std::cout << "\n";
}

void SelectSortIndex(Contact arr[], int index[], int n, int* cs, int* cc) {
    for (int i = 0; i < n; i++) {
        int min_index = i;
        
        for (int j = i + 1; j < n; j++) {
            (*cc)++;
            
            bool is_less = false;
            
            if (arr[index[j]].surname < arr[index[min_index]].surname) {
                is_less = true;
            }
            else if (arr[index[j]].surname == arr[index[min_index]].surname) {
                if (arr[index[j]].name < arr[index[min_index]].name) {
                    is_less = true;
                }
            }
            
            if (is_less) {
                min_index = j;
            }
        }
        
        (*cs) += 3;
        
        int temp = index[i];
        index[i] = index[min_index];
        index[min_index] = temp;
    }
}

void SelectSortIndexByPhone(Contact arr[], int index[], int n, int* cs, int* cc) {
    for (int i = 0; i < n; i++) {
        int min_index = i;
        
        for (int j = i + 1; j < n; j++) {
            (*cc)++;
            
            if (arr[index[j]].phone < arr[index[min_index]].phone) {
                min_index = j;
            }
        }
        
        (*cs) += 3;
        
        int temp = index[i];
        index[i] = index[min_index];
        index[min_index] = temp;
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

    int index_surname[5];
    int index_phone[5];

    for (int i = 0; i < count_contact; i++) {
        index_surname[i] = i;
        index_phone[i] = i;
    }

    print_phonebook_by_index(phonebook, index_surname, count_contact, "ИСХОДНЫЙ СПРАВОЧНИК ЧЕРЕЗ ИНДЕКСНЫЙ МАССИВ");

    int cs1 = 0, cc1 = 0;
    SelectSortIndex(phonebook, index_surname, count_contact, &cs1, &cc1);
    
    int cs2 = 0, cc2 = 0;
    SelectSortIndexByPhone(phonebook, index_phone, count_contact, &cs2, &cc2);

    print_phonebook_by_index(phonebook, index_surname, count_contact, "ОТСОРТИРОВАН ПО ФАМИЛИИ (через индекс)");
    print_phonebook_by_index(phonebook, index_phone, count_contact, "ОТСОРТИРОВАН ПО ТЕЛЕФОНУ (через индекс)");

    return 0;
}