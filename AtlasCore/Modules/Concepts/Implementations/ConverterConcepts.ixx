module;

#include "../../../../Macros/Macros.h"

export module AtlasConcepts:ConverterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concepts
{
	template<typename SourceType , typename TargetType>
	concept IsNoexceptConvertable = noexcept( Converter<Deduce::SimpleType<SourceType> , Deduce::SimpleType<TargetType>>::Convert( std::declval<SourceType>( ) ) );

	template <typename SourceType , typename TargetType>
	concept HasConverter = Converter<Deduce::SimpleType<SourceType> , Deduce::SimpleType<TargetType>>::value
}
