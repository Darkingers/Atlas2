module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:ClearAdapter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasDefinitions;

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
		private: constexpr static bool IsNoexcept = noexcept ( Type<ClearedType>::Instance( ).clear( ) );

			
		public:
		constexpr inline static void Clear( ClearedType& instance )
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
		private: constexpr static bool IsNoexcept = noexcept ( Type<ClearedType>::Instance( ).Clear( ) );

			
		public:
		constexpr inline static void Clear( ClearedType& instance )
			noexcept ( IsNoexcept )
		{
			instance.Clear( );
		}
	};
}
