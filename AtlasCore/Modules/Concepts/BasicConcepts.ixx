module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:BasicConcepts;

namespace Atlas::Concept::Implementation
{
	template <typename TestedType>
	class IsTuple :
		public std::false_type
	{};

	template <typename ...T>
	class IsTuple<std::tuple<T...>> :
		public std::true_type
	{};
}

export namespace Atlas::Concept
{
	template<typename TestedType>
	concept IsPointer = std::is_pointer<TestedType>::value;

	template<typename TestedType>
	concept IsReference = std::is_reference<TestedType>::value;

	template<typename TestedType>
	concept IsValue = !IsPointer<TestedType> && !IsReference<TestedType>;

	template<typename TestedType>
	concept IsFundamental = std::is_fundamental<TestedType>::value;

	template<typename TestedType>
	concept IsConst = std::is_const<TestedType>::value;

	template<typename TestedType>
	concept IsFloat = std::is_floating_point<std::remove_reference<TestedType>>::value;

	template<typename TestedType>
	concept IsBoolean = std::_Boolean_testable<std::remove_reference<TestedType>>;

	template<typename TestedType>
	concept IsInteger = std::is_integral<std::remove_reference<TestedType>>::value;

	template<typename TestedType>
	concept IsTuple = Implementation::IsTuple<TestedType>::value;
}