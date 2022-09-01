module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:RelationalConcepts;

export namespace Atlas
{
	template<typename BaseType , typename DerivedType>
	concept IsBaseOf = std::is_base_of<BaseType , DerivedType>::value;

	template<typename DerivedType , typename BaseType>
	concept IsDerivedFrom = std::is_base_of<DerivedType , BaseType>::value;

	template<typename AssignLeft , typename AssignRight>
	concept IsAssignableFrom = std::is_assignable<AssignLeft , AssignRight>::value;
}