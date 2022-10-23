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

			
		public:
		constexpr static inline bool ContainsAll(const CollectionType& collection, const ContainedCollectionType& containedContainer)
			noexcept( Concept::IsNoexceptIterableWith<CollectionType , DataType> )
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