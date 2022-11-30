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
		consteval static inline auto Clear( TCollection& instance )
		{
			throw "ClearAdapter::Clear is not implemented for this type";
		}
	};

	template<typename TCollection , typename TElement>
	class DLLApi ContainAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Contain( const TCollection& collection , const TElement& element )
		{
			throw "ContainAdapter::Contain is not implemented for this type";
		}
	};

	template<typename TCollectionA , typename TCollectionB>
	class DLLApi ContainAllAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto ContainAll( const TCollectionA& collection , const TCollectionB& containedCollection )
		{
			throw "ContainAllAdapter::ContainAll is not implemented for these types";
		}
	};

	template<typename TCollection>
	class DLLApi IterableAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Begin( TCollection& collection )
		{
			throw "IterableAdapter::Begin is not implemented for this type";
		}

		public:
		consteval static inline auto ConstBegin( const TCollection& collection )
		{
			throw "IterableAdapter::ConstBegin is not implemented for this type";
		}

		public:
		consteval static inline auto End( TCollection& collection )
		{
			throw "IterableAdapter::End is not implemented for this type";
		}

		public:
		consteval static inline auto ConstEnd( const TCollection& collection )
		{
			throw "IterableAdapter::ConstEnd is not implemented for this type";
		}
	};
	
	template<typename TExpected, typename TActual>
	class DLLApi CountAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Count( const TActual& instance )
		{
			throw "CountAdapter::Count is not implemented for this type";
		}
	};

	template<typename T>
	class DLLApi SizeAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Size( const T& instance )
		{
			throw "SizeAdapter::Size is not implemented for this type";
		}
	};

	template<typename T>
	class DLLApi HashAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Hash( const T& instance )
		{
			throw "HashAdapter::Hash is not implemented for this type";
		}
	};

	template<typename TIterator>
	class DLLApi IteratorAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Move( TIterator& iterator )
		{
			throw "IteratorAdapter::Move is not implemented for this type";
		}

		public:
		consteval static inline auto Current( const TIterator& iterator )
		{
			throw"IteratorAdapter::Current is not implemented for this type";
		}
	};
}
