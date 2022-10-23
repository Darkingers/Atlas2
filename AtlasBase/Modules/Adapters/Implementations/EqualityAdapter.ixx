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
	    public:
		constexpr static inline bool Equals(const TypeA& a, const TypeB& b)
			noexcept( noexcept ( a==b ) )
		{
			return a == b;
		}
	};

	template<typename TypeA , typename TypeB>
	class DLLApi EqualityAdapter<TypeA* , TypeB*> :
		public std::true_type
	{
		public:
		constexpr static inline bool Equals( const TypeA a , const TypeB b )
			noexcept( noexcept ( reinterpret_cast<TypeB>(a) == b ) )
		{
			return reinterpret_cast<TypeB>( a ) == b;
		}
	};
}