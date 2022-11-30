module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:IteratorAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi IteratorAPI
	{
		public: template<typename TIterator>
		constexpr static inline auto Current( const TIterator& iterator )
			noexcept ( Concept::IsNoexceptCurrent<TIterator> )
		{
			return IteratorAdapter<Deduce::SimpleType<TIterator>>::Current( iterator );
		}

		public: template<typename TIterator>
		constexpr static inline bool Move( TIterator& iterator , int step = 1 )
			noexcept ( Concept::IsNoexceptMove<TIterator> )
		{
			return IteratorAdapter<Deduce::SimpleType<TIterator>>::Move( iterator , step );
		}
	};
}
