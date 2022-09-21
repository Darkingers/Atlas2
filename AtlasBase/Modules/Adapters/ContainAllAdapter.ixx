module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:ContainAllAdapter;
import AtlasConcepts;
import AtlasDefinitions;
import AtlasExceptions;
import :ContainAdapter;


export namespace Atlas::Adapters
{
	template<typename CollectionType , typename ContainedCollectionType>
	class DLLApi ContainAllAdapter :
		public std::false_type
	{
		public:
		inline static bool ContainsAll( const CollectionType& collection , const ContainedCollectionType& containedContainer )
		{
			Throw<AdapterResolveException>( "Could not resolve ContainAllAdapter for "+ typeid( CollectionType ).name( )+","+ typeid( ContainedCollectionType ).name( ) );
		}
	};
	
	template<typename CollectionType, typename ContainedCollectionType>
		requires Concept::IsSame<Deduce::CollectionContainedType<CollectionType>, Deduce::CollectionContainedType<ContainedCollectionType>>
	class DLLApi ContainAllAdapter<CollectionType, ContainedCollectionType> :
		public std::true_type
	{
		private: using DataType = Deduce::CollectionContainedType<CollectionType>;
		private: using IteratorType = Deduce::IteratorType<CollectionType>;
			   	
		private: static constexpr bool IsNoExceptBegin = noexcept ( std::cbegin( std::declval<CollectionType>( ) ) );
		private: static constexpr bool IsNoExceptEnd = noexcept ( std::cend( std::declval<CollectionType>( ) ) );
		private: static constexpr bool IsNoExceptContains = noexcept ( ContainAdapter<CollectionType , DataType>::Contains( std::declval<CollectionType>( ) , std::declval<DataType>( ) ) );
		private: static constexpr bool IsNoExcept = IsNoExceptBegin && IsNoExceptEnd && IsNoExceptContains;

		public:
		constexpr inline static bool ContainsAll(const CollectionType& collection, const ContainedCollectionType& containedContainer) noexcept( IsNoExcept )
		{
			auto current = std::cbegin(containedContainer);
			const auto end = std::cend(containedContainer);

			for (; current != end; std::advance(current,1))
			{
				if (!ContainAdapter<CollectionType,DataType>::Contains(collection, *current))
				{
					return false;
				}
			}

			return true;
		}
	};
}