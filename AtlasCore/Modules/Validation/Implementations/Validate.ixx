module;

#include "../../../../Macros/Macros.h"

export module AtlasValidation:Validate;
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

		public: template<typename TA , typename TB>
		constexpr static inline void IsSame( const TA& a, const TB& b) 
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

		public: template<typename TA , typename TB>
		constexpr static inline void IsNotSame( const TA& a , const TB& b )
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

		public: template<typename TA , typename TB>
		constexpr static inline void IsLess( const TA& a, const TB& b ) 
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

		public: template<typename TA, typename TB>
		constexpr static inline void IsMore( const TA& a , const TB& b )
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

		public: template<typename TA , typename TB>
		constexpr static inline void PositiveRange( const TA& a, const TB& b ) 
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

		public: template<typename TestedType , typename TA , typename TB>
		constexpr static inline void InclusiveRange( const TestedType& tested, const TA& from , const TB& to )
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
						
		public: template<typename TestedType , typename TA , typename TB>
		constexpr static inline void ExclusiveRange( const TestedType& tested , const TA& from , const TB& to )
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

		public: template<typename TA , typename TB>
		constexpr static inline void IsLessOrEqual( const TA& a , const TB& b )
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

		public: template<typename TA , typename TB>
		constexpr static inline void IsMoreOrEqual( const TA& a , const TB& b ) 
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

		public: template<typename TA , typename TB, typename TypeC>
		constexpr static inline void IsInRange( const TA& number , const TB& inclusiveStart, const TypeC& exclusiveEnd )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( number < inclusiveStart || number >= exclusiveEnd )
			{
				throw ValidationException( "Condition: number >= inclusiveStart && number < exclusiveEnd is not fulfilled!");
			}
		}


		public: template<typename ComparedType, typename CurrentType, typename... TArgs>
		constexpr static inline void IsAny( const ComparedType& compared, const CurrentType& current, const TArgs&... args) 
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
			
			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				Validate<IsEnabled>::IsAny( compared , args... );
			}
			else
			{
				throw ValidationException( "Condition: compared == current is not fulfilled!" );
			}
		}

		public: template<typename ComparedType , typename CurrentType , typename... TArgs>
		constexpr static inline void IsNone( const ComparedType& compared , const CurrentType& current , const TArgs&... arguments ) 
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

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				Validate<IsEnabled>::IsNone( compared , TArgs... );
			}
			else
			{
				return;
			}
		}
	};
}