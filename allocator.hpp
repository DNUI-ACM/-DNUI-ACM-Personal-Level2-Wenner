#include <iostream>
#include <cstddef>

namespace mystl{
    template <typename T>
    class Allocator{
    public:
        using size_type = size_t;

        using value_type = T;
        using referance = T &;
        using pointer = T *;
        using const_pointer = const T*;
        using const_referance = const T &;
        using const_value_type = const T;
    public:
        Allocator (void) = default;
        ~Allocator (void) = default;
        inline pointer allocate (size_type _size) const;
        inline void construct (pointer& _addr) const;
        inline void construct (pointer& _addr , const_value_type _value) const;

        inline void deallocate (pointer _addr) const;
        inline void destory (pointer _addr) const;
    };

    template <typename T>
    inline typename Allocator<T>::pointer Allocator<T>::allocate (size_type _size) const{
        pointer _addr = NULL;
		try{
			_addr = (pointer)operator new(sizeof(T) * _size);
		}catch(std::bad_alloc & e){
			std::cout << e.what() << std::endl;
		}
		return _addr;
    }

    template <typename T>
    inline void Allocator<T>::construct (pointer& _addr) const{
        new(_addr)T();
    }

    template <typename T>
    inline void Allocator<T>::construct (pointer& _addr , const_value_type _value) const{
        new(_addr)T(_value);
    }

    template <typename T>
    inline void Allocator<T>::deallocate (pointer _addr) const{
        operator delete [] (_addr);
    }

    template <typename T>
    inline void Allocator<T>::destory (pointer _addr) const{
        _addr -> ~T ();
    }
}