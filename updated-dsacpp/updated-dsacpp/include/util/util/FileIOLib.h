/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileIOLib.h
 * Author: ltsach
 *
 * Created on July 1, 2021, 8:05 AM
 */

#ifndef FILEIOLIB_H
#define FILEIOLIB_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <math.h>

using namespace std;

class DataFrame{
private:
    unordered_map<string, vector<string> > map;
    vector<string> columns;
    int m_nrows;
  
public:
    DataFrame(){
        m_nrows = 0;
    }
    DataFrame(string filename, char delimiter=','){
        m_nrows = 0;
        read(filename, delimiter);
    }
    DataFrame(const DataFrame& frame){
        for(auto it=frame.map.begin(); it != frame.map.end(); it++){
            this->map.insert({it->first, it->second});
        }
        this->columns = frame.columns;
        this->m_nrows = frame.m_nrows;
    }
    DataFrame& operator=(const DataFrame& frame){
        for(auto it=frame.map.begin(); it != frame.map.end(); it++){
            this->map.insert({it->first, it->second});
        }
        this->columns = frame.columns;
        this->m_nrows = frame.m_nrows;
        return *this;
    }
    
    ~DataFrame(){}
    
    int nrows(){
        return m_nrows;
    }
    int ncols(){
        return map.size();
    }
    
    void add(string col_name, vector<string>& col_data){
        columns.push_back(col_name);
        m_nrows = max(m_nrows, (int)col_data.size());
        this->map.insert({col_name, vector<string>(col_data)});
    }
    //
    vector<string>& operator[](string col_name){
        return this->map[col_name];
    }
    vector<string> get_columns(){
        return this->columns;
    }
    void read(string filename, char delimiter=','){
        //open stream
        ifstream datastream(filename);
        if(!datastream.is_open()){
            cerr << filename << ": couldn't open for reading" << endl;
        }
        //read header
        read_header(datastream, delimiter);
                
        //read lines
        string line;
        while(getline(datastream, line)){
            //parse line
            istringstream linestream(line);
            string item;
            int col_idx = 0;
            while(getline(linestream, item, delimiter)){
                string col_name = columns[col_idx];
                this->map[col_name].push_back(item);
                col_idx += 1;
            }
        }
        
        //close stream
        datastream.close();
    }
    void write(string filename, char delimiter=','){
        //open stream
        ofstream datastream(filename);
        if(!datastream.is_open()){
            cerr << filename << ": couldn't open for writing" << endl;
        }
        //write header
        write_header(datastream, delimiter);
        
        //write lines
        int _nrows = nrows();
        int _ncols = ncols();
        for(int rowIdx=0; rowIdx < _nrows; rowIdx++){
            for(int colIdx=0; colIdx < _ncols - 1; colIdx++){
                string col_name = columns[colIdx];
                if(rowIdx > this->map[col_name].size() - 1)
                    datastream << "None" << delimiter << " ";
                else
                    datastream << this->map[col_name][rowIdx] << delimiter << " ";
            }
            if(_ncols > 0){
                string col_name = columns[_ncols - 1];
                if(rowIdx > this->map[col_name].size() - 1)
                    datastream << "None" << endl;
                else
                    datastream << this->map[col_name][rowIdx] << endl;
            }
        }
        
        //close stream
        datastream.close();
    }
    
private:
    void read_header(ifstream& datastream, char delimiter=','){
        string line;
        if(getline(datastream, line)){
            //parse line
            istringstream linestream(line);
            string col;
            while(getline(linestream, col, delimiter)){
                this->columns.push_back(col);
                this->map[col] = vector<string>();
            }
        }
    }
    void write_header(ofstream& datastream, char delimiter=','){
        for(int cidx=0; cidx < this->columns.size() - 1; cidx++)
            datastream << this->columns[cidx] << delimiter;
        if(this->columns.size() > 0)
            datastream << this->columns[this->columns.size() - 1] << endl;
    }
};

#endif /* FILEIOLIB_H */

