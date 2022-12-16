module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:ConverterDefinitions;

export namespace Atlas
{
	template<typename TSource , typename TTarget>
	class DLLApi TypeConverter :
		public std::false_type
	{
		
	public: 
		
		consteval static inline TTarget Convert( TSource data )
		{
			throw "No converter defined for this type combination.";
		}
	};
}
