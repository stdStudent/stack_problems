#ifndef STACK_AIDES_H
#define STACK_AIDES_H

#ifdef enable_comptime
#define comptime constexpr
#else
#define comptime
#endif

#if ((defined(_MSVC_LANG) && _MSVC_LANG < 201703L) || __cplusplus < 201703L)
#define nodiscard
#elif ((defined(_MSVC_LANG) && _MSVC_LANG == 201703L) || __cplusplus == 201703L)
#define nodiscard(name) [[nodiscard]]
#else
#define nodiscard(name) [[nodiscard(name)]]
#endif

#include <iostream>
#include <string>
#include <limits>

template <class T, size_t capacity_limit>
class sizeRestrictedAlloc {
public:
    // type definitions
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    // rebind allocator to type U
    template <class U>
    struct rebind {
        typedef sizeRestrictedAlloc<U, capacity_limit> other;
    };

    // return address of values
    pointer address (reference value) const
    {
        return &value;
    }

    const_pointer address (const_reference value) const
    {
        return &value;
    }

    /* constructors and destructor
     * - nothing to do because the allocator has no state
     */
    sizeRestrictedAlloc() = default;

    sizeRestrictedAlloc(const sizeRestrictedAlloc&) = default;

    template <class U>
    explicit constexpr sizeRestrictedAlloc (const sizeRestrictedAlloc<U, capacity_limit>&) noexcept { } // `= default`

    ~sizeRestrictedAlloc() = default;

    // return maximum number of elements that can be allocated
    [[nodiscard]] size_type max_size () const noexcept
    {
        /* Default implementation. */
        //return std::numeric_limits<std::size_t>::max() / sizeof(T);

        /* Custom implementation. */
        return capacity_limit;
    }

    // allocate but don't initialize num elements of type T
    nodiscard("sizeRestrictedAlloc") pointer allocate (size_type num, const void* hint = nullptr) {
        //static_assert(!(num > std::size_t(-1) / sizeof(T)));

        pointer ret;

        // print message and allocate memory with global new
        std::cerr << "allocate " << num << " element(s)"
                  << " of size " << sizeof(T) << std::endl;
        if (num > capacity_limit)
            ret = (pointer)(::operator new(capacity_limit * sizeof(T)));
        else
            ret = (pointer)(::operator new(num * sizeof(T)));
        std::cerr << " allocated at: " << (void*)ret << std::endl;

        return ret;
    }

    // initialize elements of allocated storage p with value
    void construct (pointer p, const T& value)
    {
        // initialize memory with placement new
        new((void*)p)T(value);
    }

    // destroy elements of initialized storage p
    void destroy (pointer p)
    {
        // destroy objects by calling their destructor
        p->~T();
    }

    // deallocate storage p of deleted elements
    void deallocate (pointer p, size_type num)
    {
        //static_assert(!(num > std::size_t(-1) / sizeof(T)));

        #if ((defined(_MSVC_LANG) && _MSVC_LANG < 201703L) || __cplusplus < 201703L)

        /* Old implementation: global delete. */
        std::cerr << "deallocate " << num << " element(s)"
                  << " of size " << sizeof(T)
                  << " at: " << (void*)p << std::endl;

        ::operator delete((void*)p);

        #else

        /* New implementation, const evaluation. */
        if constexpr (alignof(T) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
            return ::operator delete(p, num * sizeof(T), static_cast<std::align_val_t>(alignof(T)));
        else
            return ::operator delete(p, num * sizeof(T));

        #endif
    }
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2, size_t capacity_limit>
constexpr bool operator== (const sizeRestrictedAlloc<T1, capacity_limit>&,
                           const sizeRestrictedAlloc<T2, capacity_limit>&) noexcept
{
    return true;
}

template <class T1, class T2, size_t capacity_limit>
constexpr bool operator!= (const sizeRestrictedAlloc<T1, capacity_limit>&,
                           const sizeRestrictedAlloc<T2, capacity_limit>&) noexcept
{
    return false;
}

template<typename T>
class sizeRestrictedVector {
private:
    T* arr = nullptr;
    size_t current_capacity;
    size_t elems_cnt;
    const size_t default_capacity = 2;
    size_t max_capacity{};

public:
    explicit sizeRestrictedVector(size_t limit) {
        arr = new T[default_capacity];
        current_capacity = default_capacity;
        max_capacity = limit;
        elems_cnt = 0;
    };

    ~sizeRestrictedVector() {
        delete[] arr;
    }

    void push_back(const T& data);
    void push_back(T&& data);
    void pop_back();

    [[nodiscard]] constexpr bool empty() const;
    [[nodiscard]] constexpr size_t size() const;
    [[nodiscard]] constexpr size_t capacity() const;
    T &operator[](size_t pos);
};

template<typename T>
void sizeRestrictedVector<T>::push_back(const T &data) {
    if (elems_cnt == max_capacity)
        throw std::out_of_range("No more capacity reserved.");

    if (elems_cnt < current_capacity) {
        *(arr + elems_cnt) = data;
        elems_cnt++;
    } else {
        size_t new_size;
        if (current_capacity * 2 < max_capacity)
            new_size = current_capacity * 2;
        else
            new_size = max_capacity;

        auto tmp_arr = new T[new_size];
        current_capacity = new_size;

        for (int i = 0; i < elems_cnt; i++) {
            tmp_arr[i] = arr[i];
        }

        delete[] arr;
        arr = tmp_arr;

        *(arr + elems_cnt) = data;
        elems_cnt++;
    }
}

template<typename T>
void sizeRestrictedVector<T>::push_back(T&& data) {
    if (elems_cnt == max_capacity)
        throw std::out_of_range("No more capacity reserved.");

    if (elems_cnt < current_capacity) {
        *(arr + elems_cnt) = data;
        elems_cnt++;
    } else {
        size_t new_size;
        if (current_capacity * 2 < max_capacity)
            new_size = current_capacity * 2;
        else
            new_size = max_capacity;

        auto tmp_arr = new T[new_size];
        current_capacity = new_size;

        for (int i = 0; i < elems_cnt; i++) {
            tmp_arr[i] = arr[i];
        }

        delete[] arr;
        arr = tmp_arr;

        *(arr + elems_cnt) = data;
        elems_cnt++;
    }
}

template<typename T>
T &sizeRestrictedVector<T>::operator[](size_t pos) {
    if (pos <= elems_cnt)
        return *(this->arr + pos);
    else
        throw std::out_of_range("Out of bounds element access.");
}

template<typename T>
constexpr size_t sizeRestrictedVector<T>::size() const {
    return elems_cnt;
}

template<typename T>
constexpr size_t sizeRestrictedVector<T>::capacity() const {
    return current_capacity;
}

template<typename T>
constexpr bool sizeRestrictedVector<T>::empty() const {
    return elems_cnt == 0;
}

template<typename T>
void sizeRestrictedVector<T>::pop_back() {
    if (empty())
        return;
    elems_cnt--;
}

#endif //STACK_AIDES_H
