// Tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import AtlasExceptions;
import AtlasDefinitions;

#include <iostream>

template<typename DataType>
using Simplify = typename std::remove_const_t
<
	std::conditional
	<
	std::is_pointer<DataType>::value ,
	std::remove_pointer_t<DataType> ,
	std::conditional<std::is_reference<DataType>::value , std::remove_reference_t<DataType> , DataType>
	>
>;

int main()
{
	try
	{
		typename Simplify<const char*> hi = "fsdfsd";
		Atlas::Throw<Atlas::ValidationException>( "Hi there", "I have been extended" );
	}
	catch ( Atlas::Exception& e )
	{
		std::cout << e.ToString() << std::endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
