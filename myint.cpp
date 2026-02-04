//library's  and class
#include <iostream>
#include <cctype>
#include "myint.h"

using namespace std;

int C2I(char c)
//converts character into integer (returns -1 for error)
{
   if (c < '0' || c > '9')	return -1;	//error
   return (c - '0');				//success
}

char I2C(int x)
//converts single digit integer into character (returns '\0' for error)
{
   if (x < 0 || x > 9)		return '\0';	//error
   return (static_cast<char>(x) + '0'); 	//success
}

//helper function for reseting object value to 0
void MyInt::zero()
{
   delete[] digits;              //free the old memory
   limit = 1;
   size = 1;
   digits = new int[limit];      //allocates the new array
   digits[0] = 0;                //stores a single zero
}

//helper function for deep copying another MyInt object
void MyInt::copying(const MyInt& copy)
{
   limit = copy.size;         //allocates the same about of number of digits
   size  = copy.size;         //copying the number of digits
   digits = new int[limit];   //allocates a new array

   //for loop for copying each digit for object
   for (unsigned int i = 0; i < size; i++)
   {
      digits[i] = copy.digits[i];
   }
}

//helper function for staying in the limit
void MyInt::reserve(unsigned int newLim)
{
   //if statement for when the limit is already big enough
   if (newLim <= limit)
      return;

   int* newDigits = new int[newLim];      //creating a new array of larger size

   //for loop for coping current digits
   for (unsigned int i = 0; i < size; i++)
      newDigits[i] = digits[i];

   delete [] digits;       //freeing old array
   digits = newDigits;     //updating pointer
   limit  = newLim;        //upadating the limit
}

//helper function for removing the extra zeros before a number
void MyInt::trimZeros()
{
   //while loop for when there are more than 1 digit and lst digit is 0 then shrink size
   while (size > 1 && digits[size - 1] == 0)
      size--;

   //for loop for shrinking the array to size needed
   if (limit != size)
   {
      int* newDigits = new int[size];           //allocating smaller array

      //for loop for copying the digits
      for (unsigned int i = 0; i < size; i++)   
         newDigits[i] = digits[i];

      delete [] digits;          //freeing old array
      digits = newDigits;        //updating pointer
      limit  = size;             //upadating the limit
   }
}

//contructor
MyInt::MyInt(int n)
{
   digits = nullptr;             //intialzing the pointer to a null
   size   = 0;                   
   limit  = 0;

   //if statement for when imput is given negative
   if (n < 0)
      n = 0;

   //if statement when the input is given 0
   if (n == 0)
   {
      zero();
      return;
   }

   int temp = n;           //copy to count digits
   unsigned int len = 0;   //counter

   //while loop for counting digits
   while (temp > 0)
   {
      temp /= 10;
      len++;
   }

   limit = len;
   size  = len;
   digits = new int[limit];      //allocating array for digits

   //for loop for extracting digits
   for (unsigned int i = 0; i < len; i++)
   {
      digits[i] = n % 10;
      n /= 10;
   }
}

//second contructor for bulding MyInt 
MyInt::MyInt(const char* s)
{
   digits = nullptr;       //setting the pointer
   size   = 0;
   limit  = 0;

   //if statement for handling the null pointer
   if (s == nullptr || s[0] == '\0')
   {
      zero();        //using helper funtion to set to zero
      return;
   }

   unsigned int len = 0;      //to count valid digits

   //while loop until it hits null terminator
   while (s[len] != '\0')
   {
      //if statement when char is digit setting it to zero
      if (!isdigit(static_cast<unsigned char>(s[len])))
      {
         zero();     //helper function
         return;
      }
      len++;      //increasing the length
   }

   limit = len;      //limit equals to string length
   size  = len;      //setting the size to number of digits
   digits = new int[limit];   //allocating array 

   //for loop for copying digits starting for the smallest
   for (unsigned int i = 0; i < len; i++)
   {
      digits[i] = C2I(s[len - 1 - i]);
   }

   trimZeros();  //helper funtion to remove the zeros
}

//contruction to deep copy another object
MyInt::MyInt(const MyInt& copy)
{
   digits = nullptr;       //setting the pointer
   size   = 0;
   limit  = 0;

   copying(copy);          //helper function to copy
}

//destructor for removing the dynamic memory
MyInt::~MyInt()
{
   delete [] digits; 
}

//assiggnment operator for copying 
MyInt& MyInt::operator= (const MyInt& a)
{
   //if statemnt for checking if its self assigned
   if (this == &a)
      return *this;

   delete [] digits;    //clears existing digits
   digits = nullptr;    //reseting the pointer
   size   = 0;          //reserting the size
   limit  = 0;          //reseting the limit

   copying(a);          //helper function for deep copy
   return *this;        //for returning the reference
}  

//operator for pre incresment
MyInt& MyInt::operator++() 
{
   int carry = 1;
   unsigned int i = 0;

   //while loop to add carry to digits
   while (carry && i < size)
   {
      int sum = digits[i] + carry;     //adds carry
      digits[i] = sum % 10;            //store the last digit
      carry     = sum / 10;            //sets new carry
      i++;                             //going to next digit
   }

   //if statement for new digit
   if (carry)
   {
      reserve(size + 1);         //increase the limit
      digits[size] = carry;      //storing carry
      size++;                    //increasing the size
   }

   trimZeros();                  //helper function to clean the zeros again
   return *this;                 //to return modification
}

//operator for post increment
MyInt MyInt::operator++(int)
{
   MyInt temp(*this);  //saveing the original
   ++(*this);          //use pre increment to add
   return temp;        //returning original value
}

//operator for less than
bool operator< (const MyInt& x, const MyInt& y)
{
   //if statement to compare by size
   if (x.size < y.size) return true;
   if (x.size > y.size) return false;

   //for loop for comparing most significant digit
   for (int i = static_cast<int>(x.size) - 1; i >= 0; i--)
   {
      //if statement to compare by digits
      if (x.digits[i] < y.digits[i]) return true;
      if (x.digits[i] > y.digits[i]) return false;
   }

   return false;  //returns false when equal
}

//operator for equal
bool operator== (const MyInt& x, const MyInt& y)
{
   //if statement when different size does not equal
   if (x.size != y.size)
      return false;

   //for loop for comparing all digits
   for (unsigned int i = 0; i < x.size; i++)
   {
      //if statement when different digit does not equal
      if (x.digits[i] != y.digits[i])
         return false;
   }

   return true;      //return true when equal
}

//greater than operator
bool operator> (const MyInt& x, const MyInt& y)
{
   return (y < x);
}

//less than equal to operator
bool operator<= (const MyInt& x, const MyInt& y)
{
   return !(y < x);
}

//greather than equal to operator
bool operator>= (const MyInt& x, const MyInt& y)
{
   return !(x < y);
}

//equal operator
bool operator!= (const MyInt& x, const MyInt& y)
{
   return !(x == y);
}
//addition operator
MyInt operator+ (const MyInt& x, const MyInt& y)
{
   unsigned int maxLen = (x.size > y.size) ? x.size : y.size;     //larger lize

   MyInt result(0);              //starting with 0
   result.size = 0;
   result.reserve(maxLen + 1);   //allocating enough for possible carry

   int carry = 0;
   unsigned int i;

   //for loop for going thrugh digits
   for (i = 0; i < maxLen; i++)
   {
      int dx = (i < x.size) ? x.digits[i] : 0;        //when x is 0 or a digit
      int dy = (i < y.size) ? y.digits[i] : 0;        //when y is 0 or a digit

      int sum = dx + dy + carry;       //adds digit and the carry
      result.digits[i] = sum % 10;     //storing it
      carry = sum / 10;                //computing the new carry
   }

   //if statement adding if carry after a digit
   if (carry)
   {
      result.digits[i] = carry;
      result.size = maxLen + 1;
   }
   else
   {
      result.size = maxLen;
   }

   result.trimZeros();     //helper function again
   return result;          //returning the result
}

//multiplication operator
MyInt operator* (const MyInt& x, const MyInt& y)
{
   //if statement for when either is 0, result is 0
   if ((x.size == 1 && x.digits[0] == 0) || (y.size == 1 && y.digits[0] == 0))
      return MyInt(0);

   unsigned int lenX = x.size;         //starting with 0
   unsigned int lenY = y.size;         //size
   unsigned int lenR = lenX + lenY;    //allocate enough space needed

   MyInt result(0);        //starting with 0
   result.size = lenR;     //size
   result.reserve(lenR);   //allocate enough space needed

   //for loop for initialize result digits to 0
   for (unsigned int i = 0; i < lenR; i++)
      result.digits[i] = 0;

   //for loop for multiplication
   for (unsigned int i = 0; i < lenX; i++)
   {
      int carry = 0;
      for (unsigned int j = 0; j < lenY; j++)
      {
         int prod = x.digits[i] * y.digits[j] + result.digits[i + j] + carry;
         result.digits[i + j] = prod % 10;
         carry = prod / 10;
      }

      //if statement when carry left then adds next
      if (carry)
         result.digits[i + lenY] += carry;
   }

   result.trimZeros();        //helper function
   return result;             //returning result
}  

//stream operator for output
ostream& operator<< (ostream& out, const MyInt& num)
{
   //for loop for printing most significant digit first
   for (int i = static_cast<int>(num.size) - 1; i >= 0; i--)
   {
      out << I2C(num.digits[i]);
   }
   return out;    //return output
}

//stream operator for input
istream& operator>> (istream& in, MyInt& num)
{
   int ch = in.peek();        //for peeking into next char

   //while loop for skipping white space
   while (isspace(ch))
   {
      in.get();
      ch = in.peek();
   }

   unsigned int bufCap = 20;           //intialiging buffer limit
   unsigned int len = 0;               //digits read
   char* buffer = new char[bufCap];     //dynamically allocates buffer

   //while loop to read consecutive digits
   while (true)
   {
      ch = in.peek();         //for peeking into next char

      //if statement for stopping when not a digit
      if (!isdigit(ch))
         break;

      //if stement for needing more space
      if (len + 1 >= bufCap)     
      {
         unsigned int newLim = bufCap * 2;      //multiplies it by 2 so doubles it
         char* newBuf = new char[newLim];       //allocates larger buffer

         //for loop for copying old buffer to a new buffer
         for (unsigned int i = 0; i < len; i++)
            newBuf[i] = buffer[i];

         delete [] buffer;    //to free space
         buffer = newBuf;     //point to the new buffer
         bufCap = newLim;     //updates the limit
      }

      buffer[len++] = static_cast<char>(in.get());    //reads the digit then stores it
   }

   buffer[len] = '\0';     //adding the null terminator

   MyInt temp(buffer);     //bulding the a temp MyInt
   num = temp;             //assigns to output 

   delete [] buffer;       //free up space
   return in;              //returning stream reference
}