module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasTypeInfo:BasicTypeInfo;
import AtlasConcepts;

namespace Atlas
{
	template<typename TestedType>
	class FulfillsIsPointer :std::false_type
	{};

	template<typename TestedType> requires IsPointer<TestedType>
	class FulfillsIsPointer<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class FulfillsIsReference :std::false_type
	{};

	template<typename TestedType> requires IsReference<TestedType>
	class FulfillsIsReference<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class FulfillsIsValue :std::false_type
	{};

	template<typename TestedType> requires IsValue<TestedType>
	class FulfillsIsValue<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class FulfillsIsFundamental :std::false_type
	{};

	template<typename TestedType> requires IsFundamental<TestedType>
	class FulfillsIsFundamental<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class FulfillsIsConst :std::false_type
	{};

	template<typename TestedType> requires IsConst<TestedType>
	class FulfillsIsConst<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class FulfillsIsFloat :std::false_type
	{};

	template<typename TestedType> requires IsFloat<TestedType>
	class FulfillsIsFloat<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class FulfillsIsBoolean :std::false_type
	{};

	template<typename TestedType> requires IsBoolean<TestedType>
	class FulfillsIsBoolean<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class FulfillsIsInteger :std::false_type
	{};

	template<typename TestedType> requires IsInteger<TestedType>
	class FulfillsIsInteger<TestedType> : std::true_type
	{};
}