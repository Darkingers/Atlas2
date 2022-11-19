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
		public: template<typename CollectionType>
		constexpr static auto Minimum( const CollectionType& collection )
			noexcept( noexcept( Minimum<CollectionType>::Calculate( collection ) ))
		{
			return Minimum<CollectionType>::Calculate( collection );
		}

		public: template<typename CollectionType>
		constexpr static auto Maximum( const CollectionType& collection )
			noexcept( noexcept( Maximum<CollectionType>::Calculate( collection ) ) )
		{
			return Maximum<CollectionType>::Calculate( collection );
		}

		public: template<typename CollectionType>
		constexpr static auto Sum( const CollectionType& collection )
			noexcept( noexcept( Sum<CollectionType>::Calculate( collection ) ) )
		{
			return Sum<CollectionType>::Calculate( collection );
		}

		public: template<typename CollectionType>
		constexpr static auto Deviation( const CollectionType& collection )
			noexcept( noexcept( Deviation<CollectionType>::Calculate( collection ) ) )
		{
			return Deviation<CollectionType>::Calculate( collection );
		}
			
		public: template<typename CollectionType>
		constexpr static auto Average( const CollectionType& collection )
			noexcept( noexcept( Average<CollectionType>::Calculate( collection ) ) )
		{
			return Average<CollectionType>::Calculate( collection );
		}

		public: template<typename CollectionType>
		constexpr static auto Summary( const CollectionType& collection )
			noexcept( noexcept( Summary<CollectionType>::Calculate( collection ) ) )
		{
			return Summary<CollectionType>::Calculate( collection );
		}
	};
}