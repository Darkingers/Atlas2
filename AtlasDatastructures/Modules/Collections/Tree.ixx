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
//		public: template<typename... Args>
//		const bool Contains( const DataType& data, Args... arguments )const 
//		{
//			if ( Data == data )
//			{
//				if constexpr ( sizeof...( arguments ) == 0 )
//				{
//					return true;
//				}
//				else
//				{
//					return this->Contains( arguments... );
//				}		
//			}
//			else
//			{
//				for ( int i = 0; i < ChildCount; )
//				{
//					if (_children[i]!=nullptr && _children[i++]->Contains( data ) )
//					{
//						if constexpr ( sizeof...( arguments ) == 0 )
//						{
//							return true;
//						}
//						else
//						{
//							return this->Contains( arguments... );
//						}
//					}
//				}
//			}
//
//			return false;
//		}
//
//		public: template<typename CollectionType, typename... Args> requires Concepts::AtlasIterableCollection<CollectionType, DataType, FunctorType, ConditionType>
//		const bool Contains( const CollectionType& collection, Args... arguments )const 
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
//			if constexpr ( sizeof...( arguments ) == 0 )
//			{
//				return returnValue;
//			}
//			else
//			{
//				return returnValue && this->Contains( arguments... );
//			}
//		}
//
//		public: template<typename CollectionType, typename... Args> requires  Concepts::StandardIterableCollection<CollectionType, DataType>
//		const bool Contains( const CollectionType& collection, Args... arguments )const 
//		{
//			for ( auto data : collection )
//			{
//				if ( !this->Contains( data ) )
//				{
//					return false;			
//				}
//			}
//
//			if constexpr ( sizeof...( arguments ) == 0 )
//			{
//				return true;
//			}
//			else
//			{
//				return this->Contains( arguments... );
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
//		public: template<typename... Args>
//		TreeType& Get( Args... arguments )
//		{
//			return this->NavigateTo( arguments... ).Data;
//		}
//
//		public: template<typename... Args>
//		TreeType& NavigateTo(unsigned int index, Args... arguments )
//		{
//			if constexpr ( sizeof...( arguments ) == 0 )
//			{
//				return *_children[index];
//			}
//			else
//			{
//				return _children[index]->NavigateTo( arguments... );
//			}
//		}
//
//		public: template<typename CollectionType, typename... Args> requires Concepts::AtlasIterableCollection<CollectionType, unsigned int, FunctorType, ConditionType>
//		DataType& NavigateTo( CollectionType collection, Args... arguments )
//		{
//			TreeType* current = this;
//
//			collection.ForEach( [&current] ( unsigned int index )->mutable
//			{
//				current = current->_children[index];
//			} );
//
//			if constexpr ( sizeof...( arguments ) == 0 )
//			{
//				return *current;
//			}
//			else
//			{
//				return current->NavigateTo( arguments... );
//			}			
//		}
//
//		public: template<typename CollectionType, typename... Args> requires Concepts::StandardIterableCollection<CollectionType, unsigned int>
//		DataType& NavigateTo( CollectionType collection, Args... arguments )
//		{
//			TreeType* current = this;
//
//			for( auto index : collection )
//			{
//				current = current->_children[index];
//			}
//
//			if constexpr ( sizeof...( arguments ) == 0 )
//			{
//				return *current;
//			}
//			else
//			{
//				return current->NavigateTo( arguments... );
//			}
//		}
//
//		public: template<typename... Args>
//		TreeType* BreathFirstSearch( Args... arguments ) 
//		{
//			if ( Checker::CheckALL( Data, arguments... ))
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
//						if ( Checker::CheckALL( child.Data, arguments... ))
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
//		public: template<typename... Args>
//		TreeType* DepthFirstSearch( Args... arguments ) 
//		{
//			if ( Checker::CheckAll( Data, arguments... ) )
//			{
//				return this;
//			}
//			
//			TreeType* childResult;
//			for ( unsigned int i = 0; i < ChildCount )
//			{
//				if ( _children[i] != nullptr )
//				{
//					childResult = _children[i]->DepthFirstSearch( arguments... );
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