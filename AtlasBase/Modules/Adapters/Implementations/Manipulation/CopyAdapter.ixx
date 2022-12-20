module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:CopyAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TIteratorSource , typename TIteratorTarget> requires
		Concept::IsIterator<TIteratorSource> &&
		Concept::IsIteratorForType<TIteratorTarget, typename IteratorTraits<TIteratorTarget>::IteratedType>
	class DLLApi CopyAdapter<TIteratorSource , TIteratorSource, TIteratorTarget> :
		public std::true_type
	{
	private:
		
		using ElementType = typename IteratorTraits<TIteratorSource>::IteratedType;
		
	public:

		constexpr static inline void Copy( TIteratorSource start , TIteratorSource end , TIteratorTarget target )
			noexcept
			( 
				Concept::IsNoexceptAssignable<ElementType , ElementType>&&
				Concept::IsNoexceptIterator<TIteratorSource>&& 
				Concept::IsNoexceptIterator<TIteratorTarget> 
			)
		{
			while ( start != end )
			{
				IteratorAPI::Current( target ) = IteratorAPI::Current( start );
				IteratorAPI::Next( start );
				IteratorAPI::Next( target );
			}
		}
	};
}