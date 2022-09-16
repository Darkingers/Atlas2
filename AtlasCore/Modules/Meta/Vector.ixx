module;

#include "../../../Macros/Macros.h"
#include <vector>

export module AtlasMeta:Vector;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas::Meta
{
	class DLLApi Vector
	{
		public: template<typename DataType>
		static void Remove( std::vector<DataType>& vector , const DataType& element )
		{
			const auto end = std::cend( vector );
			auto begin = std::begin( vector );
			
			auto iterator = std::find( begin , end , element );
			if ( iterator != end )
			{
				vector.erase( iterator );
			}
		}

		public: template<typename DataType>
		static void RemoveIf( std::vector<DataType>& vector , Definition::Condition<const DataType&> condition )
		{
			const auto end = std::cend( vector );
			auto begin = std::begin( vector );

			auto iterator = std::find_if( begin , end , condition );
			if ( iterator != end )
			{
				vector.erase( iterator );
			}
		}

		public: template<typename DataType>
		static auto FindIterator( std::vector<DataType>& vector , const DataType& element )
		{
			return std::find( std::begin( vector ) , std::cend( vector ) , element );
		}
	};
}
