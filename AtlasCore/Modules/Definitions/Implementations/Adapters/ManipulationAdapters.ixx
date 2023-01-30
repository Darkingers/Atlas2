module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:ManipulationAdapters;

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

	template<typename... TArgs>
	class DLLApi ReplaceFromAdapter :
		public std::false_type
	{

	public:

		consteval static inline void ReplaceFrom( TArgs... args )
		{
			throw "ReplaceFromAdapter::ReplaceFrom is not implemented for this type";
		}
	};

	template<typename TCollectionA, typename TCollectionB>
	class DLLApi CopyCollectionToCollectionAdapter :
		public std::false_type
	{

	public:

		consteval static inline void Copy( 
			TCollectionA source , 
			unsigned int sourceStart,
			unsigned int sourceEnd,
			TCollectionB destination,
			unsigned int destinationStart
		)
		{
			throw "CopyCollectionToCollectionAdapter::Copy is not implemented for this type";
		}
	};
	
	template<typename TIterator , typename TCollection>
	class DLLApi CopyIteratorToCollectionAdapter :
		public std::false_type
	{

	public:

		consteval static inline void Copy(
			TIterator sourceStart,
			const TIterator sourceEnd,
			TCollection destination,
			unsigned int destinationStart
		)
		{
			throw "CopyIteratorToCollectionAdapter::Copy is not implemented for this type";
		}
	};

	template<typename TCollection , typename TIterator>
	class DLLApi CopyCollectionToIteratorAdapter :
		public std::false_type
	{

	public:

		consteval static inline void Copy(
			TCollection source ,
			unsigned int sourceStart,
			unsigned int sourceEnd,
			TIterator destinationStart
		)
		{
			throw "CopyCollectionToIteratorAdapter::Copy is not implemented for this type";
		}
	};

	template<typename TIteratorA , typename TIteratorB>
	class DLLApi CopyIteratorToIteratorAdapter :
		public std::false_type
	{

	public:

		consteval static inline void Copy( 
			TIteratorA sourceStart ,
			const TIteratorA sourceEnd ,
			TIteratorB destinationstart 
		)
		{
			throw "CopyIteratorToIteratorAdapter::Copy is not implemented for this type";
		}
	};

	template<typename TCollection>
	class DLLApi ShiftCollectionAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Shift(
			TCollection collection, 
			unsigned int shiftStart,
			unsigned int shiftOffset,
			unsigned int shiftSize
		)
		{
			throw "ShiftCollectionAdapter::Shift is not implemented for this type";
		}
	};

	template<typename TCollection>
	class DLLApi ResizeAdapter
	{

	public:

		consteval static inline void Resize( TCollection instance , const unsigned int newSize )
		{
			throw "ResizeAdapter::Resize is not implemented for this type";
		}
	};
}
