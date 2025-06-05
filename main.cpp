#include <atomic>
#include <iostream>

// https://www.modernescpp.com/index.php/a-lock-free-stack-a-simplified-implementation/

template<typename T>
class LockFreeStackPush {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d): data(d), next(nullptr) {}
    };
    std::atomic<Node*> head;

public:
    LockFreeStackPush() = default;
    LockFreeStackPush(const LockFreeStackPush&) = delete;
    LockFreeStackPush& operator= (const LockFreeStackPush&) = delete;
    
    void push(T val) {
        Node* const newNode = new Node(val);
        newNode->next = head.load();
        while( !head.compare_exchange_strong(newNode->next, newNode) );
    }
};
   
int main(){
    LockFreeStackPush<int> lockFreeStack1;
    lockFreeStack1.push(5);
    
    LockFreeStackPush<double> lockFreeStack2;
    lockFreeStack2.push(5.5);
}
