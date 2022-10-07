module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeHelpers;

export namespace Atlas
{
	template<typename DataType, typename ExpectedType>
	using IgnoreConst = typename std::enable_if<std::is_same<DataType , ExpectedType>::value || std::is_same<DataType , const ExpectedType>::value>::type;
	
	template<typename DataType>
	struct SimplifyImpl
	{
		using type = DataType;
	};

	template<typename DataType>
	struct SimplifyImpl<const DataType*>
	{
		using type = DataType*;
	};

	template<typename DataType>
	struct SimplifyImpl<const DataType&>
	{
		using type = DataType;
	};

	template<typename DataType>
	struct SimplifyImpl<const DataType>
	{
		using type = DataType;
	};

	template<typename DataType>
	using Simplify = typename SimplifyImpl<DataType>::type;

}