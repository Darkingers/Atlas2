module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeDeducers;

namespace Atlas::Implementation
{
	template<typename T>
	struct SimpleType
	{
		using type = T;
	};

	template<typename T>
	struct SimpleType<T*>
	{
		using type = T*;
	};

	template<typename T>
	struct SimpleType<T&>
	{
		using type = T;
	};

	template<typename T>
	struct SimpleType<const T>
	{
		using type = T;
	};

	template<typename T>
	struct SimpleType<const T*>
	{
		using type = T*;
	};

	template<typename T>
	struct SimpleType<const T&>
	{
		using type = T;
	};
}

export namespace Atlas::Deduce
{
	template<typename T>
	using DereferencedType = decltype( std::declval<T>( ).operator*( ) );

	template<typename TInvokable , typename... TArgs>
	using ReturnType = typename std::invoke_result_t<TInvokable( TArgs... )>;

	template<typename T>
	using SimpleType = typename Atlas::Implementation::SimpleType<T>::type;

	template<unsigned int Index , typename TTuple>
	using TupleIndexedType = decltype( std::get<Index>( std::declval<TTuple>( ) ) );

	template<unsigned int Index , typename... TArgs>
	using IndexedArgumentType = typename std::tuple_element<Index , std::tuple<TArgs...>>;
}