module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeDefinitions;

export namespace Atlas::Definition
{
	template<typename TReturn , typename... TArgs>
	using StaticFunction = TReturn( * )( TArgs... );

	template<typename ReturnType , typename ClassType , typename... TArgs>
	using MemberFunction = ReturnType( ClassType::* )( TArgs... );

	template<typename ReturnType , typename... TArgs>
	using ExternalFunction = ReturnType( __stdcall* )( TArgs... );

	template<typename ReturnType , typename... TArgs>
	using GeneralFunction = std::function<ReturnType( TArgs... )>;

	
	template<typename TTarget , typename TSource>
	using ConverterFunction = GeneralFunction<TTarget , TSource>;

	template<typename ComparedType>
	using ComparatorFunction = GeneralFunction<int , const ComparedType&, const ComparedType&>;

	template<typename T>
	using Predicate = GeneralFunction<bool , const T&>;

	template<typename T, typename KeyType>
	using KeyGenerator = GeneralFunction<KeyType , const T&>;
}