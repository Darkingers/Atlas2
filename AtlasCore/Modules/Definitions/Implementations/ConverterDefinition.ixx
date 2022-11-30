module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:ConverterDefinitions;

export namespace Atlas
{
	template<typename TSource , typename TTarget>
	class DLLApi Converter :
		public std::false_type
	{
		public: 
		consteval static inline TTarget Convert( const TSource& data )
		{
			throw "No converter defined for this type combination.";
		}
	};
}
