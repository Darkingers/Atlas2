module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:IteratorAdapters;

export namespace Atlas
{
	// Code generation helper:
	// Iterator<TIterator>-auto Move(TIterator)
	// Iterator<TIterator>-auto Current(TIterator)
	// Iterable<TCollection>-auto At(TCollection, const unsigned int)
	// Iterable<TCollection>-auto ConstAt(TCollection, const unsigned int)
	// Iterable<TCollection>-auto Begin(TCollection)
	// Iterable<TCollection>-auto End(TCollection)
	// Iterable<TCollection>-auto ConstBegin(TCollection)
	// Iterable<TCollection>-auto ConstEnd(TCollection)

	template<typename TIterator>
	class DLLApi IteratorAdapter :
		public std::false_type
	{

		public:

		consteval static inline auto Move( TIterator iterator , const int step )
		{
			throw "IteratorAdapter::Move is not implemented for this type";
		}

		consteval static inline auto Current( TIterator iterator )
		{
			throw"IteratorAdapter::Current is not implemented for this type";
		}
	};

	template<typename TCollection>
	class DLLApi IterableAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto At( TCollection collection , const unsigned int step )
		{
			throw "IterableAdapter::At is not implemented for this type";
		}

		consteval static inline auto ConstAt( TCollection collection , const unsigned int step )
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
}
