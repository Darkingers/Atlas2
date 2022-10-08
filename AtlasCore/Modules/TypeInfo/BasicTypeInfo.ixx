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
	class IsPointer : 
		public std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsPointer<TestedType>
	class IsPointer<TestedType> :
		public std::true_type
	{};

	template<typename TestedType>
	class IsReference :
		public std::false_type
	{};

	template<typename TestedType> 
		requires Concept::IsReference<TestedType>
	class IsReference<TestedType> : 
		public std::true_type
	{};

	template<typename TestedType>
	class IsValue :
		public std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsValue<TestedType>
	class IsValue<TestedType> : 
		public std::true_type
	{};

	template<typename TestedType>
	class IsFundamental :
		public std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsFundamental<TestedType>
	class IsFundamental<TestedType> : 
		public std::true_type
	{};

	template<typename TestedType>
	class IsConst :
		public std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsConst<TestedType>
	class IsConst<TestedType> :
		public std::true_type
	{};

	template<typename TestedType>
	class IsFloat :
		public std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsFloat<TestedType>
	class IsFloat<TestedType> : 
		public std::true_type
	{};

	template<typename TestedType>
	class IsBoolean :
		public std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsBoolean<TestedType>
	class IsBoolean<TestedType> :
		public std::true_type
	{};

	template<typename TestedType>
	class IsInteger :
		public std::false_type
	{};

	template<typename TestedType>
		requires Concept::IsInteger<TestedType>
	class IsInteger<TestedType> : 
		public std::true_type
	{};

	template <typename TestedType> 
	class IsTuple :
		public std::false_type
	{};

	template <typename ...T>
	class IsTuple<std::tuple<T...>> :
		public std::true_type
	{};
}