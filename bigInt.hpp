/**
 * @file bigInt.hpp
 * @brief Program to do addition and subtraction with integers of size 128 bit i.e. no. of digits = 41
 * @version 0.2
 * @date 2021-02-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef BIG_INT
#define BIG_INT
#include<iostream>
#include<string.h>

using namespace std;

/**
 * @class BigInt
 * @brief The BigInt class is to represent integers of size more than 64bit architecture.
 */
class BigInt
{
    string number;          //number will contain the initial input in the form of string
    int digits[64] = {0};   //the number will be divided into digits and will be assigned to the array
    bool sign;              //1 for negative and 0 for positive as in traditional signed binary

    /**
     * @brief private method to convert the input string to digits of the number
     * 
     */
    void digitConverter()
    {
        int i = number.length() - 1;            //to iterate in the loop
        int size = 63;                          //the last element of array will be at 63
        while(i>=0)
        {
            digits[size] = number[i] - '0';         
            size --;
            i--;
        }
    }

    /**
     * @brief a function to check for signs ('+'/'-') in the input string and assign the valut to sign member
     * 
     */
    void checkSign()
    {
        if(number[0] == '-')
        {
            sign = true;
            number.erase(number.begin());
        }
        else if(number[0] == '+')
        {
            sign = false;
            number.erase(number.begin());
        }
        else
        {
            sign = false;
        }
        
    }

    /**
     * @brief takes two BigInt and perform subtraction iteratively
     * 
     * @param a 
     * @param b 
     * @return BigInt 
     */
    BigInt substract(BigInt a,BigInt b)
    {
        BigInt c;
        for(int i=63; i>=0; i--)
        {
            c.digits[i] = a.digits[i] - b.digits[i];
            //debugging statement//cout<<a.digits[i]<<" - "<<b.digits[i]<<" = "<<c.digits[i]<<endl;
            if(c.digits[i] < 0)
            {
                c.digits[i] +=10;
                a.digits[i-1] -=1;
            }
        }
        return c;
    }

    /**
     * @brief takes two BigInt and performs addition iteratively
     * 
     * @param a 
     * @param b 
     * @return BigInt 
     */
    BigInt add(BigInt a, BigInt b)
    {
        BigInt c;
        for(int i=63; i>=0; i--)
        {
            c.digits[i] = a.digits[i] + b.digits[i];
            //debugging statement//cout<<a.digits[i]<<" - "<<b.digits[i]<<" = "<<c.digits[i]<<endl;
            if(c.digits[i] > 9)
            {
                c.digits[i] -=10;
                a.digits[i-1] +=1;
            }
        }
        return c;
    }

    /**
     * @brief function to check whether a is larger than b
     * 
     * @param a 
     * @param b 
     * @return true //if a is larger than b
     * @return false //if a is not larger than b
     */
    bool isALargeThanB(BigInt a, BigInt b)
    {
        int lenA = lengthOfA(a);
        int lenB = lengthOfA(b);
        if(lenA > lenB)
        {
            return true;
        }
        else if(lenA == lenB)
        {
            if(sumOfA(a) > sumOfA(b))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief a function to return the number of digits in the number.
     * 
     * @param a 
     * @return int 
     */
    static int lengthOfA(BigInt a)
    {
        int len;
        for(len=0; len<64; len++)
        {
            if(a.digits[len] > 0)
            {
                break;
            }
        }
        len = 64 - len;
    }

    /**
     * @brief a function to return the sum of digits of BigInt
     * 
     * @param a 
     * @return int 
     */
    int sumOfA(BigInt a)
    {
        int sum = 0;
        for(int i=0; i<64; i++)
        {
            sum += a.digits[i];
        }
        return sum;
    }

    public:
    /**
     * @brief input operator overloaded to take input of BigInt
     * 
     * @param in 
     * @param b 
     * @return istream& 
     */
        friend istream & operator >> (istream &in, BigInt &b)
        {
            in >> b.number;
            b.checkSign();
            b.digitConverter();
            return in;
        }

        /**
         * @brief output operator overloaded to print BigInt on screen
         * 
         * @param out 
         * @param b 
         * @return ostream& 
         */
        friend ostream & operator << (ostream &out, const BigInt &b)
        {
            if (b.sign == true)
            {
                out << '-';
            }
            int len = 64 - BigInt::lengthOfA(b);
            if(len == 64)
            {
                len = 63;
            }
            for(int i=len; i<64; i++)
            {
                out<<b.digits[i];
            }
            out << "\n";
            return out;
        }

        /**
         * @brief '+' operator overloaded to call add() function according to the signs of intergers 
         * 
         * @param a 
         * @param b 
         * @return BigInt 
         */
        friend BigInt operator + (const BigInt& a, const BigInt& b)
        {
            BigInt c;
            if(a.sign == b.sign)
            {
                //i.e. a+b or -(a+b)
                c = c.add(a,b);
                c.sign = a.sign;
            }
            else if (a.sign == false && b.sign == true)
            {
                c = b;
                c.sign = false;
                c = a - c;
            }
            else if(a.sign == true && b.sign == false)
            {
                c = a;
                c.sign = false;
                c = b - c;
            }
            return c;
        }

        /**
         * @brief '-' operator overloaded to call subtract() function according to the signs of intergers
         * 
         * @param a 
         * @param b 
         * @return BigInt 
         */
        friend BigInt operator - (const BigInt& a, const BigInt& b)
        {
            BigInt c;
            if(a.sign == true && b.sign == false)
            {
                //i.e. -a-b
                c = c.add(a,b);
                c.sign = true;
            }
            else if(a.sign == false && b.sign == true)
            {
                //i.e. a+b
                c = c.add(a,b);
                c.sign = false;
            }
            else if(a.sign == b.sign)
            {
                //i.e. max(a,b) - min(a,b) with a sign same as max(a,b)
                
                if (c.isALargeThanB(a,b) == true)
                {
                    c = c.substract(a,b);
                    c.sign = a.sign;
                }
                else
                {
                    c = c.substract(b,a);
                    c.sign = !b.sign;
                }    
            }
            if(c.sumOfA(c) == 0)
            {
                c.sign = false;
            }
            return c;
        }
};

#endif