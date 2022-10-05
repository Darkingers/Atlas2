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
	using Simplify = typename std::remove_const_t<std::remove_reference_t<DataType>> ;
}