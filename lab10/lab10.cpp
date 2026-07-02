#include <iostream>
#include <cstdlib>  
#include <ctime>

struct Node {
    int data;
    Node* next;      
};

struct Queue {
    Node* head;  
    Node* tail;  
};

void addNode(Node*& head, int value){
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;

    head = newNode;
}

void printStack(Node* head) {
    Node* curr = head; 
    std::cout << "Стек: ";
    
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next; 
    }
    
    std::cout << "\n";
}

void Ascending(Node*& head, int start, int count) {
    for (int i = 0; i < count; ++i) {
        addNode(head, start + i);
    }
}

void Descending(Node*& head, int start, int count) {
    for (int i = 0; i < count; ++i) {
        addNode(head, start - i);  
    }
}

void Random(Node*& head, int count, int minVal, int maxVal) {
    for (int i = 0; i < count; ++i) {
        int randomNum = minVal + rand() % (maxVal - minVal + 1);
        addNode(head, randomNum);
    }
}

void enqueue(Queue& q, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr; 
    
    if (q.head == nullptr) {
        q.head = newNode;
        q.tail = newNode;
    } else {
        q.tail->next = newNode;
        q.tail = newNode; 
    }
}

void printQueue(const Queue& q) {
    Node* current = q.head; 
    std::cout << "Очередь: ";
    
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    
    std::cout << "\n";
}

void QueueAscending(Queue& q, int start, int count) {
    for (int i = 0; i < count; ++i) {
        enqueue(q, start + i);
    }
}

void QueueDescending(Queue& q, int start, int count) {
    for (int i = 0; i < count; ++i) {
        enqueue(q, start - i);
    }
}

void QueueRandom(Queue& q, int count, int minVal, int maxVal) {
    for (int i = 0; i < count; ++i) {
        int randomNum = minVal + rand() % (maxVal - minVal + 1);
        enqueue(q, randomNum);
    }
}

int ControlSum(Node* head) {
    int sum = 0;
    Node* current = head;
    
    while (current != nullptr) {
        sum += current->data; 
        current = current->next;
    }
    
    return sum;
}


int CountSeries(Node* head) {
    if (head == nullptr) {
        return 0;
    }
    
    int seriesCount = 1; 
    Node* current = head;
    
    while (current->next != nullptr) {
        if (current->data >= current->next->data) {
            seriesCount++;
        }
        current = current->next;
    }
    
    return seriesCount;
}

void clearList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main(){
    srand(time(NULL));
    Node* head = nullptr;

    Ascending(head, 1, 5);
    printStack(head);

    clearList(head);

    Descending(head, 10, 4);
    printStack(head);

    clearList(head); 
    Random(head, 6, 1, 100);
    printStack(head);
    clearList(head); 

    std::cout << "\n";

    Queue q1;
    q1.head = nullptr;
    q1.tail = nullptr;
    
    std::cout << "Возрастающая очередь (1-5):\n";
    QueueAscending(q1, 1, 5);
    printQueue(q1);
    
    Queue q2;
    q2.head = nullptr;
    q2.tail = nullptr;
    
    std::cout << "Убывающая очередь (10-7):\n";
    QueueDescending(q2, 10, 4);
    printQueue(q2);
    
    Queue q3;
    q3.head = nullptr;
    q3.tail = nullptr;
    
    std::cout << "Случайная очередь (1-100, 6 штук):\n";
    QueueRandom(q3, 6, 1, 100);
    printQueue(q3);
    std::cout << "\n";

    Node* list = nullptr;

    for (int i = 0; i < 10; ++i) {
    int randomNum = 1 + rand() % 20; 
        addNode(list, randomNum);
    }
    printStack(list);
    int checksum = ControlSum(list);
    std::cout << "Контрольная сумма: " << checksum << "\n";

    int series = CountSeries(list);
    std::cout << "Количество серий: " << series << "\n";

    clearList(head); 
}