module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:Tree;
//
//export namespace Atlas
//{
//	template<typename DataType, unsigned int ChildCount>
//	class Tree
//	{
//		private: template<typename DataType> using Vector = std::vector<DataType>;
//		private: using TreeType = Tree<DataType, ChildCount>;
//		private: using ConditionType = Condition<DataType>;
//		private: using FunctorType = Functor<DataType>;
//		private: using Counter = ElementCounter<unsigned int>;
//		private: using Checker = ElementChecker<DataType, unsigned int>;
//
//
//		public: DataType Data;
//		protected: TreeType*[ChildCount] _children;
//
//
//		public: template<typename... TArgs>
//		const bool Contains( const DataType& data, TArgs... args )const 
//		{
//			if ( Data == data )
//			{
//				if constexpr ( sizeof...( TArgs ) == 0 )
//				{
//					return true;
//				}
//				else
//				{
//					return this->Contains( TArgs... );
//				}		
//			}
//			else
//			{
//				for ( int i = 0; i < ChildCount; )
//				{
//					if (_children[i]!=nullptr && _children[i++]->Contains( data ) )
//					{
//						if constexpr ( sizeof...( TArgs ) == 0 )
//						{
//							return true;
//						}
//						else
//						{
//							return this->Contains( TArgs... );
//						}
//					}
//				}
//			}
//
//			return false;
//		}
//
//		public: template<typename TCollection, typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection, DataType, FunctorType, ConditionType>
//		const bool Contains( const TCollection& collection, TArgs... args )const 
//		{
//			bool returnValue = true;
//
//			collection.Until( [&returnValue] ( const DataType& data ) mutable
//			{
//				if ( !this->Contains(data) )
//				{
//					returnValue = false;
//					return false;
//				}
//				else
//				{
//					return true;
//				}
//			} );
//
//			if constexpr ( sizeof...( TArgs ) == 0 )
//			{
//				return returnValue;
//			}
//			else
//			{
//				return returnValue && this->Contains( TArgs... );
//			}
//		}
//
//		public: template<typename TCollection, typename... TArgs> requires  Concepts::StandardIterableCollection<TCollection, DataType>
//		const bool Contains( const TCollection& collection, TArgs... args )const 
//		{
//			for ( auto data : collection )
//			{
//				if ( !this->Contains( data ) )
//				{
//					return false;			
//				}
//			}
//
//			if constexpr ( sizeof...( TArgs ) == 0 )
//			{
//				return true;
//			}
//			else
//			{
//				return this->Contains( TArgs... );
//			}
//		}
//
//		public:
//		const unsigned int GetSize()const 
//		{
//			unsigned int counter = 1;
//			for ( unsigned int i = 0; i < ChildCount; )
//			{
//				if ( _children[i] != nullptr )
//				{
//					counter += _children[i]->GetSize();
//				}
//			}
//
//			return counter;
//		}
//
//		public: template<typename... TArgs>
//		TreeType& Get( TArgs... args )
//		{
//			return this->NavigateTo( TArgs... ).Data;
//		}
//
//		public: template<typename... TArgs>
//		TreeType& NavigateTo(unsigned int index, TArgs... args )
//		{
//			if constexpr ( sizeof...( TArgs ) == 0 )
//			{
//				return *_children[index];
//			}
//			else
//			{
//				return _children[index]->NavigateTo( TArgs... );
//			}
//		}
//
//		public: template<typename TCollection, typename... TArgs> requires Concepts::AtlasIterableCollection<TCollection, unsigned int, FunctorType, ConditionType>
//		DataType& NavigateTo( TCollection collection, TArgs... args )
//		{
//			TreeType* current = this;
//
//			collection.ForEach( [&current] ( unsigned int index )->mutable
//			{
//				current = current->_children[index];
//			} );
//
//			if constexpr ( sizeof...( TArgs ) == 0 )
//			{
//				return *current;
//			}
//			else
//			{
//				return current->NavigateTo( TArgs... );
//			}			
//		}
//
//		public: template<typename TCollection, typename... TArgs> requires Concepts::StandardIterableCollection<TCollection, unsigned int>
//		DataType& NavigateTo( TCollection collection, TArgs... args )
//		{
//			TreeType* current = this;
//
//			for( auto index : collection )
//			{
//				current = current->_children[index];
//			}
//
//			if constexpr ( sizeof...( TArgs ) == 0 )
//			{
//				return *current;
//			}
//			else
//			{
//				return current->NavigateTo( TArgs... );
//			}
//		}
//
//		public: template<typename... TArgs>
//		TreeType* BreathFirstSearch( TArgs... args ) 
//		{
//			if ( Checker::CheckALL( Data, TArgs... ))
//			{
//				return this;
//			}
//
//			Vector<TreeType*> currentLevel = { this };
//			Vector<TreeType*> nextLevel;
//			TreeType* child;
//
//			do
//			{
//				for ( auto node : currentLevel )
//				{
//					for ( unsigned int i = 0; i < ChildCount; )
//					{
//						child = node->__children[i++];
//						if ( Checker::CheckALL( child.Data, TArgs... ))
//						{
//							return child;
//						}
//						else
//						{
//							nextLevel.push_back(child);
//						}
//					}
//				}
//
//				currentLevel = nextLevel;
//				nextLevel.clear();
//			}
//			while ( currentLevel.size() > 0 );
//
//			return nullptr;
//		}
//
//		public: template<typename... TArgs>
//		TreeType* DepthFirstSearch( TArgs... args ) 
//		{
//			if ( Checker::CheckAll( Data, TArgs... ) )
//			{
//				return this;
//			}
//			
//			TreeType* childResult;
//			for ( unsigned int i = 0; i < ChildCount )
//			{
//				if ( _children[i] != nullptr )
//				{
//					childResult = _children[i]->DepthFirstSearch( TArgs... );
//
//					if ( childresult != nullptr )
//					{
//						return childResult;
//					}
//				}			
//			}
//
//			return nullptr;
//		}
//	};
//}