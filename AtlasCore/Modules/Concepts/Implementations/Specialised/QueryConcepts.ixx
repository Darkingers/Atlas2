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
	
	template<typename TExpected , typename TActual>
	concept IsNoexceptCountType = noexcept( CountTypeAdapter<TExpected , TActual>::Count( std::declval<TActual>( ) ) );
	
	template<typename TCollection>
	concept IsNoexceptLength = noexcept( LengthAdapter<TCollection>::Contain( std::declval<TCollection>( ) ) );

	template<typename... TArgs>
	concept IsNoexceptContain = noexcept( ContainAdapter<TArgs...>::Contain( std::declval<TArgs>()...) );
	
	template<typename... TArgs>
	concept IsNoexceptCountElement = noexcept( CountElementAdapter<TArgs...>::Count( std::declval<TArgs>( )... ) );

	template<typename... TArgs>
	concept IsNoexceptMatch = noexcept( MatchAdapter<TArgs...>::Match( std::declval<TArgs>( )... ) );

	template<typename... TArgs>
	concept IsNoexceptContainPattern = noexcept( ContainPatternAdapter<TArgs...>::ContainsPattern( std::declval<TArgs>( )... ) );

	template<typename... TArgs>
	concept IsNoexceptCountPattern = noexcept( CountPatternAdapter<TArgs...>::CountPattern( std::declval<TArgs>( )... ) );


	template<typename... TArgs>
	concept IsNoexceptAny = noexcept( AnyAdapter<TArgs...>::Any( std::declval<TArgs>( )... ) );

	template<typename... TArgs>
	concept IsNoexceptAll = noexcept( AllAdapter<TArgs...>::All( std::declval<TArgs>( )... ) );
}
