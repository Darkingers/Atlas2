module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:VariadicConcepts;

export namespace Atlas
{
	export template<typename TestedType , typename RequiredType>
	concept IsSame = std::is_same<TestedType , RequiredType>::value;

	template<typename RequiredType , typename... TestedType>
	concept IsAll = std::conjunction<std::is_same<RequiredType,TestedType>...>::value;

	template<typename RequiredType , typename... TestedType>
	concept IsAny = std::disjunction<std::is_same<RequiredType,TestedType>...>::value;

	template<typename RequiredType , typename... TestedType>
	concept IsNone = !IsAny<RequiredType , TestedType...>;

	template<unsigned int Index, typename... Args>
	concept IsMore = sizeof...( Args ) > Index;

	template<unsigned int Index , typename... Args>
	concept IsLess = sizeof...( Args ) < Index;

	template<unsigned int Index , typename... Args>
	concept IsMoreOrEqual = sizeof...( Args ) >= Index;

	template<unsigned int Index , typename... Args>
	concept IsLessOrEqual = sizeof...( Args ) <= Index;
}