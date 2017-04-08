//Main program to run rockpaper scissor program using opencv files
//program utilizes image thresholding and image processing
//to identify hand signs thrown by user


#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <array>
#include "Ron.h"
#include "featureFinder.h"
#include <time.h>
#include <ctime>
#include <vector>

using namespace cv;
using namespace std;




//functions

//threshold function, generates binary images of photos taken by camera
void thresh(string basename, string handname)
{
    int rowsize = 200;
    int colsize = 200;
    Mat base = imread(basename);
    Mat hand = imread(handname);


    Mat binimg(200,200, CV_8UC3, Scalar(0,0,0));

    for(int row = 0; row < rowsize; row++)
    {
        for(int col = 0; col < colsize; col++)
        {
            Vec3b handcolor = 	hand.at<Vec3b>( col, row);
            uchar bluehand 	= 	handcolor.val[0];
            uchar greenhand = 	handcolor.val[1];
            uchar redhand 	= 	handcolor.val[2];

            Vec3b basecolor = 	base.at<Vec3b>( col, row);
            uchar bluebase 	= 	basecolor.val[0];
            uchar greenbase = 	basecolor.val[1];
            uchar redbase 	= 	basecolor.val[2];

            //STE COLORS
            Vec3b WHITE = binimg.at<Vec3b>(Point(col,row));
            WHITE[0] = 255;
            WHITE[1] = 255;
            WHITE[2] = 255;

            Vec3b BLACK = binimg.at<Vec3b>(Point(col,row));
            BLACK[0] = 0;
            BLACK[1] = 0;
            BLACK[2] = 0;


            int imgdiff1 = abs(bluehand - bluebase);
            int imgdiff2 = abs(greenhand - greenbase);
            int imgdiff3 = abs(redhand - redbase);


            int limit = 50; //threshold limit 35 good when && was used in if statement, but orange shirt problem occured


            //check diff in pixel spot of image
            if( imgdiff1 > limit || imgdiff2 > limit || imgdiff3 > limit)
            {

                //makes pixel white if doesn't match bachground
                binimg.at<Vec3b>(Point(row,col)) = WHITE;

            }
            else
            {
                //makes pixel black if pixel mathced background
                binimg.at<Vec3b>(Point(row,col)) = BLACK;
            }
            if(row == 199 && col == 199)
            {
                imwrite("binarytest.jpg", binimg);
            }

        }
    }


}



//image compare function, compares photo taken of user's hand to test photos in computer memory

int imgtest(String testhand, String userhand, bool righthand)
{
    int rowsize = 200;
    int colsize = 200;

    Mat tester = imread(testhand);
    Mat user   = imread(userhand);

    if(righthand == false)
    {
    flip(user, user, 1);//flip user hand so it looks right handed for image compare
    }

    int diffcount = 0;
    for(int row = 0; row < rowsize; row++)
    {
        for(int col = 0; col < colsize; col++)
        {
            Vec3b binimgcolor   = 	user.at<Vec3b>( col, row);
            uchar bluebinimg 	= 	binimgcolor.val[0];

            Vec3b testercolor   = 	tester.at<Vec3b>( col, row);
            uchar bluetester 	= 	testercolor.val[0];

            //STE COLORS


            int imgdiff = abs(bluetester - bluebinimg);

            int limit    = 35; //threshold limit

            //check diff in pixel spot of image
            if( imgdiff > limit )
            {
                diffcount++;

            }
        }
    }
    cout << "pixel difference against "<< testhand << " is "<<diffcount<< " pixels\n";
    return diffcount;
}

// function to make simple block configuration that together make lcd characters
// each block is fits in a 50 by 50 pixel square, total character is 50 by 100 pixels
//vertical block
void Vertblock(Mat screen, int startx, int starty)
{
    Vec3b BLUE = screen.at<Vec3b>(Point(0,0));
    BLUE[0] = 255;
    BLUE[1] = 0;
    BLUE[2] = 0;

    int size = 50;
    int i = 5;
    //for loop to make top tip
    for (int y = starty; y < starty + 5; y++)
    {

        for(int x = startx + i; x < startx  + (size/5); x++)
        {
            screen.at<Vec3b>(Point(x,y)) = BLUE;
        }
        i--;
    }

    //for loop to make base
    for (int x = startx; x < startx  + (size/5); x++)
    {
        for(int y = starty + 5; y < starty + size - 5; y++)
        {
            screen.at<Vec3b>(Point(x,y)) = BLUE;
        }
    }

    //for loop to make bottom tip
    i = 5;

    for (int y = starty+size; y >= starty+size - 5; y--)
    {
        for(int x = startx + i; x < startx + (size/5); x++)
        {
            screen.at<Vec3b>(Point(x,y)) = BLUE;
        }
        i--;
    }


}

//horizontal block
void Horiblock(Mat screen, int startx, int starty)
{

    Vec3b BLUE = screen.at<Vec3b>(Point(0,0));
    BLUE[0] = 255;
    BLUE[1] = 0;
    BLUE[2] = 0;

    int size = 50;

    //for loop to make left tip
    int i = 0;
    for (int x = startx ; x <= startx + 5; x++)
    {

        for(int y = starty; y < starty  + i; y++)
        {
            screen.at<Vec3b>(Point(x,y)) = BLUE;
        }
        i+=2;
    }



    // for loop to make base block
    for (int x = startx + 5; x < startx  + size - 5; x++)
    {
        for(int y = starty; y < starty + (size/5); y++)
        {
            screen.at<Vec3b>(Point(x,y)) = BLUE;
        }
    }

    //for loop to make right tip
    i = 0;
    for (int x = startx + size ; x >= startx+ size - 5; x--)
    {

        for(int y = starty; y < starty  + i; y++)
        {
            screen.at<Vec3b>(Point(x,y)) = BLUE;
        }
        i+=2;
    }


}

//text on screen function
void screentext(Mat screen, int casetype)
{
    Vec3b BLUE = screen.at<Vec3b>(Point(0,0));
    BLUE[0] = 255;
    BLUE[1] = 0;
    BLUE[2] = 0;

    //int row = 0;
    //int col = 0;
    //int rowlim = 20;
    //int collim = 20;
    //all characters are 30 by 30 pixels in size

    //timer numbers are in upper left part of screen (0,0) and are 50 by 50 pixels
    //100 by 100?


    if(casetype == 1)
    {
        Vertblock(screen, 40,  0);
        Vertblock(screen, 40, 50);
    }
    else if(casetype == 2)
    {
        Horiblock(screen,  0,   0);
        Horiblock(screen,  0,  50);
        Horiblock(screen,  0, 100);
        Vertblock(screen, 40,   0);
        Vertblock(screen,  0,  50);
    }
    else if(casetype == 3)
    {
        Horiblock(screen,  0,   0);
        Horiblock(screen,  0,  50);
        Horiblock(screen,  0, 100);
        Vertblock(screen, 40,   0);
        Vertblock(screen, 40,  50);
    }
    else if(casetype == 0)
    {
        Horiblock(screen,  0,   0);
        Horiblock(screen,  0, 100);
        Vertblock(screen, 40,   0);
        Vertblock(screen, 40,  50);
        Vertblock(screen, 0,   0);
        Vertblock(screen, 0,  50);
    }

    //end of function
}

//Method to find centroid of hand in binary image
void findcentroid(string filename)
{

    int rowsize = 200;
    int colsize = 200;
    Mat image = imread(filename);

    //STE COLORS
    Vec3b WHITE = image.at<Vec3b>(Point(0,0));
    WHITE[0] = 255;
    WHITE[1] = 255;
    WHITE[2] = 255;

    Vec3b BLACK = image.at<Vec3b>(Point(0,0));
    BLACK[0] = 0;
    BLACK[1] = 0;
    BLACK[2] = 0;

    //make a vector for rows

    //make avector for cols

    int rowcount;
    int rowavg = 0;

    int colcount = 0;
    int colavg = 0;

    for(int row = 0; row < rowsize; row++)
    {
        for(int col = 0; col < colsize; col++)
        {
            Vec3b basecolor = 	image.at<Vec3b>( col, row);
            uchar bluebase 	= 	basecolor.val[0];
            uchar greenbase = 	basecolor.val[1];
            uchar redbase 	= 	basecolor.val[2];



            if(bluebase == 255)
            {



            }

        }
    }

}



void waitgo(Mat screen,int xstart,int ystart, bool go)
{
    Vec3b GREEN = screen.at<Vec3b>(Point(0,0));
    GREEN[0] = 0;
    GREEN[1] = 255;
    GREEN[2] = 0;

    Vec3b RED = screen.at<Vec3b>(Point(0,0));
    RED[0] = 0;
    RED[1] = 0;
    RED[2] = 255;

    if(go == true)
    {
        for(int x = xstart; x<= xstart + 100; x++)
        {
            for(int y = ystart; y <= ystart + 100; y++)
            {
                screen.at<Vec3b>(Point(x,y)) = GREEN;
            }
        }
    }
    else if(go != true)
    {
        for(int x = xstart; x<= xstart + 100; x++)
        {
            for(int y = ystart; y <= ystart + 100; y++)
            {
                screen.at<Vec3b>(Point(x,y)) = RED;
            }
        }
    }



}


// void ronshake(int handout)
// {
//
//
// }


// void ronmood(int outcome)
// {
//
// }


  //                  _
  //  _ __ ___   __ _(_)_ __
  // | '_ ` _ \ / _` | | '_ \
  // | | | | | | (_| | | | | |
  // |_| |_| |_|\__,_|_|_| |_|


int main(int, char**)
{


    bool righthand = false;
    int righttest;

    cout<<"are you left handed or right handed? type 0 for left, anything else for right\n";
    cin>>righttest;

    if(righttest != 0)
    {
        righthand = true;
    }


    //Ron Ron;
    Mat img;
    int w = 800;

    // just some valid rectangle arguments
    int x = 0;
    int y = 0;
    int width = 10;
    int height = 20;
    // our rectangle...
    cv::Rect rect(x, y, width, height);
    // and its top left corner...
    cv::Point pt1(x, y);
    // and its bottom right corner.
    cv::Point pt2(x + width, y + height);
    // These two calls...
    cv::rectangle(img, pt1, pt2, cv::Scalar(0, 255, 0));
    // essentially do the same thing
    cv::rectangle(img, rect, cv::Scalar(0, 255, 0));

    //int rsize = 200;
    //int csize = 200;

    Mat frame;
    Mat cropframe;


    //initialize a window
    //namedWindow("GAME ON", CV_WINDOW_AUTOSIZE);
    //resizeWindow("GAME ON", 400, 400);


    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    // check if we succeeded
    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //int i = 0;

    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
    << "Press any key to terminate" << endl;

    //for (;;)

    //cout<<getBuildInformation();
    int errorcount = 0;
    for(int i = 0; i < 143; i++)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame); //frame is a 640 by 480 pixel image
        // check if we succeeded


        if(errorcount >9)
        {
        cout<<"error timeout";
            return -1;
        }

        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            errorcount++;
            cout<<errorcount<<endl;
            continue;
            //break;
        }
        flip(frame, frame, 1);//flip frame so it is not a mirror


rectangle(frame,
          Point( (w/4)-5, (w/4)-5 ),
          Point( (w/2)+5, (w/2)+5),
          Scalar( 255, 255 - i * 1.78, 255),
          5,
          LINE_8);
        // create a target in the image for user hand
//        rectangle(frame,
//                  Point( 220-5, -5 ),
//                  Point( (w/2)+5, (w/2)+5),
//                  Scalar( 255, 255 - i * 1.78, 255),
//                  5,
//                  LINE_8);


        //if statements for timer
        // every 33 frames is one second
        // total loop is ~ 4.29 seconds
        if(i < 33 )
        {
            waitgo(frame,200,10, false);
        }
        else if(i >= 33 && i < 66)
        {
            screentext(frame,3);
        }
        else if(i >=66 && i < 99)
        {
            screentext(frame,2);
        }
        else if(i >=99 && i < 132)
        {
            screentext(frame,1);
        }
        else if(i >=132)
        {
            screentext(frame,0);
        }


        //if statement to save base image of shirt
        if(i == 32)
        {
            cout <<"getting base image\n";
            imwrite("imtestbase.jpg", frame);

            //Rect myROI(200, 200, 200, 200);
            Rect myROI(200, 200, 200, 200);

            cropframe = frame(myROI);//cropped to 200 by 200 pixel image

            imwrite("imtestbasecrop.jpg", cropframe);

        }

        // if statement to save image of hand
        if(i == 140)
        {
            try
            {
                //cout <<"made it this far\n";
                cout <<"closing camera\n";
                imwrite("imtest.jpg", frame);

                //Rect myROI(200, 200, 200, 200);
                Rect myROI(200, 200, 200, 200);

                cropframe = frame(myROI);

                imwrite("imtestcrop.jpg", cropframe);

                frame.deallocate();
                destroyAllWindows();
                //cap.release();

                break;
            }
            catch(...)
            {
               // cout << "An exception occured\n"; debug comment
                break;
            }


        }

        //maybe try resizing window before showing it,
        //make 1280 by 750? max for mmy mac is 1280by800


        // show live and wait for a key with timeout long enough to show images



        //imshow("RPS! Live", frame);
        //namedWindow("GAME ON", CV_WINDOW_NORMAL||WINDOW_KEEPRATIO);
        //resizeWindow("GAME ON", 1280, 750);
        resize(frame, frame, cv::Size(frame.cols * 1.4,frame.rows * 1.4), 0, 0, CV_INTER_LINEAR);
        imshow("GAME ON", frame);
        waitKey(30);

}
    // the camera will be deinitialized automatically in VideoCapture destructor


    //image comparison starts






    //Image thresholding

    //make binary images

    //pixel diff checker

   // cout<<"Made it to thresh\n"; debug comment


    string basefile = "imtestbasecrop.jpg";
    string handfile = "imtestcrop.jpg";

    thresh(basefile, handfile); //run image threshold of base image and hand thrown image

    //call test image function

    //make an array of strings with names in each index
    int range = 12;
    string namelist [12] = {
                            "rock0.jpg",    "rock1.jpg",    "rock2.jpg",
                            "paper0.jpg",   "paper1.jpg",   "paper2.jpg" ,"paper3.jpg","paper4.jpg",
                            "scissor0.jpg", "scissor1.jpg", "scissor2.jpg",
                            "blank.jpg"
                           };



    //when mid is included, rock and mid get confused,
    //may need to make a finger counter and other feature finder functions

//    int range = 19;
//    string namelist [19] =
//    {
//
//        "rock0.jpg",    "rock1.jpg",    "rock2.jpg",                               //0->2   case 0
//        "paper0.jpg",   "paper1.jpg",   "paper2.jpg" , "paper3.jpg","paper4.jpg",  //3->7   case 1
//        "scissor0.jpg", "scissor1.jpg", "scissor2.jpg",                            //8->10  case 2
//        "blank.jpg",                                                               //11->14 case 3
//        "high0.jpg",    "high1.jpg",    "high2.jpg",                               //15->17 case 4
//        "mid0.jpg",     "mid1.jpg",     "mid2.jpg",   "mid3.jpg",                  //18->18 case 5
//
//    };

    int testtype = -1;
    int result = -1;
    int bestresult =10000000;
    string ufile = "binarytest.jpg";
   // cout<<"Made it to image compare\n";

    //be sure to change ii depending on which matrix is used
    for(int ii = 0; ii < range; ii++)
    {
        //cout<<"Made it to "<<ii<<"\n"; //debug comment
        //string tfile = "rock0.jpg";
        string tfile = namelist[ii];
        result = imgtest(tfile, ufile,righthand);

        if(result<bestresult)
        {
            bestresult = result;
            testtype = ii;//stores which scenario is best
        }

    }

    //cout<<"Made it past image compare \n";



   // cout<<"Made it to feature finder\n";//debug comment


    //feature finder test///////////////////////

//    Mat testimage = imread(ufile);
//
//    featureFinder test = *new featureFinder();
//
//    int r = test.horizontalFingerCheck(testimage);
//
//    cout<<"Featurefinder found this many fingers"<<r<<"\n";
//

    /////////////////////////////




  //  string handname [5] = {"rock", "paper", "scissors", "mid","flip"};

    double certain = 100 - (bestresult/40000.0)*100;

    cout<<"best hand was "<< namelist[testtype] <<"I am "<<certain<< "% sure"<<"\n";

    string handoptions[6] = {"rock", "paper", "scissors","blank","high-five","flip off"};

    int userhand;

    if(testtype <=2)
    {
        userhand = 0;
    }
    else if(testtype <=7 && testtype>=3)
    {
        userhand = 1;

    }
    else if(testtype <=10 && testtype>=8)
    {
        userhand = 2;

    }
    else if(testtype <=14 && testtype>=11)
    {
        userhand = 3;

    }
    else if(testtype <=17 && testtype>=15)
    {
        userhand = 4;

    }
    else if(testtype >=18)
    {
        userhand = 5;

    }


    int uwin;

    //srand(time(NULL));
    srand(righttest);

    int computerdecision = rand() % 3; //Ron.decision();

    //int computerdecision = 2;

    cout << "The computer throws " << handoptions[computerdecision] << "\nUser threw "<< handoptions[userhand] << endl;





    //game logic

    //unwin = 0; then user won
    //unwin = 1; then tie
    //unwin = 2; then user loss
    //unwin = 3; then user flipped the bird
    //unwin = 4; then user gave high five

    if(userhand == 0 && computerdecision == 2  )
    {
        uwin = 0;
    }
    else if(userhand == 1 && computerdecision == 0  )
    {
        uwin = 0;
    }
    else if(userhand == 2 && computerdecision == 1 )
    {
        uwin = 0;
    }
    else if(userhand == computerdecision)
    {
        uwin = 1;
    }
    else if(userhand == 3)
    {
        uwin = 3;
    }
    else if(userhand == 4)
    {
        uwin = 4;
    }
    else
    {
        uwin = 2;
    }


    _____ ____ ___ _____   _        _  _____ _____ ____
   | ____|  _ \_ _|_   _| | |      / \|_   _| ____|  _ \
   |  _| | | | | |  | |   | |     / _ \ | | |  _| | |_) |
   | |___| |_| | |  | |   | |___ / ___ \| | | |___|  _ <
   |_____|____/___| |_|   |_____/_/   \_\_| |_____|_| \_\
    {

      //ron hand animation
      ronshake(computerdecision);

      //ronmood animation
      ronmood(uwin);

    }


//    Mat testimage;
//    testimage = imread("binarytest.jpg");
//    imshow("this is only a test",testimage);
//    waitKey(30);

    //game result logic
    if (uwin == 0)
    {
        cout<<"user wins!\n";
    }
    else if (uwin == 1)
    {
        cout<<"tie!\n";
    }
    else if (uwin == 2)
    {
        cout<<"computer wins!\n";
    }
    else if (uwin == 3)
    {
        cout<<"... Did you even try?\n";

    }
    else if (uwin == 4)
    {
        //randomly generate options to say for easter eggs
        cout<<"Stop trying to high five me and lets play dude\n";
        cout<<"If I wanted to be your friend I would have asked by now, stop high fiving me and lets play\n";
        cout<<"Not sure whether you just tried to badly cover the camera or if you tried to high five me...\n"<<"either way, stop it!";

    }
    else if (uwin == 5)
    {
        cout<<"... Did you just flip me off?\n";
        cout<<"not cool dude\n";

    }

    cout<<"made it to the end of program\n";


    try
    {

        frame.deallocate();
        destroyAllWindows();
        cap.release();
    }
    catch(...)
    {
        // cout << "An exception occured\n"; debug comment
    }


    return 0;
}


    //                  _          __                   _
    //    ___ _ __   __| |   ___  / _|  _ __ ___   __ _(_)_ __
    //   / _ \ '_ \ / _` |  / _ \| |_  | '_ ` _ \ / _` | | '_ \
    //  |  __/ | | | (_| | | (_) |  _| | | | | | | (_| | | | | |
    //   \___|_| |_|\__,_|  \___/|_|   |_| |_| |_|\__,_|_|_| |_|
     //



int featureFinder::horizontalFingerCheck(Mat screen)
{

      //This code is based on the logic that we are traveling from left to right checking for white or black pixels.
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



      imwrite("fingercheck.jpg",screen);

      if( numFingers > 4)
      {

          cout << "Are you an alien" << endl;
      }
      return numFingers;

}
