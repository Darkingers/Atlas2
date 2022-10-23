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
		private: constexpr static bool IsNoexcept = noexcept( std::declval<std::hash<DataType>>( )( std::declval<DataType>( ) ) );

			
		private: static std::hash<DataType> Hash;

			
		public:
		constexpr static inline auto GetHash(const DataType& instance) 
			noexcept( IsNoexcept )
		{
			return Hash(instance);
		}
	};

	template<typename DataType>
		requires Concept::HasGetHashFunction<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept ( std::declval<DataType>( ).GetHash( ) );
			
			
	    public:
		constexpr static inline auto GetHash(const DataType& instance) 
			noexcept( IsNoexcept )
		{
			return instance.GetHash();
		}
	};
}