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

int imgtest(String testhand, String userhand)
{
    int rowsize = 200;
    int colsize = 200;
    
    Mat tester = imread(testhand);
    Mat user   = imread(userhand);
    
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
    
//prototype scrren text code
//    if(casetype == 1)
//    {
//        //make 1 appear on screen
//        for (int x = 0; x <50; x++)
//        {
//            for(int y = 0; y < 30; y++)
//            {
//                screen.at<Vec3b>(Point(x,y)) = BLUE;
//            }
//        }
//        
//        for (int x = 30; x < 50; x++)
//        {   for(int y = 30; y < 70; y++)
//            {
//                screen.at<Vec3b>(Point(x,y)) = BLUE;
//            }
//        }
//        for (int x = 0; x <100; x++)
//        {   for(int y = 70; y < 100; y++)
//            {
//                screen.at<Vec3b>(Point(x,y)) = BLUE;
//            }
//        }
//        
//    }//end of first if statement
//    
//    else if(casetype == 2)
//    {
//        //make 1 appear on screen
//        for (int x = 0; x <50; x++)
//        {
//            for(int y = 0; y < 30; y++)
//            {
//                screen.at<Vec3b>(Point(x,y)) = BLUE;
//            }
//        }
//        
//        for (int x = 0; x < 15; x++)
//        {   for(int y = 30; y < 50; y++)
//        {
//            screen.at<Vec3b>(Point(x,y)) = BLUE;
//        }
//        }
//        
//        for (int x = 30; x < 50; x++)
//        {   for(int y = 30; y < 70; y++)
//            {
//                screen.at<Vec3b>(Point(x,y)) = BLUE;
//            }
//        }
//        
//        for (int x = 0; x <100; x++)
//        {   for(int y = 70; y < 100; y++)
//            {
//                screen.at<Vec3b>(Point(x,y)) = BLUE;
//            }
//        }
//        
//    }//end of second if statement
    
    //end of function
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




int main(int, char**)
{
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
    for(int i = 0; i <143; i++)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame); //frame is a 640 by 480 pixel image
        // check if we succeeded
       
        int errorcount = 0;
        if(errorcount >9)
        {
        cout<<"serror timeout";
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
        // total loop is 4.29 seconds
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
                cout <<"made it this far\n";
                imwrite("imtest1.jpg", frame);
                
                //Rect myROI(200, 200, 200, 200);
                Rect myROI(200, 200, 200, 200);

                cropframe = frame(myROI);
                
                imwrite("imtestcrop.jpg", cropframe);
                
                //frame.deallocate();
                destroyAllWindows();
                cap.release();
                
                break;
            }
            catch(...)
            {
                cout << "An exception occured\n";
                break;
            }
            
            
        }
        
    

        // show live and wait for a key with timeout long enough to show images
        imshow("RPS! Live", frame);
        waitKey(30);
        
}
    // the camera will be deinitialized automatically in VideoCapture destructor
    
    
    //image comparison starts

    
    
    //Image thresholding
    
    //make binary images
    
    //pixel diff checker
    
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
//        "rock0.jpg",    "rock1.jpg",    "rock2.jpg",                                //0->2   case 0
//        "paper0.jpg",   "paper1.jpg",   "paper2.jpg" , "paper3.jpg","paper4.jpg",   //3->7   case 1
//        "scissor0.jpg", "scissor1.jpg", "scissor2.jpg",                             //8->10  case 2
//        "mid0.jpg",     "mid1.jpg",     "mid2.jpg", "mid3.jpg",                     //11->14 case 3
//        "high0.jpg",    "high1.jpg",    "high2.jpg",                                //15->17 case 4
//        "blank.jpg"                                                                 //18->18 case 5
//        
//    };
    
    int testtype = -1;
    int result = -1;
    int bestresult =10000000;
    
    //be sure to change ii depending on which matrix is used
    for(int ii = 0; ii < range; ii++){
        
    string ufile = "binarytest.jpg";
    
//    string tfile = "rock0.jpg";
    string tfile = namelist[ii];
    result = imgtest(tfile, ufile);
        
    if(result<bestresult)
    {
        bestresult = result;
        testtype = ii;//stores which scenario is best
    }
    
    }
    
  //  string handname [5] = {"rock", "paper", "scissors", "mid","flip"};
    
    double certain = 100 - (bestresult/40000.0)*100;
    
    cout<<"best hand was "<< namelist[testtype] <<"I am "<<certain<< "% sure"<<"\n";
    
    string handoptions[6] = {"rock", "paper", "scissors","flip off","high-five","blank"};
    
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
    int computerDecision = rand() % 3 - 1;
    {
    cout << "The computer throws " << handoptions[computerDecision] << "\nUser threw "<< handoptions[userhand] << endl;
    }
    
    //game logic
    if(userhand == 0 && computerDecision == 2  )
    {
        uwin = 0;
    }
    else if(userhand == 1 && computerDecision == 0  )
    {
        uwin = 0;
    }
    else if(userhand == 2 && computerDecision == 1 )
    {
        uwin = 0;
    }
    else if(userhand == computerDecision)
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
    
    //output logic
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
        cout<<"... Did you just flip me off?\n";
        cout<<"not cool dude\n";
        
    }/Users/julianjulian/Documents/CODE/XCODEC++/facetest copy/facetest/main.cpp
    else if (uwin == 4)
    {   //randomly generate options to say for easter eggs
        cout<<"Stop trying to high five me and lets play dude\n";
        cout<<"If I wanted to be your friend I would have asked by now, stop high fiving me and lets play\n";
        cout<<"Not sure whether you just tried to badly cover the camera or if you tried to high five me...\n"<<"either way, stop it!";
        
    }
    else if (uwin == 5)
    {
        cout<<"... Did you even try?\n";
        
    }
    
    cout<<"made it to the end of program\n";
    return 0;
}


