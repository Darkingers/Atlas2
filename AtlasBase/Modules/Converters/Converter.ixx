module;

#include "../../../Macros/Macros.h"

export module AtlasConverters:Converter;

export namespace Atlas::Converters
{
	template<typename SourceType, typename TargetType>
	class DLLApi Converter :
		public std::false_type
	{
		public: constexpr static bool IsNoexcept = false;

		public: TargetType Convert( const SourceType& data ) = delete;
	};
}

export namespace Atlas::Concept
{
	template<typename SourceType , typename TargetType>
	concept HasConverter = Atlas::Converters::Converter<SourceType, TargetType>::value;
}