
module;

#include "../../../../Macros/Macros.h"

export module AtlasBaseTypes:Span;

import AtlasAdapters;
import AtlasValidation;
import AtlasConfiguration;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi Span
	{
		private: DataType* _data;
		private: unsigned int _size;

		public:
		Span(unsigned int size )
			noexcept (!Configuration::EnableSpanConstructorCheck )
		{
			Validate<Configuration::EnableSpanConstructorCheck>::IsPositive( size );

			_size = size;
			_data = new DataType[size];
		}

		public:
		Span( DataType * data , unsigned int size )
			noexcept ( !Configuration::EnableSpanConstructorCheck )
		{
			Validate<Configuration::EnableSpanConstructorCheck>::IsArray(data, size );

			_size = size;
			_data = data;
		}

		public:
		Span(const DataType* data , unsigned int size )
			noexcept ( !Configuration::EnableSpanConstructorCheck )
		{
			Validate<Configuration::EnableSpanConstructorCheck>::IsArray( data , size );

			_size = size;
			
			_data = new DataType[size];
			for ( unsigned int j = 0; j < size; ++j )
			{
				_data[j] = data[j];
			}
		}

		public:
		Span( DataType* begin ,const DataType* end )
			noexcept ( !Configuration::EnableSpanConstructorCheck )
		{
			_size = end - begin;
			
			Validate<Configuration::EnableSpanConstructorCheck>::IsArray(begin, _size );
			
			_data = begin;
		}

		public:
		Span( const DataType* begin ,const DataType* end )
			noexcept ( !Configuration::EnableSpanConstructorCheck )
		{
			_size = end - begin;

			Validate<Configuration::EnableSpanConstructorCheck>::IsArray( begin , _size );

			_data = new DataType[_size];		
			for ( unsigned int j = 0; j < _size; ++j )
			{
				_data[j] = begin[j];
			}
		}

		public: template<unsigned int Size>
		Span( DataType (&data)[Size] )
			noexcept :
			_data( data ),
			_size( Size )
		{
			
		}

		public: template<unsigned int Size>
		Span(const DataType( &data )[Size] )
			noexcept :
			_size( Size )
		{
			_data = new DataType[_size];
			for ( unsigned int j = 0; j < _size; ++j )
			{
				_data[j] = data[j];
			}			
		}

		public:
		Span( const Span& other )
			noexcept :
			_data( other._data ) ,
			_size( other._size )
		{}

		public:
		Span( Span&& other )
			noexcept :
			_data( other._data ) ,
			_size( other._size )
		{}

		public:
		Span( )
			noexcept :
			_data( nullptr ) ,
			_size( 0 )
		{}
		
		public:
		~Span( )
			noexcept
		{
			if ( _size > 0 )
			{
				delete[] _data;
			}
		}

		public:
		DataType& operator[]( unsigned int index )
			noexcept(!Configuration::EnableSpanIndexCheck )
		{
			Validate<Configuration::EnableSpanIndexCheck>::ExclusiveRange( index , -1 , _size );

			return _data[index];
		}
		
		public:
		const DataType* Data( ) const
			noexcept
		{
			return _data;
		}
		
		public:
		unsigned int Size( ) const
			noexcept
		{
			return _size;
		}

		public:
		DataType* begin( )
			noexcept
		{
			return _data;
		}

		public:
		const DataType* cbegin( ) const
			noexcept
		{
			return _data;
		}
			
		public:
		DataType* end( )
			noexcept
		{
			return _data + _size;
		}

		public:
		const DataType* cend( ) const
			noexcept
		{
			return _data + _size;
		}

		public:
		bool IsEmpty( ) const
			noexcept
		{
			return _size == 0;
		}

		public:
		bool IsNotEmpty( ) const
			noexcept
		{
			return _size > 0;
		}

		public:
		bool operator==( const Span& other ) const
			noexcept
		{
			if ( _size != other._size )
			{
				return false;
			}

			for ( unsigned int j = 0; j < _size; ++j )
			{
				if ( _data[j] != other._data[j] )
				{
					return false;
				}
			}

			return true;
		}

		public:
		bool operator!=( const Span& other ) const
			noexcept
		{
			return !operator==( other );
		}

		public:
		bool operator<( const Span& other ) const
			noexcept
		{
			if ( _size < other._size )
			{
				return true;
			}

			if ( _size > other._size )
			{
				return false;
			}

			for ( unsigned int j = 0; j < _size; ++j )
			{
				if ( _data[j] < other._data[j] )
				{
					return true;
				}

				if ( _data[j] > other._data[j] )
				{
					return false;
				}
			}

			return false;
		}
			
		public:
		bool operator>( const Span& other ) const
			noexcept
		{
			if ( _size > other._size )
			{
				return true;
			}

			if ( _size < other._size )
			{
				return false;
			}

			for ( unsigned int j = 0; j < _size; ++j )
			{
				if ( _data[j] > other._data[j] )
				{
					return true;
				}

				if ( _data[j] < other._data[j] )
				{
					return false;
				}
			}

			return false;
		}

		public:
		bool operator<=( const Span& other ) const
			noexcept
		{
			return !operator>( other );
		}

		public:
		bool operator>=( const Span& other ) const
			noexcept
		{
			return !operator<( other );
		}					
	};
}
