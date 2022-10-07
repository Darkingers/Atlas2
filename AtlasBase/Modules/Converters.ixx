module;

#include "../../Macros/Macros.h"
#include <algorithm>

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

export namespace Atlas
{
	template<typename ConvertedType>
	class DLLApi Convert
	{
		public: template<typename TargetType>
		inline static TargetType To( const ConvertedType& data )
		{
			return Converters::Converter<Simplify<ConvertedType> , Simplify<TargetType>>::Convert( data );
		}

		public: template<typename TargetType>
			requires Concept::IsPointer<ConvertedType>
		inline static TargetType To( const ConvertedType data )
		{
			return Converters::Converter<Simplify<ConvertedType> , Simplify<TargetType>>::Convert( data );
		}

		public: template<typename SourceType>
		inline static ConvertedType From( const SourceType& data )
		{
			return Converters::Converter<Simplify<SourceType> , Simplify<ConvertedType>>::Convert( data );
		}

		public: template<typename SourceType>
			requires Concept::IsPointer<SourceType>
		inline static ConvertedType From( const SourceType data )
		{
			return Converters::Converter<Simplify<SourceType> , Simplify<ConvertedType>>::Convert( data );
		}
	};
}