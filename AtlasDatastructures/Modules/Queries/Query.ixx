module;

#include "../../../Macros/Macros.h"

export module AtlasQueries:SelectionQuery;


export namespace Atlas
{
	/*
	template<typename DataType>
	class DLLApi SelectionQuery
	{
		private: using QueryType = SelectionQuery<DataType>;
		private: using ConditionType = Lambda<bool, const DataType&>;

		private: SpeedFriendlyMemoryHandler<ConditionType> _conditions;
		private: SpeedFriendlyMemoryHandler<DataType> _results;


		public:
		SelectionQuery( DataType* initialResults, unsigned int resultCount )  :
			_results( initialResults, resultCount )
		{

		}

		public:
		~SelectionQuery() 
		{

		}

		private:
		void Evaluate() 
		{
			if ( _conditions == 0 )
			{
				return;
			}

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				bool remove = false;

				for ( auto condition : _conditions )
				{
					if ( !condition( _results[i] ) )
					{
						remove = true;
						break;
					}
				}

				if ( remove )
				{
					removed++;
				}
				else
				{
					_results[i - removed] = _results[i];
				}
			}

			_results.Resize( _results - removed );
			_conditions.Resize( 0 );
		}

		public:
		const unsigned int Count() 
		{
			Evaluate();

			return _results;
		}

		public: template<typename... TArgs>
		QueryType& Where( TArgs&&... arguments ) 
		{
			const unsigned int index = _conditions;

			_conditions.Resize( _conditions + VariadicCounter<DataType>::Count( TArgs... ) );

			Memory::ReplaceFrom( &_conditions[index], index, std::forward<TArgs>( TArgs )... );

			return *this;
		}

		private: template<typename... TArgs>
		const unsigned int UnionConcat( unsigned int distinctCount, const DataType& data,const TArgs&... arguments )
		{
			assert( distinctCount >= 0 );

			bool distinct = true;
			for ( unsigned int i=0; i< distinctCount; )
			{
				if ( _results[i++] == data )
				{
					distinct = false;
					break;
				}
			}

			if ( distinct )
			{
				_results[distinctCount++] = data;
			}

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				return UnionConcat( distinctCount, TArgs... );
			}
			else
			{
				return distinctCount;
			}
		}

		private: template<typename TCollection, typename... TArgs> requires IsIterableWith<TCollection, DataType>
		const unsigned int UnionConcat( unsigned int distinctCount, const TCollection& collection, const TArgs&... arguments )
		{
			assert( distinctCount >= 0 );

			bool distinct;

			for ( auto data : collection )
			{
				distinct = true;

				for ( unsigned int i = 0; i < distinctCount;)
				{
					if ( _results[i++] == data )
					{
						distinct = false;
						break;
					}
				}

				if ( distinct )
				{
					_results[distinctCount++] = data;
				}
			}

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				return UnionConcat( distinctCount, TArgs... );
			}
			else
			{
				return distinctCount;
			}
		}

		public: template<typename... TArgs>
		QueryType& Union( const TArgs&... arguments ) 
		{
			Distinct();

			_results.Resize( _results, VariadicCounter<DataType>::Count( TArgs... ) );

			_results.Resize( UnionConcat( _results, _results, TArgs... ) );

			return *this;
		}

		public: template<typename... TArgs>
		QueryType& Intersect( const TArgs&... arguments ) 
		{
			Evaluate();

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				if ( VariadicContainChecker<DataType>::All( _results[i], TArgs... ) )
				{
					_results[i - removed] = _results[i];
				}
				else
				{
					++removed;
				}
			}

			_results.Resize( _results - removed );

			return *this;
		}

		public: template<typename... TArgs>
		QueryType& Except( const TArgs&... arguments ) 
		{
			Evaluate();

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				if ( !VariadicContainChecker<DataType>::Any( _results[i], TArgs... ) )
				{
					_results[i - removed] = _results[i];
				}
				else
				{
					++removed;
				}
			}

			_results.Resize( _results - removed );

			return  *this;
		}

		public: template<typename... TArgs>
		QueryType& Concat( const TArgs&... arguments ) 
		{
			Evaluate();

			const unsigned int index = _results;

			_results.Resize( _results + VariadicCounter::Count( TArgs... ) );

			Memory::ReplaceFrom( _results, index, TArgs... );

			return *this;
		}

		public: template<typename ComparatorType, typename... TArgs>
		QueryType& Distinct( const ComparatorType comparator = DefaultComparator<const DataType&> ) 
		{
			Evaluate();

			bool distinct;
			unsigned int distinctCount = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				distinct = true;

				for ( unsigned int j = 0; j < distinctCount; ++j )
				{
					if ( comparator( _results[i], _results[j] ) == 0 )
					{
						distinct = false;
						break;
					}
				}

				if ( distinct )
				{
					_results[distinctCount++] = _results[i];
				}
			}

			_results.Resize( distinctCount );

			return *this;
		}

		public: template<typename... TArgs>
		QueryType& Between( const unsigned int from, const unsigned int to ) 
		{
			assert( from >= 0 && to >= 0 && from <= to );

			Evaluate();

			const unsigned int newSize = to - from + 1;

			for ( unsigned int i = 0; i < newSize; )
			{
				_results[i] = _results[i + from];
			}

			_results.Resize( newSize );

			return *this;
		}

		public: template<typename TargetDataType,typename ConverterType>
		SelectionQuery<TargetDataType>& Select( const ConverterType converter )const 
		{
			Evaluate();

			TargetDataType* resultSet = new TargetDataType[_results];

			unsigned int i = 0;
			for ( auto data : _results )
			{
				resultSet[i++] = converter( ( *data ) );
			}

			return new SelectionQuery( resultSet, _results );
		}

		public:
		DataType* begin() 
		{
			Evaluate();

			return _results.begin();
		}

		public:
		DataType* end() 
		{
			Evaluate();

			return _results.end();
		}

		public:
		DataType& operator[]( const unsigned int index ) 
		{
			assert( index >= 0 );

			Evaluate();

			assert( index <= _results );

			return _results[index];
		}
	};

	template<typename SourceTCollection, typename DataType>
	class DLLApi Query
	{
		private: using QueryType = Query<SourceTCollection, DataType>;

		class Iterator
		{
			private: SpeedFriendlyMemoryHandler<DataType*>& _results;
			private: unsigned int _current;

			public:
			Iterator( SpeedFriendlyMemoryHandler<DataType*>& results, const unsigned int current = 0 )  :
				_results(results),
				_current(current)
			{

			}

			public:
			Iterator& operator++() 
			{
				++_current;

				return *this;
			}

			public:
			Iterator& operator--() 
			{
				--_current;

				return *this;
			}


			public:
			operator DataType& ( ) 
			{
				return (*_results[_current]);
			}

			public:
			operator DataType* ( ) 
			{
				return ( *_results[_current] );
			}

			public:
			const bool operator==( const DataType& data ) const 
			{
				return (*_results[_current]) == data;
			}

			public:
			const bool operator!=( const DataType& data ) const 
			{
				return (*_results[_current]) != data;
			}

			public:
			const bool operator==( const DataType* data ) const 
			{
				return _results[_current] == data;
			}

			public:
			const bool operator!=( const DataType* data ) const 
			{
				return _results[_current] != data;
			}
		};


		private: SourceTCollection* _sourceCollection;

		private: SpeedFriendlyMemoryHandler<ConditionType> _conditions;
		private: SpeedFriendlyMemoryHandler<DataType*> _results;

		private: bool _deleteSource;


		public:
		Query( SourceTCollection* sourceCollection )  :
			_sourceCollection( sourceCollection ),
			_results( SizeAdapter<SourceTCollection>::Count( *sourceCollection ) ),
			_deleteSource(false)
		{
		}

		public:
		Query( SourceTCollection& sourceCollection )  :
			_sourceCollection( &sourceCollection ),
			_results( SizeAdapter<SourceTCollection>::Count( sourceCollection ) ),
			_deleteSource( false )
		{
		}

		public:
		Query( SourceTCollection&& sourceCollection )  :
			_sourceCollection( sourceCollection ),
			_results( SizeAdapter<SourceTCollection>::Count( sourceCollection ) ),
			_deleteSource( true )
		{
		}

		public:
		~Query() 
		{
			if ( _deleteSource && _sourceCollection != nullptr)
			{
				delete _sourceCollection;
			}
		}

		private:
		void Evaluate() 
		{
			if ( _conditions == 0 )
			{
				return;
			}

			if ( _sourceCollection != nullptr )
			{
				bool add;
				unsigned int i = 0;

				for ( auto data : ( *_sourceCollection ) )
				{
					add = true;

					for ( auto condition : _conditions )
					{
						if ( !condition( data ) )
						{
							add = false;
							break;
						}
					}

					if ( add )
					{
						_results[i++] = &data;
					}
				}

				if ( _deleteSource )
				{
					delete _sourceCollection;
				}

				_sourceCollection = nullptr;
			}
			else
			{
				unsigned int removed = 0;

				for ( unsigned int i= 0, limit = _results; i < limit; ++i )
				{
					bool remove = false;

					for ( auto condition : _conditions )
					{
						if ( !condition( *_results[i] ) )
						{
							removed = true;
							break;
						}
					}

					if ( remove )
					{
						removed++;
					}
					else
					{
						_results[i - removed] = _results[i];
					}
				}

				_results.Resize( _results - removed );
			}

			_conditions.Resize( 0 );
		}

		public:
		const unsigned int Count() 
		{
			Evaluate();

			return _results;
		}

		public: template<typename... TArgs>
		QueryType& Where( TArgs&&... arguments ) 
		{
			const unsigned int index = _conditions;

			_conditions.Resize( _conditions + VariadicCounter<DataType>::Count( TArgs... ) );

			Memory::ReplaceFrom( &_conditions[index], index, std::forward<TArgs>( TArgs )... );

			return *this;
		}

		private: template<typename... TArgs>
		unsigned int UnionConcat (unsigned int distinctCount, const DataType& data, TArgs&... arguments )
		{
			assert( distinctCount >= 0 );

			bool distinct = true;
			for ( unsigned int i = 0; i < distinctCount; )
			{
				if ( ( *_results[i++] ) == data )
				{
					distinct = false;
					break;
				}
			}

			if ( distinct )
			{
				_results[distinctCount++] = &data;
			}

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				return UnionConcat( distinctCount, TArgs... );
			}
			else
			{
				return distinctCount;
			}
		}

		private: template<typename TCollection, typename... TArgs> requires IsIterableWith<const TCollection, const DataType>
		unsigned int UnionConcat(unsigned int distinctCount, const TCollection& collection, TArgs&... arguments )
		{
			assert( distinctCount >= 0 );

			bool distinct;

			for ( auto data : collection )
			{
				distinct = true;

				for ( unsigned int i = 0; i < distinctCount; ++i )
				{
					if ( ( *_results[i] ) == data )
					{
						distinct = false;
						break;
					}
				}

				if ( distinct )
				{
					_results[distinctCount++] = &data;
				}
			}

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				return UnionConcat( distinctCount, TArgs... );
			}
			else
			{
				return distinctCount;
			}
		}

		public: template<typename... TArgs>
		QueryType& Union( const TArgs&... arguments ) 
		{
			Distinct();

			_results.Resize( _results, VariadicCounter::Count( TArgs... ) );

			_results.Resize( UnionConcat( _results, _results, TArgs...) );

			return *this;
		}

		public: template<typename... TArgs>
		QueryType& Intersect( const TArgs&... arguments ) 
		{
			Evaluate();

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				if ( VariadicContainChecker<DataType>::All( _results[i], TArgs... ) )
				{
					_results[i - removed] = _results[i];
				}
				else
				{
					++removed;
				}
			}

			_results.Resize( _results - removed );

			return *this;
		}

		public: template<typename... TArgs>
		QueryType& Except( const TArgs&... arguments ) 
		{
			Evaluate();

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit=_results; i < limit; ++i )
			{
				if ( !VariadicContainChecker<DataType>::Any( _results[i], TArgs... ) )
				{
					_results[i - removed] = _results[i];
				}
				else
				{
					++removed;
				}
			}

			_results.Resize( _results - removed );

			return  *this;
		}

		private: template<typename... TArgs>
		void ReplaceFrom( unsigned int index, const DataType& data, TArgs&... arguments )
		{
			assert( index >= 0 );

			_results[index++] = &data;

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				ReplaceFrom( index, TArgs... );
			}
		}

		private: template<typename TCollection, typename... TArgs> requires IsIterable<const TCollection, const DataType>
		void ReplaceFrom( unsigned int index, const TCollection& collection, TArgs&... arguments )
		{
			assert( index >= 0 );

			for ( auto data : collection )
			{
				_results[index++] = &data;
			}

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				ReplaceFrom( index, TArgs... );
			}
		}

		public: template<typename... TArgs>
		QueryType& Concat( const TArgs&... arguments ) 
		{
			Evaluate();

			const unsigned int index = _results;

			_results.Resize( _results + VariadicCounter::Count( TArgs... ) );

			ReplaceFrom( index, TArgs... );

			return *this;
		}

		public: template<typename ComparatorType typename... TArgs>
		QueryType& Distinct( const ComparatorType comparator = DefaultComparator<const DataType&> ) 
		{
			bool distinct;
			unsigned int distinctCount = 0;

			for ( unsigned int i = 0, limit=_results; i < limit; ++i )
			{
				distinct = true;

				for ( unsigned int j = 0; j < distinctCount; ++j )
				{
					if ( comparator( (*_results[i]), (*_results[j]) ) == 0 )
					{
						distinct = false;
						break;
					}
				}

				if ( distinct )
				{
					_results[distinctCount++] = _results[i];
				}
			}

			_results.Resize( distinctCount );

			return *this;
		}

		public: template<typename... TArgs>
		QueryType& Between( const unsigned int from, const unsigned int to ) 
		{
			assert( from >= 0 && to >= 0 && from <= to );

			const unsigned int newSize = to - from + 1;

			for ( unsigned int i = 0; i<newSize; )
			{
				_results[i] = _results[i + from];
			}

			_results.Resize( newSize );

			return *this;
		}

		public: template<typename TargetDataType, typename ConverterType>
		SelectionQuery<TargetDataType>& Select( const ConverterType converter )const 
		{
			TargetDataType* resultSet = new TargetDataType[_results];

			unsigned int i = 0;
			for ( auto data : _results )
			{
				resultSet[i++] = converter( ( *data ) );
			}

			return (*new SelectionQuery( resultSet, _results ));
		}

		public:
		Iterator begin() 
		{
			Evaluate();

			return Iterator( _results );
		}

		public:
		Iterator end() 
		{
			Evaluate();

			return Iterator( _results, _results );
		}

		public:
		DataType& operator[]( const unsigned int index ) 
		{
			assert( index >= 0 );

			Evaluate();

			assert( index <= _results );

			return (*_results[index]);
		}
	};
}
*/
}