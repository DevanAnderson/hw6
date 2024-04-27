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
        //start at the last character of k
        int i = k.size() - 1;
        //initialize hash to 0
        size_t h = 0;

        for(int weightIndex = 4; weightIndex >= 0; --weightIndex) {
            size_t weight = 0;

            //start at the last index, and continue until we have reached 6 charafcters, or there are no more characters
            for(int j = i; j >= 0 && j >= i - 5; j--){
                //compute the weight
                weight += pow(36, i - j) * letterDigitToNumber(k[j]);
            }
            h = h + (weight * rValues[weightIndex]);
            i = i - 6;
            if (i < 0){
                break;
            }
        }
        return h;
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
