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

using namespace cv;
using namespace std;




//functions

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
            //Vec3b WHITE = (255, 255, 255);
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
            
            
            int limit    = 50; //threshold limit 35 good when && was used in if statement, but orange shirt problem occured
            
            
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
    cout << "pixel difference against "<< testhand << "is "<<diffcount<< " pixels\n";
    return diffcount;
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
    
    int rsize = 200;
    int csize = 200;
    
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
    
   // cout<<getBuildInformation();
    for(int i = 0; i <143; i++)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
       
        
        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            continue;
            //break;
        }
        flip(frame, frame, 1);//flip frame so it is not a mirror

rectangle(frame,
          Point( (w/4)-5, (w/4)-5 ),
          Point( (w/2)+5, (w/2)+5),
          Scalar( 255, 255 - i * 1.78, 255),
          5,
          LINE_8);// create a target in the image for user hand

        //if statement to save base image of shirt
        if(i == 50)
        {
            cout <<"getting base image\n";
            imwrite("imtestbase.jpg", frame);
            
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
    
    
    //call test imag function
    int result = -1;
    int bestresult =10000000;
    string ufile = "binarytest.jpg";
    
    string tfile = "rock0.jpg";
    
    result = imgtest(tfile, ufile);
    
    if(result<bestresult)
    {
        bestresult = result;
    }
    
    
    
    cout<<"made it to the end\n";
    return 0;
}


