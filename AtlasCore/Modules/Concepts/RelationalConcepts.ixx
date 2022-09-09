module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:RelationalConcepts;

export namespace Atlas::Concept
{
	template<typename BaseType , typename DerivedType>
	concept IsBaseOf = std::is_base_of<BaseType , DerivedType>::value;

	template<typename DerivedType , typename BaseType>
	concept IsDerivedFrom = std::is_base_of<DerivedType , BaseType>::value;

	template<typename AssignLeft , typename AssignRight>
	concept IsAssignableFrom = std::is_assignable<AssignLeft , AssignRight>::value;

	template<unsigned int A , unsigned int B>
	concept IsMore = A > B;

	template<unsigned int A , unsigned int B>
	concept IsLess = A < B;

	template<unsigned int A , unsigned int B>
	concept IsMoreOrEqual = A >= B;

	template<unsigned int A , unsigned int B>
	concept IsLessOrEqual = A <= B;
}