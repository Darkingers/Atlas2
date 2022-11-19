module;

#include "../../../../Macros/Macros.h"

export module AtlasBaseTypes:StaticString;

import AtlasConcepts;
import AtlasAdapters;

export namespace Atlas
{
	template<unsigned int BufferSize = 500>
	class DLLApi StaticString 
	{
		private: template<typename TestedType>
		constexpr static bool IsNoexceptIndexable = noexcept( std::declval<TestedType>( ).operator[]( std::declval<unsigned int>() ) );
		
		private: char _data[BufferSize];
		private: unsigned int Size;

		public: template<unsigned int OtherSize>
		constexpr StaticString( const char (&data)[OtherSize])
			noexcept 
		{
			const unsigned int min = OtherSize < BufferSize ? OtherSize : BufferSize;
			for ( unsigned int i = 0; i < min; ++i )
			{
				_data[i] = data[i];
			}

			Size = min;
		}

		public:
		constexpr StaticString( char* data )
			noexcept
		{
			unsigned int i = 0;
			char current;
			while ( ( current = data[i] ) != '\0' && i < BufferSize )
			{
				_data[i] = current;
				++i;
			}

			Size = i;
		}

		public: template<typename StringType>
		constexpr StaticString( const StringType other )
			noexcept
		{
			const unsigned int min = other.length > BufferSize ? BufferSize : other.length;
			
			for ( unsigned int i = 0; i < min; ++i )
			{
				_data[i] = other[i];
			}

			Size = min;
		}

		public: template<unsigned int OtherSize>
		constexpr StaticString( const StaticString<OtherSize>& other )
			noexcept
		{
			const unsigned int min = OtherSize < BufferSize ? OtherSize : BufferSize;

			for ( unsigned int i = 0; i < min; ++i )
			{
				_data[i] = other[i];
			}

			Size = min;
		}

		public:
		constexpr ~StaticString( ) = default;
		
		public: template<unsigned int OtherSize>
		constexpr bool Match(unsigned int start, const char (&string)[OtherSize] ) const
			noexcept
		{
			if ( start > Size || start + OtherSize > Size )
			{
				return false;
			}

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
		constexpr bool Match(unsigned int start, const StringType& other )  const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			const auto otherSize = Adapter::Size( other );

			if ( start > Size || start + otherSize > Size )
			{
				return false;
			}
			
			for(int i = 0;i<otherSize;++i )
			{
				if ( _data[start + i] != other[i] )
				{
					return false;
				}
			}

			return true;
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool Match( unsigned int start , const StringType& other, unsigned int size ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			if ( start > Size || start + size > Size )
			{
				return false;
			}

			for ( int i = 0; i < size; ++i )
			{
				if ( _data[start + i] != other[i] )
				{
					return false;
				}
			}

			return true;
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool StartsWith( const StringType string )  const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			return Match( 0 , string );
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool EndsWith( const StringType& string ) 
			noexcept( IsNoexceptIndexable<StringType> )
		{
			const unsigned int stringSize = Adapter::Size( string );

			return Match( Size - stringSize , string, stringSize );
		}

		public:
		constexpr bool Contains( const char* string ) const
			noexcept
		{
			for ( unsigned int i = 0; i < Size; ++i )
			{
				if ( Match( i , string ) )
				{
					return true;
				}
			}
				
			return false;
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool Contains( const StringType& string ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			if ( Adapter::Size( string ) > Size )
			{
				return false;
			}

			for ( unsigned int i = 0; i < Size; i++ )
			{
				if ( Match( i , string ) )
				{
					return true;
				}
			}

			return false;
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr unsigned int Occurence( const StringType& string ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			unsigned int occurence = 0;
			const unsigned int size = Adapter::Size( string );

			for ( unsigned int i = 0; i < Size; )
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
		constexpr StaticString<BufferSize> Append( const StringType& string )
			noexcept( IsNoexceptIndexable<StringType> )
		{
			const unsigned int freeSpace = BufferSize - Size;
			const unsigned int min = Adapter::Size( string ) < freeSpace ? Adapter::Size( string ) : freeSpace;

			
		}
		
		public:
		constexpr bool operator==( const char* other ) const
			noexcept
		{
			unsigned int current = 0;

			while ( other[current] != '\0' )
			{
				if ( current >= Size || _data[current] != other[current] )
				{
					return false;
				}
				current++;
			}

			return true;
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator==( const StringType& other ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			if ( Adapter::Size(other ) != Size)
			{
				return false;
			}

			for ( unsigned int i = 0; i < Size; i++ )
			{
				if ( _data[i] != other[i] )
				{
					return false;
				}
			}

			return true;
		}	

		public:
		constexpr bool operator!=( const char* other ) const
			noexcept
		{
			return !( *this == other );
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator!=( const StringType& other )  const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			return !( *this == other );
		}	

		public: 
		constexpr bool operator<( const char* other ) const
			noexcept
		{
			unsigned int current = 0;

			while ( other[current] != '\0' )
			{
				if ( current >= Size || _data[current] < other[current] )
				{
					return true;
				}
				else if ( _data[current] > other[current] )
				{
					return false;
				}
				current++;
			}

			return false;
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator<( const StringType& other ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			unsigned int otherSize = Adapter::Count( other );
			unsigned int minSize = Size < otherSize ? Size : otherSize;

			for ( unsigned int i = 0; i < minSize; i++ )
			{
				if ( _data[i] < other[i] )
				{
					return true;
				}
				else if ( _data[i] > other[i] )
				{
					return false;
				}
			}

			return minSize < otherSize;
		}

		public:
		constexpr bool operator>( const char* other ) const
			noexcept
		{
			unsigned int current = 0;

			while ( other[current] != '\0' )
			{
				if ( current >= Size || _data[current] > other[current] )
				{
					return true;
				}
				else if ( _data[current] < other[current] )
				{
					return false;
				}
				current++;
			}

			return false;
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator>( const StringType& other ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			unsigned int otherSize = Adapter::Size( other );
			unsigned int minSize = Size < otherSize ? Size : otherSize;

			for ( unsigned int i = 0; i < minSize; i++ )
			{
				if ( _data[i] > other[i] )
				{
					return true;
				}
				else if ( _data[i] < other[i] )
				{
					return false;
				}
			}

			return Size > otherSize;
		}

			
		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator<=( const StringType& other ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			return !( *this > other );
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator>=( const StringType& other ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			return !( *this < other );
		}
		
		public:
		constexpr char& operator[]( unsigned int index )
			noexcept
		{
			return _data[index];
		}

		public: template<unsigned int OtherSize>
		constexpr auto operator+( const char (&other)[OtherSize] ) const
			noexcept
		{
			return StaticString<BufferSize + OtherSize>( *this );
		}
	};

	template<unsigned int Size>
	consteval auto ToString( const char( &string )[Size] ) noexcept
	{
		return StaticString<Size>( string );
	}
}