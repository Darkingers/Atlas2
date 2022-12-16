module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:QueryConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename TCollection , typename TElement>
	concept HasContainFunction = requires ( const TCollection collection , const TElement element )
	{
		{
			collection.Contains( element )
		}->std::convertible_to<bool>;
	};

	template<typename TCollection , typename TElement>
	concept HasCountFunction = requires ( const TCollection collection , const TElement element )
	{
		{
			collection.Count( element )
		}->std::convertible_to<unsigned int>;
	};

	template<typename TCollection>
	concept HasLength = requires ( const TCollection collection )
	{
		{
			collection.Length()
		}->std::convertible_to<unsigned int>;
	};

	template<typename TA, typename TB>
	concept HasMatch = requires ( const TA a , const TB b , const unsigned int step )
	{
		{
			a.Match( b , step )
		}->std::convertible_to<bool>;
	};

	template<typename TCollection , typename TPattern>
	concept HasContainPattern = requires ( const TCollection collection , const TPattern pattern )
	{
		{
			collection.Contains( pattern )
		}->std::convertible_to<bool>;
	};

	template<typename TCollection , typename TElement>
	concept IsNoexceptContain = noexcept( ContainAdapter<TCollection , TElement>::Contain( std::declval<TCollection>( ) , std::declval<TElement>( ) ) );

	template<typename TExpected , typename TActual>
	concept IsNoexceptCountType = noexcept( CountTypeAdapter<TExpected , TActual>::Count( std::declval<TActual>( ) ) );

	template<typename TCollection , typename TElement>
	concept IsNoexceptCountElement = noexcept( CountElementAdapter<TCollection , TElement>::Count( std::declval<TCollection>( ) , std::declval<TElement>( ) ) );

	template<typename TA , typename TB>
	concept IsNoexceptMatch = noexcept( MatchAdapter<TA , TB>::Match( std::declval<TA>( ) , std::declval<TB>( ) , std::declval<unsigned int>( ) ) );

	template<typename TCollection , typename TPattern>
	concept IsNoexceptContainPattern = noexcept( ContainPatternAdapter<TCollection , TPattern>::Contain( std::declval<TCollection>( ) , std::declval<TPattern>( ), std::declval<unsigned int>( ) ) );

	template<typename TCollection, typename TPredicate>
	concept IsNoexceptAny = noexcept( AnyAdapter<TCollection , TPredicate>::Any( std::declval<TCollection>( ) , std::declval<TPredicate>( ) ) );

	template<typename TCollection , typename TPredicate>
	concept IsNoexceptAll = noexcept( AllAdapter<TCollection , TPredicate>::All( std::declval<TCollection>( ) , std::declval<TPredicate>( ) ) );
}
