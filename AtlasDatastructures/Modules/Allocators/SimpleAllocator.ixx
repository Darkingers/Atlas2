module;

#include "../../../Macros/Macros.h"

export module AtlasAllocators:SimpleAllocator;
import AtlasInterfaces;
import AtlasValidation;
import AtlasConfiguration;
import AtlasDataFunctions;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi SimpleAllocator :
		public Interface::IAllocator<DataType>
	{
		private: DataType* _location;
		private: unsigned int _size;

		public:
		constexpr SimpleAllocator( )  :
			_location( nullptr ) ,
			_size( 0 ) 
		{

		}

		public:
		constexpr SimpleAllocator( unsigned int size )  :
			_location( new DataType[size] ) ,
			_size( size ) 
		{
			Argument::IsPositive( size );
		}

		public:
		constexpr SimpleAllocator( DataType* location , unsigned int size )  :
			_location( location ) ,
			_size( size ) 
		{
			Argument::IsPositive( size );
			if ( size > 0 )
			{
				Argument::IsNotNull( location );
			}
		}

		public:
		constexpr ~SimpleAllocator( )  final
		{
			Empty( );
		}

		public:
		constexpr inline unsigned int GetSize( )const  final
		{
			return _size;
		}

		public:
		constexpr void Allocate( const unsigned int newSize )  final
		{
			Argument::IsPositive( newSize );
			if ( _size > 0 )
			{
				Argument::IsNotNull( _location );
			}
		
			DataType* newMemory = new DataType[newSize];

			DataFunctions::Copy( _location , _size , newMemory );

			Empty( );

			_location = newMemory;

			_size = newSize;
		}

		public:
		constexpr DataType& operator[]( const unsigned int index ) final
		{
			Argument::IsPositive( index );
			Argument::IsLess( index , _size );
			Argument::IsNotNull( _location );

			return _location[index];
		}

		public:
		constexpr void Empty( ) final
		{
			if ( _size > 0 )
			{
				delete[] _location;
			}
		}
	};
}
