module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:QueryAdapterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	// Code generation helper:
	// Contain<TITerator,TEleemnt>-auto Contain(TIterator, const unsigned int, TElement)
	// Count<TExpected,TActual>-auto Count(TActual)
	// Match<TA,TB>-auto Match(TA, TB, const unsigned int)

	template<typename TITerator , typename TElement>
	concept IsNoexceptContain = noexcept( ContainAdapter<TITerator , TElement>::Contain( std::declval<TITerator>( ) , std::declval<TITerator>( ) , std::declval<TElement>( ) ) );

	template<typename TExpected , typename TActual>
	concept IsNoexceptCount = noexcept( CountAdapter<TExpected , TActual>::Count( std::declval<TActual>( ) ) );

	template<typename TA , typename TB>
	concept IsNoexceptMatch = noexcept( MatchAdapter<TA , TB>::Match( std::declval<TA>( ) , std::declval<TB>( ) , std::declval<unsigned int>( ) ) );
}
