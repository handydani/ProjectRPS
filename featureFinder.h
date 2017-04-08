

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
		public:
			featureFinder();
    	int horizontalFingerCheck(Mat screen);
};

featureFinder::featureFinder ()
{

}

#endif /* featureFinder_h */
