module;

#include <algorithm>

#include "../../Macros/Macros.h"

export module AtlasConverters;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasDefinitions;

export import :BoolConverter;
export import :Converter;
export import :DoubleConverter;
export import :FloatConverter;
export import :IntConverter;
export import :LongConverter;
export import :LongLongConverter;
export import :StringConverter;
export import :UnsignedIntConverter;
export import :UnsignedLongConverter;
export import :UnsignedLongLongConverter;

export namespace Atlas
{
	template<typename ConvertedType>
	class DLLApi Convert
	{
		using SimpleConvertedType = Deduce::SimpleType<ConvertedType>;

		public: template<typename SourceType, typename SimpleSourceType = Deduce::SimpleType<SourceType>>
		constexpr inline static ConvertedType From( const SimpleSourceType& data )
			noexcept( Converters::Converter<SimpleSourceType , SimpleConvertedType>::IsNoexcept )
		{
			return Converters::Converter<SimpleSourceType , SimpleConvertedType>::Convert( data );
		}

		public: template<typename SourceType, typename SimpleSourceType = Deduce::SimpleType<SourceType>>
			requires Concept::IsPointer<SourceType>
		constexpr inline static ConvertedType From( const SimpleSourceType data )
			noexcept( Converters::Converter<SimpleSourceType , SimpleConvertedType>::IsNoexcept )
		{
			return Converters::Converter<SimpleSourceType , SimpleConvertedType>::Convert( data );
		}
	};
}