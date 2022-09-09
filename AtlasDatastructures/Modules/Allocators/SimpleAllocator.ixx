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
		SimpleAllocator( )  :
			_location( nullptr ) ,
			_size( 0 ) 
		{

		}

		public:
		SimpleAllocator( unsigned int size )  :
			_location( new DataType[size] ) ,
			_size( size ) 
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( size );
			}
		}

		public:
		SimpleAllocator( DataType* location , unsigned int size )  :
			_location( location ) ,
			_size( size ) 
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( size );
				if ( size > 0 )
				{
					Ensure::IsNotNull( location );
				}
			}
		}

		public:
		~SimpleAllocator( )  final
		{
			Empty( );
		}

		public:
		inline unsigned int GetSize( )const  final
		{
			return _size;
		}

		public:
		void Allocate( const unsigned int newSize )  final
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( newSize );
				if ( _size > 0 )
				{
					Ensure::IsNotNull( _location );
				}
			}
		
			DataType* newMemory = new DataType[newSize];

			DataFunctions::Copy( _location , _size , newMemory );

			Empty( );

			_location = newMemory;

			_size = newSize;
		}

		public:
		DataType& operator[]( const unsigned int index ) final
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( index );
				Ensure::IsLess( index , _size );
				Ensure::IsNotNull( _location );
			}

			return _location[index];
		}

		public:
		void Empty( ) final
		{
			if ( _size > 0 )
			{
				delete[] _location;
			}
		}
	};
}
