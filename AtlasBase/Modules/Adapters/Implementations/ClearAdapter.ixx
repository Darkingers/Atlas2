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
		private: constexpr static inline bool IsNoexcept = noexcept ( std::declval<ClearedType>( ).clear( ) );

			
		public:
		constexpr static inline void Clear( ClearedType& instance )
			noexcept ( IsNoexcept )
		{
			instance.clear( );
		}
	};

	template<typename ClearedType>
		requires Concept::HasClearFunction<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		private: constexpr static inline bool IsNoexcept = noexcept ( std::declval<ClearedType>( ).Clear( ) );

			
		public:
		constexpr static inline void Clear( ClearedType& instance )
			noexcept ( IsNoexcept )
		{
			instance.Clear( );
		}
	};
}
