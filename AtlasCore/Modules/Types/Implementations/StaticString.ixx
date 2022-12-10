module;

#include "../../../../Macros/Macros.h"

export module AtlasTypes:StaticString;

import AtlasConfiguration;
import AtlasValidation;
import AtlasAPI;

namespace Atlas
{
	/// <summary>
	/// A compile-time evaluation compatible string
	/// </summary>
	/// <typeparam name="BufferSize">Maximum length of the string</typeparam>
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

		/// <summary>
		/// Returns the current length of the string
		/// </summary>
		public:
		constexpr unsigned int Length( ) 
			const noexcept
		{
			return _length;
		}

		/// <summary>
		/// Returns the maximum length of the string
		/// </summary>
		public:
		constexpr unsigned int MaxLength( )
			const noexcept
		{
			return BufferSize;
		}
		
		/// <summary>
		/// Checks whether it contains the given string.
		/// </summary>
		public: template<typename StringType>
		constexpr bool Contains( const StringType& string )
			const noexcept
		{
			auto length = CollectionAPI::Count<char>( string );

			if ( length > _length )
			{
				return false;
			}

			for ( unsigned int i = 0; i < _length; i++ )
			{
				if ( this->MatchFromImpl( string , i , length ) )
				{
					return true;
				}
			}

			return false;
		}

		/// <summary>
		/// Counts the occurence of the given string
		/// </summary>
		public: template<typename StringType>
		constexpr unsigned int Count( const StringType& string )
			const noexcept
		{
			auto length = CollectionAPI::Count<char>( string );

			if ( length > _length )
			{
				return 0;
			}

			return this->CountImpl( string, length );
		}
			
		/// <summary>
		/// Creates a substring with the specified range
		/// </summary>
		public:
		constexpr auto SubString( unsigned int inclusiveStart , unsigned int exclusiveEnd )
			const noexcept( !Configuration::EnableStaticStringCheck )
		{
			StaticString<BufferSize> result;

			result.Copy( *this , inclusiveStart , exclusiveEnd );

			return result;
		}
	
		/// <summary>
		/// Checks whether the it starts with the given string
		/// </summary>
		public: template<typename StringType>
		constexpr bool StartsWith( const StringType string )
			const noexcept
		{
			auto length = CollectionAPI::Count<char>( string );

			if ( length > _length )
			{
				return false;
			}

			return this->MatchFromImpl( string , 0, length );
		}
	
		/// <summary>
		/// Checks whether the it ends with the given string
		/// </summary>
		public:template<typename StringType>
		constexpr bool EndsWith( const StringType string )
			const noexcept
		{
			auto length = CollectionAPI::Count<char>( string );

			//Early check
			if ( length > _length )
			{
				return false;
			}
	
			return this->MatchFromImpl( string , _length - length, length );
		}

		/// <summary>
		///Copies the given part of the the given string
		/// </summary>
		public: template<typename StringType>
		constexpr void Copy( const StringType& string , unsigned int inclusivStart , unsigned int exclusiveEnd )
			noexcept( !Configuration::EnableStaticStringCheck )
		{
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , exclusiveEnd );
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( exclusiveEnd , inclusivStart );

			this->CopyImpl( string , inclusivStart , exclusiveEnd );

			_length = exclusiveEnd - inclusivStart;
		}

		/// <summary>
		/// Concats the given strings to the current
		/// </summary>
		public: template<typename StringType, typename... Args>
		consteval auto Concat(const StringType& current, const Args&... args )
			const noexcept
		{
			//Concat the current string
			this->CopyImpl( current , _length , _length+CollectionAPI::Count<char>( current ) );
			
			//Concat the rest
			if constexpr ( sizeof...( args ) > 0 )
			{
				return this->Concat( args... );
			}
			else
			{
				return *this;
			}
		}

		public:
		constexpr char operator[]( unsigned int index )
			noexcept ( !Configuration::EnableStaticStringCheck )
		{
			//Validate the index
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , index );

			return _data[index];
		}	
		
		private: template<typename StringType>
		constexpr unsigned int CountImpl( const StringType& string, const unsigned int length )
			const noexcept
		{
			unsigned int count = 0;

			for ( unsigned int i = 0; i < _length; i++ )
			{
				if ( this->MatchFromImpl( string , i, length ) )
				{
					count++;
				}
			}

			return count;
		}

		private: template<typename StringType>
		constexpr void CopyImpl( const StringType& string , unsigned int inclusivStart , unsigned int exclusiveEnd )
			noexcept
		{
			//Copy the given range
			for ( unsigned int i = inclusivStart; i < exclusiveEnd; ++i )
			{
				_data[i] = string[i];
			}
		}

		private: template<typename StringType>
		constexpr void MatchFromImpl( const StringType& string , unsigned int start , unsigned int matchLength )
			const noexcept
		{
			//Check if string matches from the start index
			for ( unsigned int i = 0; i < matchLength; i++ )
			{
				if ( _data[start + i] != string[i] )
				{
					return false;
				}
			}

			return true;
		}
	};
}
