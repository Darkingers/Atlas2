module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasTypeInfo:RelationalTypeInfo;
import AtlasConcepts;

namespace Atlas
{
	template<typename BaseType, typename DerivedType>
	class FulfillsIsBaseOf :std::false_type
	{};

	template<typename BaseType , typename DerivedType> requires IsBaseOf<BaseType, DerivedType>
	class FulfillsIsBaseOf<BaseType,DerivedType> : std::true_type
	{};

	template<typename DerivedType , typename BaseType>
	class FulfillsIsDerivedFrom :std::false_type
	{};

	template<typename DerivedType , typename BaseType> requires IsDerivedFrom<DerivedType, BaseType>
	class FulfillsIsDerivedFrom<DerivedType , BaseType> : std::true_type
	{};

	template<typename AssignLeft , typename AssignRight>
	class FulfillsIsAssignableFrom :std::false_type
	{};

	template<typename AssignLeft , typename AssignRight> requires IsAssignableFrom<AssignLeft, AssignRight>
	class FulfillsIsAssignableFrom<AssignLeft , AssignRight> : std::true_type
	{};
}