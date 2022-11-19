module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:RelationalConcepts;

export namespace Atlas::Concept
{
	template<typename TestedType , typename DerivedType>
	concept IsBaseOf = std::is_base_of<TestedType , DerivedType>::value;

	template<typename TestedType , typename BaseType>
	concept IsDerivedFrom = std::is_base_of<BaseType , TestedType>::value;

	template<typename TestedType , typename ValueType>
	concept IsAssignableFrom = std::is_assignable<TestedType , ValueType>::value;

	template<unsigned int A , unsigned int B>
	concept IsMore = A > B;

	template<unsigned int A , unsigned int B>
	concept IsLess = A < B;

	template<unsigned int A , unsigned int B>
	concept IsMoreOrEqual = A >= B;

	template<unsigned int A , unsigned int B>
	concept IsLessOrEqual = A <= B;

	template<typename TestedType, typename TargetType>
	concept IsConvertibleTo = std::is_convertible<TestedType , TargetType>::value;

	template<typename TestedType , typename TargetType>
	concept IsNoexceptConvertibleTo = std::is_nothrow_convertible<TestedType , TargetType>::value;

	template<typename TestedType, typename... ConstructorArgs>
	concept IsConstructible = std::is_constructible<TestedType , ConstructorArgs...>::value;

	template<typename TestedType, typename... ConstructorArgs>
	concept IsNoexceptConstructible = std::is_nothrow_constructible<TestedType , ConstructorArgs...>::value;
}