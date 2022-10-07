module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:ClearAdapter;

import AtlasTypeInfo;
import AtlasConcepts;

export namespace Atlas::Adapters
{
	template<typename ClearedType>
	class DLLApi ClearAdapter:
		public std::false_type
	{
	};
	
	template<typename ClearedType> 
		requires Concept::IsStandardClearable<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<ClearedType>.clear( ) );

		public:
		constexpr inline static void Clear( ClearedType& instance ) noexcept ( IsNoExcept )
		{
			instance.clear( );
		}
	};

	template<typename ClearedType>
		requires Concept::HasClearFunction<ClearedType>
	class DLLApi ClearAdapter<ClearedType> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<ClearedType>.Clear( ) );

		public:
		constexpr inline static void Clear( ClearedType& instance ) noexcept ( IsNoExcept )
		{
			instance.Clear( );
		}
	};
}

export namespace Atlas::Concept
{
	template<typename ClearedType>
	concept HasClearAdapter = Atlas::Adapters::ClearAdapter<ClearedType>::value;
}