// Implementation of a Stack using an Array by Chamath Ranasinghe

#include <iostream>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

// Initialize a class to implement a Stack using an array
class Stack{
    private:
    const int size = 10; //Size of Stack
    int stackArr[10]; // Array to be used
    int top = -1;

    public:
    void push(int data){ // Append value to the end of array

        if (isFull()){
            cout <<"Stack Overflow"<<endl;
            top--;    
        }// endif
        else{
            top ++;
            stackArr[top] = data;
        }

    }

    int pop(){ // Pop value at the end
        if(isEmpty()){
            cout<<"Stack Underflow"<<endl;
        }
        else{
            top--;
            return stackArr[top+1];

        }
    }

    bool isEmpty() { // Check if the stack is empty
        return (top == -1);
    }

    bool isFull() { // Check if the stack is full
        return (top == size - 1);
    }

    void display(){ // Display the stack
        for (int i=0; i<top+1; i++){
            cout<<stackArr[i]<<" ";
        }
        cout<<endl;
    }
};

int runOperation(){
    Stack stack;

    for (int i=0; i < 10; i++){
        stack.push(rand()/100);    
    }

    stack.display();

    for (int i=0; i < 5; i++){
        stack.pop();    
    }

    stack.display();

    for (int i=0; i < 4; i++){
        stack.push(rand()/100);    
    }

    stack.display();


}

int main(){
    auto start = chrono::high_resolution_clock::now();
    runOperation();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<< duration.count()<<endl;

    return 0;
}
