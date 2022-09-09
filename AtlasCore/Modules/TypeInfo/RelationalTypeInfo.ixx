module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasTypeInfo:RelationalTypeInfo;
import AtlasConcepts;

namespace Atlas::Fulfills
{
	template<typename BaseType, typename DerivedType>
	class IsBaseOf :std::false_type
	{};

	template<typename BaseType , typename DerivedType>
		requires Concept::IsBaseOf<BaseType, DerivedType>
	class IsBaseOf<BaseType,DerivedType> : std::true_type
	{};

	template<typename DerivedType , typename BaseType>
	class IsDerivedFrom :std::false_type
	{};

	template<typename DerivedType , typename BaseType> 
		requires Concept::IsDerivedFrom<DerivedType, BaseType>
	class IsDerivedFrom<DerivedType , BaseType> : std::true_type
	{};

	template<typename AssignLeft , typename AssignRight>
	class IsAssignableFrom :std::false_type
	{};

	template<typename AssignLeft , typename AssignRight> 
		requires Concept::IsAssignableFrom<AssignLeft, AssignRight>
	class IsAssignableFrom<AssignLeft , AssignRight> : std::true_type
	{};
}