#include <iostream>
#include <memory>
/*
## Facade Design Pattern
### Intent
* Provide a unified interface to a set of interfaces in a subsystem. Facade defines a higher-level interface that makes the subsystem easier to use.
* Wrap a complicated subsystem with a simpler interface.
### Problem
A segment of the client community needs a simplified interface to the overall functionality of a complex subsystem.
### Check list
* Identify a simpler, unified interface for the subsystem or component.
* Design a 'wrapper' class that encapsulates the subsystem.
* The facade/wrapper captures the complexity and collaborations of the component, and delegates to the appropriate methods.
* The client uses (is coupled to) the Facade only.
* Consider whether additional Facades would add value.
*/
//=========================== Shape System ==============================//
class Shape
{
public:
  virtual void draw()=0;
  virtual ~Shape() = default;
};
class Rectangle:public Shape
{
 public:
    Rectangle(){std::cout<<"Create Rectangle"<<std::endl;}
    ~Rectangle(){std::cout<<"Destroy Rectangle"<<std::endl;}
    void draw() override {std::cout<<"Draw Rectangle"<<std::endl;}
};
class Circle:public Shape
{
 public:
    Circle(){std::cout<<"Create Circle"<<std::endl;}
    ~Circle(){std::cout<<"Destroy Circle"<<std::endl;}
    void draw() override {std::cout<<"Draw Circle"<<std::endl;}
};
class Triangle:public Shape
{
 public:
    Triangle(){std::cout<<"Create Triangle"<<std::endl;}
    ~Triangle(){std::cout<<"Destroy Triangle"<<std::endl;}
    void draw() override {std::cout<<"Draw Triangle"<<std::endl;}
};
class Polygon:public Shape
{
 public:
    Polygon(){std::cout<<"Create Polygon"<<std::endl;}
    ~Polygon(){std::cout<<"Destroy Polygon"<<std::endl;}
    void draw() override {std::cout<<"Draw Polygon"<<std::endl;}
};
//=========================== Shape System ==============================//

class ShapeMaker
{
public:
    ShapeMaker()
    {
       m_Rectangle = std::make_unique<Rectangle>();
       m_Circle    = std::make_unique<Circle>();
       m_Triangle  = std::make_unique<Triangle>();
       m_Polygon   = std::make_unique<Polygon>();
    }
    void drawRectangle(){m_Rectangle->draw();}
    void drawCircle(){m_Circle->draw();}
    void drawTriangle(){m_Triangle->draw();}
    void drawPolygon(){m_Polygon->draw();}
private:
    std::unique_ptr<Shape> m_Rectangle;
    std::unique_ptr<Shape> m_Circle;
    std::unique_ptr<Shape> m_Triangle;
    std::unique_ptr<Shape> m_Polygon;
};
using namespace std;

int main()
{
    std::unique_ptr<ShapeMaker> pShapeMaker = std::make_unique<ShapeMaker>();
    pShapeMaker->drawRectangle();
    pShapeMaker->drawCircle();
    pShapeMaker->drawTriangle();
    pShapeMaker->drawPolygon();
    return 0;
}
