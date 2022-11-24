module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:IAnalysable;
import AtlasDefinitions;
import AtlasDefaultFunctions;

export namespace Atlas::Interface
{
	template<typename DataType>
	class DLLApi IAnalysable
	{
		private: using ComparatorType = Definition::Comparator<DataType>;

		public: 
		virtual DataType Maximum( const ComparatorType comparator = Default::Comparator ) const = 0;
		public:
		virtual DataType Maximum( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType comparator = Default::Comparator )const = 0;

		public: 
		virtual DataType Minimumn( const ComparatorType comparator = Default::Comparator )const = 0;
		public:
		virtual DataType Minimumn( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType comparator = Default::Comparator ) const = 0;
	
		public:
		virtual DataType Sum( ) const = 0;
		public:
		virtual DataType Sum( const unsigned int inclusiveStart , const unsigned int exclusiveEnd )const = 0;

		public:
		virtual DataType Average( )const = 0;
		public: 
		virtual DataType Average( const unsigned int inclusiveStart , const unsigned int exclusiveEnd )const = 0;
	};
}