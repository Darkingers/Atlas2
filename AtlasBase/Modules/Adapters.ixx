module;

#include "../../Macros/Macros.h"

export module AtlasAdapters;

import AtlasDefinitions;

export import :ClearAdapter;
export import :ContainAdapter;
export import :ContainAllAdapter;
export import :CountAdapter;
export import :EqualityAdapter;
export import :HashAdapter;

export namespace Atlas
{
	class DLLApi Adapter
	{
		public: template<typename CollectionType, typename SimpleCollectionType = Deduce::SimpleType<CollectionType>>
		constexpr inline static void Clear( SimpleCollectionType& collection ) 
			noexcept( Adapters::ClearAdapter<SimpleCollectionType>::IsNoexcept )
		{
			Adapters::ClearAdapter<SimpleCollectionType>::Contains( collection );
		}

		public: template<typename CollectionType , typename DataType, typename SimpleCollectionType = Deduce::SimpleType<CollectionType>, typename SimpleDataType = Deduce::SimpleType<DataType>>
		constexpr inline static bool Contains( const SimpleCollectionType& collection , const SimpleDataType& contained )
			noexcept ( Adapters::ContainAdapter<SimpleCollectionType , SimpleDataType>::IsNoexcept )
		{
			return Adapters::ContainAdapter<SimpleCollectionType , SimpleDataType>::Contains( collection , contained );
		}

		public: template<typename CollectionType , typename ContainedCollectionType , typename SimpleCollectionType = Deduce::SimpleType<CollectionType> , typename SimpleContainedCollectionType = Deduce::SimpleType<ContainedCollectionType>>
		constexpr inline static bool ContainsAll( const CollectionType& collection , const SimpleContainedCollectionType& containedContainer )
			noexcept ( Adapters::ContainAllAdapter<SimpleCollectionType , SimpleContainedCollectionType>::IsNoexcept )
		{
			return Adapters::ContainAllAdapter<SimpleCollectionType , SimpleContainedCollectionType>::Contains( collection , containedContainer );
		}

		public: template<typename DataType , typename SimpleDataType = Deduce::SimpleType<DataType>>
		constexpr inline static auto Count( const SimpleDataType& data )
			noexcept ( Adapters::CountAdapter<SimpleDataType>::IsNoexcept )
		{
			return Adapters::CountAdapter<SimpleDataType>::Count( data );
		}

		public: template<typename TypeA , typename TypeB, typename SimpleTypeA = Deduce::SimpleType<TypeA>, typename SimpleTypeB = Deduce::SimpleType<TypeB>>
		constexpr inline static bool Equals( const SimpleTypeA& A , const SimpleTypeB& B )
			noexcept ( Adapters::EqualityAdapter<SimpleTypeA , SimpleTypeB>::IsNoexcept )
		{
			return Adapters::EqualityAdapter<SimpleTypeA , SimpleTypeB>::Equals( A , B );
		}

		public: template<typename DataType , typename SimpleDataType = Deduce::SimpleType<DataType>>
		constexpr inline static void GetHash( const SimpleDataType& data )
			noexcept ( Adapters::HashAdapter<SimpleDataType>::IsNoexcept )
		{
			return Adapters::HashAdapter<SimpleDataType>::GetHash( data );
		}
	};
}