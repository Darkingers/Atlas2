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

		constexpr bool Contains( const TElement& element )
			const noexcept( noexcept( QueryAPI::Contains( *this , element ) ))
		{
			return QueryAPI::Contains( *this , element );
		}

		constexpr bool Any( const Predicate<TElement>& predicate )
			const noexcept( ( QueryAPI::Any( *this , predicate ) ) )
		{
			return QueryAPI::Any( *this , predicate );
		}

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

		constexpr void Clear( )
			noexcept
		{
			this->Destruct( 0 , _length );

			_length = 0;
		}

		constexpr auto PopBack( )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			Validate<Configuration::EnableStaticArrayCheck>::IsMore( _length , 0, "Empty array cannot be popped!" );

			return _data[--_length];
		}

		template<typename T>
		constexpr auto Insert( T data, unsigned int index)
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( _length , BufferSize , "Array is full!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( index , _length , "Index is out of bounds!" );

			for ( unsigned int i = _length; i > index; --i )
			{
				_data[i] = _data[i - 1];
			}

			_data[index] = data;

			_length++;

			return data;
		}

		constexpr auto Erase( unsigned int inclusiveFrom, unsigned int exclusiveTo )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( _length , BufferSize , "Array is full!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( inclusiveFrom , _length , "Index is out of bounds!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( exclusiveTo , _length , "Index is out of bounds!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsLess( inclusiveFrom , exclusiveTo , "Exclusive index must be greater than inclusive index!" );

			this->Destruct( inclusiveFrom , exclusiveTo );

			const auto length = exclusiveTo - inclusiveFrom;

			for ( unsigned int i = exclusiveTo; i < _length; ++i )
			{
				_data[i - length] = _data[i];
			}

			_length -= length;

			return *this;
		}

		constexpr auto Reverse( )
			noexcept
		{
			for ( unsigned int i = 0; i < _length / 2; ++i )
			{
				const auto temp = _data[i];
				_data[i] = _data[_length - i - 1];
				_data[_length - i - 1] = temp;
			}
			
			return *this;
		}

		constexpr auto SubArray( 
			unsigned int inclusiveStart, 
			unsigned int exclusiveEnd 
		) const noexcept( !Configuration::EnableStaticArrayCheck )
		{
			
			StaticArray<BufferSize> result;

			result.CopyFromBetween( *this , inclusiveStart , exclusiveEnd );

			return result;
		}

		template<typename T>
		constexpr bool StartsWith( const T data )
			const noexcept
		{
			const auto length = QueryAPI::CountType<TElement>( data );

			if ( length > _length || length == 0 )
			{
				return false;
			}

			return QueryAPI::IsMatch( _data[0] ,IteratorAPI::ConstBegin( data ) , length );
		}
	
		template<typename T>
		constexpr bool EndsWith( const T data )
			const noexcept
		{
			const auto length = QueryAPI::CountType<TElement>( data );

			if ( length > _length || length == 0 )
			{
				return false;
			}

			return QueryAPI::IsMatch( _data[_length - length] , IteratorAPI::ConstBegin( data ) , length );
		}

		template<typename T>
		constexpr auto CopyFromBetween( const T& data , const unsigned int sourceInclusivStart , const unsigned int sourceExclusiveEnd,const unsigned int targetStart = 0 )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			const unsigned int copyLength = sourceExclusiveEnd - sourceInclusivStart;
			
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( sourceInclusivStart, "Source start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( targetStart, "Target strat index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( _length - targetStart , copyLength, "Copy cannot result in increased array length!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( sourceExclusiveEnd , sourceInclusivStart, "Source end index has to be greater than the start!" );

			this->Destruct( targetStart , targetStart + copyLength );

			ManipulationAPI::Copy( IteratorAPI::ConstAt( data , sourceInclusivStart ) , _data[targetStart] , copyLength );

			return *this;
		}

		template<typename T>
		constexpr auto CopyFrom( const T& data , const unsigned int sourceStart = 0, const unsigned int targetStart = 0 )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			const unsigned int copyLength = QueryAPI::Count<TElement>( data ) - sourceStart;

			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( sourceStart, "Source start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsPositive( targetStart, "Target start index has to be positive!" );
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( _length - targetStart , copyLength, "Coppy cannot result in increased array length!" );

			this->Destruct( targetStart , targetStart + copyLength );

			ManipulationAPI::Copy( IteratorAPI::ConstAt( data , sourceStart ) , _data[targetStart] , copyLength );

			return *this;
		}

		template<typename T>
		constexpr long int IndexOf( const T& data )
			const noexcept
		{
			const auto subArrayLength = QueryAPI::CountType<TElement>( data );

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

		template<typename T>
		constexpr long int LastIndexOf( const T& data )
			const noexcept
		{
			const auto subArrayLength = QueryAPI::CountType<TElement>( data );

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

		template<typename T>
		constexpr auto Replace( const T& oldData , const T& newData )
			noexcept( !Configuration::EnableStaticArrayCheck )
		{
			const auto oldDataLength = QueryAPI::CountType<TElement>( oldData );
			const auto newDataLength = QueryAPI::CountType<TElement>( newData );

			if ( oldDataLength > _length )
			{
				return *this;
			}

			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , newDataLength , "The replacer data is larger than the array's maximum size!" );

			const auto difference = newDataLength - oldDataLength;

			if ( difference != 0 )
			{
				auto offset = 0;

				for ( unsigned int i = 0; i < _length - oldDataLength;)
				{
					if ( QueryAPI::IsMatch( _data[i] , oldData , oldDataLength ) )
					{
						if ( offset != 0 )
						{
							Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , _length + offset , "Replacing would result in an array overflow! Function aborted!" );

							this->Destruct( i + offset , i + offset + oldDataLength );

							ManipulationAPI::Shift( _data , i + oldDataLength , offset );
						}

						ManipulationAPI::Copy( IteratorAPI::ConstBegin( newData ) , _data[i] , newDataLength );

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
						this->Destruct( i , i + oldDataLength );

						ManipulationAPI::Copy( IteratorAPI::ConstBegin( newData ) , _data[i] , oldDataLength );

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

		template<typename T>
		constexpr auto Trim( const T& data )
		{
			const auto trimDataLength = QueryAPI::CountType<TElement>( data );

			this->TrimEndImpl( data , trimDataLength );

			this->TrimStartImpl( data , trimDataLength );

			return *this;
		}

		template<typename T>
		constexpr auto TrimStart( const T& data )
		{
			const auto trimDataLength = QueryAPI::CountType<TElement>( data );

			this->TrimStartImpl( data , trimDataLength );

			return *this;
		}

		template<typename T>
		constexpr auto TrimEnd( const T& data )
		{
			const auto trimDataLength = QueryAPI::Count<TElement>( data );
			
			this->TrimEndImpl( data , trimDataLength );

			return *this;
		}

		template<typename... Args>
		consteval auto Concat(const Args&... args )
			const noexcept
		{
			const auto length = (QueryAPI::CountType<TElement>( args ) + ...);

			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , _length + length, "Concatting data would result in an array overflow! Aborting function..." );

			ManipulationAPI::ReplaceFrom( _data[_length] , args... );

			_length = _length + length;

			return *this;
		}

		constexpr auto operator[]( unsigned int index )
			noexcept ( !Configuration::EnableStaticArrayCheck )
		{
			Validate<Configuration::EnableStaticArrayCheck>::IsMoreOrEqual( BufferSize , index, "Indexing invalid memory! Aborting function..." );

			return _data[index];
		}	

	protected:
		
		template<typename T>
		constexpr void TrimStartImpl( const T& data, auto trimDataLength )
		{
			unsigned int start = 0;

			while ( QueryAPI::IsMatch( _data[start] , IteratorAPI::ConstBegin( data ) , trimDataLength ) )
			{
				start += trimDataLength;
			}

			this->Destruct( 0 , start );

			ManipulationAPI::Copy( _data + start , _data , _length - start );

			_length -= start;
		}

		template<typename T>
		constexpr void TrimEndImpl( const T& data, auto trimDataLength )
		{
			unsigned int end = _length - trimDataLength;

			while ( QueryAPI::IsMatch( _data[end] , IteratorAPI::ConstBegin( data ) , trimDataLength ) )
			{
				end -= trimDataLength;
			}

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
