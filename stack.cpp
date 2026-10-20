#include <iostream>
#include <new>

#include "stack.h"

//constructor
//n is max size according to the comments in header file
Stack::Stack(int n){
    top = -1; //it's supposed to be made empty
    num = n; //assigns max to num
    array = new int[num]; //makes the array with new max num
}

//destructor
Stack::~Stack(){
    delete [] array;
}

//needs to have a check for the resize and throw an error if
//  if can't be resized
// Prof. James said to use try/catch and bad allocate for the size too big thing
void Stack::Resize(int n){
    int newCap = num*2;
    try{
        //makes it if it doesn't "explode" 
        int* newArray = new int[newCap];

        for(int x = 0; x <= top; x++)
        {
            newArray[x] = array[x];
        }
        delete[] array;
        

        array = newArray;
        num = newCap;

        top++;
        array[top] = n;
    }
    catch (const std::bad_alloc&){
        //if too big, throw this error.
        throw StackFull();
    }
}

//Pushes one number on top of the stack
void Stack::Push(int n){
    //needs to check if the stack is full, and then attempts to 
    //resize, if not able, throw an error
    if(IsFull())
    {
        int size = Size();
        Resize(size);
    }

    array[++top] = n;
}


//pops off the head of the stack
void Stack::Pop(){
    //needs to check if the stack is empty
    if(IsEmpty())
    {
        throw StackEmpty();
        return; //breaks from the code
    }


    top--; //pops off the top
}


//checks if the stack is empty
bool Stack::IsEmpty() const{
    if(top == -1)
    {
        return true;
    }

    return false;
}


//checks if the stack is full
bool Stack::IsFull() const{
    if(Size() > 0)
    {
        return true;
    }

    return false;
}


//makes the stack empty, though isn't that the same as the destructor?
//  Or can it be used in the destructor?

//Edit: No, this makes it empty, the destructor deallocates the memory and deletes the whole structure
//      This leaves the space for the structure but empties the actual info on it
void Stack::MakeEmpty(){
    while(!IsEmpty)
    {
        Pop();
    }
}

//returns the top of the stack
int Stack::Top() const{
    if(IsEmpty())
    {
        throw StackEmpty();
    }

    return top;
}

//returns the size of the stack, no modify
int Stack::Size() const{
    int size = 0;
    
    if(IsEmpty())
    {
        size = 0;
    }
    else
    {
        size = top + 1;
    }

    return size;
}



//returns the biggest num in the stack
int Stack::Max() const{
    int max = 0;
    int size = Size();

    //step through the whole stack
    for(int x = 0; x <= size; x++){
        if(array[x] > max)
        {
            max = array[x];
        }
    }

    return max;
}


//returns the smallest num in the stack
int Stack::Min() const{
    int min = array[0]; //set to the first element so that no matter the sign, I can run through the stack
    int size = Size();

    //starts at 1 so that it doesn't read the first element twice
    for(int x = 1; x <= size; x++){
        if(array[x] < min)
        {
            min = array[x];
        }
    }

    return min;
}

//looks at num n levels down from the top (remember that top is 0)
int Stack::Peek(unsigned int n) const{
    int peeked = -1;
    int size = Size();

    //I don't need a wrong number screwing it up
    //so size is a parameter for that if
    if(!IsEmpty() && n < size)
    {
        peeked = array[n];
    }

    return peeked;
}


//returns how many elements can be stored in the stack, not the same as size
//that's just num is it not?
int Stack::Capacity() const{
    return num;
}