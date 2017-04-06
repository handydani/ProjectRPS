//
//  Memory.h
//  facetest
//
//  Created by Alejandro Santacoloma on 4/1/17.
//  Copyright © 2017 Alejandro Santacoloma. All rights reserved.
//

#ifndef Memory_h
#define Memory_h
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
using namespace std;
class Memory{
private:
    int readFile(){
        
    };
    void writeFile(int result){
        
    };
    
public:
    Memory();
    int getPWins(int[] file){
        
    };
    int getRonWins(int[] file){
        
    };
    int getPLosses(int[] file){
        
    };
    int getRonLosses(int[] file){
        
    };
    int getTies(int[] file){
        
    };
    string getRecord(int [] file){
        
    };
    
};
Memory::Memory(){
    int[] file;
    readFile();
    
}
int::readFile(){
    int i = 0;
    ifstream inFile("FILE.txt");
    if (inFile.is_open())
    {
        while ( getline (inFile,line) )
        {
            i++;
            cout << line << '\n';
        }
        myfile.close();
    }

}
void::writeFile(int result){
    ofstream filo;
    filo.open( "FILE.txt");
    if(filo.is_open()){
    filo << result;
    filo.close();
    }
}
int::getPWins(int[] file){
    int wins = 0;
    int i = 0;
    while( i < file.length){
        if(file[i] = 1){
            wins++;
        }
    }
    return wins;
}
int::getRonWins(int[] file){
    int wins = 0;
    int i = 0;
    while( i < file.length){
        if(file[i] = 2){
            wins++;
        }
    }
    return wins;
}
int::getPLosses(int[] file){
    return getRonWins(file);
}
int::getRonLosses(int[] file){
    return getPWins(file);
}
int::getTies(int[] files){
    int ties = 0;
    int i = 0;
    while( i < file.length){
        if(file[i] = 2){
            ties++;
        }
    }
    return ties;
}
string::getRecord(int [] file){
    string s;
    s << getWins << " - " << getLosses;
    return s;
}
#endif /* Memory_h */
