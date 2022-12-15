module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:AdapterDefinitions;

export namespace Atlas
{
	template<typename TCollection>
	class DLLApi ClearAdapter :
		public std::false_type
	{
		
	public:
		
		consteval static inline auto Clear( TCollection instance )
		{
			throw "ClearAdapter::Clear is not implemented for this type";
		}
	};

	template<typename TITerator , typename TElement>
	class DLLApi ContainAdapter :
		public std::false_type
	{
		
	public:
		
		consteval static inline auto Contain(TITerator start, unsigned int step, TElement element )
		{
			throw "ContainAdapter::Contain is not implemented for this type";
		}
	};

	template<typename TCollection>
	class DLLApi IterableAdapter :
		public std::false_type
	{
		
	public:

		consteval static inline auto At( TCollection collection, unsigned int step )
		{
			throw "IterableAdapter::At is not implemented for this type";
		}

		consteval static inline auto ConstAt( TCollection collection , unsigned int step )
		{
			throw "IterableAdapter::ConstAt is not implemented for this type";
		}

		consteval static inline auto Begin( TCollection collection )
		{
			throw "IterableAdapter::Begin is not implemented for this type";
		}

		consteval static inline auto ConstBegin( TCollection collection )
		{
			throw "IterableAdapter::ConstBegin is not implemented for this type";
		}

		consteval static inline auto End( TCollection collection )
		{
			throw "IterableAdapter::End is not implemented for this type";
		}

		consteval static inline auto ConstEnd( TCollection collection )
		{
			throw "IterableAdapter::ConstEnd is not implemented for this type";
		}
	};
	
	template<typename TExpected, typename TActual>
	class DLLApi CountAdapter :
		public std::false_type
	{
		
	public:

		consteval static inline auto Count( TActual instance )
		{
			throw "CountAdapter::Count is not implemented for this type";
		}
	};

	template<typename 

	template<typename T>
	class DLLApi SizeAdapter :
		public std::false_type
	{
		
	public:
		
		consteval static inline auto Size( T instance )
		{
			throw "SizeAdapter::Size is not implemented for this type";
		}
	};

	template<typename T>
	class DLLApi HashAdapter :
		public std::false_type
	{
		
	public:
		
		consteval static inline auto Hash( T instance )
		{
			throw "HashAdapter::Hash is not implemented for this type";
		}
	};

	template<typename TIterator>
	class DLLApi IteratorAdapter :
		public std::false_type
	{
		
	public:
		
		consteval static inline auto Move( TIterator iterator )
		{
			throw "IteratorAdapter::Move is not implemented for this type";
		}

		consteval static inline auto Current( TIterator iterator )
		{
			throw"IteratorAdapter::Current is not implemented for this type";
		}
	};


	template<typename TIterator , typename TSource>
	class DLLApi ReplaceFromAdapter :
		public std::false_type
	{
		
	public:
		
		consteval static inline void ReplaceFrom( TIterator iterator , TSource source )
		{
			throw "ReplaceFromAdapter::ReplaceFrom is not implemented for this type";
		}
	};

	template<typename TIteratorSource , typename TITeratorTarget>
	class DLLApi CopyAdapter :
		public std::false_type
	{

	public:

		consteval static inline void Copy( TIteratorSource source, TITeratorTarget target, unsigned int count)
		{
			throw "CopyAdapter::Copy is not implemented for this type";
		}
	};

	template<typename TA,typename TB>
	class DLLApi MatchAdapter :
		public std::false_type
	{
		
	public:

		consteval static inline auto Match( TA a , TB b, unsigned int matchLength )
		{
			throw "MatchAdapter::Match is not implemented for this type";
		}
	};

	///Generate ShiftAdapter for collection
	template<typename T>
	class DLLApi ShiftAdapter
	{

	public:

		consteval static inline auto Shift( T shifted, unsigned int shiftStart, int shiftOffset )
		{
			throw "ShiftAdapter::Shift is not implemented for this type";
		}
	};

}
