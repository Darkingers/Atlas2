module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:IteratorConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{	
	template<typename TIterator, typename TElement>
	concept IsIteratorForType = requires( TIterator iterator )
	{
		IteratorMoveAdapter<TIterator>::Move( iterator );

		{
			IteratorCurrentAdapter<TIterator>::Current( iterator )
		} -> std::same_as<TElement>;
	};

	template<typename TIterator>
	concept IsIterator = IteratorTraits<TIterator>::value;

	template<typename TIterator>
	concept IsRandomAccessIterator = IsIterator<TIterator> && IteratorTraits<TIterator>::RandomAccess;

	template<typename TIterator>
	concept IsNoexceptMove = noexcept( IteratorMoveAdapter<TIterator>::Move( std::declval<TIterator>( ) , std::declval<int>( ) ) );

	template<typename TIterator>
	concept IsNoexceptCurrent = noexcept( IteratorCurrentAdapter<TIterator>::Current( std::declval<TIterator>( ) ) );

	template<typename TIterator>
	concept IsNoexceptIterator = IsNoexceptMove<TIterator> && IsNoexceptCurrent<TIterator>;

	template<typename TCollection>
	concept IsNoexceptAt = noexcept( IterableAdapter<TCollection>::At( std::declval<TCollection>( ) , std::declval<unsigned int>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstAt = noexcept( IterableAdapter<TCollection>::ConstAt( std::declval<TCollection>( ), std::declval<unsigned int>( ) ) );

	template<typename TCollection>
	concept IsNoexceptBegin = noexcept( IterableAdapter<TCollection>::Begin( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptEnd = noexcept( IterableAdapter<TCollection>::End( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstBegin = noexcept( IterableAdapter<TCollection>::ConstBegin( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstEnd = noexcept( IterableAdapter<TCollection>::ConstEnd( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept HasNoexceptIterator = IsNoexceptBegin<TCollection> && IsNoexceptEnd<TCollection> && IsNoexceptIterator<typename CollectionTraits<TCollection>::IteratorType>;

	template<typename TCollection>
	concept HasNoexceptConstIterator = IsNoexceptConstBegin<TCollection> && IsNoexceptConstEnd<TCollection> && IsNoexceptIterator<typename CollectionTraits<TCollection>::IteratorType>;

	template<typename TCollection>
	concept HasIterator = CollectionTraits<TCollection>::HasIterator;

	template<typename TCollection>
	concept IsIterable = requires ( TCollection collection )
	{
		collection.Begin( );
		collection.End( );
		collection.ConstBegin( );
		collection.ConstEnd( );
	};

	template<typename TCollection , typename TElement>
	concept IsIterableWith =
		CollectionTraits<TCollection>::HasIterator &&
		std::is_same_v<typename CollectionTraits<TCollection>::ElementType , TElement>;
		

	template<typename TIteratorA , typename TIteratorB>
	concept AreCompatibleIterators = 
		IsIterator<TIteratorA> &&
		IsIterator<TIteratorB> &&
		std::is_same_v<typename IteratorTraits<TIteratorA>::ElementType , typename IteratorTraits<TIteratorB>::ElementType>;

	template<typename TIterator , typename TCollection>
	concept IsCompatibleIteratorFor =
		IsIterator<TIterator>&& 
		std::is_same_v<typename IteratorTraits<TIterator>::CollectionType , TCollection>;
}
