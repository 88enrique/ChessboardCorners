/**
    Opencv example code: find corners from a chessboard. Useful for computing homography matrix
    Enrique Marin
    88enrique@gmail.com
*/

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>

#include <stdio.h>

using namespace std;
using namespace cv;

int main(){

    // Variables
    VideoCapture capture;
    Mat frame;

    // Open image source
    capture.open("../Videos/chessboard-1.avi");
    //capture.open(0);
    if (!capture.isOpened()){
        printf("No camera detected\n");
        return -1;
    }

    while (1){

        // Read a frame
        capture.read(frame);

        // Chessboard size
        Size patternsize(9,6); //interior number of corners
        vector<Point2f> corners; //this will be filled by the detected corners

        // Find corners on a chessboard pattern
        bool patternfound = findChessboardCorners(frame, patternsize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);

        // Draw found corners
        drawChessboardCorners(frame, patternsize, Mat(corners), patternfound);

        // Show image
        imshow("ChessboardCorners", frame);

        if ((cvWaitKey(10) & 255) == 27) break;
    }

    // Release memory
    frame.release();

    return 0;
}

