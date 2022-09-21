module;

#include "../../Macros/Macros.h"

export module AtlasAdapters;
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
		template<typename CollectionType>
		constexpr inline static void Clear( CollectionType& collection )
		{
			Adapters::ClearAdapter<CollectionType>::Contains( collection );
		}

		template<typename CollectionType , typename DataType>
		constexpr inline static bool Contains( const CollectionType& collection , const DataType& contained )
		{
			return Adapters::ContainAdapter<CollectionType , DataType>::Contains( collection , contained );
		}

		template<typename CollectionType , typename ContainedCollectionType>
		constexpr inline static bool ContainsAll( const CollectionType& collection , const ContainedCollectionType& containedContainer )
		{
			return Adapters::ContainAllAdapter<CollectionType , ContainedCollectionType>::Contains( collection , containedContainer );
		}

		template<typename DataType>
		constexpr inline static auto Count( const DataType& data )
		{
			return Adapters::CountAdapter<DataType>::Count( data );
		}

		template<typename TypeA , typename TypeB>
		constexpr inline static bool Equals( const TypeA& A , const TypeB& B )
		{
			return Adapters::EqualityAdapter<TypeA , TypeB>::Equals( A , B );
		}

		template<typename DataType>
		constexpr inline static void GetHash( const DataType& data )
		{
			return Adapters::HashAdapter<DataType>::GetHash( data );
		}
	};
}