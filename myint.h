//library's
#include <iostream>        //for ostream and istream type

class MyInt
{
   //these overload starters are declared as friend functions

   friend MyInt operator+ (const MyInt& x, const MyInt& y);
   friend MyInt operator* (const MyInt& x, const MyInt& y);          //add in multiplication, as well


   friend bool operator< (const MyInt& x, const MyInt& y);
   //add in the other comparison overloads, as well
   friend bool operator> (const MyInt& x, const MyInt& y);
   friend bool operator<= (const MyInt& x, const MyInt& y);
   friend bool operator>= (const MyInt& x, const MyInt& y);
   friend bool operator== (const MyInt& x, const MyInt& y);
   friend bool operator!= (const MyInt& x, const MyInt& y);

   //declare overloads for input and output (MUST be non-member functions)
   //you may make them friends of the class
   friend std::ostream& operator<< (std::ostream& out, const MyInt& num);        //prints MyInt
   friend std::istream& operator>> (std::istream& in, MyInt& num);               //reads MyInt

public:
   MyInt(int n = 0);		   //first constructor
    
   //be sure to add in the second constructor, and the user-defined 
   MyInt(const char* str);   //second contructor for c-string

   //versions of destructor, copy constructor, and assignment operator
   MyInt(const MyInt& copy);              //copy contructor
   ~MyInt();                              //destructor
   MyInt& operator= (const MyInt& rhs);   //assignment operator

   MyInt& operator++();          //pre incremesing
   MyInt operator++(int);        //post increasing

private:
   // member data (suggested:  use a dynamic array to store the digits)
   int* digits;                  //dynamic array to store the digits
   unsigned int size;            //for numbers currently used
   unsigned int limit;           //for the capacity

   //helper functions
   void zero();                         //for setting object to 0
   void copying(const MyInt& copy);          //for deep copy 
   void reserve(unsigned int newLim);        //for ensuring limit is greather than newLim
   void trimZeros();                          //for removing extra zeros at the front
};