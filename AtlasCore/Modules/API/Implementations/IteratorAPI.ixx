module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:IteratorAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi IteratorAPI
	{
	
	public:
		
		template<typename TIterator>
		constexpr static inline auto Current( const TIterator& iterator ) 
		{
			return IteratorCurrentAdapter<const TIterator&>::Current( iterator );
		}

		template<typename TIterator>
		constexpr static inline bool Move( TIterator& iterator, const int step ) 
		{
			return IteratorMoveAdapter<TIterator&>::Move( iterator , step );
		}

		template<typename TIterator>
		constexpr static inline bool Next( TIterator& iterator )
		{
			return IteratorAPI::Move( iterator , 1 );
		}

		template<typename TIterator>
		constexpr static inline bool Previous( TIterator& iterator)
		{
			return IteratorAPI::Move( iterator , -1 );
		}
		
		template<typename TCollection>
		constexpr static inline auto At( const TCollection& collection, const unsigned int index )
		{
			return IterableAdapter<const TCollection&>::At( collection , index );
		}

		template<typename TCollection>
		constexpr static inline auto ConstAt( const TCollection& collection ,const unsigned int index )
		{
			return IterableAdapter<const TCollection&>::ConstAt( collection , index );
		}

		template<typename TCollection>
		constexpr static inline auto Begin( const TCollection& collection )
		{
			return IterableAdapter<const TCollection&>::Begin( collection );
		}

		template<typename TCollection>
		constexpr static inline auto ConstBegin(const TCollection& collection)
		{
			return IterableAdapter<const TCollection&>::ConstBegin( collection );
		}

		template<typename TCollection>
		constexpr static inline auto End( 	const TCollection& collection)
		{
			return IterableAdapter<const TCollection&>::End( collection );
		}

		template<typename TCollection>
		constexpr static inline auto ConstEnd( const TCollection& collection )
		{
			return IterableAdapter<const TCollection&>::ConstEnd( collection );
		}
	};
}
