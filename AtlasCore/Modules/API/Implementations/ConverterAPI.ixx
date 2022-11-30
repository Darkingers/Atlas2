module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:ConverterAPI;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	template<typename TTarget>
	class DLLApi Convert
	{
		public: template<typename TSource>
		constexpr static inline TTarget From( const TSource& data )
			noexcept( Concept::IsNoexceptConvertable<TSource , TTarget> )
		{
			return Converter<Deduce::SimpleType<TSource> , Deduce::SimpleType<TTarget>>::Convert( data );
		}

		public: template<typename TSource>
			requires Concept::IsPointer<TSource>
		constexpr static inline TTarget From( const TSource data )
			noexcept( Concept::IsNoexceptConvertable<TSource,TTarget> )
		{
			return Converter<Deduce::SimpleType<TSource> , Deduce::SimpleType<TTarget>>::Convert( data );
		}
	};
}