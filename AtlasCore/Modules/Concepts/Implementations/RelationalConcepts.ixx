module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <typeinfo>

export module AtlasConcepts:RelationalConcepts;

export namespace Atlas::Concept
{
	template<typename TActual , typename TDerived>
	concept IsBaseOf = std::is_base_of<TActual , TDerived>::value;

	template<typename TActual , typename TBase>
	concept IsDerivedFrom = std::is_base_of<TBase , TActual>::value;

	template<unsigned int A , unsigned int B>
	concept IsMore = A > B;

	template<unsigned int A , unsigned int B>
	concept IsLess = A < B;

	template<unsigned int A , unsigned int B>
	concept IsMoreOrEqual = A >= B;

	template<unsigned int A , unsigned int B>
	concept IsLessOrEqual = A <= B;
}