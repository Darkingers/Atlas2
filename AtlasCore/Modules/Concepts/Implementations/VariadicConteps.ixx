module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:VariadicConcepts;

export namespace Atlas::Concept
{
	export template<typename TestedType , typename RequiredType>
	concept IsSame = std::is_same<TestedType , RequiredType>::value;

	template<typename TestedType , typename... RequiredType>
	concept IsAll = std::conjunction<std::is_same<RequiredType,TestedType>...>::value;

	template<typename TestedType , typename... RequiredType>
	concept IsAny = std::disjunction<std::is_same<RequiredType,TestedType>...>::value;

	template<typename TestedType , typename... RequiredType>
	concept IsNone = !IsAny<TestedType , RequiredType...>;
}