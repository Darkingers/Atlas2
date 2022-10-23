module;

#include "../../../../Macros/Macros.h"

export module AtlasAdapters:HashAdapter;

import AtlasConcepts;
import AtlasIntegration;

export namespace Atlas::Adapters
{
	template<typename DataType>
		requires Concept::IsStandardHashable<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
		private: static std::hash<DataType> Hash;

			
		public:
		constexpr static inline auto GetHash(const DataType& instance) 
			noexcept( noexcept( Hash(instance) ) )
		{
			return Hash(instance);
		}
	};

	template<typename DataType>
		requires Concept::HasGetHashFunction<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
	    public:
		constexpr static inline auto GetHash(const DataType& instance) 
			noexcept( noexcept ( instance.GetHash( ) ) )
		{
			return instance.GetHash();
		}
	};
}