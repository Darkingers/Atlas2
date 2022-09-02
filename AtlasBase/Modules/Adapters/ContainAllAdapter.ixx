module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:ContainAllAdapter;
import AtlasConcepts;
import AtlasDefinitions;
import AtlasExceptions;
import :ContainAdapter;


export namespace Atlas
{
	template<typename CollectionType, typename ContainedCollectionType>
	class DLLApi ContainAllAdapter :
		public std::false_type
	{
	    public:
		inline static bool ContainsAll(const CollectionType& collection, const ContainedCollectionType& containedContainer)
		{
			throw AdapterResolveException( "Could not resolve ContainAdapter", &collection);
		}
	};

	template<typename CollectionType, typename ContainedCollectionType>
		requires IsSame<
			DeduceCollectionContainedType<CollectionType>, 
			DeduceCollectionContainedType<ContainedCollectionType>>
	class DLLApi ContainAllAdapter<CollectionType, ContainedCollectionType> :
		public std::true_type
	{
		private: using DataType = DeduceCollectionContainedType<CollectionType>;
		private: using IteratorType = DeduceIteratorType<CollectionType>;
			   	
		private: static constexpr bool NoExceptBegin = noexcept ( std::cbegin( std::declval<CollectionType>( ) ) );
		private: static constexpr bool NoExceptEnd = noexcept ( std::cend( std::declval<CollectionType>( ) ) );
		private: static constexpr bool NoExceptContains = noexcept ( ContainAdapter<CollectionType , DataType>::Contains( std::declval<CollectionType>( ) , std::declval<DataType>( ) ) );
		private: static constexpr bool NoExcept = NoExceptBegin && NoExceptEnd && NoExceptContains;

		public:
		inline static bool ContainsAll(const CollectionType& collection, const ContainedCollectionType& containedContainer) noexcept( NoExcept )
		{
			IteratorType current = std::cbegin(containedContainer);
			const IteratorType end = std::cend(containedContainer);

			for (; current != end; std::advance(current,1))
			{
				if (!ContainAdapter<CollectionType, DataType>::Contains(collection, *current))
				{
					return false;
				}
			}

			return true;
		}
	};
}