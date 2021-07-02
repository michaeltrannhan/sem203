/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueueTest.h
 * Author: LTSACH
 *
 * Created on 27 August 2020, 11:18
 */

#ifndef QUEUETEST_H
#define QUEUETEST_H

#include "doctest.h"

#include "stacknqueue/Queue.h"
#include "util/Point.h"
#include "util/ArrayLib.h"
#include "geom/Point3D.h"
#include "geom/Vector3D.h"

TEST_CASE( "Queue<int>:" ) {
    Queue<int> queue;
    REQUIRE(queue.empty() == true);
    REQUIRE(queue.size() == 0);
    
    int item[] = {3, 1, 4, 5, 2, 8, 10, 12};
        //index:  0  1  2  3  4  5  6   7
    for(int idx=0; idx < 8; idx++) queue.push(item[idx]);
    REQUIRE(queue.empty() == false);
    REQUIRE(queue.size() == 8);
    
    SUBCASE("Queue: clear/empty/size"){
        queue.clear();
        REQUIRE(queue.empty() == true);
        REQUIRE(queue.size() == 0);
    }
    SUBCASE("Queue: peek/pop"){
        for(int idx=0; idx < 8; idx++){
            REQUIRE(queue.peek() == item[idx]);
            REQUIRE(queue.pop() == item[idx]);
        }
    }
    SUBCASE("Queue: contains"){
        for(int idx=0; idx < 8; idx++){
            REQUIRE(queue.contains(item[idx]) == true);
            queue.pop();
            REQUIRE(queue.contains(item[idx]) == false);
        }
        REQUIRE(queue.contains(100) == false);
        queue.push(100);
        REQUIRE(queue.contains(100) == true);
    }
    SUBCASE("Queue: remove"){
        REQUIRE(queue.contains(12) == true);
        queue.remove(12);
        REQUIRE(queue.contains(12) == false);
        
        REQUIRE(queue.contains(3) == true);
        queue.remove(3);
        REQUIRE(queue.contains(3) == false);
        
        REQUIRE(queue.contains(5) == true);
        queue.remove(5);
        REQUIRE(queue.contains(5) == false);
    }
    SUBCASE("Queue: iterator for reading"){
        Queue<int>::Iterator it;
        int idx = 0;
        for(it = queue.front(); it != queue.rear(); it++){
            REQUIRE(*it == item[idx++]);
        }
    }
    SUBCASE("Queue: iterator for removing"){
        queue.clear();
        REQUIRE(queue.empty() == true);
        
        for(int idx =0; idx < 10; idx++) queue.push(idx);
        REQUIRE(queue.empty() == false);
        REQUIRE(queue.size() == 10);
        
        Queue<int>::Iterator it;
        for(it = queue.front(); it != queue.rear(); it++){
            if(*it % 2 == 1) it.remove(); //remove odd
        }
        REQUIRE(queue.size() == 5); //from top: 0,2,4,6,8
        
        //check values
        int exp[] = {0,2,4,6,8};
        int idx = 0;
        while(!queue.empty()){
            REQUIRE(queue.pop() == exp[idx]);
            idx += 1;
        }
    }
}
// TEST_CASE("Queue<int>: size+empty+clear") {
//     Queue<int> queue;
    
//     SUBCASE("With empty queue"){
//         REQUIRE(queue.size() == 0);
//         REQUIRE(queue.empty() == true);
//         try{
//             queue.clear();
//             REQUIRE(queue.size() == 0);
//             REQUIRE(queue.empty() == true);
//         }
//         catch(exception& e){ 
//             REQUIRE(1==1);
//         } 
//     }
    
//     SUBCASE("With non-empty queue"){
//         int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
//         for(int idx=0; idx < nsizes; idx++){
//             //making queue empty
//             queue.clear();
//             REQUIRE( queue.size() == 0 );
//             REQUIRE( queue.empty() == true );

//             //pushing items
//             int size = sizes[idx];
//             int* items = genIntArray(size, -500, 500, true, 2021);
//             for(int i=0; i < size; i++) queue.push(items[i]);

//             //enforcing queue size
//             REQUIRE( queue.size() == size );
//             REQUIRE( queue.empty() == ((size == 0) ? true: false));
            
//             //freeing mem
//             delete []items;
//         }
//         delete []sizes;
//     }
// }

// TEST_CASE("Queue<int>: peek + pop: WHEN queue empty"){
//     Queue<int> queue;
//     try{
//         queue.peek();
//     }
//     catch(exception& e){
//         REQUIRE(1==1);
//     }
//     try{
//         queue.pop();
//     }
//     catch(exception& e){
//         REQUIRE(1==1);
//     }
// }

// TEST_CASE("Queue<int>: push+pop+peek") {
//     Queue<int> queue;
    
//     SUBCASE("push->peek+pop"){
//         int* sizes = genIntArray(nsizes, 0, max_length, true, 2021);
//         for(int idx=0; idx < nsizes; idx++){
//             //making queue empty
//             queue.clear();

//             //pushing items
//             int size = sizes[idx];
//             int* items = genIntArray(size, -500, 500, true, 2021);
//             for(int i=0; i < size; i++) queue.push(items[i]);
            
//             for(int i=0; i < size; i++){
//                 REQUIRE(queue.size() == (size-i));
//                 int item = queue.peek();
//                 REQUIRE(item == items[i]);
                
//                 item = queue.pop();
//                 REQUIRE(item == items[i]);
//                 REQUIRE(queue.size() == (size-i-1));
//             }
//             delete []items;
//         }
//         delete []sizes;
//     }
    
//     SUBCASE("push->pop->push->peek+pop"){
//         queue.clear();
//         int half_length = max_length/2;
//         for(int v=0; v < max_length; v++) queue.push(v);
        
//         //push
//         REQUIRE(queue.size() == max_length);
        
//         //pop a half
//         for(int v=0; v < half_length; v++){
//             int item = queue.pop();
//             REQUIRE(item == v);
//         }
//         REQUIRE(queue.size() == half_length);
        
//         //push again
//         for(int v=0; v < half_length; v++) queue.push(max_length + v);
        
//         int item;
//         for(int v=half_length; !queue.empty(); v++, queue.pop()){
//             item = queue.peek();
//             REQUIRE(v == item);
//         }
//     }
// }

// TEST_CASE("Queue<int>: remove"){
//     Queue<int> queue;
    
//     SUBCASE("remove: rear"){
//         queue.clear();
//         for(int v=0; v < max_length; v++) queue.push(v);
//         bool found;
//         for(int v=max_length-1; v >=0; v--){
//             found = queue.remove(v);
//             REQUIRE(found == true);
//             REQUIRE(queue.size() == v);
//         }
//         REQUIRE(queue.empty() == true);
//     }
    
//     SUBCASE("remove: front"){
//         queue.clear();
//         for(int v=0; v < max_length; v++) queue.push(v);
//         bool found;
//         for(int v=0; v < max_length; v++){
//             REQUIRE(queue.peek() == v);
//             found = queue.remove(v);
//             REQUIRE(found == true);
//             REQUIRE(queue.size() == (max_length-v-1));
//         }
//         REQUIRE(queue.empty() == true);
//     }
    
//     SUBCASE("remove: not found"){
//         queue.clear();
//         for(int v=0; v < max_length; v++) queue.push(v);
//         bool found;
//         int items[] = {max_length-500, max_length-400, max_length-300, max_length + 100, max_length + 400};
//         for(int item: items){
//             found = queue.remove(item);
//             REQUIRE(found == false);
//             REQUIRE(queue.size() == max_length);
//         }
//         REQUIRE(queue.empty() == false);
//     }
//     SUBCASE("remove: random item"){
//         queue.clear();
//         //push max_length item
//         for(int v=0; v < max_length; v++) queue.push(v);
        
//         //remove random item
//         int* items = permutation(max_length, true, 2021);
//         bool found;
//         for(int idx =0; idx < max_length; idx++){
//             int item = items[idx];
//             found = queue.remove(item);
//             REQUIRE(found == true);
//             REQUIRE(queue.size() == max_length-1-idx);
//         }
//         REQUIRE(queue.empty() == true);
        
//         delete []items;
//     }
// }

// TEST_CASE("Queue<int>: contains"){
//     Queue<int> queue;
    
//     SUBCASE("with found items"){
//         int* items = permutation(max_length, true, 2021);
//         for(int idx=0; idx < max_length; idx++) queue.push(items[idx]);
//         bool found;
//         for(int idx=0; idx < max_length; idx++){
//             found = queue.contains(items[idx]);
//             REQUIRE(found == true);
//         }
//         delete []items;
//     }
//     SUBCASE("with not found items"){
//         int* items = permutation(max_length, true, 2021);
//         for(int idx=0; idx < max_length; idx++) queue.push(items[idx]);
//         bool found;
//         for(int idx=0; idx < max_length; idx++){
//             found = queue.contains(items[idx] + max_length);
//             REQUIRE(found == false);
//         }
//         delete []items;
//     }
// }

// TEST_CASE("Queue<int>: Iteraror"){
//     Queue<int> queue;
    
//     SUBCASE("iterator -> equality"){
//         int* items = permutation(max_length, true, 2021);
//         for(int idx=0; idx < max_length; idx++) queue.push(items[idx]);
//         Queue<int>::Iterator it;
//         int idx;
//         for(it=queue.front(), idx=0; it != queue.rear(); it++, idx++){
//             REQUIRE(*it == items[idx]);
//         }
//         //
//         delete []items;
//     }
//     SUBCASE("iterator -> remove"){
//         int* items = permutation(max_length, true, 2021);
//         for(int idx=0; idx < max_length; idx++) queue.push(items[idx]);
        
//         Queue<int>::Iterator it;
//         for(int idx=0; idx < max_length; idx++){
//             int item = items[idx];
//             //remove item;
//             it = queue.front();
//             while(it != queue.rear()){
//                 if(*it == item) it.remove();
//                 it++;
//             }
//             //ensure size
//             REQUIRE(queue.size() == max_length - 1 - idx);
//         }
//         REQUIRE(queue.empty() == true);
//         //
//         delete []items;
//     }
// }

// ///Test polymorphism: using stack via pointer to IDeck
// TEST_CASE("IDeck<int>*: stack via ptr to IDeck") {
//     IDeck<int> *pdeck = new Queue<int>();
    
//     //require empty
//     REQUIRE(pdeck->size() == 0);
//     REQUIRE(pdeck->empty() == true);
    
//     //push some
//     for(int v=0; v < max_length; v++) pdeck->push(v);
//     REQUIRE(pdeck->size() == max_length);
    
//     //clear + require empty
//     pdeck->clear();
//     REQUIRE(pdeck->size() == 0);
//     REQUIRE(pdeck->empty() == true);
    
//     //deallocate
//     delete pdeck;
// }
#endif /* QUEUETEST_H */

