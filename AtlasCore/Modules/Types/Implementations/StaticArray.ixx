module;

#include "../../../../Macros/Macros.h"

export module AtlasTypes:StaticArray;

import AtlasConfiguration;
import AtlasValidation;
import AtlasDefinitions;
import AtlasAPI;

namespace Atlas
{
	template<typename TElement, unsigned int BufferSize = Configuration::StaticArrayBufferSize>
	class DLLApi StaticArray
	{
		
	protected: 
		
		TElement _data[BufferSize];
		unsigned int _length;

	public: 
		
		template<typename... Args>
		constexpr StaticArray( const Args&... args )
			noexcept( noexcept( Concat( args... ) ) ) :
			_length( 0 )
		{
			if constexpr ( sizeof...( args ) > 0 )
			{
				this->Concat( args... );
			}
		}
			
		constexpr ~StaticArray( ) = default;

		constexpr unsigned int Length( ) 
			const noexcept
		{
			return _length;
		}

		constexpr const TElement* Data( )
			const noexcept
		{
			return _data;
		}

		constexpr unsigned int MaxLength( )
			const noexcept
		{
			return BufferSize;
		}
		
		template<typename T>
		constexpr bool ContainsPattern( const T& data )
			const noexcept( noexcept( QueryAPI::ContainsPattern( *this , data ) ) )
		{
			return QueryAPI::ContainsPattern( *this , data );
		}

		/// <summary>
		/// Checks whether it contains the given element.
		/// </summary>
		constexpr bool Contains( const TElement& element )
			const noexcept( noexcept( QueryAPI::Contains( *this , element ) ))
		{
			return QueryAPI::Contains( *this , element );
		}

		/// <summary>
		/// Checks whether any element satisfies the given predicate
		/// </summary>
		constexpr bool Any( const Predicate<TElement>& predicate )
			const noexcept( ( QueryAPI::Any( *this , predicate ) ) )
		{
			return QueryAPI::Any( *this , predicate );
		}

		/// <summary>
		/// Checks whether all element satisfies the given predicate
		/// </summary>
		constexpr bool All( const Predicate<TElement>& predicate )
			const noexcept( ( QueryAPI::All( *this , predicate ) ) )
		{
			return QueryAPI::All( *this , predicate );
		}


		template<typename T>
		constexpr auto Count( const T& data )
			const noexcept( noexcept( QueryAPI::Count( *this , data ) ))
		{
			return QueryAPI::Count( *this , data );
		}

		constexpr auto Count( const TElement& element )
			const noexcept( noexcept( QueryAPI::CountElement( *this , element ) ))
		{
			return QueryAPI::CountElement( *this , element );
		}

		/// <summary>
		/// Counts how many elements satisfy the given predicate
		/// </summary>

		
		/// <summary>
		/// Clears the array
		/// </summary>
		constexpr void Clear( )
			noexcept
		{
			//Destroy all elements
			this->Destruct( 0 , _length );

			_length = 0;
		}

		/// <summary>
		///  Removes the last element from the array and returns it
		/// </summary>
		constexpr auto PopBack( )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			//Validate length
			Validate<Configuration::EnableStaticArrayCheck>::IsMore( _length , 0, "Empty array cannot be popped!" );

			//Return the last element
			return _data[--_length];
		}

		/// <summary>
		/// Inserts a given element at a specified index in the array
		/// </summary>
		template<typename T>
		constexpr auto Insert( T data, unsigned int index)
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			//Validate input
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( _length , BufferSize , "Array is full!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( index , _length , "Index is out of bounds!" );

			//Move all elements after the index to the right
			for ( unsigned int i = _length; i > index; --i )
			{
				_data[i] = _data[i - 1];
			}

			//Insert the element
			_data[index] = data;

			//Increment length
			_length++;

			//Return the inserted element
			return data;
		}

		/// <summary>
		/// Removes a range of elements from the array, specified by a starting index and length
		/// </summary>
		constexpr auto Erase( unsigned int inclusiveFrom, unsigned int exclusiveTo )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			//Validate input
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( _length , BufferSize , "Array is full!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( inclusiveFrom , _length , "Index is out of bounds!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( exclusiveTo , _length , "Index is out of bounds!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( inclusiveFrom , exclusiveTo , "Exclusive index must be greater than inclusive index!" );

			//Destroy erased elements
			this->Destruct( inclusiveFrom , exclusiveTo );

			const auto length = exclusiveTo - inclusiveFrom;

			//Move all elements after the index to the right
			for ( unsigned int i = exclusiveTo; i < _length; ++i )
			{
				_data[i - length] = _data[i];
			}

			//Decrement length
			_length -= length;

			return *this;
		}

		/// <summary>
		/// Reverses the order of the elements in the array
		/// </summary>
		constexpr auto Reverse( )
			noexcept
		{
			//Iterate over the elements, and if there is a match from the given index, increment counter
			for ( unsigned int i = 0; i < _length / 2; ++i )
			{
				const auto temp = _data[i];
				_data[i] = _data[_length - i - 1];
				_data[_length - i - 1] = temp;
			}
			
			return *this;
		}


		/// <summary>
		/// Creates a subarray with the specified range
		/// </summary>
		constexpr auto SubArray( 
			unsigned int inclusiveStart, 
			unsigned int exclusiveEnd 
		) const noexcept( !Configuration::EnableStaticArrayCheck )
		{
			
			StaticArray<BufferSize> result;

			//Copy the range into the array
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
			const auto length = QueryAPI::CountType<TElement>( data );

			//Length is too big, so return false
			if ( length > _length || length == 0 )
			{
				return false;
			}

			//Check if the data matches with the beginning of the array
			return QueryAPI::IsMatch( _data[0] ,IteratorAPI::ConstBegin( data ) , length );
		}
	
		/// <summary>
		/// Checks whether the it ends with the given data
		/// </summary>
		template<typename T>
		constexpr bool EndsWith( const T data )
			const noexcept
		{
			const auto length = QueryAPI::CountType<TElement>( data );

			//Length is too big, so return false
			if ( length > _length || length == 0 )
			{
				return false;
			}
	
			//Check if the data matches with the end of the array
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
			
			//Validate input
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( sourceInclusivStart, "Source start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( targetStart, "Target strat index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( _length - targetStart , copyLength, "Copy cannot result in increased array length!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( sourceExclusiveEnd , sourceInclusivStart, "Source end index has to be greater than the start!" );

			//Manually calling destructors
			this->Destruct( targetStart , targetStart + copyLength );

			//Copy the data
			ManipulationAPI::Copy( IteratorAPI::ConstAt( data , sourceInclusivStart ) , _data[targetStart] , copyLength );

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

			//Validate input
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( sourceStart, "Source start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( targetStart, "Target start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( _length - targetStart , copyLength, "Coppy cannot result in increased array length!" );

			//Manually calling destructors
			this->Destruct( targetStart , targetStart + copyLength );

			//Copy the data
			ManipulationAPI::Copy( IteratorAPI::ConstAt( data , sourceStart ) , _data[targetStart] , copyLength );

			return *this;
		}
		
		/// <summary>
		/// Returns the index of the first occurence of the given data
		/// </summary>
		template<typename T>
		constexpr long int IndexOf( const T& data )
			const noexcept
		{
			const auto subArrayLength = QueryAPI::CountType<TElement>( data );

			//Length is too big, so return -1
			if ( subArrayLength > _length )
			{
				return -1; 
			}

			//Iterate over the elements, and if there is a match from the given index, return it
			for ( unsigned int i = 0; i < _length; i++ )
			{
				if ( QueryAPI::IsMatch( _data[i] , IteratorAPI::ConstBegin( data ) , subArrayLength ) )
				{
					return i;
				}
			}

			//No match found
			return -1;
		}
		
		/// <summary>
		/// Returns the index of the last occurence of the given data
		/// </summary>
		template<typename T>
		constexpr long int LastIndexOf( const T& data )
			const noexcept
		{
			const auto subArrayLength = QueryAPI::CountType<TElement>( data );

			//Length is too big, so return -1
			if ( subArrayLength > _length )
			{
				return -1;
			}

			//Iterate over the elements, and if there is a match from the given index, return it
			for ( unsigned int i = _length - subArrayLength; i >= 0; i-- )
			{
				if ( QueryAPI::IsMatch( _data[i] , IteratorAPI::ConstBegin( data ) , subArrayLength ) )
				{
					return i;
				}
			}

			//No match found
			return -1;
		}

		/// <summary>
		/// Replaces every occurence of a data with another.
		/// </summary>
		template<typename T>
		constexpr auto Replace( const T& oldData , const T& newData )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			// Calculate the length of the old and new data.
			const auto oldDataLength = QueryAPI::CountType<TElement>( oldData );
			const auto newDataLength = QueryAPI::CountType<TElement>( newData );

			// If the old data is longer than the array, the replace operation is impossible.
			if ( oldDataLength > _length )
			{
				// Return the unchanged array.
				return *this;
			}

			// Validate that the new data is not longer than the maximum size of the array.
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , newDataLength , "The replacer data is larger than the array's maximum size!" );

			// Calculate the difference in length between the old and new data.
			const auto difference = newDataLength - oldDataLength;

			// If the difference is not zero, the array will need to be resized.
			if ( difference != 0 )
			{
				// Initialize an offset variable to keep track of the resizing.
				auto offset = 0;

				// Loop through the array.
				for ( unsigned int i = 0; i < _length - oldDataLength;)
				{
					// If the current element matches the old data.
					if ( QueryAPI::IsMatch( _data[i] , oldData , oldDataLength ) )
					{
						// If the array has been resized previously, shift the elements after the current element by the offset amount.
						if ( offset != 0 )
						{
							// Validate that the array will not overflow after the shift operation.
							Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , _length + offset , "Replacing would result in an array overflow! Function aborted!" );

							//Manually destroy elements
							this->Destruct( i + offset , i + offset + oldDataLength );
							
							// Shift the elements after the current element by the offset amount.
							ManipulationAPI::Shift( _data , i + oldDataLength , offset );
						}

						// Replace the current element with the new data.
						ManipulationAPI::Copy( IteratorAPI::ConstBegin( newData ) , _data[i] , newDataLength );

						// Move to the next element after the old data.
						i += oldDataLength;

						// Update the offset variable with the difference in length between the old and new data.
						offset += difference;
					}
					else
					{
						// Move to the next element.
						i++;
					}
				}
			}
			// If the difference is zero, the array does not need to be resized.
			else
			{
				// Loop through the array.
				for ( unsigned int i = 0; i < _length - oldDataLength;)
				{
					// If the current element matches the old data.
					if ( QueryAPI::IsMatch( _data[i] , oldData , oldDataLength ) )
					{
						//Manually destroy elements
						this->Destruct( i , i + oldDataLength );
						
						// Replace the current element with the new data.
						ManipulationAPI::Copy( IteratorAPI::ConstBegin( newData ) , _data[i] , oldDataLength );

						// Move to the next element after the old data.
						i += oldDataLength;
					}
					else
					{
						// Move to the next element.
						i++;
					}
				}
			}

			// Return the modified array.
			return *this;
		}

		/// <summary>
		/// Trims data from both ends of array
		/// </summary>
		template<typename T>
		constexpr auto Trim( const T& data )
		{
			const auto trimDataLength = QueryAPI::CountType<TElement>( data );

			//Trim from end first, in case it results in less shifting later
			this->TrimEndImpl( data , trimDataLength );

			//Trim from start
			this->TrimStartImpl( data , trimDataLength );

			return *this;
		}
		
		/// <summary>
		/// Trims the given data from the start of the array
		/// </summary>
		template<typename T>
		constexpr auto TrimStart( const T& data )
		{
			const auto trimDataLength = QueryAPI::CountType<TElement>( data );

			this->TrimStartImpl( data , trimDataLength );

			return *this;
		}
		
		/// <summary>
		/// Trims the given data from the end of the array
		/// </summary>
		template<typename T>
		constexpr auto TrimEnd( const T& data )
		{
			const auto trimDataLength = QueryAPI::Count<TElement>( data );
			
			this->TrimEndImpl( data , trimDataLength );

			return *this;
		}

		/// <summary>
		/// Concats the given data
		/// </summary>
		template<typename... Args>
		consteval auto Concat(const Args&... args )
			const noexcept
		{
			const auto length = (QueryAPI::CountType<TElement>( args ) + ...);
			
			//Validate that the array will not overflow after the concat operation.
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , _length + length, "Concatting data would result in an array overflow! Aborting function..." );

			//Replace starting from the end.
			ManipulationAPI::ReplaceFrom( _data[_length] , args... );

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

	private:
		
		template<typename T>
		constexpr void TrimStartImpl( const T& data, auto trimDataLength )
		{
			unsigned int start = 0;

			//Find the trimmed length from the start
			while ( QueryAPI::IsMatch( _data[start] , IteratorAPI::ConstBegin( data ) , trimDataLength ) )
			{
				start += trimDataLength;
			}

			//Destroy trimmed objects
			this->Destruct( 0 , start );

			//Shift remaining objects
			ManipulationAPI::Copy( _data + start , _data , _length - start );

			_length -= start;
		}

		template<typename T>
		constexpr void TrimEndImpl( const T& data, auto trimDataLength )
		{
			unsigned int end = _length - trimDataLength;

			//Find trim length from end
			while ( QueryAPI::IsMatch( _data[end] , IteratorAPI::ConstBegin( data ) , trimDataLength ) )
			{
				end -= trimDataLength;
			}

			//Destroy trimmed objects
			this->Destruct( end + trimDataLength , _length );

			_length = end + trimDataLength;
		}

		constexpr void Destruct(unsigned int iclusiveFrom, unsigned int exclusiveTo ) 
			noexcept
		{
			for ( unsigned int i = iclusiveFrom; i < exclusiveTo; i++ )
			{
				_data[i].~TElement( );
			}
		}
	};
}
