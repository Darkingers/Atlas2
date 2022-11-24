module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:ConverterDefinitions;

export namespace Atlas
{
	template<typename SourceType , typename TargetType>
	class DLLApi Converter :
		public std::false_type
	{
		public: 
		consteval static inline TargetType Convert( const SourceType& data )
		{
			throw "No converter defined for this type combination.";
		}
	};
}
