module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:RelationalConcepts;

export namespace Atlas::Concept
{
	template<typename TActual , typename TDerived>
	concept IsBaseOf = std::is_base_of<TActual , TDerived>::value;

	template<typename TActual , typename TBase>
	concept IsDerivedFrom = std::is_base_of<TBase , TActual>::value;

	template<typename TActual , typename TValue>
	concept IsAssignable = std::is_assignable<TActual , TValue>::value;

	template<unsigned int A , unsigned int B>
	concept IsMore = A > B;

	template<unsigned int A , unsigned int B>
	concept IsLess = A < B;

	template<unsigned int A , unsigned int B>
	concept IsMoreOrEqual = A >= B;

	template<unsigned int A , unsigned int B>
	concept IsLessOrEqual = A <= B;

	template<typename TSource , typename TTarget>
	concept IsConvertibleTo = std::is_convertible<TSource , TTarget>::value;

	template<typename TSource , typename TTarget>
	concept IsNoexceptConvertibleTo = std::is_nothrow_convertible<TSource , TTarget>::value;

	template<typename TActual , typename... TArgs>
	concept IsConstructible = std::is_constructible<TActual , TArgs...>::value;

	template<typename TActual , typename... TArgs>
	concept IsNoexceptConstructible = noexcept ( TActual( std::declval<TArgs>()... ) );

	template<typename TLeft, typename TRight>
	concept IsNoexceptAssignable = noexcept ( std::declval<TLeft>( ) = std::declval<TRight>( ) );

	template<typename TLeft , typename TRight>
	concept IsNoexceptEqual = noexcept ( std::declval<TLeft>( ) == std::declval<TRight>( ) );

	template<typename TLeft , typename TRight>
	concept IsNoexceptNotEqual = noexcept ( std::declval<TLeft>( ) != std::declval<TRight>( ) );
}