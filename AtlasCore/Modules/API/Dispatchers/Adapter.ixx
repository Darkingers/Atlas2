module;

#include "../../../../Macros/Macros.h"

export module AtlasIntegration:Adapter;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi Adapter
	{
		public: template<typename CollectionType>
		constexpr static inline void Clear( CollectionType& collection )
			noexcept( Concept::IsNoexceptClear<CollectionType> )
		{
			ClearAdapter<Deduce::SimpleType<CollectionType>>::Clear( collection );
		}

		public: template<typename CollectionType , typename ElementType>
		constexpr static inline bool Contains( const CollectionType& collection , const ElementType& element )
			noexcept ( Concept::IsNoexceptContain<CollectionType, ElementType> )
		{
			return ContainAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<ElementType>>::Contains( collection , element );
		}

		public: template<typename CollectionType , typename ContainedCollectionType>
		constexpr static inline bool ContainsAll( const CollectionType& collection , const ContainedCollectionType& containedContainer )
			noexcept ( Concept::IsNoexceptContainAll<CollectionType, ContainedCollectionType> )
		{
			return ContainAllAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<ContainedCollectionType>>::ContainsAll( collection , containedContainer );
		}

		public: template<typename ExpectedType, typename ActualType>
		constexpr static inline auto Count( const ActualType& data )
			noexcept ( Concept::IsNoexceptCount<ExpectedType, ActualType> )
		{
			return CountAdapter<Deduce::SimpleType<ExpectedType>,Deduce::SimpleType<ActualType>>::Count( data );
		}

		public: template<typename DataType>
		constexpr static inline void GetHash( const DataType& data )
			noexcept ( Concept::IsNoexceptHash<DataType> )
		{
			return HashAdapter<Deduce::SimpleType<DataType>>::GetHash( data );
		}

		public: template<typename CollectionType>
		constexpr static inline auto Begin( const CollectionType& collection )
			noexcept ( Concept::IsNoexceptBegin<CollectionType> )
		{
			return IterableAdapter<Deduce::SimpleType<CollectionType>>::Begin( collection );
		}

		public: template<typename CollectionType>
		constexpr static inline auto ConstBegin( const CollectionType& collection )
			noexcept ( Concept::IsNoexceptConstBegin<CollectionType> )
		{
			return IterableAdapter<Deduce::SimpleType<CollectionType>>::ConstBegin( collection );
		}

		public: template<typename CollectionType>
		constexpr static inline auto End( const CollectionType& collection )
			noexcept ( Concept::IsNoexceptEnd<CollectionType> )
		{
			return IterableAdapter<Deduce::SimpleType<CollectionType>>::End( collection );
		}

		public: template<typename CollectionType>
		constexpr static inline auto ConstEnd( const CollectionType& collection )
			noexcept ( Concept::IsNoexceptConstEnd<CollectionType> )
		{
			return IterableAdapter<Deduce::SimpleType<CollectionType>>::ConstEnd( collection );
		}

		public: template<typename IteratorType>
		constexpr static inline auto Current( const IteratorType& iterator )
			noexcept ( Concept::IsNoexceptCurrent<IteratorType> )
		{
			return IteratorAdapter<Deduce::SimpleType<IteratorType>>::Current( iterator );
		}

		public: template<typename IteratorType>
		constexpr static inline bool Move( IteratorType& iterator, int step = 1 )
			noexcept ( Concept::IsNoexceptMove<IteratorType> )
		{
			return IteratorAdapter<Deduce::SimpleType<IteratorType>>::Move( iterator, step );
		}
	};
}
