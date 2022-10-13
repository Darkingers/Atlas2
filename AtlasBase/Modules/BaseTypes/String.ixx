module;

#include "../../../Macros/Macros.h"

export module AtlasBaseTypes:String;

import AtlasConcepts;
import AtlasAdapters;

export namespace Atlas
{
	class DLLApi String 
	{
		private: template<typename TestedType>
		constexpr static bool IsNoexceptIndexable = noexcept( std::declval<TestedType>( ).operator[]( unsigned int ) );
		
		private: const char* _data;
		private: unsigned int _size;

			
		public: template<unsigned int Size>
		constexpr String ( const char ( &data )[Size] )
			noexcept :
			_data( data ) ,
			_size( Size - 1 )
		{}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int, char>
		constexpr String( const StringType& copy )
			noexcept ( IsNoexceptIndexable<StringType> ) :
			_size( Adapter::Count( copy ) )
		{
			for(unsigned int i = 0;i<_size;++i )
			{
				_data[i] = copy[i];
			}
		}
		
		public:
		constexpr String( const char* data , unsigned int size ) 
			noexcept :
			_data( data ) ,
			_size( size )
		{}
			
		public:
		constexpr String( const char* data )
			noexcept :
			_data( data ) ,
			_size( 0 )
		{
			while ( data[_size] != '\0' )
			{
				_size++;
			}
		}

		public:
		constexpr String( const String& other ) 
			noexcept :
			_data( other._data ) ,
			_size( other._size )
		{}

		public: 
		constexpr String( String&& other ) 
			noexcept :
			_data( other._data ) ,
			_size( other._size )
		{}

		public:
		constexpr String( ) 
			noexcept :
			_data( nullptr ) ,
			_size( 0 )
		{}
		
		public:
		constexpr bool Match(unsigned int start, const char* string ) const
			noexcept
		{
			unsigned int i = 0;
			while ( string[i] != '\0' )
			{
				if ( _data[start + i] != string[i] )
				{
					return false;
				}
				i++;
			}
			
			return true;
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool Match(unsigned int start, const StringType& string ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			auto size = Adapter::Count( string );
			for(int i = 0;i<size;++i )
			{
				if ( _data[start + i] != string[i] )
				{
					return false;
				}
			}

			return true;
		}

		public: 
		constexpr bool StartsWith( const char* string ) const
			noexcept
		{
			return Match( 0 , string );
		}
		
		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool StartsWith( const StringType string ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			return Match( 0 , string );
		}

		public:
		constexpr bool EndsWith( const char* string ) const
			noexcept
		{
			const unsigned int stringSize = Adapter::Count( string );

			if ( stringSize > _size )
			{
				return false;
			}

			return Match( _size - stringSize , string );
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool EndsWith( const StringType& string ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			const unsigned int stringSize = Adapter::Count( string );

			if ( stringSize > _size )
			{
				return false;
			}

			return Match( _size - string._size , string );
		}

		public:
		constexpr bool Contains( const char* string ) const
			noexcept
		{
			for ( unsigned int i = 0; i < _size; ++i )
			{
				if ( Match( i , string ) )
				{
					return true;
				}
			}
				
			return false;
		}

		public:template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool Contains( const StringType& string )
			noexcept( IsNoexceptIndexable<StringType> )
		{
			if ( Adapter::Count( string ) > _size )
			{
				return false;
			}

			for ( unsigned int i = 0; i < _size; i++ )
			{
				if ( Match( i , string ) )
				{
					return true;
				}
			}

			return false;
		}

		public:
		constexpr unsigned int Occurence( const char* string ) const
			noexcept
		{
			unsigned int occurence = 0;
			const unsigned int size = Adapter::Count( string );
			
			for ( unsigned int i = 0; i < _size; )
			{
				if ( Match( i , string ) )
				{
					occurence++;
					i += size;
				}
				else
				{
					i++;
				}
			}

			return occurence;
		}
	
		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr unsigned int Occurence( const StringType& string ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			unsigned int occurence = 0;
			const unsigned int size = Adapter::Count( string );

			for ( unsigned int i = 0; i < _size; )
			{
				if ( Match( i , string ) )
				{
					occurence++;
					i += size;
				}
				else
				{
					i++;
				}
			}

			return occurence;
		}
		
		public:
		constexpr String& operator=( const String& other )
			noexcept
		{
			_data = other._data;
			_size = other._size;

			return *this;
		}

		public:
		constexpr String& operator=( String&& other )
			noexcept
		{
			_data = other._data;
			_size = other._size;

			return *this;
		}

		public:
		constexpr bool operator==( const String& other )
			noexcept
		{
			if ( _size != other._size )
			{
				return false;
			}

			for ( unsigned int i = 0; i < _size; i++ )
			{
				if ( _data[i] != other._data[i] )
				{
					return false;
				}
			}

			return true;
		}

		public:
		constexpr bool operator!=( const String& other )
			noexcept
		{
			return !( *this == other );
		}

		public:
		constexpr bool operator<( const String& other )
			noexcept
		{
			unsigned int minSize = _size < other._size ? _size : other._size;

			for ( unsigned int i = 0; i < minSize; i++ )
			{
				if ( _data[i] < other._data[i] )
				{
					return true;
				}
				else if ( _data[i] > other._data[i] )
				{
					return false;
				}
			}

			return _size < other._size;
		}

		public:
		constexpr bool operator>( const String& other )
			noexcept
		{
			unsigned int minSize = _size < other._size ? _size : other._size;

			for ( unsigned int i = 0; i < minSize; i++ )
			{
				if ( _data[i] > other._data[i] )
				{
					return true;
				}
				else if ( _data[i] < other._data[i] )
				{
					return false;
				}
			}

			return _size > other._size;
		}

		public:
		constexpr bool operator<=( const String& other )
			noexcept
		{
			return !( *this > other );
		}

		public:
		constexpr bool operator>=( const String& other )
			noexcept
		{
			return !( *this < other );
		}

		public:
		constexpr char operator[]( const unsigned int index ) const
		{
			return 
		}
	};
}