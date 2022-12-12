module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:ConverterAPI;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	/// <summary>
	/// An API that calls the appropriate converter between types
	/// </summary>
	template<typename TTarget>
	class DLLApi Convert
	{
		
	public:
		
		/// <summary>
		/// Convert the given value to the target type
		/// </summary>
		template<typename TSource>
		constexpr static inline TTarget From( const TSource& data )
			noexcept( Concept::IsNoexceptConvertable<const TSource& , TTarget> )
		{
			return Converter<const TSource&, TTarget>::Convert( data );
		}

		 /// <summary>
		/// Convert the given value to the target type
		/// </summary>
		template<typename TSource>
			requires Concept::IsFundamental<TSource>
		constexpr static inline TTarget From( TSource data )
			noexcept( Concept::IsNoexceptConvertable<TSource , TTarget> )
		{
			return Converter<TSource, TTarget>::Convert( data );
		}
	};
}