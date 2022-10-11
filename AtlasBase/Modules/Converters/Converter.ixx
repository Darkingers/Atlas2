module;

#include "../../../Macros/Macros.h"

export module AtlasConverters:Converter;

export namespace Atlas::Converters
{
	template<typename SourceType, typename TargetType>
	class DLLApi Converter :
		public std::false_type
	{
	};
}

export namespace Atlas::Concept
{
	template<typename SourceType , typename TargetType>
	concept HasConverter = Atlas::Converters::Converter<SourceType, TargetType>::value;
}