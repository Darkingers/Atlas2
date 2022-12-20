module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:ManipulationConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{

	template<typename TCollection>
	concept HasClearFunction = requires ( TCollection instance )
	{
		instance.Clear( );
	};

	template<typename TCollection>
	concept IsNoexceptClear = noexcept( ClearAdapter<TCollection>::Clear( std::declval<TCollection>( ) ) );
	
	template<typename... TArgs>
	concept IsNoexceptReplaceFrom = noexcept( ReplaceFromAdapter<TArgs...>::ReplaceFrom(  std::declval<TArgs>( )... ) );

	template<typename... TArgs>
	concept IsNoexceptCopy = noexcept( CopyAdapter<TArgs...>::Copy( std::declval<TArgs>( )... ) );
	
	template<typename... TArgs>
	concept IsNoexceptShift = noexcept ( ShiftAdapter<TArgs...>::Shift( std::declval<TArgs>( )...) );

	template<typename TCollection>
	concept IsNoexceptResize = noexcept ( ResizeAdapter<TCollection>::Resize( std::declval<TCollection>( ) , std::declval<unsigned int>( ) ) );
}
