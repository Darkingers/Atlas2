module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasTypeInfo:VariadicTypeInfo;
import AtlasConcepts;

namespace Atlas::Fulfills
{
	template<typename TestedType, typename... Args>
	class IsSame :std::false_type
	{};

	template<typename TestedType , typename... Args> 
		requires Concept::IsSame<TestedType , Args...>
	class IsSame<TestedType , Args...> : std::true_type
	{};

	template<typename TestedType , typename... Args>
	class IsAll :std::false_type
	{};

	template<typename TestedType , typename... Args> 
		requires Concept::IsAll<TestedType , Args...>
	class IsAll<TestedType , Args...> : std::true_type
	{};

	template<typename TestedType , typename... Args>
	class IsAny :std::false_type
	{};

	template<typename TestedType , typename... Args>
		requires Concept::IsAny<TestedType , Args...>
	class IsAny<TestedType , Args...> : std::true_type
	{};

	template<typename TestedType , typename... Args>
	class IsNone :std::false_type
	{};

	template<typename TestedType , typename... Args>
		requires Concept::IsNone<TestedType , Args...>
	class IsNone<TestedType , Args...> : std::true_type
	{};
}