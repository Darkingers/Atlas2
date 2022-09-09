module;

#include "../../../../Macros/Macros.h"

export module AtlasCollectionTraits:Analysable;
import AtlasDefinitions;
import AtlasInterfaces;
import AtlasDefaultFunctions;
import AtlasAnalysisFunctions;

export namespace Atlas::Trait
{
	template<typename DerivedType>
	class DLLApi Analysable:
		public Interface::IAnalysable<Deduce::CollectionContainedType<DerivedType>>
	{
		private: using DataType = Deduce::CollectionContainedType<DerivedType>;
		private: using Iterator = Deduce::ConstBeginIteratorType<DerivedType>;
		private: using ComparatorType = Definition::Comparator<DataType>;


		public:
		DataType Maximum( const ComparatorType& comparator = Default::Comparator ) const final
		{
			return Analysis::Maximum( This() , comparator );
		}
		
		public:
		DataType Maximum( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator = Default::Comparator ) const final
		{
			return Analysis::Maximum( This(), inclusiveFrom , exclusiveTo , comparator );
		}

		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		ConvertResultType Maximum( const ConverterType& converter , const ComparatorType& comparator = Default::Comparator ) const
		{
			return Analysis::Maximum( This(), converter , comparator );
		}
		
		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		ConvertResultType Maximum( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::Maximum( This(), inclusiveFrom , exclusiveTo , converter , comparator );
		}

		public:
		Iterator MaximumBy( const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MaximumBy( This(), comparator );
		}
		
		public:
		Iterator MaximumBy( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType comparator = Default::Comparator )const
		{
			return Analysis::MaximumBy( This(), inclusiveFrom , exclusiveTo , comparator );
		}

		public: template<typename ConverterType>
		Iterator MaximumBy( const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MaximumBy( This(), converter , comparator );
		}
		
		public: template<typename ConverterType>
		Iterator MaximumBy( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MaximumBy( This(), inclusiveFrom , exclusiveTo , converter , comparator );
		}

		public:
		DataType Minimumn( ComparatorType& comparator = Default::Comparator )const final
		{
			return Analysis::Minimumn( This(), comparator );
		}
		
		public:
		DataType Minimumn( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator = Default::Comparator )const final
		{
			return Analysis::Minimumn( This(), inclusiveFrom , exclusiveTo , comparator );
		}

		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		ConvertResultType Minimumn( const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::Minimumn( This(), converter , comparator );
		}
		
		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		ConvertResultType Minimumn( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::Minimumn( This(), inclusiveFrom , exclusiveTo , converter , comparator );
		}

		public:
		Iterator MinimumBy( const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MinimumBy( This(), comparator );
		}
		
		public:
		Iterator MinimumBy( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MinimumBy( This(), inclusiveFrom , exclusiveTo , comparator );
		}

		public: template<typename ConverterType>
		Iterator MinimumBy( const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MinimumBy( This(), converter , comparator );
		}
		
		public: template<typename ConverterType>
		Iterator MinimumBy( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MinimumBy( This(), inclusiveFrom , exclusiveTo , converter , comparator );
		}

		public: 
		DataType Sum()const final
		{
			return Analysis::Sum( This() );
		}
		
		public:
		DataType Sum( const unsigned int inclusiveFrom , const unsigned int exclusiveTo )const final
		{
			return Analysis::Sum( This(), inclusiveFrom , exclusiveTo );
		}

		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		ConvertResultType Sum( const ConverterType& converter )const
		{
			return Analysis::Sum( This(), converter );
		}
		
		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		ConvertResultType Sum( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter )const
		{
			return Analysis::Sum( This(), inclusiveFrom , exclusiveTo , converter );
		}

		public: 
		DataType Average( )const final
		{
			return Analysis::Average( This() );
		}
		
		public:
		DataType Average( const unsigned int inclusiveFrom , const unsigned int exclusiveTo )const final
		{
			return Analysis::Average( This(), inclusiveFrom , exclusiveTo );
		}

		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		ConvertResultType Average( const ConverterType& converter )const
		{
			return Analysis::Average( This(), converter );
		}
		
		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		ConvertResultType Average( const unsigned int inclusiveFrom , const unsigned int exclusiveTo , const ConverterType& converter )const
		{
			return Analysis::Average( This(), inclusiveFrom , exclusiveTo , converter );
		}

		private:
		inline const DerivedType& This( ) const
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}