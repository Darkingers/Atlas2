module;

#include "../../../../Macros/Macros.h"

export module AtlasAdapters:ContainAllAdapter;

import AtlasConcepts;
import AtlasDefinitions;
import AtlasIntegration;

export namespace Atlas
{
	template<typename TCollection, typename ContainedTCollection>
		requires Concept::IsSameContainedDataType<TCollection , ContainedTCollection>
	class DLLApi ContainAllAdapter<TCollection, ContainedTCollection> :
		public std::true_type
	{
		private: using DataType = Deduce::CollectionContainedType<TCollection>;

			
		public:
		constexpr static inline bool ContainsAll(const TCollection& collection, const ContainedTCollection& containedContainer)
			noexcept( Concept::IsNoexceptIterableWith<TCollection , DataType> )
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