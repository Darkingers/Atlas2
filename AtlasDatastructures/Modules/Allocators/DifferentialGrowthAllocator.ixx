module;

#include "../../../Macros/Macros.h"

export module AtlasAllocators:DifferentialGrowthAllocator;
import AtlasInterfaces;
import AtlasValidation;
import AtlasConfiguration;
import AtlasDataFunctions;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi DifferentialGrowthAllocator :
		public Interface::IAllocator<DataType>
	{
		private: DataType* _location;
		private: unsigned int _size;
		private: unsigned int _allocatedSize;

		public:
		constexpr DifferentialGrowthAllocator( )  :
			_location( nullptr ) ,
			_size( 0 ) ,
			_allocatedSize( 0 )
		{

		}

		public:
		constexpr DifferentialGrowthAllocator( unsigned int size )  :
			_location( new DataType[size] ) ,
			_size( size ) ,
			_allocatedSize( size )
		{
			Validate::IsPositive( size );
		}

		public:
		constexpr DifferentialGrowthAllocator( DataType* location , unsigned int size )  :
			_location( location ) ,
			_size( size ) ,
			_allocatedSize( size )
		{
			Validate::IsPositive( size );
			if ( size > 0 )
			{
				Validate::IsNotNull( location );
			}
		}

		public:
		constexpr ~DifferentialGrowthAllocator( )  final
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
			Validate::IsPositive( newSize );
			if ( _size > 0 )
			{
				Validate::IsNotNull( _location );
			}

			if ( newSize > _allocatedSize )
			{
				DataType* newMemory = new DataType[newSize];

				DataFunctions::Copy( _location , _size , newMemory );

				Empty( );

				_allocatedSize = newSize;

				_location = newMemory;
			}

			_size = newSize;
		}

		public:
		constexpr DataType& operator[]( const unsigned int index ) final
		{
			Validate::IsPositive( index );
			Validate::IsLess( index , _size );
			Validate::IsNotNull( _location );

			return _location[index];
		}

		public:
		constexpr void Empty()  final
		{
			if ( _allocatedSize > 0 )
			{
				delete[] _location;
			}
		}
	};
}
