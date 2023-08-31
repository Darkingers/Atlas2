module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:HashAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename T> requires
		Concept::IsHashable<T>
	class DLLApi HashAdapter<T> :
		public std::true_type
	{
		
	public:

		constexpr static inline auto Hash( T instance )
		{
			return instance.GetHash( );
		}
	};

	template<typename T> requires
		Concept::Standard::IsHashable<T>
	class DLLApi HashAdapter<T> :
		public std::true_type
	{
	
	private:
		
		static std::hash<T> _hash;

	public:

		constexpr static inline auto Hash( T instance )
		{
			return _hash( instance );
		}
	};
}