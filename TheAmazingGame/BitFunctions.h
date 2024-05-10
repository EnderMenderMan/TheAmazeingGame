#pragma once
#include <iostream>
class BitFunctions
{
public:
    template <typename T>
    static void WriteAllBits(T value);
    template <typename T>
    static void WriteAllBits(T value, char zero, char one);
    template <typename T>
    static void WriteAllBits(T value, char zero, char one,short writeBits);

    template <typename T>
    static bool CheckBitAt(T value, short bitIndex);

};

template <typename T>
static void BitFunctions::WriteAllBits(T value) {

    T evValue = 1 << sizeof(T) * 8 - 1;

    for (size_t i = 0; i < sizeof(T) * 8; i++)
    {
        if (value & evValue)
            std::cout << "1";
        else
            std::cout << "0";

        value = value << 1;
    }
}
template <typename T>
static void BitFunctions::WriteAllBits(T value,char zero,char one) {

    T evValue = 1 << sizeof(T) * 8 - 1;

    for (size_t i = 0; i < sizeof(T) * 8; i++)
    {
        if (value & evValue)
            std::cout << one;
        else
            std::cout << zero;

        value = value << 1;
    }
}
template <typename T>
static void BitFunctions::WriteAllBits(T value, char zero, char one, short writeBits) {

    T evValue = 1 << sizeof(T) * 8 - 1;

    for (size_t i = 0; i < writeBits; i++)
    {
        if (value & evValue)
            std::cout << one;
        else
            std::cout << zero;

        value = value << 1;
    }
}