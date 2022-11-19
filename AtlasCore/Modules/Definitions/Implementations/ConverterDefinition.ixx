module;

#include "../../../../Macros/Macros.h"

export module AtlasDefinitions:ConverterDefinitions;

export namespace Atlas
{
	template<typename SourceType , typename TargetType>
	class DLLApi Converter :
		public std::false_type
	{
		public: 
		constexpr static inline TargetType Convert( const SourceType& data )
		{
			static_assert( false , "No converter defined for this type combination." );
		}
	};
}
