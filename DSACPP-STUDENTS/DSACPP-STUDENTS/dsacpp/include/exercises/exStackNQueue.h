/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StackNQueue.h
 * Author: LTSACH
 *
 * Created on 1 September 2020, 15:34
 */
/*
 * References:
 * [1] https://www.cs.princeton.edu/courses/archive/spr01/cs126/exercises/adt.html
 */
#ifndef STACKNQUEUE_H
#define STACKNQUEUE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "stacknqueue/Stack.h"
#include "stacknqueue/Queue.h"
using namespace std;


/*
A letter means push and an asterisk means pop in the following sequence.
Give the sequence of values returned by the pop operations
when this sequence of operations is performed on an initially empty LIFO stack.
 * Input sequence: EAS*Y*QUE**ST***IO*N***
Requirements:
 * a) Answer without programming: S, Y, E, U, T, S, Q, O, N, I, ... : 0 score!
 * b) Write a program determine and print the sequence mentioned above
 * c) what are the contents of the stack (from the top to the bottom), 
 *    after processing the input string: [DCBA]
 */

void stackInOut(){
    string input = "EAS*Y*QUE***ST***IO*N***ABCD";
    //SYEUQTSAONIE
    stringstream os;
    Stack<char> stack;
    for(int idx=0; idx < input.length(); idx++){
        char current = input[idx];
        if(current == '*'){
            char top = stack.pop();
            os << top;
        }
        else stack.push(current);
    }
    string output = os.str();
    cout << "Sequence from stack: "  << output << endl;
    cout << "Current stack (from top): [";
    while(!stack.empty()) cout << stack.pop();
    cout << "]" << endl;
}


/*
A letter means push and an asterisk means pop in the following sequence.
Give the sequence of values returned by the pop operations
when this sequence of operations is performed on an initially empty queue.
 * Input sequence: E A S * Y * Q U E * * * S T * * * I O * N * * *
Requirements:
 * a) Answer without programming: EASY ....
 * b) Write a program determine and print the sequence mentioned above
 */

void QueueInOut(){
    string input = "EAS*Y*QUE***ST***IO*N***TUMCH";
    stringstream os;
    Queue<char> queue;
    for(int idx=0; idx < input.length(); idx++){
        char current = input[idx];
        if(current == '*'){
            char top = queue.pop();
            os << top;
        }
        else queue.push(current);
    }
    string output = os.str();
    cout << "Sequence from queue: "  << output << endl;
    cout << "Current queue (from front->rear): [";
    while(!queue.empty()) cout << queue.pop();
    cout << "]" << endl;
}
/* 
With stack:
A letter means push and an asterisk means pop in the following sequence.
Give the contents of s[0], ..., s[4 (0->4: from the top) in the stack.
 * Input sequence: LA*STI*N*FIR*ST**OU*T****** 
Requirements:
 * a) Answer without programming
 * b) Write a program determine and print the sequence mentioned above
*/

void stackReading(){
    string input = "LA*STI*N*FIR*ST**OU*T******";
    int begin = 0, end = 4;
    stringstream os;
    Stack<char> stack;
    for(int idx=0; idx < input.length(); idx++){
        char current = input[idx];
        if(current == '*'){
            char top = stack.pop();
            os << top;
        }
        else stack.push(current);
    }
    string output = os.str();
    cout << "Sequence from stack: "  << output << endl;
    cout << "Current stack (from top): [";
    for(Stack<char>::Iterator it= stack.top(); it != stack.bottom(); it++)
        cout << *it;
    cout << "]" << endl;
    cout << "Stack: from " << begin << " to " << end << "(from top): ";
    int count = 0;
    while(!stack.empty() && (count <= end)){
        cout << stack.pop();
        count++;
    }
}

/*
 Write a program that:
 *  reads in a sequence of characters, and 
 *  determines whether its parentheses, braces, and curly braces are "balanced."  

Hint:  
 * for left delimiters, push onto stack; 
 * for right delimiters, pop from stack and 
   check whether popped element matches right delimiter.
 */

void check_balanced(){
    string input = "[(3 + 4) * 6] - [(4 - 2) - (22*2)]]";
    //
    string open_list =      "[{(";
    string closed_list =    "]})";
    Stack<char> stack;

    
    bool matched = true;
    for(int idx=0; idx< input.length(); idx++){
        char c = input[idx];
        
        if(open_list.find(c) != -1) stack.push(c);
        else{
            int close_idx = closed_list.find(c);
            if(close_idx != -1){
                char expected_char = open_list[close_idx]; //get the corresponding open delimiter
                
                char open_char;
                if(stack.empty()) {
                    cout << "Delimiters are imbalanced";
                    return;
                }
                else open_char = stack.pop();
                
                if(expected_char != open_char){
                    matched = false;
                    break;
                }
            }
            //other than Delimiters (number, operator): do not take any action! 
        }
    }
    if(!stack.empty()) matched = false;

    if(matched) cout << "Delimiters are balanced";
    else cout << "Delimiters are imbalanced";
}

/*
 Write a program that:
 * reads in a positive integer and 
 * prints the binary representation of that integer. 
 * 
 * Hint:  divide the integer by 2.
 */

void toBinary(int dec){
    Stack<char> stack;
    int counter =0;
    while(dec > 0){ //when dec = 0: the body of while-loop will be processed or not???
        char bit = (char)('0' + (dec % 2)); //num2char: possible results: 0, 1
        if(counter >= 4){ stack.push('.'); counter =0; }
        stack.push(bit);
        dec = dec/2; //
        counter++;
    }
    
    //stacK
    while(!stack.empty()){
        char bit = stack.pop();            
        cout << bit;
    }
    cout << endl;
}
#endif /* STACKNQUEUE_H */

