module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:QueryAdapters;

export namespace Atlas
{
	//The following text block is a code-generation helper.
	// ContainAdapter<TITerator,TEleemnt>-auto Contain(TIterator, const unsigned int, TElement)
	// CountAdapter<TExpected,TActual>-auto Count(TActual)
	// MatchAdapter<TA,TB>-auto Match(TA, TB, const unsigned int)

	template<typename TITerator , typename TElement>
	class DLLApi ContainAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Contain( TITerator start ,const unsigned int step , TElement element )
		{
			throw "ContainAdapter::Contain is not implemented for this type";
		}
	};
	
	template<typename TExpected , typename TActual>
	class DLLApi CountAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Count( TActual instance )
		{
			throw "CountAdapter::Count is not implemented for this type";
		}
	};

	template<typename TA , typename TB>
	class DLLApi MatchAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Match( TA a , TB b ,const unsigned int matchLength )
		{
			throw "MatchAdapter::Match is not implemented for this type";
		}
	};
}
