module;

#include "../../../../Macros/Macros.h"

export module AtlasIntegration:Converter;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	template<typename TargetType>
	class DLLApi Convert
	{
		public: template<typename SourceType>
		constexpr static inline TargetType From( const SourceType& data )
			noexcept( Concept::IsNoexceptConvertable<SourceType , TargetType> )
		{
			return Converter<Deduce::SimpleType<SourceType> , Deduce::SimpleType<TargetType>>::Convert( data );
		}

		public: template<typename SourceType>
			requires Concept::IsPointer<SourceType>
		constexpr static inline TargetType From( const SourceType data )
			noexcept( Concept::IsNoexceptConvertable<SourceType,TargetType> )
		{
			return Converter<Deduce::SimpleType<SourceType> , Deduce::SimpleType<TargetType>>::Convert( data );
		}
	};
}