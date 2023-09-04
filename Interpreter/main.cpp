#include <iostream>
#include <memory>
#include <string.h>
/*
## Interpreter Design Pattern
### Intent
* Given a language, define a representation for its grammar along with an interpreter that uses the representation to interpret sentences in the language.
* Map a domain to a language, the language to a grammar, and the grammar to a hierarchical object-oriented design.
### Problem
A class of problems occurs repeatedly in a well-defined and well-understood domain. If the domain were characterized with a "language", then problems could be easily solved with an interpretation "engine".
### Check list
* Decide if a "little language" offers a justifiable return on investment.
* Define a grammar for the language.
* Map each production in the grammar to a class.
* Organize the suite of classes into the structure of the Composite pattern.
* Define an interpret(Context) method in the Composite hierarchy.
* The Context object encapsulates the current state of the input and output as the former is parsed and the latter is accumulated. It is manipulated by each grammar class as the "interpreting" process transforms the input into the output.
*/

class RomanNumber
{
public:
    virtual ~RomanNumber()=default;
    virtual void interpret(char *input, int &total)
    {
        // for internal use
        int index;
        index = 0;
        if (!strncmp(input, nine(), 2))
        {
            total += 9 * multiplier();
            index += 2;
        }
        else if (!strncmp(input, four(), 2))
        {
            total += 4 * multiplier();
            index += 2;
        }
        else
        {
            if (input[0] == five())
            {
                total += 5 * multiplier();
                index = 1;
            }
            else
              index = 0;
            for (int end = index + 3; index < end; index++)
              if (input[index] == one())
                total += 1 * multiplier();
              else
                break;
        }
        strcpy(input, &(input[index]));
    } // remove leading chars processed
    virtual char one()=0;
    virtual char *four()=0;
    virtual char five()=0;
    virtual char *nine()=0;
    virtual int multiplier()=0;
};
class Thousand: public RomanNumber
{
  public:
    char one(){return 'M';}
    char *four(){return "";}
    char five(){return '\0';}
    char *nine(){return "";}
    int multiplier(){return 1000;}
};

class Hundred: public RomanNumber
{
  public:
    char one(){return 'C';}
    char *four(){return "CD";}
    char five(){return 'D';}
    char *nine(){return "CM";}
    int multiplier(){return 100;}
};

class Ten: public RomanNumber
{
  public:
    char one(){return 'X';}
    char *four(){return "XL";}
    char five(){return 'L';}
    char *nine(){return "XC";}
    int multiplier(){return 10;}
};

class One: public RomanNumber
{
  public:
  protected:
    char one(){return 'I';}
    char *four(){return "IV";}
    char five(){return 'V';}
    char *nine(){return "IX";}
    int multiplier(){return 1;}
};

class RNInterpreter
{
public:
    RNInterpreter()
    {
        m_Thousands = std::make_unique<Thousand>();
        m_Hundreds  = std::make_unique<Hundred>();
        m_Tens      = std::make_unique<Ten>();
        m_Ones      = std::make_unique<One>();
    }
    int interpret(char *input)
    {
     int total;
     total = 0;
     m_Thousands->interpret(input, total);
     m_Hundreds->interpret(input, total);
     m_Tens->interpret(input, total);
     m_Ones->interpret(input, total);
     if (strcmp(input, ""))
     // if input was invalid, return 0
     return 0;
     return total;
   }
   private:
    std::unique_ptr<RomanNumber> m_Thousands;
    std::unique_ptr<RomanNumber> m_Hundreds;
    std::unique_ptr<RomanNumber> m_Tens;
    std::unique_ptr<RomanNumber> m_Ones;
};

int main()
{
  RNInterpreter interpreter;
  char input[20];
  std::cout << "Enter Roman Numeral: ";
  while (std::cin >> input)
  {
    std::cout << "   interpretation is " << interpreter.interpret(input) << std::endl;
    std::cout << "Enter Roman Numeral: ";
  }
}
