module;


#include "../../Macros/Macros.h"
#include <utility>

export module AtlasInterfaces:IAllocator;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi IAllocator
	{
		public:
		virtual ~IAllocator()  = 0;

		public:
		virtual unsigned int GetSize( ) const  = 0;

		public:
		virtual void Allocate( const unsigned int newSize ) = 0;

		public:
		virtual void Empty( )  =0 ;

		public:
		virtual DataType& operator[]( const unsigned int index ) = 0;
	};
}