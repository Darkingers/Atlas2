module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeDefinitions;

export namespace Atlas::Definition
{
	template<typename ReturnType , typename... Arguments>
	using StaticFunction = ReturnType( * )( Arguments... );

	template<typename ReturnType , typename ClassType , typename... Arguments>
	using MemberFunction = ReturnType( ClassType::* )( Arguments... );

	template<typename ReturnType , typename... Arguments>
	using ExternalFunction = ReturnType( __stdcall* )( Arguments... );

	template<typename ReturnType , typename... Arguments>
	using LambdaFunction = std::function<ReturnType( Arguments... )>;

	
	template<typename TargetType , typename SourceType>
	using ConverterFunction = LambdaFunction<TargetType , SourceType>;

	template<typename ComparedType>
	using ComparatorFunction = LambdaFunction<int , const ComparedType&, const ComparedType&>;

	template<typename T>
	using ConditionFunction = LambdaFunction<bool , const T&>;

	template<typename T, typename KeyType>
	using KeyGeneratorFunction = LambdaFunction<KeyType , const T&>;
}