module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:EqualityAdapter;
import AtlasConcepts;
import AtlasExceptions;

export namespace Atlas::Adapters
{
	template<typename TypeA , typename TypeB>
	class DLLApi EqualityAdapter :
		public std::false_type
	{
		public:
		inline static bool Equals( const TypeA& a , const TypeB& b )
		{
			Throw<AdapterResolveException>( "Could not resolve EqualityAdapter" , a , b );
		}
	};
	
	template<typename TypeA, typename TypeB>
		requires Concept::HasEqualOperator<TypeA, TypeB>
	class DLLApi EqualityAdapter<TypeA, TypeB> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<TypeA>( ) == std::declval<TypeB>() );

	    public:
		inline static bool Equals(const TypeA& a, const TypeB& b) noexcept( IsNoExcept )
		{
			return a == b;
		}
	};
}