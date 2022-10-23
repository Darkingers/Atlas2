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

	template<typename SourceType, typename TargetType>
	concept IsConvertibleTo = std::is_convertible<SourceType , TargetType>::value;

	template<typename SourceType , typename TargetType>
	concept IsNoexceptConvertibleTo = std::is_nothrow_convertible<SourceType , TargetType>::value;

	template<typename TestedType, typename... ConstructorArgs>
	concept IsConstructible = std::is_constructible<TestedType , ConstructorArgs...>::value;

	template<typename TestedType, typename... ConstructorArgs>
	concept IsNoexceptConstructible = std::is_nothrow_constructible<TestedType , ConstructorArgs...>::value;
}