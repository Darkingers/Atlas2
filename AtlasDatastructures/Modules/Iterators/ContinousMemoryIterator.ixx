module;

#include "../../../Macros/Macros.h"

export module AtlasIterators:ContinousMemoryIterator;
import AtlasInterfaces;

export namespace Atlas
{
    template<typename DataType>
    class DLLApi ContinousMemoryIterator :
        public Interface::IIterator<DataType>
    {
        private: using TIterator = ContinousMemoryIterator<DataType>;

        public: using iterator_category = std::random_access_iterator_tag;
        public: using difference_type = std::ptrdiff_t;
        public: using value_type = DataType;
        public: using pointer = DataType*;
        public: using reference = DataType&;

       
        private: DataType* _current;


        public:
        constexpr ContinousMemoryIterator( DataType* current )  :
            _current( current )
        {

        }

        public:
        constexpr ~ContinousMemoryIterator( ) final
        {

        }

        public: 
        constexpr DataType& operator*() final
        { 
            return *_current;
        }

        public: 
        constexpr DataType* operator->() final
        { 
            return _current;
        }

        public: 
        constexpr TIterator& operator++()  final
        {
            _current++;
            return *this; 
        }

        public:
        constexpr TIterator operator++( int ) final
        { 
            TIterator tmp = *this;
            ++( *this );
            return tmp; 
        }

        public:
        constexpr TIterator& operator--( )  final
        {
            _current--;
            return *this;
        }

        public:
        constexpr TIterator operator--( int ) final
        {
            TIterator tmp = *this;
            --( *this );
            return tmp;
        }

        constexpr friend bool operator== ( const TIterator& a, const TIterator& b )
        {
            return a._current == b._current;
        };

        constexpr friend bool operator!= ( const TIterator& a, const TIterator& b )
        { 
            return a._current != b._current;
        };
    };
}
