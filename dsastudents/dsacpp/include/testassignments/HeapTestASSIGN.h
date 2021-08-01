/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HeapTestASSIGN.h
 * Author: ltsach
 *
 * Created on July 8, 2021, 5:24 PM
 */

#ifndef HEAPTESTASSIGN_H
#define HEAPTESTASSIGN_H
#include "testassignments/commons.h"


string heap_kind(string filename){
    string name_woext = filename.substr(0, filename.rfind('.'));
    string kind = name_woext.substr(name_woext.rfind('_') + 1);
    return kind;
}
int item_removed(string colname){
    string val = colname.substr(colname.rfind('_') + 1);
    stringstream stream(val);
    int item; stream >> item;
    return item;
}

void heap_heapify(Heap<int> *heap, vector<string>& items){
    int *items_ = new int[items.size()];
    int count = 0;
    for(auto dit=items.begin(); dit != items.end(); dit++){
        string item = trimstring(*dit);
        if(item == "None") break;
        stringstream stream(item);
        int iitem; stream >> iitem;
        items_[count++] = iitem;
    }
    heap->heapify(items_, count);
    delete []items_;
}

void heap_push(Heap<int> *heap, vector<string>& items){
    for(auto dit=items.begin(); dit != items.end(); dit++){
        string item = trimstring(*dit);
        if(item == "None") break;
        stringstream stream(item);
        int iitem; stream >> iitem;
        heap->push(iitem);
    }
}


int countValid(vector<string>& items){
    int count = 0;
    for(auto dit=items.begin(); dit != items.end(); dit++){
        string item = trimstring(*dit);
        if(item == "None") break;
        count += 1;
    }
    return count;
}
vector<int> heap_data(Heap<int> *heap){
    vector<int> data;
    Heap<int>::Iterator it;
    for(it = heap->begin(); it != heap->end(); it++)
        data.push_back(*it);
    return data;
}

bool equals(vector<int> sdata, vector<string>& gt){
    REQUIRE(sdata.size() <= gt.size());
    vector<int>::iterator sit;
    vector<string>::iterator git;
    bool same = true;
    for(sit= sdata.begin(), git=gt.begin(); git != gt.end(); sit++, git++){
        string exp = trimstring(*git);
        if(exp == "None") break;
        
        stringstream stream(exp);
        int gvalue; stream >> gvalue;
        if((sit == sdata.end()) || (gvalue != *sit)){
            same = false;
            break;
        }
    }
    REQUIRE(sit == sdata.end());
    return same;
}

TEST_CASE( "Heap<int>: contruction => size + empty" ) {
    DataFrame master("heap_dat/heap_tests.csv");
    vector<string> filenames = master["filename"];
    for(auto it=filenames.begin(); it != filenames.end(); it++){
        string filename = *it;
        
        string kind = heap_kind(filename);
        Heap<int> *heap = NULL;
        if(kind == "max") heap = new Heap<int>(&max_comparator);
        else if (kind == "min") heap = new Heap<int>(&min_comparator);
        else{
            cout << "heap kind: invalid => quit tests" << endl;
            exit(1);
        }
        
        DataFrame df(filename);
        
        heap_heapify(heap, df["item"]);
        int nvalid;
        nvalid = countValid(df["heapify"]);
        REQUIRE(heap->size() == nvalid);
        REQUIRE(heap->empty() == (nvalid == 0));
        
        heap->clear();
        heap_push(heap, df["item"]);
        nvalid = countValid(df["push"]);
        REQUIRE(heap->size() == nvalid);
        REQUIRE(heap->empty() == (nvalid == 0));
        //
        delete heap;
    }
}
TEST_CASE( "Heap<int>: heapify" ) {
    DataFrame master("heap_dat/heap_tests.csv");
    vector<string> filenames = master["filename"];
    Heap<int> *heap = NULL;
    Heap<int>::Iterator it;
    
    for(auto it=filenames.begin(); it != filenames.end(); it++){
        string filename = *it;
        string kind = heap_kind(filename);
        
        if(kind == "max") heap = new Heap<int>(&max_comparator);
        else if (kind == "min") heap = new Heap<int>(&min_comparator);
        else{
            cout << "heap kind: invalid => quit tests" << endl;
            exit(1);
        }
        
        DataFrame df(filename);
        heap_heapify(heap, df["item"]);
        REQUIRE( equals(heap_data(heap), df["heapify"]) == true);
        
        //
        delete heap;
    }
}

TEST_CASE( "Heap<int>: push" ) {
    DataFrame master("heap_dat/heap_tests.csv");
    vector<string> filenames = master["filename"];
    Heap<int> *heap = NULL;
    Heap<int>::Iterator it;
    
    for(auto it=filenames.begin(); it != filenames.end(); it++){
        string filename = *it;
        string kind = heap_kind(filename);
        
        if(kind == "max") heap = new Heap<int>(&max_comparator);
        else if (kind == "min") heap = new Heap<int>(&min_comparator);
        else{
            cout << "heap kind: invalid => quit tests" << endl;
            exit(1);
        }
        
        DataFrame df(filename);
        heap_push(heap, df["item"]);
        REQUIRE( equals(heap_data(heap), df["push"]) == true);
        
        //
        delete heap;
    }
}


TEST_CASE( "Heap<int>: peek" ) {
    DataFrame master("heap_dat/heap_tests.csv");
    vector<string> filenames = master["filename"];
    Heap<int> *heap = NULL;
    Heap<int>::Iterator it;
    
    for(auto it=filenames.begin(); it != filenames.end(); it++){
        string filename = *it;
        string kind = heap_kind(filename);
        
        if(kind == "max") heap = new Heap<int>(&max_comparator);
        else if (kind == "min") heap = new Heap<int>(&min_comparator);
        else{
            cout << "heap kind: invalid => quit tests" << endl;
            exit(1);
        }
        
        DataFrame df(filename);
        heap_push(heap, df["item"]);
        
        vector<int> peek_list;
        while(!heap->empty()){
            int item = heap->peek();
            peek_list.push_back(item);
            heap->pop();
        }
        REQUIRE( equals(peek_list, df["peek"]) == true);
        //
        delete heap;
    }
}

TEST_CASE( "Heap<int>: pop" ) {
    DataFrame master("heap_dat/heap_tests.csv");
    vector<string> filenames = master["filename"];
    Heap<int> *heap = NULL;
    Heap<int>::Iterator it;
    
    for(auto it=filenames.begin(); it != filenames.end(); it++){
        string filename = *it;
        string kind = heap_kind(filename);
        
        if(kind == "max") heap = new Heap<int>(&max_comparator);
        else if (kind == "min") heap = new Heap<int>(&min_comparator);
        else{
            cout << "heap kind: invalid => quit tests" << endl;
            exit(1);
        }
        
        DataFrame df(filename);
        heap_push(heap, df["item"]);
        
        vector<int> pop_list;
        while(!heap->empty()){
            int item = heap->pop();
            pop_list.push_back(item);
        }
        REQUIRE( equals(pop_list, df["pop"]) == true);
        //
        delete heap;
    }
}

TEST_CASE( "Heap<int>: remove_first_peek" ) {
    DataFrame master("heap_dat/heap_tests.csv");
    vector<string> filenames = master["filename"];
    Heap<int> *heap = NULL;
    Heap<int>::Iterator it;
    
    for(auto it=filenames.begin(); it != filenames.end(); it++){
        string filename = *it;
        string kind = heap_kind(filename);
        
        if(kind == "max") heap = new Heap<int>(&max_comparator);
        else if (kind == "min") heap = new Heap<int>(&min_comparator);
        else{
            cout << "heap kind: invalid => quit tests" << endl;
            exit(1);
        }
        
        DataFrame df(filename);
        heap_push(heap, df["item"]);
        
        vector<int> remove_first_peek_vec;
        while(!heap->empty()){
            int item = heap->peek();
            heap->remove(item);
            if(!heap->empty()){
                int next = heap->peek();
                remove_first_peek_vec.push_back(next);
            }
        }
        REQUIRE( equals(remove_first_peek_vec, df["remove_first_peek"]) == true);
        //
        delete heap;
    }
}

TEST_CASE( "Heap<int>: remove_random" ) {
    DataFrame master("heap_dat/heap_tests.csv");
    vector<string> filenames = master["filename"];
    Heap<int> *heap = NULL;
    Heap<int>::Iterator it;
    
    for(auto it=filenames.begin(); it != filenames.end(); it++){
        string filename = *it;
        string kind = heap_kind(filename);
        
        if(kind == "max") heap = new Heap<int>(&max_comparator);
        else if (kind == "min") heap = new Heap<int>(&min_comparator);
        else{
            cout << "heap kind: invalid => quit tests" << endl;
            exit(1);
        }
        
        DataFrame df(filename);
        
        //
        vector<string> columns = df.get_columns();
        for(auto it= columns.begin(); it != columns.end(); it++){
            //build heap
            heap->clear();
            heap_push(heap, df["item"]);
            
            //remvove
            string colname = *it;
            if(     (colname.find("remove_") != std::string::npos) && 
                    ((colname.find("first_peek") == std::string::npos))){
                int removed = item_removed(colname);
                heap->remove(removed);
                vector<int> sdata = heap_data(heap);
                REQUIRE( equals(sdata, df[colname]) == true);
                
            }
        }
        //
        delete heap;
    }
}

TEST_CASE("Heap<int>: peek with empty heap"){
    Heap<int> heap;
    try{
        heap.peek();
    }
    catch(exception& e){
        REQUIRE(1==1);
    }
}
TEST_CASE("Heap<int>: pop with empty heap"){
    Heap<int> heap;
    try{
        heap.pop();
    }
    catch(exception& e){
        REQUIRE(1==1);
    }
}
TEST_CASE("Heap<int>: contains"){
    Heap<int> heap;
    int items[] = {10, 20, 40, 50, 70};
    int notfounds[] = {15, 25, 45, 55, 75};
    heap.heapify(items, 5);
    for(int found: items) REQUIRE(heap.contains(found) == true);
    for(int notfound: notfounds) REQUIRE(heap.contains(notfound) == false);    
}

TEST_CASE("Heap<int>: polymorphism"){
    IHeap<int>* heap = new Heap<int>();
    int items[] = {10, 20, 40, 50, 70};
    int notfounds[] = {15, 25, 45, 55, 75};
    heap->heapify(items, 5);
    for(int found: items) REQUIRE(heap->contains(found) == true);
    for(int notfound: notfounds) REQUIRE(heap->contains(notfound) == false); 
    delete heap;
}
#endif /* HEAPTESTASSIGN_H */

