module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:DataAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	/// <summary>
	/// Calls the appropriate adapter for given objects
	/// </summary>
	class DLLApi DataAPI
	{
		/// <summary>
		/// Returns the size of the given object in bytes
		/// </summary>
		public: template<typename TTarget , typename... TSource>
			constexpr static inline auto Copy( const TTarget& target , const TSource&... source )
			noexcept ( Concept::IsNoexceptSize<T> )
		{
			return 
		}
	};
}
