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
		inline static constexpr void IsTrue( const bool a )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( !a )
			{
				Throw<ValidationException>( "Condition: a==true is not fulfilled!" );
			}
		}

		public:
		inline static constexpr void IsFalse( const bool a )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a )
			{
				Throw<ValidationException>( "Condition: a==false is not fulfilled!" );
			}
		}

		public: template<typename DataType>
		inline static constexpr void IsNull( const DataType* pointer )
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

		public:template<typename DataType>
		inline static constexpr void IsNotNull( const DataType* pointer )
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

		public:template<typename TypeA , typename TypeB>
		inline static constexpr void IsSame( const TypeA& a, const TypeB& b)
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( !EqualityAdapter<TypeA , TypeB>::Equals( a,b ) )
			{
				Throw<ValidationException>( "Condition: a==b is not fulfilled!", nullptr, a, b );
			}
		}

		public:template<typename TypeA , typename TypeB>
		inline static constexpr void IsNotSame( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( EqualityAdapter<TypeA , TypeB>::Equals( a , b ) )
			{
				Throw<ValidationException>( "Condition: a!=b is not fulfilled!",nullptr, a , b );
			}
		}

		public:template<typename DataType>
		inline static constexpr void IsPositive( const DataType& a)
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a <0 )
			{
				Throw<ValidationException>( "Condition: a>=b is not fulfilled!" , nullptr, a );
			}
		}

		public:template<typename DataType>
		inline static constexpr void IsNegative( const DataType& a )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a>=0 )
			{
				Throw<ValidationException>( "Condition: a < 0 is not fulfilled!",nullptr, a );
			}
		}

		public:template<typename TypeA , typename TypeB>
		inline static constexpr void IsLess( const TypeA& a, const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a>=b)
			{
				Throw<ValidationException>( "Condition: a < b is not fulfilled!", nullptr, a, b );
			}
		}

		public:template<typename TypeA, typename TypeB>
		inline static constexpr void IsMore( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a <= b )
			{
				Throw<ValidationException>( "Condition: a > b is not fulfilled!", nullptr, a , b );
			}
		}

		public:template<typename TypeA , typename TypeB>
		inline static constexpr void PositiveRange( const TypeA& a, const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( (a<0 || b<0 || a>b) )
			{
				Throw<ValidationException>( "Condition: a>=0 && b>=0 && a<=b is not fulfilled!", nullptr, a , b );
			}
		}

		public:template<typename TypeA , typename TypeB>
		inline static constexpr void IsLessOrEqual( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a > b )
			{
				Throw<ValidationException>( "Condition: a<=b is not fulfilled!", nullptr, a , b );
			}
		}

		public:template<typename TypeA , typename TypeB>
		inline static constexpr void IsMoreOrEqual( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( a < b )
			{
				Throw<ValidationException>( "Condition: a>=b is not fulfilled!", nullptr, a , b );
			}
		}

		public:template<typename CollectionType>
		inline static constexpr void IsEmpty( const CollectionType& collection )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			const unsigned int collectionCount = CountAdapter<CollectionType>::Count( collection );

			if ( collectionCount != 0 )
			{
				Throw<ValidationException>( "Condition: collection.Count==0 is not fulfilled!" , &collection , collectionCount );
			}
		}

		public:template<typename CollectionType>
		inline static constexpr void IsNotEmpty( const CollectionType& collection )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			const unsigned int collectionCount = CountAdapter<CollectionType>::Count( collection );

			if ( collectionCount <= 0 )
			{
				Throw<ValidationException>( "Condition: collection.Count>0 is not fulfilled!" , &collection , collectionCount );
			}
		}

		public:template<typename CollectionType, typename DataType = DeduceCollectionContainedType<CollectionType>>
		inline static constexpr void Contains( const CollectionType&& collection , const DataType& data )
		{
			if constexpr ( !Configuration::EnableEnsure )
			{
				return;
			}

			if ( !ContainAdapter<CollectionType,DataType>::Contains( collection , data))
			{
				Throw<ValidationException>( "Condition: collection.Countains(data) is not fulfilled", &collection, data );
			}
		}
	};
}