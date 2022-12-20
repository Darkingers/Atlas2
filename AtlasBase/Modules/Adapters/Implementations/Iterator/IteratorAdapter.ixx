module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:IteratorAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TIterator> requires 
		Concept::IsIterator<TIterator>&&
		(!Concept::IsRandomAccessIterator<TIterator>)
	class DLLApi IteratorMoveAdapter<TIterator> :
		public std::true_type
	{

	public:
		
		constexpr static inline auto Move( TIterator iterator , const int step )
			noexcept( noexcept(iterator++) && noexcept(--iterator) )
		{
			if ( step > 0 )
			{
				for ( int i = 0; i < step; i++ )
				{
					++iterator;
				}
			}
			else
			{
				for ( int i = 0; i > step; i-- )
				{
					--iterator;
				}
			}

			return iterator;
		}
	};

	template<typename TIterator> requires
		Concept::IsIterator<TIterator> &&
		Concept::IsRandomAccessIterator<TIterator>
	class DLLApi IteratorMoveAdapter<TIterator> :
		public std::true_type
	{

	public:

		constexpr static inline auto Move( TIterator iterator , const int step )
			noexcept( iterator + step )
		{
			return iterator + step;
		}
	};

	template<typename TIterator> requires
		Concept::IsIterator<TIterator>
	class DLLApi IteratorCurrentAdapter<TIterator> :
		public std::true_type
	{
		constexpr static inline auto Current( TIterator iterator )
			noexcept( *iterator )
		{
			return *iterator;
		}
	};
	
	template<typename TCollection> requires
		Concept::IsIterable<TCollection>
	class DLLApi IterableAdapter<TCollection> :
		public std::true_type
	{

	public:

		constexpr static inline auto At( TCollection collection , const unsigned int step )
			noexcept( Concept::HasNoexceptIterator<TCollection> )
		{
			auto iterator = IteratorAPI::Begin( collection );
			
			IteratorAPI::Move( iterator , step );
			
			return IteratorAPI::Current( iterator );
		}

		constexpr static inline auto ConstAt( TCollection collection , const unsigned int step )
			noexcept( Concept::HasNoexceptConstIterator<TCollection> )
		{
			auto iterator = IteratorAPI::ConstBegin( collection );
			
			IteratorAPI::Move( iterator , step );
			
			return IteratorAPI::Current( iterator );
		}

		constexpr static inline auto Begin( TCollection collection )
			noexcept( collection.Begin() )
		{
			return collection.Begin( );
		}

		constexpr static inline auto ConstBegin( TCollection collection )
			noexcept( collection.ConstBegin( ) )
		{
			return collection.ConstBegin( );
		}

		constexpr static inline auto End( TCollection collection )
			noexcept( collection.End( ) )
		{
			return collection.End( );
		}

		constexpr static inline auto ConstEnd( TCollection collection )
			noexcept( collection.ConstEnd( ) )
		{
			return collection.ConstEnd( );
		}
	};

	template<typename TCollection> requires
		Concept::Standard::IsIterable<TCollection>
	class DLLApi IterableAdapter<TCollection> :
		public std::true_type
	{

		public:

		constexpr static inline auto At( TCollection collection , const unsigned int step )
			noexcept( Concept::HasNoexceptIterator<TCollection> )
		{
			auto iterator = IteratorAPI::Begin( collection );
			IteratorAPI::Move( iterator , step );
			return IteratorAPI::Current( iterator );
		}

		constexpr static inline auto ConstAt( TCollection collection , const unsigned int step )
			noexcept( Concept::HasNoexceptConstIterator<TCollection> )
		{
			auto iterator = IteratorAPI::ConstBegin( collection );
			IteratorAPI::Move( iterator , step );
			return IteratorAPI::Current( iterator );
		}


		constexpr static inline auto Begin( TCollection collection )
			noexcept( collection.begin( ) )
		{
			return collection.begin( );
		}

		constexpr static inline auto ConstBegin( TCollection collection )
			noexcept( collection.cbegin( ) )
		{
			return collection.cbegin( );
		}

		constexpr static inline auto End( TCollection collection )
			noexcept( collection.end( ) )
		{
			return collection.end( );
		}

		constexpr static inline auto ConstEnd( TCollection collection )
			noexcept( collection.cend( ) )
		{
			return collection.cend( );
		}
	};
}