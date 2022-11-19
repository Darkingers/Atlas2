module;

#include "../../../../Macros/Macros.h"

export module AtlasBaseTypes:String;

import AtlasConcepts;
import AtlasValidation;
import AtlasConfiguration;
import AtlasAdapters;

export namespace Atlas
{
	class DLLApi String
	{
		private: char* _data;
		private: unsigned int _size;
		private: unsigned int _allocatedSize;

			
		public:
		String( )
			noexcept :
			_size( 0 ) ,
			_data( nullptr ) ,
			_allocatedSize( 0 )
		{}
			
		public:
		String( char* data, unsigned int size ) 
			noexcept:
			_size(size ),
			_data(data ),
			_allocatedSize(size )
		{}

		public:
		String( const char* data ) 
			noexcept:
			_size( Adapter::Size(data) ),
			_data( new char[_size] ),
			_allocatedSize(_size )
			
		{
			for ( unsigned int j = 0; j < _size; ++j )
			{
				_data[j] = data[j];
			}
		}

		public: template<unsigned int Size>
		String( const char( &data )[Size] )
			noexcept :
			_size( Size ) ,
			_data( new char[_size] ) ,
			_allocatedSize( _size )

		{
			for ( unsigned int j = 0; j < _size; ++j )
			{
				_data[j] = data[j];
			}
		}

		public: 
		String( const String& other )
			noexcept :
			_size( other.Size( ) ) ,
			_data( new char[_size] ) ,		
			_allocatedSize( _size )
		{
			for ( unsigned int i = 0; i < _size; ++i )
			{
				_data[i] = other._data[i];
			}
		}

		public:
		String( const std::string& other )
			noexcept :
			_size( other.size( ) ),
			_data( new char[_size] ) ,
			_allocatedSize( _size )
		{
			for ( unsigned int i = 0; i < _size; ++i )
			{
				_data[i] = other[i];
			}
		}

		public: template<typename... StringType>
		String( const StringType&... other )
			noexcept :
			_size( 0) ,
			_data( nullptr ) ,
			_allocatedSize( 0)
		{
			String::Copy( other... );
		}
		
		public:
		~String( ) 
			noexcept
		{
			if( _allocatedSize>0 )
			{
				delete[] _data;
			}
		}

		public:
		inline unsigned int Size( )
			const noexcept
		{
			return _size;
		}

		public:
		inline const char* Data( )
			const noexcept
		{
			return _data;
		}

		public: template<typename... StringType>
		String& Copy( const StringType&... other )
			noexcept
		{
			const unsigned int otherSize = ( ( Adapter::Size( other ) ) + ... );
			
			if ( otherSize > _allocatedSize )
			{
				delete[] _data;
				_data = new char[otherSize];
				_allocatedSize = otherSize;
			}
			
			unsigned int current = 0;
			( current += String::CopyImpl( other , current ) , ... );

			return *this;
		}

		private: template<typename StringType>
		unsigned int CopyImpl( const StringType& other , unsigned int offset = 0 )
			noexcept( !Configuration::EnableStringCopyCheck )
		{
			const unsigned int otherSize = Adapter::Size( other );

			for ( unsigned int i = 0; i < otherSize; ++i )
			{
				_data[offset + i] = other[i];
			}

			return otherSize;
		}

		public: template<typename... StringType>
		String& Concat( const StringType&... other )
			noexcept
		{
			const unsigned int otherSize =( (Adapter::Size( other )) + ...);
			const unsigned int newSize = _size + otherSize;

			if ( newSize > _allocatedSize )
			{
				char* newData = new char[newSize];
				for ( unsigned int i = 0; i < _size; ++i )
				{
					newData[i] = _data[i];
				}

				delete[] _data;
				_data = newData;
				_allocatedSize = newSize;
			}

			unsigned int current = _size;
			( current += String::CopyImpl( other , current ) , ... );
			
			return *this;
		}

		public: template<typename... StringType>
		bool Match(const StringType&... other )const 
			noexcept
		{
			for ( unsigned int i = 0; i < _size; ++i )
			{
				if ( String::MatchImpl( i , other... ) )
				{
					return true;
				}
			}
		
			return false;
		}
			
		private: template<typename CurrentType, typename... StringType>
		bool MatchImpl( unsigned int offset ,const CurrentType& current, const StringType&... other )const
			noexcept
		{
			const unsigned int currentSize = Adapter::Size( current );
			if ( offset + currentSize > _size )
			{
				return false;
			}

			for ( unsigned int i = 0; i < currentSize; ++i )
			{
				if ( _data[offset + i] != current[i] )
				{
					return false;
				}
			}

			if constexpr ( sizeof...( StringType ) > 0 )
			{
				return String::MatchImpl( offset + currentSize , other... );
			}
			else
			{
				return true;
			}
		}		

		public: template<typename... StringType>
		bool MatchFrom(unsigned int offset, const StringType&... other )const 
			noexcept(!Configuration::EnableStringMatchCheck )
		{
			Validate<Configuration::EnableStringMatchCheck>::ExclusiveRange( offset , -1 , _size );

			return String::MatchImpl( offset , other... );
		}

		public: template<typename... StringType>
		bool StartsWith( const StringType&... other ) const
			noexcept
		{
			return String::MatchFrom( 0 , other... );
		}

		public: template<typename... StringType>
		bool EndsWith( const StringType&... other )const 
			noexcept
		{
			const unsigned int otherSize = ( ( Adapter::Size( other ) ) + . .. );
			if ( otherSize > _size )
			{
				return false;
			}

			unsigned int current = _size - otherSize;
			return String::MatchImpl( current , other... );
		}

		public: template<typename StringType>
		bool Contains( const StringType& other ) const
			noexcept
		{
			return String::Match( other );
		}

		public: template<typename StringType>
		unsigned int Occurence( const StringType& other )const
			noexcept
		{
			const unsigned int otherSize = Adapter::Size( other );

			unsigned int occurence = 0;
			bool found;
			
			for ( unsigned int i = 0; i < _size; )
			{
				found = true;
				for ( unsigned j = i; j < otherSize; ++j )
				{
					if ( _data[j] != other[j] )
					{
						found = false;
						break;
					}
				}

				if ( found )
				{
					++occurence;
					i += otherSize;
				}
				else
				{
					++i;
				}
			}

			return occurence;
		}

		public: template<typename StringType>
		String SubString(unsigned int inclusiveFrom, unsigned int exclusiveTo ) const
		{
			Validate<Configuration::EnableStringSubStringCheck>::ExclusiveRange( inclusiveFrom , -1 , _size );
			Validate<Configuration::EnableStringSubStringCheck>::ExclusiveRange( exclusiveTo , inclusiveFrom , _size );

			const unsigned int newSize = exclusiveTo - inclusiveFrom;
			char* newData = new char[newSize];
			for ( unsigned int i = 0; i < newSize; ++i )
			{
				newData[i] = _data[inclusiveFrom + i];
			}

			return String( newData , newSize );
		}

		public: template<typename StringType>
		String& Replace( const StringType& from , const StringType& to )
			noexcept
		{
			const unsigned int fromSize = Adapter::Size( from );
			const unsigned int toSize = Adapter::Size( to );

			if ( fromSize == 0 )
			{
				return *this;
			}

			unsigned int occurence = String::Occurence( from );
			if ( occurence == 0 )
			{
				return *this;
			}

			const unsigned int newSize = _size + ( toSize - fromSize ) * occurence;
			char* newData = new char[newSize];

			unsigned int current = 0;
			unsigned int i = 0;
			while ( i < _size )
			{
				if ( String::MatchImpl( i , from ) )
				{
					for ( unsigned int j = 0; j < toSize; ++j )
					{
						newData[current + j] = to[j];
					}

					current += toSize;
					i += fromSize;
				}
				else
				{
					newData[current] = _data[i];
					++current;
					++i;
				}
			}

			delete[] _data;
			_data = newData;
			_size = newSize;
			_allocatedSize = newSize;

			return *this;
		}

			
		public:
		inline char& operator[]( unsigned int index ) 
			noexcept( !Configuration::EnableStringIndexCheck )
		{
			Validate<Configuration::EnableStringIndexCheck>::ExclusiveRange( index , -1 , _size );
			
			return _data[index];
		}
	};
}
