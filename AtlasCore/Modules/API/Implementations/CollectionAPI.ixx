module;
#include "../../../../Macros/Macros.h"

export module AtlasAPI:CollectionAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi CollectionAPI
	{
		public: template<typename TCollection>
		constexpr static inline void Clear( TCollection& collection )
			noexcept( Concept::IsNoexceptClear<TCollection> )
		{
			ClearAdapter<Deduce::SimpleType<TCollection>>::Clear( collection );
		}

		public: template<typename TCollection , typename TElement>
		constexpr static inline bool Contains( const TCollection& collection , const TElement& element )
			noexcept ( Concept::IsNoexceptContain<TCollection, TElement> )
		{
			return ContainAdapter<Deduce::SimpleType<TCollection> , Deduce::SimpleType<TElement>>::Contains( collection , element );
		}

		public: template<typename TCollectionA , typename TCollectionB>
		constexpr static inline bool ContainsAll( const TCollectionA& collection , const TCollectionB& containedContainer )
			noexcept ( Concept::IsNoexceptContainAll<TCollectionA , TCollectionB> )
		{
			return ContainAllAdapter<Deduce::SimpleType<TCollectionA> , Deduce::SimpleType<TCollectionB>>::ContainsAll( collection , containedContainer );
		}

		public: template<typename TExpected, typename TActual>
		constexpr static inline auto Count( const TActual& data )
			noexcept ( Concept::IsNoexceptCount<TExpected , TActual> )
		{
			return CountAdapter<Deduce::SimpleType<TExpected>,Deduce::SimpleType<TActual>>::Count( data );
		}

		public: template<typename TCollection>
		constexpr static inline auto Begin( const TCollection& collection )
			noexcept ( Concept::IsNoexceptBegin<TCollection> )
		{
			return IterableAdapter<Deduce::SimpleType<TCollection>>::Begin( collection );
		}

		public: template<typename TCollection>
		constexpr static inline auto ConstBegin( const TCollection& collection )
			noexcept ( Concept::IsNoexceptConstBegin<TCollection> )
		{
			return IterableAdapter<Deduce::SimpleType<TCollection>>::ConstBegin( collection );
		}

		public: template<typename TCollection>
		constexpr static inline auto End( const TCollection& collection )
			noexcept ( Concept::IsNoexceptEnd<TCollection> )
		{
			return IterableAdapter<Deduce::SimpleType<TCollection>>::End( collection );
		}

		public: template<typename TCollection>
		constexpr static inline auto ConstEnd( const TCollection& collection )
			noexcept ( Concept::IsNoexceptConstEnd<TCollection> )
		{
			return IterableAdapter<Deduce::SimpleType<TCollection>>::ConstEnd( collection );
		}
	};
}
