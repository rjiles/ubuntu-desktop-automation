#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

namespace ef
{
    class entityFinder
    {
    public:
        int find(int, char**);
        void MatchingMethod( int, void* );
    };

}