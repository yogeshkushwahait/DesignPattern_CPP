#include <iostream>
#include <memory>
#include <thread>
/*
Singleton in C++
Intent:
1. Ensure a class has only one instance, and provide a global point of access to it.
2. Encapsulated "just-in-time initialization" or "initialization on first use".
Problem:
Application needs one, and only one, instance of an object. Additionally, lazy initialization and global access are necessary.
Check list:
1. Define all constructors to be protected or private.
2. Define a public static accessor function in the class which return instance of class
3. Do "lazy initialization" (creation on first use) in the accessor function.
4. Clients may only use the accessor function to manipulate the Singleton.
*/
using namespace std;
struct Setting
{
 std::string ThreadName{"ThreadName"};
};

class GlobalSettings
{
private:
    GlobalSettings(){std::cout<<"GlobalSettings Create"<<std::endl;}
    GlobalSettings(const GlobalSettings&) =delete;
    GlobalSettings(const GlobalSettings&&) =delete;
    GlobalSettings& operator==(const GlobalSettings&) =delete;
    GlobalSettings& operator==(const GlobalSettings&&) =delete;
  public:
    ~GlobalSettings(){std::cout<<"GlobalSettings Destroy"<<std::endl;}
    static GlobalSettings &GetInstance()
    {
        static GlobalSettings Instance;
        return Instance;
    }
    void setSettings(const Setting & settings){ m_Setting = settings;}
    void printSettings()
    {
        std::cout<<m_Setting.ThreadName<<std::endl;
    }
private:
    Setting m_Setting;
};
void threadFunc(const std::string ThreadName)
{
    Setting setting{ThreadName};
    GlobalSettings::GetInstance().setSettings(setting);
    GlobalSettings::GetInstance().printSettings();
}
int main()
{
    std::thread Thread1{threadFunc,"Thread1"};
    Thread1.join();
    std::thread Thread2{threadFunc,"Thread2"};
    Thread2.join();
    std::thread Thread3{threadFunc,"Thread3"};
    Thread3.join();
    std::thread Thread4{threadFunc,"Thread4"};
    Thread4.join();
    std::thread Thread5{threadFunc,"Thread5"};
    Thread5.join();
    return 0;
}
