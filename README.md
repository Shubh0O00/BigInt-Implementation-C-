# Big Int Implementation using C++  
##### Big Integer is considered to be of atleast twice the size of 8-Bytes(64-bits) integer  

**The datatype is implemeted using a class**    
```C++
class BigInt
{
    string number;          
    int digits[64] = {0};   
    bool sign;
    /*
    various methods
    */
}
```  
  
The class contains three members:-  
1. **number**: A string to take initial input from user.
1. **digits[64]**: An array of integers of size 64 to store digits of the number in each integer of the array. This is initialise to contain 0 in all blocks to avoid having garbage value during operations.
1. **sign**: A boolean value to store the sign of the integer.

The Data type supports four operation:-  
1. Input
1. Output
1. Addition
1. Subtraction
  


