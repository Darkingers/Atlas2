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
		constexpr static inline auto Clear( ClearedType& instance )
		{
			static_assert( false , "ClearAdapter::Clear is not implemented for this type" );
		}
	};

	template<typename CollectionType , typename ElementType>
	class DLLApi ContainAdapter :
		public std::false_type
	{
		public:
		constexpr static inline auto Contain( const CollectionType& collection , const ElementType& element )
		{
			static_assert( false , "ContainAdapter::Contain is not implemented for this type" );
		}
	};

	template<typename CollectionType , typename ContainedCollectionType>
	class DLLApi ContainAllAdapter :
		public std::false_type
	{
		public:
		constexpr static inline auto ContainAll( const CollectionType& collection , const ContainedCollectionType& containedCollection )
		{
			static_assert( false , "ContainAllAdapter::ContainAll is not implemented for these types" );
		}
	};

	template<typename T>
	class DLLApi SizeAdapter :
		public std::true_type
	{
		public:
		constexpr static inline auto Size( const T& instance ) noexcept
		{
			static_assert( false , "SizeAdapter::Size is not implemented for this type" );
		}
	};

	template<typename HashableType>
	class DLLApi HashAdapter :
		public std::false_type
	{
		public:
		constexpr static inline auto Hash( const HashableType& instance ) noexcept
		{
			static_assert( false , "HashAdapter::Hash is not implemented for this type" );
		}
	};

	template<typename CollectionType>
	class DLLApi IterableAdapter :
		public std::false_type
	{
		public:
		constexpr static inline auto Begin( CollectionType& collection )
		{
			static_assert( false , "IterableAdapter::Begin is not implemented for this type" );
		}
		
		public:
		constexpr static inline auto ConstBegin( const CollectionType& collection )
		{
			static_assert( false , "IterableAdapter::ConstBegin is not implemented for this type" );
		}

		public:
		constexpr static inline auto End( CollectionType& collection )
		{
			static_assert( false , "IterableAdapter::End is not implemented for this type" );
		}

		public:
		constexpr static inline auto ConstEnd( const CollectionType& collection )
		{
			static_assert( false , "IterableAdapter::ConstEnd is not implemented for this type" );
		}
	};

	template<typename IteratorType>
	class DLLApi IteratorAdapter :
		public std::false_type
	{
		public:
		constexpr static inline auto Move( IteratorType& iterator )
		{
			static_assert( false , "IteratorAdapter::Move is not implemented for this type" );
		}

		public:
		constexpr static inline auto Current( const IteratorType& iterator )
		{
			static_assert( false , "IteratorAdapter::Current is not implemented for this type" );
		}
	};
}
