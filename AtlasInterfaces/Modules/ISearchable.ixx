module;

#include "../../Macros/Macros.h"

export module AtlasInterfaces:ISearchable;
import AtlasDefinitions;
import AtlasDefaultFunctions;

export namespace Atlas::Interface
{
	template<typename DataType>
	class DLLApi ISearchable
	{
		private: using ComparatorType = Definition::Comparator<DataType>;

		public:
		virtual const unsigned int BinarySearch( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType value , const ComparatorType comparator = Default::Comparator )const  = 0;
		public:
		virtual const unsigned int BinarySearch( const DataType value , const ComparatorType comparator = Default::Comparator )const  = 0;

		public:
		virtual const unsigned int LinearSearch( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType value , const ComparatorType comparator )const  = 0;
		public:
		virtual const unsigned int LinearSearch( const DataType value , const ComparatorType comparator = Default::Comparator )const  = 0;

		public:
		virtual const unsigned int JumpSearch( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const DataType value , const ComparatorType comparator = Default::Comparator )const  = 0;
		public:
		virtual const unsigned int JumpSearch( const DataType value , const ComparatorType comparator = Default::Comparator )const  = 0;
	};
}