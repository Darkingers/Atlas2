module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:ClearAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection> requires 
		Concept::HasClearFunction<TCollection>
	class DLLApi ClearAdapter<TCollection> :
		public std::true_type
	{

	public:

		constexpr static inline void Clear( TCollection collection )
			noexcept( noexcept( collection.Clear( ) ) )
		{
			collection.Clear( );
		}
	};

	template<typename TCollection> requires
		Concept::Standard::HasClearFunction<TCollection>
	class DLLApi ClearAdapter<TCollection> :
		public std::true_type
	{

	public:

		constexpr static inline void Clear( TCollection collection )
			noexcept( noexcept( collection.clear( ) ) )
		{
			collection.clear( );
		}
	};
}