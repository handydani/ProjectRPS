

#ifndef featureFinder_h
#define featureFinder_h

#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <array>

using namespace cv;
using namespace std;
class featureFinder
{
	private:
	
	
	
	public:
featureFinder();
    
    int horizontalFingerCheck(Mat screen)
    {
        //This code is base on the logic that we are traveling from left to right checking for white or black pixels.
        //a range of 20 pixels of white or more means that we have found a finger
        
        int rowsize = 200;
        int colsize = 120; // a little more than half so that the rest of the palm is ignored
        int numFingers = 0; //possibly delete later
        
        Vec3b RED = screen.at<Vec3b>(Point(0,0));
        RED[0] =   0;
        RED[1] =   0;
        RED[2] = 255;
        
        for(int row = 0; row<200; row++)
        {
            for(int col = 40; col< 70; col++)
            {
                                Vec3b screencolor   = 	screen.at<Vec3b>( col, row);
                                uchar bluescreen 	= 	screencolor.val[0];
                                uchar greenscreen   = 	screencolor.val[1];
                                uchar redscreen 	= 	screencolor.val[2];
                
                if(bluescreen == 255)
                {
                    int whitecount = 0;
                    //for loop to make red markers for debug purposes
                    for(int i = 0; i<15; i++)
                    {
                        for(int j = 0;j<15;j++)
                        {
                            Vec3b screencolor   = 	screen.at<Vec3b>( col, row);
                            uchar bluescreen 	= 	screencolor.val[0];
                            
                            if(bluescreen == 255)
                            {
                                whitecount++;
                            }
                            if (whitecount>150)
                            {
                                numFingers++;
                                row = row + 20;
                                break;
                            }
                            screen.at<Vec3b>(Point(col+i,row+j)) = RED;
                            
                        }
                    }
                    
                }
                
            }
        }
        
//        int numFingers = 0;
//        //go left to right, then next row
//        for(int row = 30; row < rowsize-80; row++)
//        {
//            //for(int col = 10; col < colsize-15; col++)
//            for(int col = 10; col < 70; col++)
//            {
//                Vec3b screencolor   = 	screen.at<Vec3b>( col, row);
//                uchar bluescreen 	= 	screencolor.val[0];
//                uchar greenscreen   = 	screencolor.val[1];
//                uchar redscreen 	= 	screencolor.val[2];
//                
//                int currColor = (int)bluescreen; // color at curr pixel
//                int rangeOfWhite = 0; //
//                
//                while(currColor == 255 && col < colsize)
//                {
//                    
//                    rangeOfWhite++;
//                    if(rangeOfWhite == 30)
//                    {
//                        //for loop to make red markers for debug purposes
//                        for(int i = -5; i<5; i++)
//                        {
//                            for(int j = -5;j<5;j++)
//                            {
//                                screen.at<Vec3b>(Point(col+i,row+j)) = RED;
//                            }
//                        }
//                        numFingers++;
//                        
//                        rangeOfWhite = 0;
//                        
//                        row += 30;
//                        continue;
//                    }
//                    
//                    col++;
//                }
//            }
//        }
        
        imwrite("fingercheck.jpg",screen);
        
        if( numFingers > 4)
        {
            
            cout << "Are you an alien" << endl;
        }
        return numFingers;
        
    }
    
};
featureFinder::featureFinder ()
{

}

#endif /* featureFinder_h */
