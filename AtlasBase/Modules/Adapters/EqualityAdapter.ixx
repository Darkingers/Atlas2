module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:EqualityAdapter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasExceptions;

export namespace Atlas::Adapters
{
	template<typename TypeA , typename TypeB>
	class DLLApi EqualityAdapter :
		public std::false_type
	{
	};
	
	template<typename TypeA, typename TypeB>
		requires Concept::HasEqualOperator<TypeA, TypeB>
	class DLLApi EqualityAdapter<TypeA, TypeB> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = noexcept ( std::declval<TypeA>( ) == std::declval<TypeB>() );

			
	    public:
		constexpr inline static bool Equals(const TypeA& a, const TypeB& b)
			noexcept( IsNoexcept )
		{
			return a == b;
		}
	};
}