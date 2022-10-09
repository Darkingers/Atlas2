// Tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import AtlasExceptions;
import AtlasDefinitions;
import AtlasAdapters;
import AtlasConverters;
import AtlasExtensions;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <vector>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

int main()
{
	std::string g = "Hi there";

	char* t = new char[400];
	delete[] t;
	std::vector<int> vec;

	for ( int i = 0; i < 10000; ++i )
	{
		vec.push_back( i );
	}
	
	for ( int i = 0; i < 1000000000; ++i )
	{
		try
		{		
			//throw std::make_tuple( 1 , 2 , 3 , 4 , 5 , 5 );

			Atlas::Throw<Atlas::ValidationException>(g, 1, 2,3, 4,5 );
		}
		catch ( Atlas::Exception& e )
		{
			std::cout<< e.ToString( );
		}
		catch ( std::string& e)
		{
			std::cout << e;
		}
		catch ( std::tuple<int , int , int , int , int , int>& tuple )
		{
			std::cout << std::get<0>( tuple ) << std::endl;
			std::cout << std::get<1>( tuple ) << std::endl;
			std::cout << std::get<2>( tuple ) << std::endl;
			std::cout << std::get<3>( tuple ) << std::endl;
			std::cout << std::get<4>( tuple ) << std::endl;
			std::cout << std::get<5>( tuple ) << std::endl;
		}
		catch ( ... )
		{
			std::cout << "Unknown exception";
		}
	}

	_CrtDumpMemoryLeaks( );
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
