module;

#include "../../../../Macros/Macros.h"

export module AtlasAdapters:ClearAdapter;

import AtlasConcepts;
import AtlasIntegration;

export namespace Atlas
{
	template<typename ClearedType> 
		requires Concept::IsStandardClearable<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		public:
		constexpr static inline void Clear( ClearedType& instance )
			noexcept ( noexcept ( instance.clear( ) ) )
		{
			instance.clear( );
		}
	};

	template<typename ClearedType>
		requires Concept::HasClearFunction<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		public:
		constexpr static inline void Clear( ClearedType& instance )
			noexcept ( noexcept ( instance.Clear( ) ) )
		{
			instance.Clear( );
		}
	};
}
