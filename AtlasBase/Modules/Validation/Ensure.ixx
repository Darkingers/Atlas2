module;

#include "../../../Macros/Macros.h"

export module AtlasValidation:Ensure;
import AtlasConfiguration;
import AtlasDefinitions;
import AtlasAdapters;
import AtlasExceptions;

export namespace Atlas
{
	class DLLApi Ensure 
	{
		public:
		constexpr inline static void IsTrue( const bool a )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( !a )
			{
				Throw<ValidationException>( "Condition: a==true is not fulfilled!", a );
			}
		}

		public:
		constexpr inline static void IsFalse( const bool a )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a )
			{
				Throw<ValidationException>( "Condition: a==false is not fulfilled!", a );
			}
		}

		public: template<typename DataType>
		constexpr inline static void IsNull( const DataType* pointer )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( pointer !=nullptr )
			{
				Throw<ValidationException>( "Condition: pointer==nullptr is not fulfilled!", pointer );
			}
		}

		public: template<typename DataType>
		constexpr inline static void IsNotNull( const DataType* pointer )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( pointer == nullptr )
			{
				Throw<ValidationException>( "Condition: pointer!=nullptr is not fulfilled!", pointer );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsSame( const TypeA& a, const TypeB& b)
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( !Adapter::Equals( a,b ) )
			{
				Throw<ValidationException>( "Condition: a==b is not fulfilled!", a, b );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsNotSame( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( Adapter::Equals( a , b ) )
			{
				Throw<ValidationException>( "Condition: a!=b is not fulfilled!" , a , b );
			}
		}

		public: template<typename DataType>
		constexpr inline static void IsPositive( const DataType& a)
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a <0 )
			{
				Throw<ValidationException>( "Condition: a>=b is not fulfilled!" , a );
			}
		}

		public: template<typename DataType>
		constexpr inline static void IsNegative( const DataType& a )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a>=0 )
			{
				Throw<ValidationException>( "Condition: a < 0 is not fulfilled!" , a );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsLess( const TypeA& a, const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a>=b)
			{
				Throw<ValidationException>( "Condition: a < b is not fulfilled!" , a, b );
			}
		}

		public: template<typename TypeA, typename TypeB>
		constexpr inline static void IsMore( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a <= b )
			{
				Throw<ValidationException>( "Condition: a > b is not fulfilled!" , a , b );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void PositiveRange( const TypeA& a, const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a<0 || b<0 || a>b )
			{
				Throw<ValidationException>( "Condition: a>=0 && b>=0 && a<=b is not fulfilled!" , a , b );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsLessOrEqual( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a > b )
			{
				Throw<ValidationException>( "Condition: a<=b is not fulfilled!" , a , b );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsMoreOrEqual( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a < b )
			{
				Throw<ValidationException>( "Condition: a>=b is not fulfilled!" , a , b );
			}
		}

		public: template<typename TypeA , typename TypeB, typename TypeC>
		constexpr inline static void IsInRange( const TypeA& number , const TypeB& inclusiveFrom, const TypeC& exclusiveTo )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( number < inclusiveFrom || number >= exclusiveTo )
			{
				Throw<ValidationException>( "Condition: number >= inclusiveFrom && number < exclusiveTo is not fulfilled!" , number, inclusiveFrom, exclusiveTo );
			}
		}

		public: template<typename CollectionType>
		constexpr inline static void IsEmpty( const CollectionType& collection )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			const auto collectionCount = Adapter::Count( collection );

			if ( collectionCount != 0 )
			{
				Throw<ValidationException>( "Condition: collection.Count==0 is not fulfilled!" , collection , collectionCount );
			}
		}

		public: template<typename CollectionType>
		constexpr inline static void IsNotEmpty( const CollectionType& collection )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			const auto collectionCount = Adapter::Count( collection );

			if ( collectionCount <= 0 )
			{
				Throw<ValidationException>( "Condition: collection.Count>0 is not fulfilled!" , collection , collectionCount );
			}
		}

		public: template<typename CollectionType, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static void Contains( const CollectionType& collection , const DataType& data )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( !Adapter::Contains( collection , data))
			{
				Throw<ValidationException>( "Condition: collection.Countains(data) is not fulfilled" , collection, data );
			}
		}
	};
}