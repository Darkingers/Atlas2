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

	template<typename TCollection>
	class DLLApi IterableAdapter :
		public std::false_type
	{
		public:
		consteval static inline auto Begin( TCollection collection )
		{
			throw "IterableAdapter::Begin is not implemented for this type";
		}

		public:
		consteval static inline auto ConstBegin( TCollection collection )
		{
			throw "IterableAdapter::ConstBegin is not implemented for this type";
		}

		public:
		consteval static inline auto End( TCollection collection )
		{
			throw "IterableAdapter::End is not implemented for this type";
		}

		public:
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

		public:
		consteval static inline auto Current( TIterator iterator )
		{
			throw"IteratorAdapter::Current is not implemented for this type";
		}
	};

	template<typename TTarget , typename TSource>
	class DLLApi CopyAdapter:
		public std::false_type
	{
		public:
		consteval static inline void Copy( TTarget target , TSource source )
		{
			throw "CopyAdapter::Copy is not implemented for this type";
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
}
