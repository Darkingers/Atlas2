module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasTypeInfo:BasicTypeInfo;
import AtlasConcepts;

namespace Atlas::Fulfills
{
	template<typename TestedType>
	class IsPointer :std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsPointer<TestedType>
	class IsPointer<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class IsReference :std::false_type
	{};

	template<typename TestedType> 
		requires Concept::IsReference<TestedType>
	class IsReference<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class IsValue :std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsValue<TestedType>
	class IsValue<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class IsFundamental :std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsFundamental<TestedType>
	class IsFundamental<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class IsConst :std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsConst<TestedType>
	class IsConst<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class IsFloat :std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsFloat<TestedType>
	class IsFloat<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class IsBoolean :std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsBoolean<TestedType>
	class IsBoolean<TestedType> : std::true_type
	{};

	template<typename TestedType>
	class IsInteger :std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsInteger<TestedType>
	class IsInteger<TestedType> : std::true_type
	{};
}