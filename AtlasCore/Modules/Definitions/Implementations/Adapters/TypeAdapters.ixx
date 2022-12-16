module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:TypeAdapters;

export namespace Atlas
{
	//The following text block is a code-generation helper.
	// SizeAdapter<T>-auto Size(T)
	// HashAdapter<T>-auto Hash(T)
	
	template<typename T>
	class DLLApi SizeAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Size( T instance )
		{
			throw "SizeAdapter::Size is not implemented for this type";
		}
	};

	template<typename T>
	class DLLApi HashAdapter :
		public std::false_type
	{

	public:

		consteval static inline auto Hash( T instance )
		{
			throw "HashAdapter::Hash is not implemented for this type";
		}
	};
}
