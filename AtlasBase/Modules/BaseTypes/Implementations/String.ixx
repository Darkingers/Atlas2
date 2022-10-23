module;

#include "../../../../Macros/Macros.h"

export module AtlasBaseTypes:StaticString;

import AtlasConcepts;
import AtlasAdapters;

export namespace Atlas
{
	template<unsigned int Size>
	class DLLApi StaticString 
	{
		private: template<typename TestedType>
		constexpr static bool IsNoexceptIndexable = noexcept( std::declval<TestedType>( ).operator[]( std::declval<unsigned int>() ) );
		
		private: char _data[Size];

		public: 
		constexpr StaticString( const char (&data)[Size])
			noexcept 
		{
			for ( unsigned int i = 0; i < Size; ++i )
			{
				_data[i] = data[i];
			}
		}

		public:
		constexpr StaticString( const StaticString<Size>& other )
			noexcept 
		{
			for ( unsigned int i = 0; i < Size; ++i )
			{
				_data[i] = other[i];
			}
		}
		
		public:
		constexpr bool Match(unsigned int start, const char* string ) const
			noexcept
		{
			unsigned int i = 0;
			while ( string[i] != '\0' )
			{
				if ( start + i >= Size || _data[start + i] != string[i] )
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
				if ( start + i >= Size || _data[start + i] != string[i] )
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

			if ( stringSize > Size )
			{
				return false;
			}

			return Match( Size - stringSize , string );
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool EndsWith( const StringType& string ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			const unsigned int stringSize = Adapter::Count( string );

			if ( stringSize > Size )
			{
				return false;
			}

			return Match( Size - string.Size , string );
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

		public:template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool Contains( const StringType& string )
			noexcept( IsNoexceptIndexable<StringType> )
		{
			if ( Adapter::Count( string ) > Size )
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

		public:
		constexpr unsigned int Occurence( const char* string ) const
			noexcept
		{
			unsigned int occurence = 0;
			const unsigned int size = Adapter::Count( string );
			
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
		constexpr unsigned int Occurence( const StringType& string ) const
			noexcept( IsNoexceptIndexable<StringType> )
		{
			unsigned int occurence = 0;
			const unsigned int size = Adapter::Count( string );

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
		
		public:
		constexpr bool operator==( const char* other )
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
		constexpr bool operator==( const StringType& other )
			noexcept( IsNoexceptIndexable<StringType> )
		{
			if ( Adapter::Count(other ) != Size)
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
		constexpr bool operator!=( const char* other )
			noexcept
		{
			return !( *this == other );
		}

		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator!=( const StringType& other )
			noexcept( IsNoexceptIndexable<StringType> )
		{
			return !( *this == other );
		}	

		public: 
		constexpr bool operator<( const char* other )
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
		constexpr bool operator<( const StringType& other )
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

			return Size < otherSize;
		}

		public:
		constexpr bool operator>( const char* other )
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
		constexpr bool operator>( const StringType& other )
			noexcept( IsNoexceptIndexable<StringType> )
		{
			unsigned int otherSize = Adapter::Count( other );
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

		public:
		constexpr bool operator<=( const char* other )
			noexcept
		{
			return !( *this > other );
		}
			
		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator<=( const StringType& other )
			noexcept( IsNoexceptIndexable<StringType> )
		{
			return !( *this > other );
		}

		public:
		constexpr bool operator>=( const char* other )
			noexcept
		{
			return !( *this < other );
		}
			
		public: template<typename StringType>
			requires Concept::HasIndexOperator<StringType , unsigned int , char>
		constexpr bool operator>=( const StringType& other )
			noexcept( IsNoexceptIndexable<StringType> )
		{
			return !( *this < other );
		}
		
		public:
		constexpr char operator[]( unsigned int index )
			noexcept
		{
			return _data[index];
		}

		public:
		
			
		
	};
}