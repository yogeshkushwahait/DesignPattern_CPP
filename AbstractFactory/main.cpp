#include <iostream>
#include <vector>
/*
## Abstract Factory Design Pattern
### Intent
* Provide an interface for creating families of related or dependent objects without specifying their concrete classes.
* A hierarchy that encapsulates: many possible "platforms", and the construction of a suite of "products".
* The new operator considered harmful.
### Problem
If an application is to be portable, it needs to encapsulate platform dependencies. These "platforms" might include: windowing system, operating system, database, etc. Too often, this encapsulation is not engineered in advance, and lots of #ifdef case statements with options for all currently supported platforms begin to procreate like rabbits throughout the code.
### Check list
* Decide if "platform independence" and creation services are the current source of pain.
* Map out a matrix of "platforms" versus "products".
* Define a factory interface that consists of a factory method per product.
* Define a factory derived class for each platform that encapsulates all references to the new operator.
* The client should retire all references to new, and use the factory methods to create the product objects.
*/
using namespace std;
using namespace std;

class Shape
{
public:
  virtual void draw()=0;
  virtual ~Shape() = default;
};
class Rectangle:public Shape
{
};
class OpenGLRectangle:public Rectangle
{
 public:
    OpenGLRectangle(){std::cout<<"Create OpenGLRectangle"<<std::endl;}
    ~OpenGLRectangle(){std::cout<<"Destroy OpenGLRectangle"<<std::endl;}
    void draw() override {std::cout<<"Draw OpenGLRectangle"<<std::endl;}
};
class VulkanRectangle:public Rectangle
{
 public:
    VulkanRectangle(){std::cout<<"Create VulkanRectangle"<<std::endl;}
    ~VulkanRectangle(){std::cout<<"Destroy VulkanRectangle"<<std::endl;}
    void draw() override {std::cout<<"Draw VulkanRectangle"<<std::endl;}
};

class Circle:public Shape
{
};
class OpenGLCircle:public Circle
{
 public:
    OpenGLCircle(){std::cout<<"Create OpenGLCircle"<<std::endl;}
    ~OpenGLCircle(){std::cout<<"Destroy OpenGLCircle"<<std::endl;}
    void draw() override {std::cout<<"Draw OpenGLCircle"<<std::endl;}
};
class VulkanCircle:public Circle
{
 public:
    VulkanCircle(){std::cout<<"Create VulkanCircle"<<std::endl;}
    ~VulkanCircle(){std::cout<<"Destroy VulkanCircle"<<std::endl;}
    void draw() override {std::cout<<"Draw VulkanCircle"<<std::endl;}
};

class ShapeFactory
{
public:
    virtual Shape* CreateRectangle()=0;
    virtual Shape* CreateCircle()=0;
};
class OpenGLShapeFactory:public ShapeFactory
{
    Shape* CreateRectangle() override {return new OpenGLRectangle;}
    Shape* CreateCircle()override {return new OpenGLCircle;}
};
class VulkanShapeFactory:public ShapeFactory
{
    Shape* CreateRectangle()override {return new VulkanRectangle;}
    Shape* CreateCircle()override{return new VulkanCircle;}
};
//#define OPENGL_DRAW
int main()
{
#ifdef OPENGL_DRAW
    ShapeFactory * shapefactory = new OpenGLShapeFactory;
#else
    ShapeFactory * shapefactory = new VulkanShapeFactory;
#endif
    std::vector<Shape*> ListShape;
    ListShape.push_back(shapefactory->CreateCircle());
    ListShape.push_back(shapefactory->CreateRectangle());
    for(auto& shape:ListShape)
    {
        shape->draw();
    }
    for(auto& shape:ListShape)
    {
       delete shape;
    }
    return 0;
}
