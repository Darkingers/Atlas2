module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:TypeAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi TypeAPI
	{		
		public: template<typename T>
		constexpr static inline auto Size( const T& data )
			noexcept ( Concept::IsNoexceptSize<T> )
		{
			return SizeAdapter<Deduce::SimpleType<T>>::Size( data );
		}

		public: template<typename T>
		constexpr static inline void GetHash( const T& data )
			noexcept ( Concept::IsNoexceptHash<T> )
		{
			return HashAdapter<Deduce::SimpleType<T>>::GetHash( data );
		}
	};
}
