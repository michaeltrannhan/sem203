#include <iostream>
#include <hash/IMap.h>
#include <hash/XHashMap.h>
#include <hash/XHashMapDemo.h>
using namespace std;

int hash_code(int& key, int size){
    return abs(key) % size;
}

int main(){
    // XHashMap<int, int> map(&XHashMap<int, int>::simpleHash);
    // int keys[]      = {2,  12, 42,  72, 3,  45, 76, 30};
    //     int values[]    = {35, 67, 100, 23, 68, 68, 72, 45};
    //     for(int idx=0; idx < 8; idx++){
    //         map.put(keys[idx], values[idx]);
    //     }
    //     map.remove(2);
    //     map.println();
    //     //
    //     /*
    //     for(int idx=0; idx < 8; idx++){
    //         cout << " contains key" << map.containsKey(keys[idx]) << endl;
    //         cout << " contains value " << map.containsValue(values[idx]) << endl;
    //     }
        
    //     cout << "contains key" << map.containsKey(1000) << endl;
    //     cout << "contains value" << map.containsValue(1000) << endl;
    //     */

    XHashMap<int, int> map(&hash_code);
    
    int nsizes = 5;
    int sizes[] = {10, 50, 100, 1000, 10000};
    for(int sidx=0; sidx < nsizes; sidx++){
        int size = sizes[sidx];
        for(int kidx=0; kidx < 2*size; kidx++){
            int key = kidx % size;
            int value = key*( 1 + kidx/size); //[value-1st: key; value-2nd: 2*key]
            map.put(key, value);
        }
        //map.println();
        
        //remove a half number of keys
        int nremoved = size/2;
        cout << "is at idx" << sidx << "---------" << endl;
        for(int key=0; key < nremoved; key++){
            if(key == 0){
                map.remove(key, key);
                // REQUIRE(map.containsKey(key) == false);
                // REQUIRE(map.containsValue(2*key) == false);
            }
            else{
                map.remove(key, key);
                cout << map.containsKey(key) <<endl;
               //REQUIRE(map.containsKey(key) == true);
                //cout << map.containsValue(2*key) << endl;
                //REQUIRE(map.containsValue(2*key) == true);
                map.remove(key, 2*key);
                // REQUIRE(map.containsKey(key) == false);
                // REQUIRE(map.containsValue(2*key) == false);
            }
        }
        //test found for remaining keys
        for(int key=nremoved; key < size; key++){
            // REQUIRE(map.containsKey(key) == true);
            // REQUIRE(map.containsValue(2*key) == true);
        }
    }
}