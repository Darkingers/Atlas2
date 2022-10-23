module;

#include "../../../../Macros/Macros.h"

export module AtlasAdapters:EqualityAdapter;

import AtlasConcepts;
import AtlasIntegration;

export namespace Atlas
{

	template<typename TypeA, typename TypeB>
		requires Concept::HasEqualOperator<TypeA, TypeB>
	class DLLApi EqualityAdapter<TypeA, TypeB> :
		public std::true_type
	{
		private: constexpr static bool IsNoexcept = noexcept ( std::declval<TypeA>( ) == std::declval<TypeB>() );

			
	    public:
		constexpr static inline bool Equals(const TypeA& a, const TypeB& b)
			noexcept( IsNoexcept )
		{
			return a == b;
		}
	};
}