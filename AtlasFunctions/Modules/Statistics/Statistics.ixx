module;

#include "../../../Macros/Macros.h"

export module AtlasStatistics;

import AtlasDefinitions;
import AtlasConfiguration;

export import AtlasStatistics:Minimum;
export import AtlasStatistics:Maximum;
export import AtlasStatistics:Sum;
export import AtlasStatistics:Deviation;
export import AtlasStatistics:Average;
export import AtlasStatistics:Summary;

export namespace Atlas
{
	class DLLApi Statistics
	{
		public: template<typename TCollection>
		constexpr static auto Minimum( const TCollection& collection )
			noexcept( noexcept( Minimum<TCollection>::Calculate( collection ) ))
		{
			return Minimum<TCollection>::Calculate( collection );
		}

		public: template<typename TCollection>
		constexpr static auto Maximum( const TCollection& collection )
			noexcept( noexcept( Maximum<TCollection>::Calculate( collection ) ) )
		{
			return Maximum<TCollection>::Calculate( collection );
		}

		public: template<typename TCollection>
		constexpr static auto Sum( const TCollection& collection )
			noexcept( noexcept( Sum<TCollection>::Calculate( collection ) ) )
		{
			return Sum<TCollection>::Calculate( collection );
		}

		public: template<typename TCollection>
		constexpr static auto Deviation( const TCollection& collection )
			noexcept( noexcept( Deviation<TCollection>::Calculate( collection ) ) )
		{
			return Deviation<TCollection>::Calculate( collection );
		}
			
		public: template<typename TCollection>
		constexpr static auto Average( const TCollection& collection )
			noexcept( noexcept( Average<TCollection>::Calculate( collection ) ) )
		{
			return Average<TCollection>::Calculate( collection );
		}

		public: template<typename TCollection>
		constexpr static auto Summary( const TCollection& collection )
			noexcept( noexcept( Summary<TCollection>::Calculate( collection ) ) )
		{
			return Summary<TCollection>::Calculate( collection );
		}
	};
}