 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include <iostream>
 #include <stdio.h>

/*
using namespace cimg_library;
 using namespace std;
 using namespace cv;


int main()
{

CascadeClassifier face_cascade;
CascadeClassifier eye_cascade; 
	
face_cascade.CascadeClassifier('/Users/jibrankhan/Desktop/DSA/opencv-2.4.9/data/haarcascades/haarcascade_frontalface_default.xml')
eye_cascade.CascadeClassifier('/Users/jibrankhan/Desktop/DSA/opencv-2.4.9/data/haarcascades/haarcascade_eye.xml')
IplImage* image=(cvLoadImage("brett.jpeg");

//CImg<unsigned char> img("brett.jpeg");
//img = imread('brett.jpeg')
gray=cvtColor(img, cv2.COLOR_BGR2GRAY);

faces = face_cascade.detectMultiScale(gray, 1.3, 5)
for (x,y,w,h) in faces:
    //cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
    rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
    roi_gray = gray[y:y+h, x:x+w]
    roi_color = img[y:y+h, x:x+w]
    eyes = eye_cascade.detectMultiScale(roi_gray)
    for (ex,ey,ew,eh) in eyes:
        cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)

cv2.imshow('img',img)
cv2.waitKey(0)
cv2.destroyAllWindows()

return 0;
}
*/

#include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

 #include <iostream>
 #include <stdio.h>

 using namespace std;
 using namespace cv;



 /** Function Headers */
 void detectAndDisplay( Mat frame );

 /** Global variables */
 String face_cascade_name = "/Users/jibrankhan/Desktop/DSA/opencv-2.4.9/data/haarcascades/haarcascade_frontalface_alt.xml";
 String eyes_cascade_name = "/Users/jibrankhan/Desktop/DSA/opencv-2.4.9/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);

 /** @function main */
 int main( int argc, const char** argv )
 {
   //CvCapture* capture;
   IplImage* img=cvLoadImage("group.png",1);
   Mat frame(img);

   //-- 1. Load the cascades
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

   //-- 2. Read the video stream
   //capture = cvCaptureFromCAM( -1 );
   //if( capture )
   //{
     //while( true )
     //{
       
       //frame = cvQueryFrame( capture );

   //-- 3. Apply the classifier to the frame
       if( !frame.empty() )
       { detectAndDisplay( frame ); }
       else
       { printf(" --(!) No captured frame -- Break!");  }

       
      cvWaitKey(0);
   
   return 0;
 }

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(1,1) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    
    Point pt1(faces[i].x,faces[i].y);
    Point pt2(faces[i].x+faces[i].width,faces[i].y+faces[i].height);
    rectangle( frame, pt1, pt2, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );
    std::vector<Rect> eyes;

    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(1, 1) );
    
    



    
    for( size_t j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
     }

     
  }
  //-- Show what you got
  imshow( window_name, frame);

 }