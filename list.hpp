#ifndef INCLUDE_LIST_WENNER__
#define INCLUDE_LIST_WENNER__

#include <iostream>
#include <initializer_list>
#include <cstddef>
#include "allocator.hpp"


namespace mystl {
    template <class T , class Alloc = mystl::Allocator<T>>
    class list{
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using allocator = Alloc;
        using const_value_type = const T;
        using size_type = size_t;
        using pointer = typename allocator::pointer;
        using const_pointer = typename allocator::const_pointer;

    private:
        class Node{
        friend class list;
        private:
            Node* pre;
            Node* next;
            pointer element;
        public:
            Node () : pre (nullptr) , next(nullptr) , element (nullptr){}
            Node (Node* _pre , Node* _next){
                this -> pre = _pre;
                this -> next = _next;
                this -> element = nullptr;
                _pre -> next = this;
                _next -> pre = this;
            }
            ~Node (){
                delete element;
            }
            value_type getElement (){
                return *this -> element;
            }
            void structureElement (pointer p){
                this -> element = p;
            }
            void setElement (const_reference value){
                *(this -> element) = value;
            }
            void setNext (Node* _next){
                this -> next = _next;
            }
            void setPre (Node* _pre){
                this -> pre = _pre;
            }
            Node* getNext (){
                return this -> next;
            }
            Node* getPre (){
                return this -> pre;
            }
        };
    public:
        using Pointer = Node*;

    private:
        Pointer _ldummy , _rdummy;
        Pointer head , tail;
        size_type _size;

    public:
        class iterator {
        friend class list;
        private:
            Pointer p;
            iterator (Pointer _p){
                this -> p = _p;
            }
        public:
            iterator () : p(nullptr){}
            ~iterator (){}

        public:
            iterator operator ++ (int){
                Pointer _p = this -> p;
                this -> p = _p -> getNext ();
                return _p;
            }
            iterator operator ++ (){
                this -> p = this -> p -> getNext ();
                return this -> p;
            }
            iterator operator -- (int){
               Pointer _p = this -> p;
                this -> p = _p -> getPre ();
                return _p;
            }
            iterator operator -- (){
                this -> p = this -> p -> getPre ();
                return this -> p;
            }
            reference operator * (){
                return *(this -> p -> element);
            }
            pointer operator -> (){
                return (this -> p) -> element;
            }
            bool operator == (iterator rsh){
                return (this -> p) == (rsh.p);
            }
            bool operator != (iterator rsh){
                return (this -> p) != (rsh.p);
            }
            iterator operator = (iterator rsh){
                this -> p = rsh.p;
                return *this;
            }
        };
        class const_iterator {
        friend class list;
        private:
            Pointer p;
            const_iterator (Pointer _p){
                this -> p = _p;
            }
        public:
            const_iterator () : p(nullptr){}
            ~const_iterator (){}

        public:
            const_iterator operator ++ (int){
                Pointer _p = this -> p;
                this -> p = _p -> getNext ();
                return _p;
            }
            const_iterator operator ++ (){
                this -> p = this -> p -> getNext ();
                return this -> p;
            }
            const_iterator operator -- (int){
               Pointer _p = this -> p;
                this -> p = _p -> getPre ();
                return _p;
            }
            const_iterator operator -- (){
                this -> p = this -> p -> getPre ();
                return this -> p;
            }
            value_type operator * (){
                return *(this -> p -> element);
            }
            pointer operator -> (){
                return (this -> p) -> element;
            }
            bool operator == (const_iterator rsh){
                return (this -> p) == (rsh.p);
            }
            bool operator != (const_iterator rsh){
                return (this -> p) != (rsh.p);
            }
            const_iterator operator = (const_iterator rsh){
                this -> p = rsh.p;
                return *this;
            }
        };
        class reverse_iterator {
        friend class list;
        private:
            Pointer p;
            reverse_iterator (Pointer _p){
                this -> p = _p;
            }
        public:
            reverse_iterator () : p(nullptr){}
            ~reverse_iterator (){}

        public:
            reverse_iterator operator -- (int){
                Pointer _p = this -> p;
                this -> p = _p -> getNext ();
                return _p;
            }
            reverse_iterator operator -- (){
                this -> p = this -> p -> getNext ();
                return this -> p;
            }
            reverse_iterator operator ++ (int){
               Pointer _p = this -> p;
                this -> p = _p -> getPre ();
                return _p;
            }
            reverse_iterator operator ++ (){
                this -> p = this -> p -> getPre ();
                return this -> p;
            }
            reference operator * (){
                return *(this -> p -> element);
            }
            pointer operator -> (){
                return (this -> p) -> element;
            }
            bool operator == (reverse_iterator rsh){
                return (this -> p) == (rsh.p);
            }
            bool operator != (reverse_iterator rsh){
                return (this -> p) != (rsh.p);
            }
            reverse_iterator operator = (reverse_iterator rsh){
                this -> p = rsh.p;
                return *this;
            }
        };
        class const_reverse_iterator {
        friend class list;
        private:
            Pointer p;
            const_reverse_iterator (Pointer _p){
                this -> p = _p;
            }
        public:
            const_reverse_iterator () : p(nullptr){}
            ~const_reverse_iterator (){}

        public:
            const_reverse_iterator operator -- (int){
                Pointer _p = this -> p;
                this -> p = _p -> getNext ();
                return _p;
            }
            const_reverse_iterator operator -- (){
                this -> p = this -> p -> getNext ();
                return this -> p;
            }
            const_reverse_iterator operator ++ (int){
               Pointer _p = this -> p;
                this -> p = _p -> getPre ();
                return _p;
            }
            const_reverse_iterator operator ++ (){
                this -> p = this -> p -> getPre ();
                return this -> p;
            }
            value_type operator * (){
                return *(this -> p -> element);
            }
            pointer operator -> (){
                return (this -> p) -> element;
            }
            bool operator == (const_reverse_iterator rsh){
                return (this -> p) == (rsh.p);
            }
            bool operator != (const_reverse_iterator rsh){
                return (this -> p) != (rsh.p);
            }
            const_reverse_iterator operator = (const_reverse_iterator rsh){
                this -> p = rsh.p;
                return *this;
            }
        };

    public:

        list ();
        explicit list(const allocator& alloc); //Default constructor. Constructs an empty container. If no allocator is supplied, allocator is obtained from a default-constructed instance.
        explicit list(size_type count, const T& value = T(),const allocator& alloc = allocator()); //Constructs the container with count copies of elements with value value.
        explicit list(size_type count); //Constructs the container with count default-inserted instances of T. No copies are made.
        // template<class InputIt>
        // list(InputIt first, InputIt last,const allocator& alloc = allocator());//Constructs the container with the contents of the range [first, last).
        explicit list(size_type count, const allocator& alloc = allocator());  //Copy constructor. Constructs the container with the copy of the contents of other. If alloc is not provided, allocator is obtained as if by calling 
        list(const list& other); //Move constructor. Constructs the container with the contents of other using move semantics. Allocator is obtained by move-construction from the allocator belonging to other.
        list(const list& other, const allocator& alloc); //Allocator-extended move constructor. Using alloc as the allocator for the new container, moving the contents from other; if alloc != other.get_allocator(), this results in an element-wise move.
        list(std::initializer_list<T> init,const allocator& alloc = allocator()); //Constructs the container with the contents of the initializer list init.

        ~list ();

        list& operator=(const list& other);
        list& operator=(list&& other);
        list& operator=(std::initializer_list<T> ilist);

        void assign(size_type count, const T& value);
        template<class InputIt>
        void assign(InputIt first, InputIt last);
        void assign(std::initializer_list<T> ilist);

        allocator get_allocator() const;

        reference front();
        const_reference front ()const;
        reference back();
        const_reference back ()const;

        //iterator begin();
        iterator begin() noexcept;
        //const_iterator begin() const;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;

        // iterator end();
        iterator end() noexcept;
        // const_iterator end() const;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;

        // reverse_iterator rbegin();
        reverse_iterator rbegin() noexcept;
        // const_reverse_iterator rbegin() const;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;

        // reverse_iterator rend();
        reverse_iterator rend() noexcept;
        // const_reverse_iterator rend() const;
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crend() const noexcept;

        // bool empty() const;
        bool empty() const noexcept;
        size_type size() const;
        size_type max_size() const;
        void clear();

        iterator insert(iterator pos, const T& value);
        iterator insert(const_iterator pos, const T& value);
        iterator insert(const_iterator pos, T&& value);
        void insert(iterator pos, size_type count, const T& value);
        iterator insert(const_iterator pos, size_type count, const T& value);
        // template< class InputIt >
        // void insert( iterator pos, InputIt first, InputIt last);
        template< class InputIt >
        iterator insert(const_iterator pos, InputIt first, InputIt last);
        iterator insert(const_iterator pos, std::initializer_list<T> ilist);

        // template< class... Args > 
        // iterator emplace( const_iterator pos, Args&&... args );

        iterator erase(iterator pos);
        iterator erase(const_iterator pos);
        iterator erase(iterator first, iterator last);
        iterator erase(const_iterator first, const_iterator last);


        void push_back(const T& value);
        void push_back(T&& value);

        void push_front(const T& value);
        void push_front(T&& value);

        // template< class... Args >
        // void emplace_back( Args&&... args );
        // template< class... Args >
        // reference emplace_back( Args&&... args );

        void pop_back();
        void pop_front();

        void resize(size_type count, T value = T());
        void resize(size_type count);
        void resize(size_type count, const value_type& value);


        void swap(list& other);

        void merge(list& other);
        void merge(list&& other);
        template <class Compare> 
        void merge(list& other, Compare comp);
        template <class Compare> 
        void merge(list&& other, Compare comp);

        // void splice(const_iterator pos, list& other);
        // void splice(const_iterator pos, list&& other);
        // void splice(const_iterator pos, list& other, const_iterator it);
        // void splice(const_iterator pos, list&& other, const_iterator it);
        // void splice(const_iterator pos, list& other,const_iterator first, const_iterator last);
        // void splice(const_iterator pos, list&& other,const_iterator first, const_iterator last);
        // void reverse();
        void reverse() noexcept;

        // void sort();
        // template<class Compare> 
        // void sort(Compare comp);

        // void swap(list<T,Alloc>& lhs,list<T,Alloc>& rhs);
    };
        template <class T , class Alloc>
        inline list<T,Alloc>::list () : _size (0) , head (nullptr) , tail(nullptr){
            this -> _ldummy = new Node ();
            this -> _rdummy = new Node ();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
        }

        template <class T , class Alloc>
        inline list<T , Alloc>::list(const allocator& alloc){
            this -> _size = 0;
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> head = nullptr;
            this -> tail = nullptr;
        }

        template <class T , class Alloc>
        inline list<T , Alloc>::list(size_type count, const T& value ,const allocator& alloc){
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = count;
            for (int i = 0;i < count;i++){
                Pointer tmp = new Node(_ldummy , _ldummy -> getNext ());
                tmp -> structureElement (alloc.allocate (1));
                tmp -> setElement (value);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();        
        }

        template<class T , class Alloc>
        inline list<T , Alloc>::list(size_type count){
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = count;
            for (int i = 0;i < count;i++){
                Pointer tmp = new Node(_ldummy , _ldummy -> getNext ());
                tmp -> structureElement (new value_type);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre (); 
        }

        // template<class InputIt>
        // inline list(InputIt first, InputIt last,const allocator& alloc = allocator());//Constructs the container with the contents of the range [first, last).

        template<class T , class Alloc>
        inline list<T , Alloc>::list(size_type count, const allocator& alloc){
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = count;
            for (int i = 0;i < count;i++){
                Pointer tmp = new Node(_ldummy , _ldummy -> getNext ());
                tmp -> structureElement (alloc.allocate(1));
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre (); 
        }

        template<class T , class Alloc>
        inline list<T,Alloc>::list(const list& other){
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            for (auto iter = other.begin ();iter != other.end ();iter++){
                Pointer tmp = new Node(_rdummy -> getPre () , _rdummy);
                tmp -> structureElement (new value_type);
                tmp -> setElement (*iter);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }

        template<class T , class Alloc>
        inline list<T,Alloc>::list(const list& other, const allocator& alloc){
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            for (auto iter = other.begin ();iter != other.end ();iter++){
                Pointer tmp = new Node(_rdummy -> getPre () , _rdummy);
                tmp -> structureElement (alloc.pointer);
                tmp -> setElement (*iter);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }

        template<class T , class Alloc>
        inline list<T,Alloc>::list(std::initializer_list<T> init,const allocator& alloc){
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = init.size ();
            for (auto iter = init.begin ();iter != init.end ();iter++){
                Pointer tmp = new Node(_rdummy -> getPre () , _rdummy);
                tmp -> structureElement (alloc.allocate(1));
                tmp -> setElement (*iter);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }

        template<class T , class Alloc>
        inline list<T,Alloc>::~list (){
            Pointer cur = _ldummy;
            while (cur){
                Pointer tmp = cur;
                cur = cur -> getNext ();
                delete tmp;
            }
        }

        template<class T , class Alloc>
        inline list<T , Alloc>& list<T,Alloc>::operator = (const list& other){
            this -> clear ();
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = other.size ();
            for (auto iter = other.begin ();iter != other.end ();iter++){
                Pointer tmp = new Node(_rdummy -> getPre () , _rdummy);
                tmp -> structureElement (new value_type);
                tmp -> setElement (*iter);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }

        template<class T , class Alloc>
        inline list<T , Alloc>& list<T,Alloc>::operator = (list&& other){
            this -> clear ();
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = other.size ();
            for (auto iter = other.begin ();iter != other.end ();iter++){
                Pointer tmp = new Node(_rdummy -> getPre () , _rdummy);
                tmp -> structureElement (new value_type);
                tmp -> setElement (*iter);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }

        template<class T , class Alloc>
        inline list<T , Alloc>& list<T,Alloc>::operator = (std::initializer_list<T> ilist){
            this -> clear ();
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = ilist.size ();
            for (auto iter = ilist.begin ();iter != ilist.end ();iter++){
                Pointer tmp = new Node(_rdummy -> getPre () , _rdummy);
                tmp -> structureElement (new value_type);
                tmp -> setElement (*iter);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }

        template<class T , class Alloc>
        inline void list<T,Alloc>::assign(size_type count, const T& value){
            this -> clear ();
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = count;
            for (int i = 0;i < count;i++){
                Pointer tmp = new Node(_ldummy , _ldummy -> getNext ());
                tmp -> structureElement (new value_type);
                tmp -> setElement (value);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre (); 
        }

        // template< class InputIt >
        // inline void assign(InputIt first, InputIt last);
        template<class T , class Alloc>
        inline void list<T,Alloc>::assign(std::initializer_list<T> ilist){
            this -> clear ();
            this -> _ldummy = new Node();
            this -> _rdummy = new Node();
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (_rdummy);
            this -> _rdummy -> setPre (_ldummy);
            this -> _rdummy -> setNext (nullptr);
            this -> _size = ilist.size ();
            for (auto iter = ilist.begin ();iter != ilist.end ();iter++){
                Pointer tmp = new Node(_ldummy , _ldummy -> getNext ());
                tmp -> structureElement (new value_type);
                tmp -> setElement (*iter);
            }
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre (); 
        }

        template<class T , class Alloc>
        inline typename list<T,Alloc>::allocator list<T,Alloc>::get_allocator() const{
            Alloc alloc;
            return alloc;
        }

        template<class T , class Alloc>
        inline typename list<T,Alloc>::reference list<T,Alloc>::front(){
            return *(this -> head);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_reference list<T,Alloc>::front ()const{
            return *(this -> head);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::reference list<T,Alloc>::back(){
            return *(this -> tail);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_reference list<T,Alloc>::back ()const{
            return *(this -> tail);
        }

        // template<class T , class Alloc>
        //inline iterator begin();
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::begin() noexcept{
            return iterator(this -> head);
        }
        // template<class T , class Alloc>
        // inline const_iterator begin() const;
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_iterator list<T,Alloc>::begin() const noexcept{
            return iterator(this -> head);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_iterator list<T,Alloc>::cbegin() const noexcept{
            return const_iterator(this -> head);
        }

        // template<class T , class Alloc>
        // inline iterator end();
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::end() noexcept{
            return iterator(this -> _rdummy);
        }

        // template<class T , class Alloc>
        // inline const_iterator end() const;
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_iterator list<T,Alloc>::end() const noexcept{
            return iterator(this -> _rdummy);
        }

        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_iterator list<T,Alloc>::cend() const noexcept{
            return const_iterator(this -> _rdummy);
        }

        // template<class T , class Alloc>
        // inline reverse_iterator rbegin();
        template<class T , class Alloc>
        inline typename list<T,Alloc>::reverse_iterator list<T,Alloc>::rbegin() noexcept{
            return reverse_iterator(this -> head);
        }
        // template<class T , class Alloc>
        // inline const_reverse_iterator rbegin() const;
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_reverse_iterator list<T,Alloc>::rbegin() const noexcept{
            return reverse_iterator (this -> head);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_reverse_iterator list<T,Alloc>::crbegin() const noexcept{
            return const_reverse_iterator (this -> head);
        }

        // template<class T , class Alloc>
        // inline reverse_iterator rend();
        template<class T , class Alloc>
        inline typename list<T,Alloc>::reverse_iterator list<T,Alloc>::rend() noexcept{
            return reverse_iterator(this -> _rdummy);
        }
        // template<class T , class Alloc>
        // inline const_reverse_iterator rend() const;
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_reverse_iterator list<T,Alloc>::rend() const noexcept{
            return reverse_iterator (this -> _rdummy);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::const_reverse_iterator list<T,Alloc>::crend() const noexcept{
            return const_reverse_iterator (this -> _rdummy);
        }

        // template<class T , class Alloc>
        // inline bool empty() const;
        template<class T , class Alloc>
        inline bool list<T,Alloc>::empty() const noexcept{
            return (this -> size () == 0);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::size_type list<T,Alloc>::size() const{
            return this -> _size;
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::size_type list<T,Alloc>::max_size() const{
            // return 768614336404564650;
        }
        template<class T , class Alloc>
        inline void list<T,Alloc>::clear(){
            ~list ();
            this -> _size = 0;
        }

        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::insert(iterator pos, const T& value){
            if (this -> size () == 0){
                this -> push_back (value);
                return head;
            }
            Pointer lsh = pos.p -> getPre ();
            Pointer rsh = pos.p;
            Pointer t = new Node (lsh , rsh);
            t -> structureElement (new value_type (value));
            this -> _size++;
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
            return iterator (t);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::insert(const_iterator pos, const T& value){
            if (this -> size () == 0){
                this -> push_back (value);
                return head;
            }
            Pointer lsh = pos.p -> getPre ();
            Pointer rsh = pos.p;
            Pointer t = new Node (lsh , rsh);
            t -> structureElement (new value_type (value));
            this -> _size++;
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
            return iterator (t);
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::insert(const_iterator pos, T&& value){
            if (this -> size () == 0){
                this -> push_back (value);
                return head;
            }
            Pointer lsh = pos.p -> getPre ();
            Pointer rsh = pos.p;
            Pointer t = new Node (lsh , rsh);
            t -> structureElement (new value_type (value));
            this -> _size++;
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
            return iterator (t);
        }
        template<class T , class Alloc>
        inline void list<T,Alloc>::insert(iterator pos, size_type count, const T& value){
            if (this -> size () == 0){
                for (int i = 0;i < count;i++)
                    this -> push_back (value);
                return head;
            }
            this -> _size = this -> size() + count;
            while (count--){
                Pointer lsh = pos.p -> getPre ();
                Pointer rsh = pos.p;
                Pointer tmp = new Node (lsh , rsh);
                tmp -> structureElement (new value_type (value));
            }
            this -> head = this -> _ldummy -> getNext ();
            this -> tail = this -> _rdummy -> getPre ();
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::insert(const_iterator pos, size_type count, const T& value){
            this -> _size = this -> size() + count;
            while (count--){
                Pointer lsh = pos.p -> getPre ();
                Pointer rsh = pos.p;
                Pointer tmp = new Node (lsh , rsh);
                tmp -> structureElement (new value_type (value));
            }
            this -> head = this -> _ldummy -> getNext ();
            this -> tail = this -> _rdummy -> getPre ();
        }
        // template<class T , class Alloc>
        // template< class InputIt >
        // template<class T , class Alloc>
        // inline void insert( iterator pos, InputIt first, InputIt last);
        // template <class T , class Alloc>
        // template <class InputIt>
        // inline typename list<T,Alloc>::iterator list<T,Alloc>::insert(const_iterator pos, InputIt first, InputIt last){
            
        // }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::insert(const_iterator pos, std::initializer_list<T> ilist){
            this -> _size = this -> size() + ilist.size ();
            for (auto iter = ilist.begin ();iter != ilist.end ();iter++){
                Pointer lsh = pos.p -> getPre ();
                Pointer rsh = pos.p;
                Pointer tmp = new Node (lsh , rsh);
                tmp -> structureElement (new value_type (*iter));
            }
            this -> head = this -> _ldummy -> getNext ();
            this -> tail = this -> _rdummy -> getPre ();
        }

        // template<class T , class Alloc>
        // inline template< class... Args > 
        // template<class T , class Alloc>
        // inline iterator emplace( const_iterator pos, Args&&... args );

        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::erase(iterator pos){
            this -> _size--;
            pos.p -> getPre () -> setNext (pos.p -> getNext ());
            pos.p -> getNext () -> setPre (pos.p -> getPre ());
            if (this -> size () == 0){
                this -> head = nullptr;
                this -> end = nullptr;
                return this -> end ();
            }
            else {
                this -> head = this -> _ldummy -> getNext ();
                this -> tail = this -> _rdummy -> getPre ();
                Pointer tmp = pos.p -> getNext ();
                delete pos.p;
                return iterator (tmp);
            } 
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::erase(const_iterator pos){
            this -> _size--;
            pos.p -> getPre () -> setNext (pos.p -> getNext ());
            pos.p -> getNext () -> setPre (pos.p -> getPre ());
            if (this -> size () == 0){
                this -> head = nullptr;
                this -> end = nullptr;
                return this -> end ();
            }
            else {
                this -> head = this -> _ldummy -> getNext ();
                this -> tail = this -> _rdummy -> getPre ();
                Pointer tmp = pos.p -> getNext ();
                delete pos.p;
                return iterator (tmp);
            }
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::erase(iterator first, iterator last){
            while (first != end){
                Pointer tmp = first.p;
                first++;
                tmp -> getNext () -> setNext (tmp -> getNext ());
                tmp -> getPre () -> setPre (tmp -> getPre ());
                delete tmp;
                this -> _size--;
            }
            if (this -> size () == 0){
                this -> head = nullptr;
                this -> end = nullptr;
                return this -> end ();
            }
            else {
                this -> head = this -> _ldummy -> getNext ();
                this -> tail = this -> _rdummy -> getPre ();
                return end;
            }
            return end;
        }
        template<class T , class Alloc>
        inline typename list<T,Alloc>::iterator list<T,Alloc>::erase(const_iterator first, const_iterator last){
            while (first != end){
                Pointer tmp = first.p;
                first++;
                tmp -> getNext () -> setNext (tmp -> getNext ());
                tmp -> getPre () -> setPre (tmp -> getPre ());
                delete tmp;
                this -> _size--;
            }
            if (this -> size () == 0){
                this -> head = nullptr;
                this -> end = nullptr;
                return this -> end ();
            }
            else {
                this -> head = this -> _ldummy -> getNext ();
                this -> tail = this -> _rdummy -> getPre ();
                return end;
            }
            return end;
        }


        template<class T , class Alloc>
        inline void list<T,Alloc>::push_back(const T& value){
            Pointer tmp = new Node (_rdummy -> getPre () , _rdummy);
            tmp -> element -> structureElement (new value_type);
            tmp -> element -> setElement (value);
            this -> _size++;
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }
        template<class T , class Alloc>
        inline void list<T,Alloc>::push_back(T&& value){
            Pointer tmp = new Node (_rdummy -> getPre () , _rdummy);
            tmp -> element -> structureElement (new value_type);
            tmp -> element -> setElement (value);
            this -> _size++;
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }

        template<class T , class Alloc>
        inline void list<T,Alloc>::push_front(const T& value){
            Pointer tmp = new Node (_ldummy , _ldummy -> getNext ());
            tmp -> structureElement (new value_type);
            tmp -> setElement (value);
            this -> _size++;
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }
        template<class T , class Alloc>
        inline void list<T,Alloc>::push_front( T&& value ){
            Pointer tmp = new Node (_ldummy , _ldummy -> getNext ());
            tmp -> structureElement (new value_type);
            tmp -> setElement (value);
            this -> _size++;
            this -> head = _ldummy -> getNext ();
            this -> tail = _rdummy -> getPre ();
        }

        // template<class T , class Alloc>
        // template< class... Args >
        // template<class T , class Alloc>
        // inline void emplace_back( Args&&... args );
        // template<class T , class Alloc>
        // inline template< class... Args >
        // template<class T , class Alloc>
        // inline reference emplace_back( Args&&... args );

        template<class T , class Alloc>
        inline void list<T,Alloc>::pop_back(){
            this -> tail -> getNext () -> setPre (this -> getPre ());
            this -> tail -> getPre () -> setNext (this -> getNext ());
            this -> _size--;
            Pointer t = this -> tail;
            this -> tail = t -> getPre ();
            delete t;
            if (this -> size() == 0){
                this -> head = nullptr;
                this -> tail = nullptr;
            }
            else {
                this -> head = _ldummy -> getNext ();
                this -> tail = _rdummy -> getPre ();
            }
        }
        template<class T , class Alloc>
        inline void list<T,Alloc>::pop_front(){
            this -> head -> getNext () -> setPre (this -> head -> getPre ());
            this -> head -> getPre () -> setNext (this -> head -> getNext ());
            this -> _size--;
            Pointer t = this -> head;
            this -> head = t -> getNext ();
            delete t;
            if (this -> size () == 0){
                this -> head = nullptr;
                this -> tail = nullptr;
            }
            else {
                this -> head = this -> _ldummy -> getNext ();
                this -> tail = this -> _rdummy -> getPre ();
            }
        }

        // template<class T , class Alloc>
        // inline void list<T,Alloc>::resize(size_type count, T value){

        // }
        // template<class T , class Alloc>
        // inline void list<T,Alloc>::resize(size_type count){

        // }
        // template<class T , class Alloc>
        // inline void list<T,Alloc>::resize(size_type count, const value_type& value){
            
        // }

        template<class T , class Alloc>
        inline void list<T,Alloc>::swap(list& other){
            size_type size = this -> size ();
            this -> _size = other.size ();
            other._size = size;

            Pointer tmp = this -> _ldummy;
            this -> _ldummy = other._ldummy;
            other._ldummy = tmp;

            tmp = this -> _rdummy;
            this -> _rdummy = other._rdummy;
            other._rdummy = tmp;

            tmp = this -> head;
            this -> head = other.head;
            other.head = tmp;

            tmp = this -> tail;
            this -> tail = other.tail;
            other.tail = tmp;
        }

        template<class T , class Alloc>
        inline void list<T,Alloc>::merge(list& other){
            while (other.size ()){
                Pointer tmp = other.head;
                tmp -> getPre () -> setNext (tmp -> getNext ());
                tmp -> getNext () -> setPre (tmp -> getPre ());
                other.head = other._ldummy -> getNext ();
                other._size--;

                this -> tail -> getNext () -> setPre (tmp);
                this -> tail -> setNext (tmp);
                tmp -> setPre (this -> tail);
                tmp -> setNext (this -> _rdummy);
                this -> _size++;
                this -> tail = this -> tail -> getNext ();
            }
        }
        template<class T , class Alloc>
        inline void list<T,Alloc>::merge(list&& other){
            while (other.size ()){
                Pointer tmp = other.head;
                tmp -> getPre () -> setNext (tmp -> getNext ());
                tmp -> getNext () -> setPre (tmp -> getPre ());
                other.head = other._ldummy -> getNext ();
                other._size--;

                this -> tail -> getNext () -> setPre (tmp);
                this -> tail -> setNext (tmp);
                tmp -> setPre (this -> tail);
                tmp -> setNext (this -> _rdummy);
                this -> _size++;
                this -> tail = this -> tail -> getNext ();
            }
        }
        template <class T,class Alloc>
        template <class Compare> 
        inline void list<T,Alloc>::merge(list& other, Compare comp){
            this -> _size += other.size ();
            auto iter1 = this -> begin ();
            auto iter2 = other.begin ();
            while (iter2 != other.end () && iter1 != this -> end ()){
                if (comp(iter1.p -> getElement () , iter2.p -> getElement ()) == false){
                    auto tmp = iter2;
                    iter2++;
                    tmp.p -> setPre (iter1.p -> getPre ());
                    tmp.p -> setNext (iter2.p);
                    iter1.p -> getPre () -> setNext (tmp.p);
                    iter1.p -> setPre (tmp.p);
                    other._size--;
                }
                else {
                    iter1++;
                }
            }
            if (iter1 == this -> end () && other.size () != 0){
                this -> tail -> setNext (other.head);
                other.head -> setPre (this -> tail);
                this -> _rdummy -> setPre (other.tail);
                this -> tail = other.tail ();
                this -> tail -> setNext (this -> _rdummy);
                other._size = 0;
            }
        }
        template <class T,class Alloc>
        template <class Compare> 
        inline void list<T,Alloc>::merge(list&& other, Compare comp){

        }

        // template<class T , class Alloc>
        // inline void list<T,Alloc>::splice(const_iterator pos, list& other){

        // }
        // template<class T , class Alloc>
        // inline void splice(const_iterator pos, list&& other);
        // template<class T , class Alloc>
        // inline void list<T,Alloc>::splice(const_iterator pos, list& other, const_iterator it){

        // }
        // template<class T , class Alloc>
        // inline void splice(const_iterator pos, list&& other, const_iterator it);
        // template<class T , class Alloc>
        // inline void list<T,Alloc>::splice(const_iterator pos, list& other,const_iterator first, const_iterator last){

        // }
        // template<class T , class Alloc>
        // inline void splice(const_iterator pos, list&& other,const_iterator first, const_iterator last);
        // template<class T , class Alloc>
        // inline void reverse();
        template<class T , class Alloc>
        inline void list<T,Alloc>::reverse() noexcept{
            Pointer t = this -> _ldummy;
            this -> _ldummy = this -> _rdummy;
            this -> _rdummy = t;
            this -> _ldummy -> setPre (nullptr);
            this -> _ldummy -> setNext (head);
            this -> _ldummy -> setPre (tail);
            this -> _rdummy -> setNext (nullptr);
            t = this -> head;
            this -> head = this -> tail;
            this -> tail = t;
            Pointer p = this -> head;
            while (p != this -> tail){
                Pointer tmp = p -> getPre ();
                p -> setPre (p -> getNext ());
                p -> setNext (tmp);

                p = p -> getNext ();
            }
            Pointer tmp = p -> getPre ();
            p -> setPre (p -> getNext ());
            p -> setNext (tmp);

            p = p -> getPre ();
        }

        // template<class T , class Alloc>
        // inline void list<T,Alloc>::sort(){

        // }
        // template<class T , class Alloc>
        // template<class Compare>
        // inline void list<T,Alloc>::sort(Compare comp){

        // }

        // template< class T, class Alloc >
        // inline void list<T,Alloc>::swap(list<T,Alloc>& lhs,list<T,Alloc>& rhs){

        // }
}
#endif //INCLUDE_LIST_WENNER__