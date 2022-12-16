module;

#include "../../../../../Macros/Macros.h"

export module AtlasDefinitions:TypeAdapters;

export namespace Atlas
{
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
