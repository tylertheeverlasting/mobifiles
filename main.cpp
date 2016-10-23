#include<iostream>
#include<time.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cmath>

using namespace cv;
using namespace std;

int main()
{
    srand(time(NULL));
    int rvx,rvy;
    int radius = 10;
    rvx = 30;
    rvy = 30;
    int ballspeed = 10;
    Point currcen = Point(rvx,rvy);
    Point target = Point(rvx,rvy);
    Point targeterror;
    namedWindow("Original");
    namedWindow("FLoating ball");
    VideoCapture cam(0);
    if(cam.isOpened() == false)
    {
        cout << "Camera not found" << endl;
        return 0;
    }
    Mat orig,ballim;
    while(1)
    {
        if(!cam.read(orig))
        {
            cout << "No fram read" << endl;
            break;
        }
        ballim = orig.clone();
        circle(ballim,currcen,radius,Scalar(0,0,255),-1);
        targeterror.x = target.x-currcen.x;
        targeterror.y = target.y-currcen.y;
        cout << "Targeterror" << targeterror << endl;
        if(abs(targeterror.x) > radius || abs(targeterror.y) > radius)
        {
            currcen.x += (-2*signbit(targeterror.x)+1)*ballspeed;
            currcen.y += (-2*signbit(targeterror.y)+1)*ballspeed;
        }
        else
        {
            rvx = rand()%(orig.cols-radius)+radius;
            rvy = rand()%(orig.rows-radius)+radius;
            target = Point(rvx,rvy);
            cout << "New target" << target << endl;
        }

        imshow("Original",orig);
        imshow("Floating ball",ballim);
        //if(waitKey(10) == 27)
          //      break;
        waitKey(10);
    }
return 0;
}
