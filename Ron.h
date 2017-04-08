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
      void mood(int outcome);
      void shakeHand(int handout);
      int decision();
};
Ron::Ron()
{

}
void Ron::mood(int outcome)
{

      Mat ronface;


      //unwin = 0; then user won
      //unwin = 1; then tie
      //unwin = 2; then user loss
      //unwin = 3; then user flipped the bird
      //unwin = 4; then user gave high five

      if (outcome == 0)
      {

          string mood[7] =
          {
              "sad0.png","sad1.png","sad2.png","sad3.png",
              "sad4.png","sad5.png","sad6.png"
          };

          for(int i = 0; i<7;i++)
          {
              ronface  = imread(mood[i]);
              imshow("RON", ronface);
              waitKey(400);

          }


      }
      else if (outcome == 1)
      {

          string mood[5] =
          {
              "surprised0.png","surprised1.png","surprised2.png",
              "surprised3.png","surprised4.png"
          };

          for(int i = 0; i<5;i++)
          {
              ronface  = imread(mood[i]);
              imshow("RON", ronface);
              waitKey(400);

          }


      }
      else if (outcome == 2)
      {

          string mood[5] =
          {
              "happy0.png","happy1.png","happy2.png",
              "happy3.png","happy4.png"
          };

          for(int i = 0; i<5;i++)
          {
              ronface  = imread(mood[i]);
              imshow("RON", ronface);
              waitKey(400);

          }


      }
      else
      {
      cout<<"More moods in DLC pack1\n";
      }

}
void Ron::shakeHand(int handout)
{
  //set up ron's window

  Mat ronhand;
  namedWindow("RON", CV_WINDOW_NORMAL||WINDOW_KEEPRATIO);
  //ron shakes his hand
  string filename;
  string hands[10] =
  {
      "hand0.png","hand1.png","hand2.png",
      "hand3.png","hand4.png","hand5.png",
      "hand6.png","hand7.png","hand8.png","hand9.png"
  };

  for(int i = 0; i<10;i++)
  {
      ronhand = imread(hands[i]);
      imshow("RON", ronhand);
      waitKey(300);

  }
   string finalhand[3] =
  {
      "ronrock.png","ronpaper.png","ronscissor.png"
  };
  ronhand  = imread(finalhand[handout]);
  imshow("RON", ronhand);
  waitKey(3000);
}
int Ron::decision()
{
    return rand() % 3 - 1;
}

#endif /* Ron_h */
