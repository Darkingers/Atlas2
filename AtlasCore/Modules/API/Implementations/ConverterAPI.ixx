module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:ConverterAPI;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	template<typename TTarget>
	class DLLApi ConvertAPI
	{
		
	public:
		
		template<typename TSource>
		constexpr static inline TTarget From
			( 
				const TSource& data 
			) 
			noexcept( Concept::IsNoexceptConvertable<const TSource& , TTarget> )
		{
			return TypeConverter<const TSource&, TTarget>::Convert( data );
		}

		template<typename TSource> requires 
			Concept::IsFundamental<TSource>
		constexpr static inline TTarget From
			(
				TSource data
			)
			noexcept( Concept::IsNoexceptConvertable<TSource , TTarget> )
		{
			return TypeConverter<TSource, TTarget>::Convert( data );
		}
	};
}