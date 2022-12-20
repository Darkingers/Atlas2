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
			noexcept ( Concept::IsNoexceptCurrent<const TIterator&> )
		{
			return IteratorCurrentAdapter<const TIterator&>::Current( iterator );
		}

		template<typename TIterator>
		constexpr static inline bool Move( TIterator& iterator ,const int step )
			noexcept ( Concept::IsNoexceptMove<TIterator&> )
		{
			return IteratorMoveAdapter<TIterator&>::Move( iterator , step );
		}

		template<typename TIterator>
		constexpr static inline bool Next( TIterator& iterator )
			noexcept ( Concept::IsNoexceptMove<TIterator&> )
		{
			return IteratorAPI::Move( iterator , 1 );
		}

		template<typename TIterator>
		constexpr static inline bool Previous( TIterator& iterator )
			noexcept ( Concept::IsNoexceptMove<TIterator&> )
		{
			return IteratorAPI::Move( iterator , -1 );
		}
		
		template<typename TCollection>
		constexpr static inline auto At( const TCollection& collection, const unsigned int step )
			noexcept ( Concept::IsNoexceptAt<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::At( collection , step );
		}

		template<typename TCollection>
		constexpr static inline auto ConstAt( const TCollection& collection , const unsigned int step )
			noexcept ( Concept::IsNoexceptConstAt<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::ConstAt( collection , step );
		}

		template<typename TCollection>
		constexpr static inline auto Begin( const TCollection& collection )
			noexcept ( Concept::IsNoexceptBegin<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::Begin( collection );
		}

		template<typename TCollection>
		constexpr static inline auto ConstBegin( const TCollection& collection )
			noexcept ( Concept::IsNoexceptConstBegin<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::ConstBegin( collection );
		}

		template<typename TCollection>
		constexpr static inline auto End( const TCollection& collection )
			noexcept ( Concept::IsNoexceptEnd<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::End( collection );
		}

		template<typename TCollection>
		constexpr static inline auto ConstEnd( const TCollection& collection )
			noexcept ( Concept::IsNoexceptConstEnd<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::ConstEnd( collection );
		}
	};
}
