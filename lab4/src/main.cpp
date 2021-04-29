/**
 * @ Author: Daniel Kaehn
 * @ Course: CS 3210 011
 * @ Modified by: Daniel Kaehn
 * @ Modified time: 2021-04-15 08:13:55
 * @ Description: Test driver of basic graphics context functionality
 */

#include "image.h"
#include "line.h"
#include "shape.h"
#include "triangle.h"
#include "x11context.h"
#include <cmath> // for trig functions
#include <fstream>
#include <iostream>
#include <ostream>
#include <unistd.h>

using namespace std;

//Driver to ad-hoc test image class
int main(void)
{
    GraphicsContext *gc = new X11Context(800, 600, GraphicsContext::BLACK);

    image pic;

    pic.add(new triangle(gc->CYAN, 0, 0, 50, 100, 100, 100));
    pic.add(new triangle(gc->RED, 100, 100, 150, 200, 200, 200));
    pic.add(new triangle(gc->CYAN, 500, 500, 550, 500, 600, 560));
    pic.add(new triangle(gc->BLUE, 500, 0, 50, 500, 100, 100));
    pic.add(new triangle(gc->CYAN, 300, 400, 150, 200, 600, 200));
    pic.add(new triangle(gc->CYAN, 700, 700, 800, 800, 600, 560));

    cout << "Draw the original" << endl;
    pic.draw(gc);

    sleep(3);

    image pic2;
    pic2 = pic;
    pic.erase();
    gc->clear();

    sleep(1);

    cout << "Draw assigned deep copy" << endl;
    pic2.draw(gc);

    sleep(3);

    image pic3(pic2);
    pic2.erase();
    gc->clear();

    sleep(1);

    cout << "Draw copy made from copy constructor" << endl;
    pic3.draw(gc);

    sleep(3);

    std::ofstream fileout("./test.stl");
    pic3.out(fileout);
    fileout.close();

    gc->clear();

    sleep(1);

    std::fstream filein("./test.stl");
    pic.in(filein);
    cout << "Draw written and read from file" << endl;
    pic.draw(gc);

    sleep(2);

    pic.erase();
    gc->clear();

    sleep(1);

    pic.add(new line(gc->RED, 0, 0, 500, 500));
    pic.add(new line(gc->MAGENTA, 600, 500, 200, 700));
    pic.draw(gc);

    sleep(2);

    try
    {
        pic.out(cout);
        cout<<"Expected exception writing out line to STL file"<<endl;
    }
    catch (unsupportedShapeOperationException &e)
    {
        cout<<"Tested line::out throws exception"<<endl;
    }
    

    delete gc;
    return 0;
}
