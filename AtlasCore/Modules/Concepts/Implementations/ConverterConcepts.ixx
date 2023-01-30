module;

#include "../../../../Macros/Macros.h"

export module AtlasConcepts:ConverterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename TSource , typename TTarget>
	concept IsConvertible = Converter<Deduce::SimpleType<TSource> , Deduce::SimpleType<TTarget>>::value;

	template<typename TSource , typename TTarget>
	concept IsNoexceptConvertable = noexcept( Converter<Deduce::SimpleType<TSource> , Deduce::SimpleType<TTarget>>::Convert( std::declval<TSource>( ) ) );

	template <typename TSource , typename TTarget>
	concept HasConverter = Converter<Deduce::SimpleType<TSource> , Deduce::SimpleType<TTarget>>::value;
}
