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
		
	private: 
		
		char _data[BufferSize];
		unsigned int _length;

	public: 
		
		template<typename... StringType>
		constexpr StaticString( const StringType&... strings )
			noexcept( !Configuration::EnableStaticStringCheck )
			:
			_length( 0 )
		{
			if constexpr ( sizeof...(strings ) > 0 )
			{
				this->Concat( strings... );
			}
		}
			
		constexpr ~StaticString( ) = default;

		/// <summary>
		/// Returns the current length of the string
		/// </summary>
		constexpr unsigned int Length( ) 
			const noexcept
		{
			return _length;
		}

		/// <summary>
		/// Returns the string as a const char*
		/// </summary>
		constexpr const char* Data( )
			const noexcept
		{
			return _data;
		}

		/// <summary>
		/// Returns the maximum length of the string
		/// </summary>
		constexpr unsigned int MaxLength( )
			const noexcept
		{
			return BufferSize;
		}
		
		/// <summary>
		/// Checks whether it contains the given string.
		/// </summary>
		template<typename StringType>
		constexpr bool Contains( const StringType& string )
			const noexcept
		{
			auto length = CollectionAPI::Count<char>( string );

			if ( length > _length || length == 0 )
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
		template<typename StringType>
		constexpr unsigned int Count( const StringType& string )
			const noexcept
		{
			auto length = CollectionAPI::Count<char>( string );

			if ( length > _length || length == 0 )
			{
				return 0;
			}

			return this->CountImpl( string, length );
		}
			
		/// <summary>
		/// Creates a substring with the specified range
		/// </summary>
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
		template<typename StringType>
		constexpr bool StartsWith( const StringType string )
			const noexcept
		{
			auto length = CollectionAPI::Count<char>( string );

			if ( length > _length || length == 0 )
			{
				return false;
			}

			return this->MatchFromImpl( string , 0, length );
		}
	
		/// <summary>
		/// Checks whether the it ends with the given string
		/// </summary>
		template<typename StringType>
		constexpr bool EndsWith( const StringType string )
			const noexcept
		{
			auto length = CollectionAPI::Count<char>( string );

			if ( length > _length || length == 0 )
			{
				return false;
			}
	
			return this->MatchFromImpl( string , _length - length, length );
		}

		/// <summary>
		///Copies the given part of the the given string
		/// </summary>
		template<typename StringType>
		constexpr auto CopyBetween( const StringType& string , unsigned int inclusivStart , unsigned int exclusiveEnd )
			noexcept( !Configuration::EnableStaticStringCheck )
		{
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , exclusiveEnd );
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( exclusiveEnd , inclusivStart );

			this->CopyBetweenImpl( string , inclusivStart , exclusiveEnd );

			_length = exclusiveEnd - inclusivStart;

			return *this;
		}

		/// <summary>
		///Copies the string from the specified index.
		/// </summary>
		template<typename StringType>
		constexpr auto CopyFrom( const StringType& string , unsigned int start )
			noexcept( !Configuration::EnableStaticStringCheck )
		{
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , start );

			auto length = CollectionAPI::Count<char>( string );

			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize, start + length );

			this->CopyFromImpl( string , start, length );
			
			auto newLength = start + length;

			if ( newLength > _length )
			{
				_length = newLength;
			}

			return *this;
		}

		/// <summary>
		/// Returns the index of the first occurence of the given string
		/// </summary>
		template<typename StringType>
		constexpr long int IndexOf( const StringType& substring )
			const noexcept
		{
			auto substringLength = CollectionAPI::Count<char>( substring );
			if ( substringLength > _length )
			{
				return -1; // -1 indicates that the substring was not found
			}

			for ( unsigned int i = 0; i < _length; i++ )
			{
				if ( this->MatchFromImpl( substring , i , substringLength ) )
				{
					return i; // return the index of the first occurrence of the substring
				}
			}

			return -1; // substring was not found
		}
		
		/// <summary>
		/// Returns the index of the last occurence of the given string
		/// </summary>
		template<typename StringType>
		constexpr long int LastIndexOf( const StringType& substring )
			const noexcept
		{
			auto substringLength = CollectionAPI::Count<char>( substring );
			if ( substringLength > _length )
			{
				return -1; // -1 indicates that the substring was not found
			}

			for ( unsigned int i = _length - substringLength; i >= 0; i-- )
			{
				if ( this->MatchFromImpl( substring , i , substringLength ) )
				{
					return i; // return the index of the last occurrence of the substring
				}
			}

			return -1; // substring was not found
		}

		template<typename StringType>
		constexpr auto Trim( const StringType& trimString )
		{
			auto trimStringLength = CollectionAPI::Count<char>( trimString );

			if ( trimStringLength == 0 )
			{
				return *this;
			}
			
			// Trim from the end first, so we might have to copy less later
			unsigned int end = _length - trimStringLength;
			while ( this->MatchFrom( trimString , end , trimStringLength ) )
			{
				end -= trimStringLength;
			}

			_length = end + trimStringLength;
			
			// Trim from the start
			unsigned int start = 0;
				
			while ( this->MatchFrom( trimString , start, trimStringLength ) )
			{
				start += trimStringLength;
			}
		
			DataAPI::Copy( _data + start , _data , _length - start );
			
			_length -= start;

			return *this;
		}
		
		template<typename StringType>
		constexpr auto TrimStart( const StringType& trimString )
		{
			unsigned int start = 0;
			auto trimStringLength = CollectionAPI::Count<char>( trimString );

			while ( this->MatchFrom( trimString , start , trimStringLength ) )
			{
				start += trimStringLength;
			}

			DataAPI::Copy( _data + start, _data , _length - start );
			
			_length -= start;

			return *this;
		}

		template<typename StringType>
		constexpr auto TrimEnd( const StringType& trimString )
		{
			auto trimStringLength = CollectionAPI::Count<char>( trimString );
			
			// Trim from the end
			unsigned int end = _length - trimStringLength;
			while ( this->MatchFrom( trimString , end , trimStringLength ) )
			{
				end -= trimStringLength;
			}

			_length = end + trimStringLength;

			return *this;
		}

		/// <summary>
		/// Concats the given strings to the current
		/// </summary>
		template<typename StringType, typename... Args>
		consteval auto Concat(const StringType& current, const Args&... args )
			const noexcept
		{
			//Validate
			auto length = CollectionAPI::Count<char>( current );
			
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , _length + length );

			DataAPI::ReplaceFrom( _data[_length] , current , args... );

			_length = _length + length;

			return *this;
		}

		constexpr char operator[]( unsigned int index )
			noexcept ( !Configuration::EnableStaticStringCheck )
		{
			//Validate the index
			Validate<Configuration::EnableStaticStringCheck>::IsMoreOrEqual( BufferSize , index );

			return _data[index];
		}	
		
	private: 
		
		template<typename StringType>
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

	    template<typename StringType>
		constexpr void CopyBetweenImpl( const StringType& string , unsigned int inclusivStart , unsigned int exclusiveEnd )
			noexcept
		{

			for ( unsigned int i = inclusivStart; i < exclusiveEnd; ++i )
			{
				_data[i] = string[i];
			}
		}

		template<typename StringType>
		constexpr void CopyFromImpl( const StringType& string , unsigned int start , unsigned int count )
			noexcept
		{
			const unsigned int end = start + count;

			for ( unsigned int i = start , j = 0; i < end; ++i , ++j )
			{
				_data[j] = string[i];
			}
		}

		template<typename StringType>
		constexpr void MatchFromImpl( const StringType& string , unsigned int start , unsigned int matchLength )
			const noexcept
		{
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
