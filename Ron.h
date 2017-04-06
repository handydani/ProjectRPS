//
//  Ron.h
//  facetest
//
//  Created by Alejandro Santacoloma on 4/1/17.
//  Copyright © 2017 Alejandro Santacoloma. All rights reserved.
//

#ifndef Ron_h
#define Ron_h
#include <string>
class Ron
{
private:
    std::string mood;
    void show(std::string emotion)
    {
        
    };
    void memory()
    {
        
    };
    void readFile ()
    {
        
    };
    void writeFile ()
    {
        
    };
public:
    Ron();
    int decision ()
    {
        return 0;
    };
    void setMemory ()
    {
        
    };
    
    
    
};
Ron::Ron()
{
    
}
void Ron::show(std::string emotion)
{
    
}
int Ron::decision()
{
    return rand() % 3 - 1;
}

#endif /* Ron_h */
