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
  public:
      Ron();

};
Ron::Ron()
{

}
void Ron::mood(int outcome)
{

}
void Ron::shakeHand(int handout)
{

}
int Ron::decision()
{
    return rand() % 3 - 1;
}

#endif /* Ron_h */
