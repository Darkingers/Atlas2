module;

#include "../../../../Macros/Macros.h"

export module AtlasValidation:Validate;
import :ValidationException;

export namespace Atlas
{
	/// <summary>
	/// A compile-time compatible validation class
	/// </summary>
	/// <typeparam name="IsEnabled">If true, disables all validation.</typeparam>
	template<bool IsEnabled = true>
	class DLLApi Validate 
	{

	public:
	
		/// <summary>
		/// Checks whether the given criteria is true
		/// </summary>
		constexpr static inline void IsTrue( const bool a, const char* errorMessage =  "Condition: a==true is not fulfilled!" ) 
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( !a )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given criteria is false
		/// </summary>
		constexpr static inline void IsFalse( const bool a , const char* errorMessage = "Condition: a==false is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given pointer is null
		/// </summary>
		template<typename DataType>
		constexpr static inline void IsNull( const DataType* pointer , const char* errorMessage = "Condition: pointer==nullptr is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( pointer !=nullptr )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given pointer is not null
		/// </summary>
		template<typename DataType>
		constexpr static inline void IsNotNull( const DataType* pointer , const char* errorMessage = "Condition: pointer!=nullptr is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( pointer == nullptr )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given value is equal to the other value
		/// </summary>
		template<typename TA , typename TB>
		constexpr static inline void IsSame( const TA& a , const TB& b , const char* errorMessage = "Condition: a==b is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a!=b)
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given value is not equal to the other value
		/// </summary>
		template<typename TA , typename TB>
		constexpr static inline void IsNotSame( const TA& a , const TB& b , const char* errorMessage = "Condition: a!=b is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a==b )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given value is positive
		/// </summary>
		template<typename DataType>
		constexpr static inline void IsPositive( const DataType& a , const char* errorMessage = "Condition: a>0 is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a <0 )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given value is negative
		/// </summary>
		template<typename DataType>
		constexpr static inline void IsNegative( const DataType& a , const char* errorMessage = "Condition: a<0 is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a>=0 )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given value is less than the other value
		/// </summary>
		template<typename TA , typename TB>
		constexpr static inline void IsLess( const TA& a , const TB& b , const char* errorMessage = "Condition: a<b is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a>=b)
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given value is greater than the other value
		/// </summary>
		template<typename TA, typename TB>
		constexpr static inline void IsMore( const TA& a , const TB& b , const char* errorMessage = "Condition: a>b is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a <= b )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		///Checks whether the given values define a valid positive range
		template<typename TA , typename TB>
		constexpr static inline void IsPositiveRange( const TA& from , const TB& to , const char* errorMessage = "Condition: from<=to is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( from <0 || to<from )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the tested value fits in the given inclusive range
		/// </summary>
		template<typename TestedType , typename TA , typename TB>
		constexpr static inline void IsInInclusiveRange( const TestedType& tested , const TA& from , const TB& to , const char* errorMessage = "Condition: from<=tested<=to is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( tested<from || tested>to)
			{
				throw ValidationException( errorMessage );
			}
		}
			
		/// <summary>
		/// Checks whether the tested value fits in the given exclusive range
		/// </summary>
		template<typename TestedType , typename TA , typename TB>
		constexpr static inline void IsInExclusiveRange( const TestedType& tested , const TA& from , const TB& to , const char* errorMessage = "Condition: from<tested<to is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( tested<=from || tested>=to )
			{
				throw ValidationException( errorMessage );
			}
		}
	
		
		/// <summary>
		/// Checks whether the given value is less or equal to the other value
		/// </summary>
		template<typename TA , typename TB>
		constexpr static inline void IsLessOrEqual( const TA& a , const TB& b , const char* errorMessage = "Condition: a<=b is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a > b )
			{
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the given value is greater or equal to the other value
		/// </summary>
		template<typename TA , typename TB>
		constexpr static inline void IsMoreOrEqual( const TA& a , const TB& b , const char* errorMessage = "Condition: a>=b is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( a < b )
			{
				throw ValidationException( errorMessage );
			}
		}

		template<typename TA , typename TB, typename TypeC>
		constexpr static inline void IsInRange( const TA& number , const TB& inclusiveStart , const TypeC& exclusiveEnd , const char* errorMessage = "Condition: inclusiveStart<=number<exclusiveEnd is not fulfilled!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( number < inclusiveStart || number >= exclusiveEnd )
			{
				throw ValidationException( errorMessage );
			}
		}


		/// <summary>
		/// Checks whether the tested value matches any other variadic value
		/// </summary>
		template<typename ComparedType, typename CurrentType, typename... TArgs>
		constexpr static inline void IsAny( const ComparedType& compared , const CurrentType& current , const TArgs&... args , const char* errorMessage = "Condition: compared is not equal to any of the given values!" )
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
				throw ValidationException( errorMessage );
			}
		}

		/// <summary>
		/// Checks whether the tested value matches any other variadic value
		/// </summary>
		template<typename ComparedType , typename CurrentType , typename... TArgs>
		constexpr static inline void IsAll( const ComparedType& compared , const CurrentType& current , const TArgs&... args , const char* errorMessage = "Condition: compared is not equal to all of the given values!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( compared != current )
			{
				throw ValidationException( errorMessage );
			}

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				Validate<IsEnabled>::IsAll( compared , args... );
			}
		}

		/// <summary>
		/// Checks whether the tested value matches none other variadic value
		/// </summary>
		template<typename ComparedType , typename CurrentType , typename... TArgs>
		constexpr static inline void IsNone( const ComparedType& compared , const CurrentType& current , const TArgs&... args , const char* errorMessage = "Condition: compared is equal to one of the given values!" )
			noexcept( !IsEnabled )
		{
			if constexpr ( !IsEnabled )
			{
				return;
			}

			if ( compared == current )
			{
				throw ValidationException( errorMessage );
			}

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				Validate<IsEnabled>::IsNone( compared , args... );
			}
			else
			{
				return;
			}
		}
	};
}