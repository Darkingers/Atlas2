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
		private: using Iterator = Deduce::ConstBeginTIterator<DerivedType>;
		private: using ComparatorType = Definition::Comparator<DataType>;


		public:
		constexpr DataType Maximum( const ComparatorType& comparator = Default::Comparator ) const final
		{
			return Analysis::Maximum( This() , comparator );
		}
		public:
		constexpr DataType Maximum( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType& comparator = Default::Comparator ) const final
		{
			return Analysis::Maximum( This(), inclusiveStart , exclusiveEnd , comparator );
		}

		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr ConvertResultType Maximum( const ConverterType& converter , const ComparatorType& comparator = Default::Comparator ) const
		{
			return Analysis::Maximum( This(), converter , comparator );
		}
		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr ConvertResultType Maximum( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::Maximum( This(), inclusiveStart , exclusiveEnd , converter , comparator );
		}

		public:
		constexpr Iterator MaximumBy( const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MaximumBy( This(), comparator );
		}
		public:
		constexpr Iterator MaximumBy( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType comparator = Default::Comparator )const
		{
			return Analysis::MaximumBy( This(), inclusiveStart , exclusiveEnd , comparator );
		}

		public: template<typename ConverterType>
		constexpr Iterator MaximumBy( const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MaximumBy( This(), converter , comparator );
		}	
		public: template<typename ConverterType>
		constexpr Iterator MaximumBy( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MaximumBy( This(), inclusiveStart , exclusiveEnd , converter , comparator );
		}

		public:
		constexpr DataType Minimumn( ComparatorType& comparator = Default::Comparator )const final
		{
			return Analysis::Minimumn( This(), comparator );
		}
		public:
		constexpr DataType Minimumn( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType& comparator = Default::Comparator )const final
		{
			return Analysis::Minimumn( This(), inclusiveStart , exclusiveEnd , comparator );
		}

		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr ConvertResultType Minimumn( const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::Minimumn( This(), converter , comparator );
		}	
		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr ConvertResultType Minimumn( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::Minimumn( This(), inclusiveStart , exclusiveEnd , converter , comparator );
		}

		public:
		constexpr Iterator MinimumBy( const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MinimumBy( This(), comparator );
		}	
		public:
		constexpr Iterator MinimumBy( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MinimumBy( This(), inclusiveStart , exclusiveEnd , comparator );
		}

		public: template<typename ConverterType>
		constexpr Iterator MinimumBy( const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MinimumBy( This(), converter , comparator );
		}	
		public: template<typename ConverterType>
		constexpr Iterator MinimumBy( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ConverterType& converter , const ComparatorType& comparator = Default::Comparator )const
		{
			return Analysis::MinimumBy( This(), inclusiveStart , exclusiveEnd , converter , comparator );
		}

		public: 
		constexpr DataType Sum()const final
		{
			return Analysis::Sum( This() );
		}	
		public:
		constexpr DataType Sum( const unsigned int inclusiveStart , const unsigned int exclusiveEnd )const final
		{
			return Analysis::Sum( This(), inclusiveStart , exclusiveEnd );
		}

		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr ConvertResultType Sum( const ConverterType& converter )const
		{
			return Analysis::Sum( This(), converter );
		}	
		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr ConvertResultType Sum( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ConverterType& converter )const
		{
			return Analysis::Sum( This(), inclusiveStart , exclusiveEnd , converter );
		}

		public: 
		constexpr DataType Average( )const final
		{
			return Analysis::Average( This() );
		}	
		public:
		constexpr DataType Average( const unsigned int inclusiveStart , const unsigned int exclusiveEnd )const final
		{
			return Analysis::Average( This(), inclusiveStart , exclusiveEnd );
		}

		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr ConvertResultType Average( const ConverterType& converter )const
		{
			return Analysis::Average( This(), converter );
		}		
		public: template<typename ConverterType , typename ConvertResultType = Deduce::ReturnType<ConverterType , DataType>>
		constexpr ConvertResultType Average( const unsigned int inclusiveStart , const unsigned int exclusiveEnd , const ConverterType& converter )const
		{
			return Analysis::Average( This(), inclusiveStart , exclusiveEnd , converter );
		}

		private:
		constexpr inline const DerivedType& This( ) const
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}