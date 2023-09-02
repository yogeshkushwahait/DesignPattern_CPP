#include <iostream>
#include <memory>
#include <vector>
/*
## Composite Design Pattern
### Intent
* Compose objects into tree structures to represent whole-part hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.
* Recursive composition
* "Directories contain entries, each of which could be a directory."
* 1-to-many "has a" up the "is a" hierarchy
### Problem
Application needs to manipulate a hierarchical collection of "primitive" and "composite" objects. Processing of a primitive object is handled one way, and processing of a composite object is handled differently. Having to query the "type" of each object before attempting to process it is not desirable.
### Check list
* Ensure that your problem is about representing "whole-part" hierarchical relationships.
* Consider the heuristic, "Containers that contain containees, each of which could be a container." For example, "Assemblies that contain components, each of which could be an assembly." Divide your domain concepts into container classes, and containee classes.
* Create a "lowest common denominator" interface that makes your containers and containees interchangeable. It should specify the behavior that needs to be exercised uniformly across all containee and container objects.
* All container and containee classes declare an "is a" relationship to the interface.
* All container classes declare a one-to-many "has a" relationship to the interface.
* Container classes leverage polymorphism to delegate to their containee objects.
* Child management methods [e.g. addChild(), removeChild()] should normally be defined in the Composite class. Unfortunately, the desire to treat Leaf and Composite objects uniformly may require that these methods be promoted to the abstract Component class. See the Gang of Four for a discussion of these "safety" versus "transparency" trade-offs.
*/
class Menu
{
public:
    Menu(const std::string& Name):MenuName{Name}{}
    void AddSubMenu(const std::shared_ptr<Menu>& subMenu){m_subMenuList.push_back(subMenu);}
    void printMenu()
    {
        std::cout<<MenuName<<std::endl;
        for(auto sub:m_subMenuList)
        {
           printMenu(sub);
        }
    }
    void printMenu(const std::shared_ptr<Menu>& menu)
    {
        static std::string tabs = " ";
        tabs += " ";
        std::cout<<tabs<<"|-"<<menu->MenuName<<std::endl;
        for(auto sub:menu->m_subMenuList)
        {
           printMenu(sub);
        }
        tabs.resize(tabs.length()-1);
    }
private:
    std::string MenuName;
    std::vector<std::shared_ptr<Menu>> m_subMenuList;

};

using namespace std;

int main()
{
    std::shared_ptr<Menu> File = std::make_shared<Menu>("File");
    std::shared_ptr<Menu> New  = std::make_shared<Menu>("New");
    std::shared_ptr<Menu> EmptyFile  = std::make_shared<Menu>("EmptyFile");
    std::shared_ptr<Menu> ClassFile = std::make_shared<Menu>("Class");
    std::shared_ptr<Menu> ProjectFile  = std::make_shared<Menu>("Project");
    std::shared_ptr<Menu> Open  = std::make_shared<Menu>("open");
    std::shared_ptr<Menu> Save  = std::make_shared<Menu>("Save");
    std::shared_ptr<Menu> SaveAs  = std::make_shared<Menu>("SaveAs");
    std::shared_ptr<Menu> Close  = std::make_shared<Menu>("Close");
    std::shared_ptr<Menu> Export  = std::make_shared<Menu>("Export");
    std::shared_ptr<Menu> ExportHTML  = std::make_shared<Menu>("ExportHTML");
    std::shared_ptr<Menu> ExportRTF  = std::make_shared<Menu>("ExportRTF");
    New->AddSubMenu(EmptyFile);
    New->AddSubMenu(ClassFile);
    New->AddSubMenu(ProjectFile);
    Export->AddSubMenu(ExportHTML);
    Export->AddSubMenu(ExportRTF);
    File->AddSubMenu(New);
    File->AddSubMenu(Open);
    File->AddSubMenu(Save);
    File->AddSubMenu(SaveAs);
    File->AddSubMenu(Close);
    File->AddSubMenu(Export);
    File->printMenu();
    return 0;
}
