#include<iostream>
#include<time.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<cmath>

using namespace cv;
using namespace std;
int hl=0,hh=0,sl=0,sh=0,vl=0,vh=0;
Point trackhand(Mat image);
Point getnewsnitchposition(Point oldpos,double heading,Point dxy,Size imsize);
int runradius = 60;
double handheading;
int diffx,diffy;
int hx=340,hy = 240;
double abs_distance(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main()
{
    Size imsize;
   //  srand(time(NULL));
    //int ballspeed = 10;
    Point snitch = Point(70,70);
    Point dapp;
    Point snitchtarget=snitch,snitcherr;
    int snitchspeed = 10;
    int radius = 6;
    Point hand;//,prevhand,dhand;
    vector<float> angles;
    namedWindow("Original");
  //  namedWindow("Snitch");
    VideoCapture cam(0);
    namedWindow("Track");
    createTrackbar("HL","Track",&hl,255);
    createTrackbar("HH","Track",&hh,255);
    createTrackbar("SL","Track",&sl,255);
    createTrackbar("SH","Track",&sh,255);
    createTrackbar("VL","Track",&vl,255);
    createTrackbar("VH","Track",&vh,255);
    createTrackbar("Handx","Track",&hx,640);
    createTrackbar("Handy","Track",&hy,480);
    //for(int i=0;i<numangles;i++)
    //{
    //    angles.push_back();
    //}
    if(cam.isOpened() == false)
    {
        cout << "Camera not found" << endl;
        return 0;
    }
    Mat orig,ballim;
    if(!cam.read(orig))
    {

        cout << "No frame read" << endl;
        return 0;
    }
    imsize = orig.size();
 //   prevhand = trackhand(orig);

    while(1)
    {
        if(!cam.read(orig))
        {
            cout << "No fram read" << endl;
            break;
        }
        hand = trackhand(orig); // make this function - using crosshairs now
        ballim = orig.clone();
        circle(ballim,snitch,10,Scalar(255,0,0),-1);
        circle(ballim,snitch,runradius,Scalar(0,255,0),2);
        line(ballim,Point(hx,0),Point(hx,480),Scalar(0,255,255),1);
        line(ballim,Point(0,hy),Point(640,hy),Scalar(0,255,255),1);
   //     diffx = hand.x - snitch.x;                                 - Probably not needed
   //     diffy = hand.y - snitch.y;
   //     dhand = Point((hand.x -prevhand.x),(hand.y - prevhand.y));
      //  handheading = atan(dhand.y/dhand.x);
        //prevhand = hand;
        if(abs_distance(snitch,hand)<runradius)
        {

            dapp = Point((hand.x -snitch.x),(hand.y - snitch.y));
            if(dapp.x !=0)
                handheading = atan(dapp.y/dapp.x);
            else
                handheading = signbit(dapp.y)*1.57;

            snitch = getnewsnitchposition(snitch,handheading,dapp,imsize);
            //cout << "here" << endl;
        }
        //else - generate new snitch target with a timer and random generator

     /*   snitcherr.x = snitchtarget.x-snitch.x;
        snitcherr.y = snitchtarget.y-snitch.y;
        cout << "Targeterror" << snitcherr << endl;
        if(abs(snitcherr.x) > radius || abs(snitcherr.y) > radius) // how dafuq to fix dis shit
        {
            int div = abs(snitcherr.y/snitcherr.x);
            snitch.x += (-2*signbit(snitcherr.x)+1)*snitchspeed*cos(atan(div));
            snitch.y += (-2*signbit(snitcherr.y)+1)*snitchspeed*sin(atan(div));
        }*/

        imshow("Original",orig);
        imshow("Snitch",ballim);
        //if(waitKey(10) == 27)
          //      break;
        waitKey(10);
    }
return 0;
}
Point trackhand(Mat image)
{
    return Point(hx,hy);
}
Point getnewsnitchposition(Point oldpos,double heading,Point dxy,Size imsize)
{
    //Point newpos;
    int newx = oldpos.x -dxy.x;//- runradius*cos(heading); ---  why this sin cos no works correctly have to figure out
    int newy = oldpos.y -dxy.y;//- runradius*sin(heading);
    cout << newx << " " << newy << endl;
    if(newx<0)
        newx = imsize.width+newx;
    cout << imsize.width;
    newx = newx%(imsize.width);
    if(newy<0)
        newy = imsize.height+newy;
    newy = newy%(imsize.height);
    cout << "Value is " << newx <<  " " << newy << endl; 
     return Point(newx,newy);
}

