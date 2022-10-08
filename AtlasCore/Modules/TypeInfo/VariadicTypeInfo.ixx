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
	class IsSame :
		public std::false_type
	{};

	template<typename TestedType , typename... Args> 
		requires Concept::IsSame<TestedType , Args...>
	class IsSame<TestedType , Args...> : 
		public std::true_type
	{};

	template<typename TestedType , typename... Args>
	class IsAll :
		public std::false_type
	{};

	template<typename TestedType , typename... Args> 
		requires Concept::IsAll<TestedType , Args...>
	class IsAll<TestedType , Args...> :
		public std::true_type
	{};

	template<typename TestedType , typename... Args>
	class IsAny :
		public std::false_type
	{};

	template<typename TestedType , typename... Args>
		requires Concept::IsAny<TestedType , Args...>
	class IsAny<TestedType , Args...> :
		public std::true_type
	{};

	template<typename TestedType , typename... Args>
	class IsNone :
		public std::false_type
	{};

	template<typename TestedType , typename... Args>
		requires Concept::IsNone<TestedType , Args...>
	class IsNone<TestedType , Args...> : 
		public std::true_type
	{};
}