module;

#include <algorithm>

#include "../../../Macros/Macros.h"

export module AtlasConverters:Convert;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasDefinitions;
import :Converter;

export namespace Atlas
{
	template<typename ConvertedType>
	class DLLApi Convert
	{
		using SimpleConvertedType = Deduce::SimpleType<ConvertedType>;

		public: template<typename SourceType>
			constexpr inline static ConvertedType From( const SourceType& data )
			noexcept( noexcept( Converters::Converter<Deduce::SimpleType<SourceType> , SimpleConvertedType>::Convert( SourceType( ) ) ) )
		{
			return Converters::Converter<Deduce::SimpleType<SourceType> , SimpleConvertedType>::Convert( data );
		}

		public: template<typename SourceType>
			requires Concept::IsPointer<SourceType>
			  constexpr inline static ConvertedType From( const SourceType data )
				  noexcept( noexcept( Converters::Converter<Deduce::SimpleType<SourceType> , SimpleConvertedType>::Convert( SourceType( ) ) ) )
		{
			return Converters::Converter<Deduce::SimpleType<SourceType> , SimpleConvertedType>::Convert( data );
		}
	};
}