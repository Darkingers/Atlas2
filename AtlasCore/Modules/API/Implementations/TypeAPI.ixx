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
		constexpr static inline auto Size(const T& data)
		{
			return SizeAdapter<const T&>::Size( data );
		}

		template<typename T> requires
			Concept::IsFundamental<T>
		constexpr static inline auto Size(T data)
		{
			return SizeAdapter<T>::Size( data );
		}

		template<typename T>requires
			Concept::IsFundamental<T>
		constexpr static inline unsigned int GetHash(T data )
		{
			return HashAdapter<T>::Hash( data );
		}
	};
}
