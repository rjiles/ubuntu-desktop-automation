#include "entityFinder.h" // header in local directory
#include <iostream> // header in standard library
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <vector>

using namespace ef;
using namespace std;
using namespace cv;

bool use_mask;
Mat img; Mat templ; Mat mask; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";
int match_method;
int max_Trackbar = 5;
void MatchingMethod( int, void* );
const char* keys =
"{ help  h| | Print help message. }"
"{ @input1 | Template_Matching_Original_Image.jpg | image_name }"
"{ @input2 | Template_Matching_Template_Image.jpg | template_name }"
"{ @input3 |  | mask_name }";
int entityFinder::find( int argc, char** argv )
{
  CommandLineParser parser( argc, argv, keys );
  samples::addSamplesDataSearchSubDirectory( "../entities/" );
  img = imread( "/home/john/ubuntu-desktop-automation/entities/multi.png" );
  templ = imread( "/home/john/ubuntu-desktop-automation/entities/logo_2.png" );
  if(argc > 3) {
    use_mask = true;
    mask = imread(samples::findFile( parser.get<String>("@input3") ), IMREAD_COLOR );
  }
  if(img.empty() || templ.empty() || (use_mask && mask.empty()))
  {
    cout << img.empty() << endl;
    cout << templ.empty() << endl;
    cout << "Can't read one of the images" << endl;
    return EXIT_FAILURE;
  }
  namedWindow( image_window, WINDOW_AUTOSIZE );
  namedWindow( result_window, WINDOW_AUTOSIZE );
  const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  //createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );
  MatchingMethod( 0, 0 );
  waitKey(0);
  return EXIT_SUCCESS;
}
void entityFinder::MatchingMethod( int, void* )
{
  Mat img_display;
  img.copyTo( img_display );
  int result_cols = img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;
  result.create( result_rows, result_cols, CV_32FC1 );
  bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);
  if (use_mask && method_accepts_mask)
    { matchTemplate( img, templ, result, match_method, mask); }
  else
    { matchTemplate( img, templ, result, match_method); }
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;
  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
  if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  imshow( image_window, img_display );
  imshow( result_window, result );
  return;
}

void ImageFromDisplay(std::vector<uint8_t>& Pixels, int& Width, int& Height, int& BitsPerPixel)
{
    Display* display = XOpenDisplay(nullptr);
    Window root = DefaultRootWindow(display);

    XWindowAttributes attributes = {0};
    XGetWindowAttributes(display, root, &attributes);

    Width = attributes.width;
    Height = attributes.height;

    XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
    BitsPerPixel = img->bits_per_pixel;
    Pixels.resize(Width * Height * 4);

    memcpy(&Pixels[0], img->data, Pixels.size());

    XDestroyImage(img);
    XCloseDisplay(display);
}
