module;

#include "../../../../Macros/Macros.h"

export module AtlasTypes:StaticString;

import AtlasConfiguration;
import AtlasValidation;
import AtlasAPI;

namespace Atlas
{
	template<unsigned int BufferSize = Configuration::StaticStringBufferSize>
	class DLLApi StaticString
	{
		private: char _data[BufferSize];
		private: unsigned int _length;

		
		public: template<unsigned int OtherSize>
		constexpr StaticString( const char( &data )[OtherSize] )
			noexcept(!Configuration::EnableStaticStringCheck )
		{
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , OtherSize );

			CopyImpl( data ,0, OtherSize );

			_length = OtherSize;
		}

		public:
		constexpr StaticString( const char* data )
			noexcept( !Configuration::EnableStaticStringCheck )
		{		
			if ( data != nullptr )
			{
				unsigned int i = 0;
				char current;
				while ( ( current = data[i] ) != '\0' )
				{
					Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , i );
					
					_data[i++] = current;
				}

				_length = i-1;
			}
			else
			{
				_length = 0;
			}
		}

		public: template<typename StringType>
		constexpr StaticString( const StringType& string )
			noexcept( !Configuration::EnableStaticStringCheck )
		{
			auto length = CollectionAPI::Count<char>( string );

			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , length );

			CopyImpl( string , 0 , length );

			_length = length;
		}
			
		public:
		constexpr ~StaticString( ) = default;

		public:
		constexpr unsigned int Length( ) 
			const noexcept
		{
			return _length;
		}

		public:
		constexpr unsigned int MaxLength( )
			const noexcept
		{
			return BufferSize-1;
		}

		public:
		constexpr auto SubString( unsigned int inclusiveStart , unsigned int exclusiveEnd )
			const noexcept( !Configuration::EnableStaticStringCheck )
		{
			StaticString<BufferSize> result;

			result.Copy( *this , inclusiveStart , exclusiveEnd );

			return result;
		}


		public: template<typename StringType>
		constexpr void Copy( const StringType& string , unsigned int inclusivStart , unsigned int exclusiveEnd )
			noexcept( !Configuration::EnableStaticStringCheck )
		{
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , exclusiveEnd );
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( exclusiveEnd , inclusivStart );

			CopyImpl( string , inclusivStart , exclusiveEnd );

			_length = exclusiveEnd - inclusivStart;
		}

		public:
		constexpr char operator[]( unsigned int index )
			noexcept ( !Configuration::EnableStaticStringCheck )
		{
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , index );

			return _data[index];
		}	
		
		private:template<typename StringType>
		constexpr void CopyImpl( const StringType& string , unsigned int inclusivStart , unsigned int exclusiveEnd )
			noexcept
		{
			for ( unsigned int i = inclusivStart; i < exclusiveEnd; ++i )
			{
				_data[i] = string[i];
			}
		}
	};
}
