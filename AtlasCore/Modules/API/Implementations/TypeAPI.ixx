module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:TypeAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	/// <summary>
	/// Calls the appropriate adapter for given objects
	/// </summary>
	class DLLApi TypeAPI
	{		
		/// <summary>
		/// Returns the size of the given object in bytes
		/// </summary>
		public: template<typename T>
		constexpr static inline auto Size( const T& data )
			noexcept ( Concept::IsNoexceptSize<T> )
		{
			return SizeAdapter<Deduce::SimpleType<T>>::Size( data );
		}

		/// <summary>
		/// Returns the hash of the given object
		/// </summary>
		public: template<typename T>
		constexpr static inline unsigned int GetHash( const T& data )
			noexcept ( Concept::IsNoexceptHash<T> )
		{
			return HashAdapter<Deduce::SimpleType<T>>::GetHash( data );
		}
	};
}
