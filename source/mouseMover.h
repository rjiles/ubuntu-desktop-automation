#include <tuple>

namespace mm
{
    class mouseMover
    {
    public:
        std::tuple<int, int> getMousePosition();
        void move_mouse(int, int);
        void bezier(int, int, int, int);
        int binomialCoefficients(int, int);
        int nPr(int, int);
        int nCr(int, int);
        int fact(int);
    };

}