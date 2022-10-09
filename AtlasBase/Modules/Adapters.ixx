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
		public: template<typename CollectionType>
		constexpr inline static void Clear( CollectionType& collection )
			noexcept( Adapters::ClearAdapter<Deduce::SimpleType<CollectionType>>::IsNoexcept )
		{
			Adapters::ClearAdapter<Deduce::SimpleType<CollectionType>>::Clear( collection );
		}

		public: template<typename CollectionType , typename DataType>
		constexpr inline static bool Contains( const CollectionType& collection , const DataType& contained )
			noexcept ( Adapters::ContainAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<DataType>>::IsNoexcept )
		{
			return Adapters::ContainAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<DataType>>::Contains( collection , contained );
		}

		public: template<typename CollectionType , typename ContainedCollectionType>
		constexpr inline static bool ContainsAll( const CollectionType& collection , const ContainedCollectionType& containedContainer )
			noexcept ( Adapters::ContainAllAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<ContainedCollectionType>>::IsNoexcept )
		{
			return Adapters::ContainAllAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<ContainedCollectionType>>::ContainsAll( collection , containedContainer );
		}

		public: template<typename DataType>
		constexpr inline static auto Count( const DataType& data )
			noexcept ( Adapters::CountAdapter<Deduce::SimpleType<DataType>>::IsNoexcept )
		{
			return Adapters::CountAdapter<Deduce::SimpleType<DataType>>::Count( data );
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static bool Equals( const TypeA& a , const TypeB& b )
			noexcept ( Adapters::EqualityAdapter<Deduce::SimpleType<TypeA> , Deduce::SimpleType<TypeB>>::IsNoexcept )
		{
			return Adapters::EqualityAdapter<Deduce::SimpleType<TypeA> , Deduce::SimpleType<TypeB>>::Equals( a , b );
		}

		public: template<typename DataType>
		constexpr inline static void GetHash( const DataType& data )
			noexcept ( Adapters::HashAdapter<Deduce::SimpleType<DataType>>::IsNoexcept )
		{
			return Adapters::HashAdapter<Deduce::SimpleType<DataType>>::GetHash( data );
		}
	};
}