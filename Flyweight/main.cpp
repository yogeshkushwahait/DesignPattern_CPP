#include <iostream>
#include <map>
#include <memory>
/*
## Flyweight Design Pattern
### Intent
* Use sharing to support large numbers of fine-grained objects efficiently.
* The Motif GUI strategy of replacing heavy-weight widgets with light-weight gadgets.
### Problem
Designing objects down to the lowest levels of system "granularity" provides optimal flexibility, but can be unacceptably expensive in terms of performance and memory usage.
### Check list
* Ensure that object overhead is an issue needing attention, and, the client of the class is able and willing to absorb responsibility realignment.
* Divide the target class's state into: shareable (intrinsic) state, and non-shareable (extrinsic) state.
* Remove the non-shareable state from the class attributes, and add it the calling argument list of affected methods.
* Create a Factory that can cache and reuse existing class instances.
* The client must use the Factory instead of the new operator to request objects.
* The client (or a third party) must look-up or compute the non-shareable state, and supply that state to class methods.
*/
using namespace std;

class Player
{
public:
    virtual void assignWeapon(const std::string& weapon) =0;
    virtual void mission() =0;
};
class Soldier : public Player
{
public:
   Soldier(){m_task="DIFFUSE BOMB";}
   void assignWeapon(const std::string& weapon){m_weapon=weapon;}
   void mission(){std::cout<<"soldier with weapon "<<m_weapon<<" and task is "<<m_task<<std::endl;}
private:
    std::string m_weapon;
    std::string m_task;
};
class Terrorist: public Player
{
public:
   Terrorist (){m_task="PLANT A BOMB";}
   void assignWeapon(const std::string& weapon){m_weapon=weapon;}
   void mission(){std::cout<<"Terrorist with weapon "<<m_weapon<<" and task is "<<m_task<<std::endl;}
private:
    std::string m_weapon;
    std::string m_task;
};
enum class PlayerType
{
    PT_Soldier,
    PT_Terrorist
};
class PlayerFactory
{
public:
    static std::shared_ptr<Player>& getPlayer(const PlayerType& type,const std::string & weapon)
    {
        auto itrPlayer = m_PlayerMap.find(type);
        if(itrPlayer == m_PlayerMap.end())
        {
           switch(type)
           {
           case PlayerType::PT_Soldier:
             cur_player = make_shared<Soldier>();
             break;
           case PlayerType::PT_Terrorist:
             cur_player = make_shared<Terrorist>();
             break;
            default:
             cur_player = make_shared<Soldier>();
             break;
           }
           m_PlayerMap[type] = cur_player;
        }
        else
        {
            cur_player = itrPlayer->second;
        }
        cur_player->assignWeapon(weapon);
        return cur_player;
    }
private:
   static std::shared_ptr<Player> cur_player;
   static std::map<PlayerType,std::shared_ptr<Player>> m_PlayerMap;
};
std::map<PlayerType,std::shared_ptr<Player>> PlayerFactory::m_PlayerMap{};
std::shared_ptr<Player> PlayerFactory::cur_player{};
int main()
{
    std::shared_ptr<Player> player1 = PlayerFactory::getPlayer(PlayerType::PT_Soldier,"AK-47");
    player1->mission();
    std::shared_ptr<Player> player2 =PlayerFactory::getPlayer(PlayerType::PT_Soldier,"Maverick");
    player2->mission();
    std::shared_ptr<Player> player3 =PlayerFactory::getPlayer(PlayerType::PT_Terrorist,"AK-47");
    player3->mission();
    std::shared_ptr<Player> player4 =PlayerFactory::getPlayer(PlayerType::PT_Terrorist,"Maverick");
    player4->mission();
    return 0;
}
