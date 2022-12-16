module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:TypeConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename T>
	concept IsNoexceptSize = noexcept( SizeAdapter<T>::Size( std::declval<T>( ) ) );

	template<typename T>
	concept IsNoexceptHash = noexcept( HashAdapter<T>::Hash( std::declval<T>( ) ) );
}
