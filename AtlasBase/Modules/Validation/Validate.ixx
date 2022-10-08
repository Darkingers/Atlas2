module;

#include "../../../Macros/Macros.h"

export module AtlasValidation:Validate;

import AtlasDefinitions;
import AtlasAdapters;
import AtlasExceptions;

export namespace Atlas
{
	template<bool IsEnabled = true>
	class DLLApi Validate 
	{
		public:
		constexpr inline static void IsTrue( const bool a ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( !a )
			{
				throw ValidationException( "Condition: a==true is not fulfilled!");
			}
		}

		public:
		constexpr inline static void IsFalse( const bool a ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a )
			{
				throw ValidationException( "Condition: a==false is not fulfilled!");
			}
		}

		public: template<typename DataType>
		constexpr inline static void IsNull( const DataType* pointer ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( pointer !=nullptr )
			{
				throw ValidationException( "Condition: pointer==nullptr is not fulfilled!");
			}
		}

		public: template<typename DataType>
		constexpr inline static void IsNotNull( const DataType* pointer ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( pointer == nullptr )
			{
				throw ValidationException( "Condition: pointer!=nullptr is not fulfilled!");
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsSame( const TypeA& a, const TypeB& b) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( !Adapter::Equals( a,b ) )
			{
				throw ValidationException( "Condition: a==b is not fulfilled!");
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsNotSame( const TypeA& a , const TypeB& b )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( Adapter::Equals( a , b ) )
			{
				throw ValidationException( "Condition: a!=b is not fulfilled!");
			}
		}

		public: template<typename DataType>
		constexpr inline static void IsPositive( const DataType& a) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a <0 )
			{
				throw ValidationException( "Condition: a>=b is not fulfilled!" );
			}
		}

		public: template<typename DataType>
		constexpr inline static void IsNegative( const DataType& a )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a>=0 )
			{
				throw ValidationException( "Condition: a < 0 is not fulfilled!");
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsLess( const TypeA& a, const TypeB& b ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a>=b)
			{
				throw ValidationException( "Condition: a < b is not fulfilled!" );
			}
		}

		public: template<typename TypeA, typename TypeB>
		constexpr inline static void IsMore( const TypeA& a , const TypeB& b )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a <= b )
			{
				throw ValidationException( "Condition: a > b is not fulfilled!" );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void PositiveRange( const TypeA& a, const TypeB& b ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a<0 || b<0 || a>b )
			{
				throw ValidationException( "Condition: a>=0 && b>=0 && a<=b is not fulfilled!" );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsLessOrEqual( const TypeA& a , const TypeB& b )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a > b )
			{
				throw ValidationException( "Condition: a<=b is not fulfilled!" );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsMoreOrEqual( const TypeA& a , const TypeB& b ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a < b )
			{
				throw ValidationException( "Condition: a>=b is not fulfilled!" );
			}
		}

		public: template<typename TypeA , typename TypeB, typename TypeC>
		constexpr inline static void IsInRange( const TypeA& number , const TypeB& inclusiveFrom, const TypeC& exclusiveTo )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( number < inclusiveFrom || number >= exclusiveTo )
			{
				throw ValidationException( "Condition: number >= inclusiveFrom && number < exclusiveTo is not fulfilled!");
			}
		}

		public: template<typename CollectionType>
		constexpr inline static void IsEmpty( const CollectionType& collection ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			const auto collectionCount = Adapter::Count( collection );

			if ( collectionCount != 0 )
			{
				throw ValidationException( "Condition: collection.Count==0 is not fulfilled!" );
			}
		}

		public: template<typename CollectionType>
		constexpr inline static void IsNotEmpty( const CollectionType& collection )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			const auto collectionCount = Adapter::Count( collection );

			if ( collectionCount <= 0 )
			{
				throw ValidationException( "Condition: collection.Count>0 is not fulfilled!" );
			}
		}

		public: template<typename CollectionType, typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static void Contains( const CollectionType& collection , const DataType& data ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( !Adapter::Contains( collection , data))
			{
				throw ValidationException( "Condition: collection.Countains(data) is not fulfilled" );
			}
		}

		public: template<typename ComparedType, typename CurrentType, typename... Args>
		constexpr inline static void IsAny( const ComparedType& compared, const CurrentType& current, const Args&... arguments) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( compared == current )
			{
				return;
			}
			
			if constexpr ( sizeof...( arguments ) > 0 )
			{
				Validate<IsEnabled>::IsAny( compared , arguments... );
			}
			else
			{
				throw ValidationException( "Condition: compared == current is not fulfilled!" );
			}
		}

		public: template<typename ComparedType , typename CurrentType , typename... Args>
		constexpr inline static void IsNone( const ComparedType& compared , const CurrentType& current , const Args&... arguments ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( compared == current )
			{
				throw ValidationException( "Condition: compared != current is not fulfilled!" );
			}

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				Validate<IsEnabled>::IsNone( compared , arguments... );
			}
			else
			{
				return;
			}
		}
	};
}