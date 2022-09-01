module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:EqualityAdapter;
import AtlasConcepts;
import AtlasExceptions;

export namespace Atlas
{
	template<typename TypeA, typename TypeB>
	class DLLApi EqualityAdapter :
		public std::false_type
	{
	    public:
		inline static constexpr bool Equals(const TypeA& a, const TypeB& b)
		{
			throw AdapterResolveException( "Could not resolve EqualityAdapter");
		}
	};

	template<typename TypeA, typename TypeB>
		requires HasEqualOperator<TypeA, TypeB>
	class DLLApi EqualityAdapter<TypeA, TypeB> :
		public std::true_type
	{
		private: static constexpr bool NoExcept = noexcept ( std::declval<TypeA>( ) == std::declval<TypeB>() );

	    public:
		inline static constexpr bool Equals(const TypeA& a, const TypeB& b) noexcept( NoExcept )
		{
			return a == b;
		}
	};
}