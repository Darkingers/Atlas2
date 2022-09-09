module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeDefinitions;

export namespace Atlas::Definition
{
	template<typename ReturnType , typename... Args>
	using StaticFunction = ReturnType( * )( Args... );

	template<typename ReturnType , typename InstanceType , typename... Args>
	using MemberFunction = ReturnType( InstanceType::* )( Args... );

	template<typename ReturnType , typename... Args>
	using ExternalFunction = ReturnType( __stdcall* )( Args... );

	template<typename ReturnType , typename... Args>
	using LambdaFunction = std::function<ReturnType( Args... )>;

	template<typename ConversionType , typename ConvertedType>
	using Converter = LambdaFunction<ConversionType , ConvertedType>;

	template<typename ComparedType>
	using Comparator = LambdaFunction<int , const ComparedType&, const ComparedType&>;

	template<typename DataType>
	using Condition = LambdaFunction<bool , const DataType&>;
}