module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasTypeInfo:VariadicTypeInfo;
import AtlasConcepts;

namespace Atlas
{
	template<typename TestedType, typename... Args>
	class FulfillsIsSame :std::false_type
	{};

	template<typename TestedType , typename... Args> requires IsSame<TestedType , Args...>
	class FulfillsIsSame<TestedType , Args...> : std::true_type
	{};

	template<typename TestedType , typename... Args>
	class FulfillsIsAll :std::false_type
	{};

	template<typename TestedType , typename... Args> requires IsAll<TestedType , Args...>
	class FulfillsIsAll<TestedType , Args...> : std::true_type
	{};

	template<typename TestedType , typename... Args>
	class FulfillsIsAny :std::false_type
	{};

	template<typename TestedType , typename... Args> requires IsAny<TestedType , Args...>
	class FulfillsIsAny<TestedType , Args...> : std::true_type
	{};

	template<typename TestedType , typename... Args>
	class FulfillsIsNone :std::false_type
	{};

	template<typename TestedType , typename... Args> requires IsNone<TestedType , Args...>
	class FulfillsIsNone<TestedType , Args...> : std::true_type
	{};
}