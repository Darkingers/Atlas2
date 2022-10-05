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
	class IsBaseOf :
		public std::false_type
	{};

	template<typename BaseType , typename DerivedType>
		requires Concept::IsBaseOf<BaseType, DerivedType>
	class IsBaseOf<BaseType,DerivedType> :
		public std::true_type
	{};

	template<typename DerivedType , typename BaseType>
	class IsDerivedFrom :
		public std::false_type
	{};

	template<typename DerivedType , typename BaseType> 
		requires Concept::IsDerivedFrom<DerivedType, BaseType>
	class IsDerivedFrom<DerivedType , BaseType> :
		public std::true_type
	{};

	template<typename AssignLeft , typename AssignRight>
	class IsAssignableFrom :
		public std::false_type
	{};

	template<typename AssignLeft , typename AssignRight> 
		requires Concept::IsAssignableFrom<AssignLeft, AssignRight>
	class IsAssignableFrom<AssignLeft , AssignRight> :
		public std::true_type
	{};
}