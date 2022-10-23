module;

#include "../../../../Macros/Macros.h"

export module AtlasAdapters:ContainAllAdapter;

import AtlasConcepts;
import AtlasDefinitions;
import AtlasIntegration;

export namespace Atlas
{
	template<typename CollectionType, typename ContainedCollectionType>
		requires Concept::IsSameContainedDataType<CollectionType , ContainedCollectionType>
	class DLLApi ContainAllAdapter<CollectionType, ContainedCollectionType> :
		public std::true_type
	{
		private: using DataType = Deduce::CollectionContainedType<CollectionType>;
		private: using SimpleCollectionType = Deduce::SimpleType<CollectionType>;
		private: using SimpleContainedType = Deduce::SimpleType<ContainedCollectionType>;

		private: constexpr static inline bool IsNoexcept = Concept::IsNoexceptIterableWith<CollectionType , DataType>;
			
			
		public:
		constexpr static inline bool ContainsAll(const SimpleCollectionType& collection, const SimpleContainedType& containedContainer)
			noexcept( IsNoexcept )
		{
			auto current = std::cbegin(containedContainer);
			const auto end = std::cend(containedContainer);

			for (; current != end; std::advance(current,1))
			{
				if (!Adapter::Contains(collection, *current))
				{
					return false;
				}
			}

			return true;
		}
	};
}