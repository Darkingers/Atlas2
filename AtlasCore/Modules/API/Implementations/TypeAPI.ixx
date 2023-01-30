module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:TypeAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi TypeAPI
	{		

	public:
		
		template<typename T>
		constexpr static inline auto Size(
				const T& data
			)
			noexcept ( Concept::IsNoexceptSize<T> )
		{
			return SizeAdapter<const T&>::Size( data );
		}

		template<typename T> requires
			Concept::IsFundamental<T>
		constexpr static inline auto Size(
				T data
			)
			noexcept ( Concept::IsNoexceptSize<T> )
		{
			return SizeAdapter<T>::Size( data );
		}

		template<typename T>requires
			Concept::IsFundamental<T>
		constexpr static inline unsigned int GetHash(
				T data 
			)
			noexcept ( Concept::IsNoexceptHash<T> )
		{
			return HashAdapter<T>::Hash( data );
		}
	};
}
