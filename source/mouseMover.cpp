// my_class.cpp
#include "mouseMover.h" // header in local directory
#include <iostream> // header in standard library
#include <unistd.h> // used for execvp command
#include <sstream>
#include <string.h>
#include <cmath>
#include <unistd.h>
#include <cstdio>
#include <memory>
#include <array>
#include <tuple>
#include <string>
#include <regex>

using namespace mm;
using namespace std;

tuple<int, int> mouseMover::getMousePosition() {
    const char* cmd = "xdotool getmouselocation";
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    cout << result << endl;
    std::string pattern("x:([0-9]*) y:([0-9]*)");         // Regex expression
   
    // regex expression for pattern to be searched 
    regex regexp("x:([0-9]+) y:([0-9]+)"); 
   
    // flag type for determining the matching behavior (in this case on string objects)
     smatch m; 
   
    // regex_search that searches pattern regexp in the string mystr  
    regex_search(result, m, regexp); 
  
    cout<<"String that matches the pattern:"<<endl;
    for (auto x : m) 
        cout << x << " ";
        cout << stoi((std::string) m[1]) << endl; 
    return std::make_tuple(stoi((std::string) m[1]), stoi((std::string) m[2]));;
}

void mouseMover::move_mouse(int x, int y)
{
    //cout << "Moving mouse to " << x << ", " << y << endl;
    char xdotool[] = { 'x', 'd', 'o', 't', 'o', 'o', 'l', '\0' }; //getting rid of warnings
    char mousemove[] = { 'm', 'o', 'u', 's', 'e', 'm', 'o', 'v', 'e', '\0' }; //getting rid of warnings
    stringstream strs_x;
    strs_x << x;
    string temp_str_x = strs_x.str();
    char* x_char = (char*) temp_str_x.c_str();
    stringstream strs_y;
    strs_y << y;
    string temp_str_y = strs_y.str();
    char* y_char = (char*) temp_str_y.c_str();
    char* argument_list[] = {xdotool, mousemove, x_char, y_char, NULL}; // NULL terminated array of char* strings

    if (fork() == 0) {
        // Newly spawned child Process. This will be taken over by "ls -l"
        int status_code = execvp(xdotool, argument_list);

        //printf("ls -l has taken control of this child process. This won't execute unless it terminates abnormally!\n");

        if (status_code == -1) {
            //printf("Terminated Incorrectly\n");
        }
    }
    else {
        // Old Parent process. The C program will come here
        //printf("This line will be printed\n");
    }

    

    //std::string command = "xdotool mousemove " + std::to_string(x) + " " + std::to_string(y);
    //system(command.c_str());

    
}

void mouseMover::bezier(int x, int y, int n, int time_ms)
{
    std::tuple<int, int> curMousePosition = getMousePosition();
    int curX = std::get<0>(curMousePosition);
    int curY = std::get<1>(curMousePosition);
    double t_delta = (double)1.0/time_ms;
    double B_x;
    double B_y;
    // int P_x[n+1] = {curX, 300, 275, 450, 600, x};
    // int P_y[n+1] = {curY, 25, 150, 100, 300, y};
    int P_x[n+1];
    int P_y[n+1];
    P_x[0] = curX;
    P_y[0] = curY;
    P_x[n] = x;
    P_y[n] = y;
    for (int i = 1; i < n; i++)
    {
        P_x[i] = rand() % 1920;
        P_y[i] = rand() % 1080;
    }
    for (double t = (double)0.0; t <= (double)1.0; t=t+t_delta)
    {
        //cout << t_delta << endl;
        //cout << t << endl;
        B_x = 0.0;
        B_y = 0.0;
        for (int i = 0; i <= n; i++) 
        {
            //B_x += (double)binomialCoefficients(n, i)*pow((double)1.0 - t,(double)n-i)*pow(t,(double)i)*(double)P_x[i];
            // cout << "(double)binomialCoefficients(" << n << ", " << i << "): " << (double)binomialCoefficients(n, i) << endl;
            // cout << "(double)nCr(" << n << ", " << i << "): " << (double)nCr(n, i) << endl;
            // cout << "pow((double)1.0 - " << t << ",(double)" << n << "-" << i << "): " << pow((double)1.0 - t,(double)n-i) << endl;
            // cout << "pow(" << t << ",(double)" << i << "): " << pow(t,(double)i) << endl;
            // cout << "(double)P_y[" << i << "]: " << (double)P_y[i] << endl;
            B_x += (double)nCr(n, i)*pow((double)1.0 - t,(double)n-i)*pow(t,(double)i)*(double)P_x[i];
            B_y += (double)nCr(n, i)*pow((double)1.0 - t,(double)n-i)*pow(t,(double)i)*(double)P_y[i];
            //cout << "B_y: " << B_y << endl; 
        }
        // cout << "B_x: " << B_x << endl;
        // cout << "B_y: " << B_y << endl;
        move_mouse((int) B_x, (int) B_y);
        usleep(1000);
    }
    move_mouse(x, y);
}

int mouseMover::binomialCoefficients(int n, int k)
{
   if (k == 0 || k == n)
   return 1;
   return binomialCoefficients(n - 1, k - 1) + binomialCoefficients(n - 1, k);
}

int mouseMover::nPr(int n, int r)
{
    return fact(n) / fact(n-r);
}

int mouseMover::nCr(int n, int r)
{
    return fact(n) / (fact(r) * fact(n - r));
}
 
// Returns factorial of n
int mouseMover::fact(int n)
{
      if(n==0)
      return 1;
    int res = 1;
    for (int i = 2; i <= n; i++)
        res = res * i;
    return res;
}

