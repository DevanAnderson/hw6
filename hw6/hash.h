#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        //create an initial long long array with each cell assigned to 0
        unsigned long long w[5]{0,0,0,0,0};
        std::string s;
        int a = 4;
        int len = 0;
        len = k.size() - 1;
        
        while(len>=0){
            //get the proper values of the string k
            if(len >= 5){
            s = k.substr(len-5,6);
            }
            else{
                s = k.substr(0,len+1);
            }

            //assign the propere hash value to the weights
            unsigned long long val = 0;
            for(int j = 0; j < s.size(); j++){
                val = val * 36 + letterDigitToNumber(s[j]);
            }
            w[a--] = val;
            if(len > 5){
                len-=6;
            }
            else{
                break;
            }
        }

        //calculate the hash
        size_t r = 0;
            for (unsigned int m = 0; m < 5; m++) {
                // std::cout << w[m] << std::endl;
                r += rValues[m] * w[m];
            }
        return r;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        //deal with lower case letters
        if(letter >= 'a' && letter <= 'z'){
            return letter - 'a';
        }
        //deal with upper case letters
        else if(letter >= 'A' && letter <= 'Z'){
            return letter - 'A';
        }
        //deal with digits
        else if(letter >= '0' && letter <= '9'){
            return letter - '0' + 26;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
