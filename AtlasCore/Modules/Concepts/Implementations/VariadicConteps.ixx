module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:VariadicConcepts;

export namespace Atlas::Concept
{
	export template<typename TActual , typename TExpected>
	concept IsSame = std::is_same<TActual , TExpected>::value;

	template<typename TActual , typename... TExpected>
	concept IsAll = std::conjunction<std::is_same<TExpected , TActual>...>::value;

	template<typename TActual , typename... TExpected>
	concept IsAny = std::disjunction<std::is_same<TExpected , TActual>...>::value;

	template<typename TActual , typename... TExpected>
	concept IsNone = !IsAny<TActual , TExpected...>;
}