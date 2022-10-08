module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:Implementations;

export namespace Atlas::Implementation
{
	template<typename DataType>
	struct SimpleType
	{
		using type = DataType;
	};

	template<typename DataType>
	struct SimpleType<DataType*>
	{
		using type = DataType*;
	};

	template<typename DataType>
	struct SimpleType<DataType&>
	{
		using type = DataType;
	};

	template<typename DataType>
	struct SimpleType<const DataType>
	{
		using type = DataType;
	};

	template<typename DataType>
	struct SimpleType<const DataType*>
	{
		using type = DataType*;
	};

	template<typename DataType>
	struct SimpleType<const DataType&>
	{
		using type = DataType;
	};
}