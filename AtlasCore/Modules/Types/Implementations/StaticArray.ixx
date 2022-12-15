module;

#include "../../../../Macros/Macros.h"

export module AtlasTypes:StaticArray;

import AtlasConfiguration;
import AtlasValidation;
import AtlasAPI;

namespace Atlas
{
	/// <summary>
	/// A compile-time evaluation compatible array
	/// </summary>
	/// <typeparam name="BufferSize">Maximum length of the array</typeparam>
	template<typename TElement, unsigned int BufferSize = Configuration::StaticArrayBufferSize>
	class DLLApi StaticArray
	{
		
	private: 
		
		TElement _data[BufferSize];
		unsigned int _length;

	public: 
		
		template<typename... Args>
		constexpr StaticArray( const Args&... args )
			noexcept( !Configuration::EnableStaticArrayCheck ) :
			_length( 0 )
		{
			if constexpr ( sizeof...( args ) > 0 )
			{
				this->Concat( args... );
			}
		}
			
		constexpr ~StaticArray( ) = default;

		/// <summary>
		/// Returns the current length of the array
		/// </summary>
		constexpr unsigned int Length( ) 
			const noexcept
		{
			return _length;
		}

		/// <summary>
		/// Returns the data as const TElement*
		/// </summary>
		constexpr const TElement* Data( )
			const noexcept
		{
			return _data;
		}

		/// <summary>
		/// Returns the maximum length of the array
		/// </summary>
		constexpr unsigned int MaxLength( )
			const noexcept
		{
			return BufferSize;
		}
		
		/// <summary>
		/// Checks whether it contains the given data.
		/// </summary>
		template<typename T>
		constexpr bool Contains( const T& data )
			const noexcept
		{
			const auto length = QueryAPI::Count<TElement>( data );

			if ( length > _length || length == 0 )
			{
				return false;
			}

			for ( unsigned int i = 0; i < _length - length; ++i )
			{
				if ( QueryAPI::IsMatch( _data[i] , IteratorAPI::ConstBegin( data ), length ) )
				{
					return true;
				}
			}

			return false;
		}

		/// <summary>
		/// Counts the occurence of the given data
		/// </summary>
		template<typename T>
		constexpr unsigned int Count( const T& data )
			const noexcept
		{
			const auto length = QueryAPI::Count<TElement>( data );

			if ( length > _length || length == 0 )
			{
				return 0;
			}

			unsigned int count = 0;

			for ( unsigned int i = 0; i < _length - length; ++i )
			{
				if ( QueryAPI::IsMatch( _data[i] , IteratorAPI::ConstBegin( data ) , length ) )
				{
					count++;
				}
			}

			return count;
		}
			
		/// <summary>
		/// Creates a subarray with the specified range
		/// </summary>
		constexpr auto SubArray( unsigned int inclusiveStart , unsigned int exclusiveEnd )
			const noexcept( !Configuration::EnableStaticArrayCheck )
		{
			StaticArray<BufferSize> result;

			result.CopyFromBetween( *this , inclusiveStart , exclusiveEnd );

			return result;
		}
	
		/// <summary>
		/// Checks whether the it starts with the given data
		/// </summary>
		template<typename T>
		constexpr bool StartsWith( const T data )
			const noexcept
		{
			const auto length = QueryAPI::Count<TElement>( data );

			if ( length > _length || length == 0 )
			{
				return false;
			}

			return QueryAPI::IsMatch( _data[0] ,IteratorAPI::ConstBegin( data ) , length );
		}
	
		/// <summary>
		/// Checks whether the it ends with the given data
		/// </summary>
		template<typename T>
		constexpr bool EndsWith( const T data )
			const noexcept
		{
			const auto length = QueryAPI::Count<TElement>( data );

			if ( length > _length || length == 0 )
			{
				return false;
			}
	
			return QueryAPI::IsMatch( _data[_length - length] , IteratorAPI::ConstBegin( data ) , length );
		}

		/// <summary>
		///Copies the given part of the the given data
		/// </summary>
		template<typename T>
		constexpr auto CopyFromBetween( const T& data , const unsigned int sourceInclusivStart , const unsigned int sourceExclusiveEnd,const unsigned int targetStart = 0 )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			const unsigned int copyLength = sourceExclusiveEnd - sourceInclusivStart;
			
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( sourceInclusivStart, "Source start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( targetStart, "Target strat index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( _length - targetStart , copyLength, "Copy cannot result in increased array length!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( sourceExclusiveEnd , sourceInclusivStart, "Source end index has to be greater than the start!" );

			DataAPI::Copy( IteratorAPI::ConstAt( data , sourceInclusivStart ) , _data[targetStart] , copyLength );

			return *this;
		}

		/// <summary>
		/// Copies the data from the specified index.
		/// </summary>
		template<typename T>
		constexpr auto CopyFrom( const T& data , const unsigned int sourceStart = 0, const unsigned int targetStart = 0 )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			const unsigned int copyLength = QueryAPI::Count<TElement>( data ) - sourceStart;

			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( sourceStart, "Source start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( targetStart, "Target start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( _length - targetStart , copyLength, "Coppy cannot result in increased array length!" );

			DataAPI::Copy( IteratorAPI::ConstAt( data , sourceStart ) , _data[targetStart] , copyLength );

			return *this;
		}
		
		/// <summary>
		/// Returns the index of the first occurence of the given data
		/// </summary>
		template<typename T>
		constexpr long int IndexOf( const T& data )
			const noexcept
		{
			const auto subArrayLength = QueryAPI::Count<TElement>( data );
			if ( subArrayLength > _length )
			{
				return -1; 
			}

			for ( unsigned int i = 0; i < _length; i++ )
			{
				if ( QueryAPI::IsMatch( _data[i] , IteratorAPI::ConstBegin( data ) , subArrayLength ) )
				{
					return i;
				}
			}

			return -1;
		}
		
		/// <summary>
		/// Returns the index of the last occurence of the given data
		/// </summary>
		template<typename T>
		constexpr long int LastIndexOf( const T& data )
			const noexcept
		{
			const auto subArrayLength = QueryAPI::Count<char>( data );
			if ( subArrayLength > _length )
			{
				return -1;
			}

			for ( unsigned int i = _length - subArrayLength; i >= 0; i-- )
			{
				if ( QueryAPI::IsMatch( _data[i] , IteratorAPI::ConstBegin( data ) , subArrayLength ) )
				{
					return i;
				}
			}

			return -1;
		}

		/// <summary>
		/// Replaces every occurence of a data with another.
		/// </summary>
		template<typename T>
		constexpr auto Replace( const T& oldData , const T& newData )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			const auto oldDataLength = QueryAPI::Count<TElement>( oldData );
			const auto newDataLength = QueryAPI::Count<TElement>( newData );

			if ( oldDataLength > _length )
			{
				return *this;
			}
			
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , newDataLength, "The replacer data is larger than the array's maximum size!" );

			const auto difference = newDataLength - oldDataLength;
			if ( difference != 0)
			{
				auto offset = 0;
				for ( unsigned int i = 0; i < _length - oldDataLength;)
				{
					if ( QueryAPI::IsMatch( _data[i] , oldData , oldDataLength ) )
					{
						if ( offset != 0 )
						{
							Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , _length + offset, "Replacing would result in an array overflow! Function aborted!" );
							
							DataAPI::Shift( _data , i + oldDataLength , offset );
						}

						DataAPI::Copy( IteratorAPI::ConstBegin( newData ) , _data[i] , newDataLength );

						i += oldDataLength;

						offset += difference;
					}
					else
					{
						i++;
					}
				}
			}
			else
			{
				for ( unsigned int i = 0; i < _length - oldDataLength;)
				{
					if ( QueryAPI::IsMatch( _data[i] , oldData , oldDataLength ) )
					{
						DataAPI::Copy( IteratorAPI::ConstBegin( newData ) , _data[i] , oldDataLength );

						i += oldDataLength;
					}
					else
					{
						i++;
					}
				}
			}

			return *this;
		}

		/// <summary>
		/// Trims data from both ends of array
		/// </summary>
		template<typename T>
		constexpr auto Trim( const T& data )
		{
			const auto trimDataLength = QueryAPI::Count<TElement>( data );

			if ( trimDataLength == 0 )
			{
				return *this;
			}
			
			// Trim from the end first, so we might have to copy less later
			unsigned int end = _length - trimDataLength;
			
			while ( QueryAPI::IsMatch( _data[end] , IteratorAPI::ConstBegin( data ) , trimDataLength ) )
			{
				end -= trimDataLength;
			}

			_length = end + trimDataLength;
			
			// Trim from the start
			unsigned int start = 0;
				
			while ( QueryAPI::IsMatch( _data[start] , IteratorAPI::ConstBegin( data ) , trimDataLength ) )
			{
				start += trimDataLength;
			}
		
			DataAPI::Copy( _data + start , _data , _length - start );
			
			_length -= start;

			return *this;
		}
		
		/// <summary>
		/// Trims the given data from the start of the array
		/// </summary>
		template<typename T>
		constexpr auto TrimStart( const T& data )
		{
			unsigned int start = 0;
			const auto trimDataLength = QueryAPI::Count<TElement>( data );

			while ( QueryAPI::IsMatch( _data[start] , IteratorAPI::ConstBegin( data ) , trimDataLength ) )
			{
				start += trimDataLength;
			}

			DataAPI::Copy( _data + start, _data , _length - start );
			
			_length -= start;

			return *this;
		}
		
		/// <summary>
		/// Trims the given data from the end of the array
		/// </summary>
		template<typename T>
		constexpr auto TrimEnd( const T& data )
		{
			const auto trimDataLength = QueryAPI::Count<TElement>( data );
			
			unsigned int end = _length - trimDataLength;
			while ( QueryAPI::IsMatch( _data[end] , IteratorAPI::ConstBegin( data ) , trimDataLength ) )
			{
				end -= trimDataLength;
			}

			_length = end + trimDataLength;

			return *this;
		}

		/// <summary>
		/// Concats the given data
		/// </summary>
		template<typename... Args>
		consteval auto Concat(const Args&... args )
			const noexcept
		{
			//Validate
			const auto length = (QueryAPI::Count<TElement>( args ) + ...);
			
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , _length + length, "Concatting data would result in an array overflow! Aborting function..." );

			DataAPI::ReplaceFrom( _data[_length] , args... );

			_length = _length + length;

			return *this;
		}

		constexpr auto operator[]( unsigned int index )
			noexcept ( !Configuration::EnableStaticArrayCheck )
		{
			//Validate the index
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , index, "Indexing invalid memory! Aborting function..." );

			return _data[index];
		}	
	};
}
