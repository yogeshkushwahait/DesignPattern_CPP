#include <iostream>
#include <memory>
/*
## Builder Design Pattern
### Intent
* Separate the construction of a complex object from its representation so that the same construction process can create different representations.
* Parse a complex representation, create one of several targets.
### Problem
An application needs to create the elements of a complex aggregate. The specification for the aggregate exists on secondary storage and one of many representations needs to be built in primary storage.
### Check list
* Decide if a common input and many possible representations (or outputs) is the problem at hand.
* Encapsulate the parsing of the common input in a Reader class.
* Design a standard protocol for creating all possible output representations. Capture the steps of this protocol in a Builder interface.
* Define a Builder derived class for each target representation.
* The client creates a Reader object and a Builder object, and registers the latter with the former.
* The client asks the Reader to "construct".
* The client asks the Builder to return the result.
*/
using namespace std;
class HousePlan
{
public:
	virtual void setBasement(const std::string& basement)=0;
	virtual void setStructure(const std::string& structure)=0;
	virtual void setRoof(const std::string& roof)=0;
	virtual void setInterior(const std::string& interior)=0;
};

class House :public HousePlan
{
public:
	 void setBasement(const std::string& basement) override{this->basement = basement;}
	 void setStructure(const std::string& structure)override{this->structure = structure;}
     void setRoof(const std::string& roof) override{this->roof = roof;}
     void setInterior(const std::string& interior)override{this->interior = interior;}
     friend std::ostream& operator<<(std::ostream& ostream,const House& house);
private:
	std::string basement;
	std::string structure;
	std::string roof;
	std::string interior;
};

std::ostream& operator << (std::ostream& housestream,const House& house)
{
   housestream<<"/////////////////House build/////////////////"<<std::endl;
   housestream<<"Basement:"<<house.basement<<std::endl;
   housestream<<"Roof:"<<house.roof<<std::endl;
   housestream<<"Structure:"<<house.structure<<std::endl;
   housestream<<"Interior:"<<house.interior<<std::endl;
   housestream<<"/////////////////House build/////////////////"<<std::endl;
   return housestream;
}
class HouseBuilder
{
public:
    virtual void buildBasement() =0;
    virtual void buildStructure()=0;
	virtual void buildRoof()=0;
	virtual void buildInterior()=0;
	virtual std::shared_ptr<House> getHouse()=0;
};

class IglooHouseBuilder :public HouseBuilder
{
public:
    IglooHouseBuilder(){this->house = make_shared<House>();}
    void buildBasement() override{house->setBasement("Ice Bars");}
    void buildStructure()override{house->setStructure("Ice Blocks");}
	void buildRoof() override{house->setRoof("Ice Dome");}
	void buildInterior()override{house->setInterior("Ice Carvings");}
	std::shared_ptr<House> getHouse()override{return this->house;}
private:
    std::shared_ptr<House> house;
};
class TipiHouseBuilder :public HouseBuilder
{
public:
    TipiHouseBuilder(){this->house = make_shared<House>();}
    void buildBasement() override{house->setBasement("Wooden Poles");}
    void buildStructure()override{house->setStructure("Wood and Ice");}
	void buildRoof() override{house->setRoof("Wood, caribou and seal skins");}
	void buildInterior()override{house->setInterior("Fire Wood");}
	std::shared_ptr<House> getHouse()override{return this->house;}
private:
    std::shared_ptr<House> house;
};
class CivilEngineer
{
public:
    CivilEngineer(const std::shared_ptr<HouseBuilder>& houseBuilder){this->houseBuilder = houseBuilder;}
    std::shared_ptr<House> getHouse(){return this->houseBuilder->getHouse();}
    void constructHouse()
    {
        this->houseBuilder->buildBasement();
        this->houseBuilder->buildStructure();
        this->houseBuilder->buildRoof();
        this->houseBuilder->buildInterior();
    }
private:
    std::shared_ptr<HouseBuilder> houseBuilder;
};
//#define IGLOO_HOUSE
int main()
{
#ifdef IGLOO_HOUSE
  std::shared_ptr<HouseBuilder> houseBuilder = std::make_shared<IglooHouseBuilder>();
#else
  std::shared_ptr<HouseBuilder> houseBuilder = std::make_shared<TipiHouseBuilder>();
#endif
  std::unique_ptr<CivilEngineer> engineer = std::make_unique<CivilEngineer>(houseBuilder);
  engineer->constructHouse();
  std::cout<<*engineer->getHouse();
  return 0;
}
