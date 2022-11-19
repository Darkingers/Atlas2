module;

#include "../../../Macros/Macros.h"

export module AtlasMath;

export import :Abs;
export import :Ceil;
export import :Floor;
export import :Sin;
export import :ASin;
export import :Cos;
export import :ACos;
export import :Sqrt;
export import :Pow;
export import :Log;
export import :Factorial;

export namespace Atlas
{
	class DLLApi Math
	{
		public: template<typename NumberType>
		constexpr static inline auto Abs( NumberType number )
			noexcept( noexcept( Abs<NumberType>( number ) ) )
		{
			return Abs<NumberType>::Calculate( number );
		}

		public: template<typename NumberType>
		constexpr static inline auto Ceil( NumberType number )
			noexcept( noexcept( Ceil<NumberType>( number ) ) )
		{
			return Ceil<NumberType>::Calculate( number );
		}

		public: template<typename NumberType>
		constexpr static inline auto Floor( NumberType number )
			noexcept( noexcept( Floor<NumberType>( number ) ) )
		{
			return Floor<NumberType>::Calculate( number );
		}

		public: template<typename NumberType>
		constexpr static inline auto Sin( NumberType number )
			noexcept( noexcept( Sin<NumberType>( number ) ) )
		{
			return Sin<NumberType>::Calculate( number );
		}
			
		public: template<typename NumberType>
		constexpr static inline auto ASin( NumberType number )
			noexcept( noexcept( ASin<NumberType>( number ) ) )
		{
			return ASin<NumberType>::Calculate( number );
		}

		public: template<typename NumberType>
		constexpr static inline auto Cos( NumberType number )
			noexcept( noexcept( Cos<NumberType>( number ) ) )
		{
			return Cos<NumberType>::Calculate( number );
		}
			
		public: template<typename NumberType>
		constexpr static inline auto ACos( NumberType number )
			noexcept( noexcept( ACos<NumberType>( number ) ) )
		{
			return ACos<NumberType>::Calculate( number );
		}
			
		public: template<typename NumberType>
		constexpr static inline auto Sqrt( NumberType number )
			noexcept( noexcept( Sqrt<NumberType>( number ) ) )
		{
			return Sqrt<NumberType>::Calculate( number );
		}
		
		public: template<typename NumberType>
		constexpr static inline auto Pow( NumberType number , NumberType power )
			noexcept( noexcept( Pow<NumberType>( number , power ) ) )
		{
			return Pow<NumberType>::Calculate( number , power );
		}
			
		public: template<typename NumberType>
		constexpr static inline auto Log( NumberType number )
			noexcept( noexcept( Log<NumberType>( number ) ) )
		{
			return Log<NumberType>::Calculate( number );
		}		

		public: template<typename NumberType>
		constexpr static inline auto Factorial( NumberType number )
			noexcept( noexcept( Factorial<NumberType>( number ) ) )
		{
			return Factorial<NumberType>::Calculate( number );
		}
	};
}