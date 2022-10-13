module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:ContainAllAdapter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasDefinitions;

import :ContainAdapter;

export namespace Atlas::Adapters
{
	template<typename CollectionType , typename ContainedCollectionType>
	class DLLApi ContainAllAdapter :
		public std::false_type
	{
	};
	
	template<typename CollectionType, typename ContainedCollectionType>
		requires Concept::IsSame<Deduce::CollectionContainedType<CollectionType>, Deduce::CollectionContainedType<ContainedCollectionType>>
	class DLLApi ContainAllAdapter<CollectionType, ContainedCollectionType> :
		public std::true_type
	{
		private: using DataType = Deduce::CollectionContainedType<CollectionType>;
		private: using SimpleCollectionType = Deduce::SimpleType<CollectionType>;
		private: using SimpleContainedType = Deduce::SimpleType<ContainedCollectionType>;
		private: using ContainAdapterType = ContainAdapter<SimpleCollectionType , DataType>;
   	
			
		private: constexpr static bool IsNoexceptBegin = Concept::IsNoexceptBegin<CollectionType>;
		private: constexpr static bool IsNoexceptEnd = Concept::IsNoexceptConstEnd<CollectionType>;
		private: constexpr static bool IsNoexceptContains = noexcept ( ContainAdapterType::Contains( CollectionType( ) , DataType( ) ) );
		private: constexpr static bool IsNoexcept = IsNoexceptBegin && IsNoexceptEnd && IsNoexceptContains;

			
		public:
		constexpr inline static bool ContainsAll(const SimpleCollectionType& collection, const SimpleContainedType& containedContainer)
			noexcept( IsNoexcept )
		{
			auto current = std::cbegin(containedContainer);
			const auto end = std::cend(containedContainer);

			for (; current != end; std::advance(current,1))
			{
				if (!ContainAdapterType::Contains(collection, *current))
				{
					return false;
				}
			}

			return true;
		}
	};
}