module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:AdapterDefinitions;

export namespace Atlas
{
	template<typename ClearedType>
	class DLLApi ClearAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Clear( ClearedType& instance )
		{
			throw "ClearAdapter::Clear is not implemented for this type";
		}
	};

	template<typename CollectionType , typename ElementType>
	class DLLApi ContainAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Contain( const CollectionType& collection , const ElementType& element )
		{
			throw "ContainAdapter::Contain is not implemented for this type";
		}
	};

	template<typename CollectionType , typename ContainedCollectionType>
	class DLLApi ContainAllAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto ContainAll( const CollectionType& collection , const ContainedCollectionType& containedCollection )
		{
			throw "ContainAllAdapter::ContainAll is not implemented for these types";
		}
	};

	template<typename ExpectedType, typename ActualType>
	class DLLApi CountAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Count( const ActualType& instance )
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

	template<typename HashableType>
	class DLLApi HashAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Hash( const HashableType& instance )
		{
			throw "HashAdapter::Hash is not implemented for this type";
		}
	};

	template<typename CollectionType>
	class DLLApi IterableAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Begin( CollectionType& collection )
		{
			throw "IterableAdapter::Begin is not implemented for this type";
		}
		
		public:
		consteval static inline auto ConstBegin( const CollectionType& collection )
		{
			throw "IterableAdapter::ConstBegin is not implemented for this type";
		}

		public:
		consteval static inline auto End( CollectionType& collection )
		{
			throw "IterableAdapter::End is not implemented for this type";
		}

		public:
		consteval static inline auto ConstEnd( const CollectionType& collection )
		{
			throw "IterableAdapter::ConstEnd is not implemented for this type";
		}
	};

	template<typename IteratorType>
	class DLLApi IteratorAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Move( IteratorType& iterator )
		{
			throw "IteratorAdapter::Move is not implemented for this type";
		}

		public:
		consteval static inline auto Current( const IteratorType& iterator )
		{
			throw"IteratorAdapter::Current is not implemented for this type";
		}
	};
}
