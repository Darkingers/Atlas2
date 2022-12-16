module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:QueryAdapters;

export namespace Atlas
{
	template<typename TCollection , typename TElement>
	class DLLApi ContainAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Contain( TCollection collection , TElement element )
		{
			throw "ContainAdapter::Contain is not implemented for this type";
		}
	};

	
	template<typename TExpected , typename TActual>
	class DLLApi CountTypeAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Count( TActual instance )
		{
			throw "CountAdapter::Count is not implemented for this type";
		}
	};

	template<typename TCollection , typename TElement>
	class DLLApi CountElementAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Count( TCollection start , TElement element )
		{
			throw "ContainAdapter::Contain is not implemented for this type";
		}
	};

	template<typename TCollection>
	class DLLApi LengthAdapter :
		public std::false_type
	{

		public:

		consteval static inline auto Length( TCollection instance )
		{
			throw "LengthAdapter::Length is not implemented for this type";
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

	template<typename TCollection , typename TPattern>
	class DLLApi ContainPatternAdapter :
		public std::false_type
	{
		public:

		consteval static inline auto Contains( TCollection collection , TPattern pattern , const unsigned int matchLength )
		{
			throw "PatternMatchAdapter::Match is not implemented for this type";
		}
	};
}
