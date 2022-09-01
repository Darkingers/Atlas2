module;


#include "../../Macros/Macros.h"
#include <utility>

export module AtlasInterfaces:IAllocator;

export namespace Atlas
{
	template<typename Data>
	class DLLApi IAllocator
	{
		virtual ~IAllocator()  = 0;

		virtual unsigned int GetSize( ) const  = 0;

		virtual void Allocate( const unsigned int newSize ) = 0;

		virtual void Empty( )  =0 ;

		virtual Data& operator[]( const unsigned int index ) = 0;
	};
}