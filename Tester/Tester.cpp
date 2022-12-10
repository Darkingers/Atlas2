// Tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <typeinfo>

template <typename T>
std::string getTypeName( )
{
    return typeid( T ).name( );
}

int main( )
{
	constexpr const char* name = getTypeName<int>( ).c_str();
    std::cout << getTypeName<std::string>( ) << std::endl;
    return 0;
}
