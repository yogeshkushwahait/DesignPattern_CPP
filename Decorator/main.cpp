#include <iostream>
#include <memory>
/*
## Decorator Design Pattern
### Intent
* Attach additional responsibilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending functionality.
* Client-specified embellishment of a core object by recursively wrapping it.
* Wrapping a gift, putting it in a box, and wrapping the box.
### Problem
You want to add behavior or state to individual objects at run-time. Inheritance is not feasible because it is static and applies to an entire class.
### Check list
* Ensure the context is: a single core (or non-optional) component, several optional embellishments or wrappers, and an interface that is common to all.
* Create a "Lowest Common Denominator" interface that makes all classes interchangeable.
* Create a second level base class (Decorator) to support the optional wrapper classes.
* The Core class and Decorator class inherit from the Widget interface.
* The Decorator class declares a composition relationship to the Widget interface, and this data member is initialized in its constructor.
* The Decorator class delegates to the Widget object.
* Define a Decorator derived class for each optional embellishment.
* Decorator derived classes implement their wrapper functionality - and - delegate to the Decorator base class.
* The client configures the type and ordering of Core and Decorator objects.
*/
class Widget
{
public:
    virtual void draw() =0;
    virtual ~Widget()=default;
};
class MainWindow : public Widget
{
public:
    void draw() override {std::cout<<"Draw MainWindow ";}
};

class Decorator:public Widget
{
public:
    Decorator(std::shared_ptr<Widget>& aWidget):m_Widget(aWidget){}
    virtual void draw() {m_Widget->draw();}
    virtual ~Decorator()= default;
private:
 std::shared_ptr<Widget> m_Widget;
};
class VerticalSB : public Decorator
{
public:
    VerticalSB(std::shared_ptr<Widget>& aWidget):Decorator(aWidget){}
    void draw() override {Decorator::draw();std::cout<<"&& Decorator VerticalSB ";}
};
class HorizontalSB : public Decorator
{
public:
    HorizontalSB(std::shared_ptr<Widget>& aWidget):Decorator(aWidget){}
    void draw() override {Decorator::draw();std::cout<<"&& Decorator HorizontalSB ";}
};
class Border : public Decorator
{
public:
    Border(std::shared_ptr<Widget>& aWidget):Decorator(aWidget){}
    void draw() override {Decorator::draw();std::cout<<"&& Decorator Border ";}
};
using namespace std;

int main()
{
    std::shared_ptr<Widget> aWidget = make_shared<MainWindow>();
    aWidget->draw();
    std::cout<<std::endl;
    std::shared_ptr<Widget> aBorderWidget = make_shared<Border>(aWidget);
    aBorderWidget->draw();
    std::cout<<std::endl;
    std::shared_ptr<Widget> aHorizontalSB = make_shared<HorizontalSB>(aBorderWidget);
    aHorizontalSB->draw();
    std::cout<<std::endl;
    std::shared_ptr<Widget> aVerticalSB = make_shared<VerticalSB>(aHorizontalSB);
    aVerticalSB->draw();
    std::cout<<std::endl;
    return 0;
}
