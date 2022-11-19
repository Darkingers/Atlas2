module;

#include "../../../../Macros/Macros.h"

export module AtlasValidation:Validate;

import AtlasDefinitions;
import :ValidationException;

export namespace Atlas
{
	template<bool IsEnabled = true>
	class DLLApi Validate 
	{
		public:
		constexpr static inline void IsTrue( const bool a ) 
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
		constexpr static inline void IsFalse( const bool a ) 
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
		constexpr static inline void IsNull( const DataType* pointer ) 
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
		constexpr static inline void IsNotNull( const DataType* pointer ) 
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
		constexpr static inline void IsSame( const TypeA& a, const TypeB& b) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a!=b)
			{
				throw ValidationException( "Condition: a==b is not fulfilled!");
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr static inline void IsNotSame( const TypeA& a , const TypeB& b )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a==b )
			{
				throw ValidationException( "Condition: a!=b is not fulfilled!");
			}
		}

		public: template<typename DataType, typename NumberType>
		constexpr static inline void IsArray( const DataType* array, const NumberType& size )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( size<0 )
			{
				throw ValidationException( "Condition: size>0 is not fulfilled!" );
			}
			else if ( size > 0 && array == nullptr )
			{
				throw ValidationException( "Condition: array!=nullptr is not fulfilled!" );
			}
		}

		public: template<typename DataType>
		constexpr static inline void IsPositive( const DataType& a) 
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
		constexpr static inline void IsNegative( const DataType& a )
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
		constexpr static inline void IsLess( const TypeA& a, const TypeB& b ) 
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
		constexpr static inline void IsMore( const TypeA& a , const TypeB& b )
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
		constexpr static inline void PositiveRange( const TypeA& a, const TypeB& b ) 
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

		public: template<typename TestedType , typename TypeA , typename TypeB>
		constexpr static inline void InclusiveRange( const TestedType& tested, const TypeA& from , const TypeB& to )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( tested<from || tested>to)
			{
				throw ValidationException( "Condition: tested<from || tested>to is not fulfilled!" );
			}
		}
						
		public: template<typename TestedType , typename TypeA , typename TypeB>
		constexpr static inline void ExclusiveRange( const TestedType& tested , const TypeA& from , const TypeB& to )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( tested<=from || tested>=to )
			{
				throw ValidationException( "Condition: tested<=from || tested>=to is not fulfilled!" );
			}
		}

		public: template<typename TypeA , typename TypeB>
		constexpr static inline void IsLessOrEqual( const TypeA& a , const TypeB& b )
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
		constexpr static inline void IsMoreOrEqual( const TypeA& a , const TypeB& b ) 
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
		constexpr static inline void IsInRange( const TypeA& number , const TypeB& inclusiveFrom, const TypeC& exclusiveTo )
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
		constexpr static inline void IsEmpty( const CollectionType& collection ) 
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
		constexpr static inline void IsNotEmpty( const CollectionType& collection )
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
		constexpr static inline void Contains( const CollectionType& collection , const DataType& data ) 
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

		public: template<typename ComparedType, typename CurrentType, typename... Arguments>
		constexpr static inline void IsAny( const ComparedType& compared, const CurrentType& current, const Arguments&... arguments) 
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

		public: template<typename ComparedType , typename CurrentType , typename... Arguments>
		constexpr static inline void IsNone( const ComparedType& compared , const CurrentType& current , const Arguments&... arguments ) 
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