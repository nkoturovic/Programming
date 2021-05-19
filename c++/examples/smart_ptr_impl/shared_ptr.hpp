#ifndef SHARED_PTR
#define SHARED_PTR

#include <utility> // std::move

/* ---------------COPY-SWAP-IDIOM---------------------
 * Trebaju nam 3 stvari:
 * 1) copy constructor
 * 2) swap funkcija
 * 3) destructor (indirektno potreban)
 * operator= i move operator= se oslanjaju na copy 
 * constructor i na funkciju swap
-----------------------------------------------------
 * - implementiran je copy konstruktor
 * - move konstruktor se oslanja na swap
 * - operator= se oslanja na copy konstruktor i na swap
 * - move operator= se oslanja na swap */

namespace kotur {

template <typename T>
class shared_ptr {
private:
    T* m_raw_pointer = nullptr;
    long * m_use_count = nullptr;
    
public:
    shared_ptr(T*);
    shared_ptr(shared_ptr<T> const&);
    shared_ptr(shared_ptr<T> &&);
    ~shared_ptr();

    T* get() const noexcept;
    long use_count() const;
    T& operator*();

    T& operator=(shared_ptr<T>);
    T& operator=(shared_ptr<T> &&);
    T* operator->();

    template <typename U>
    friend void swap(shared_ptr<U> &lhs, shared_ptr<U> &rhs) noexcept;

    void swap(shared_ptr<T>&) noexcept;
};

template <typename U>
void swap(shared_ptr<U> &lhs, shared_ptr<U> &rhs) noexcept;

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr) {
    m_raw_pointer = ptr;
    if (ptr == nullptr)
        m_use_count = new long(0);
    else
        m_use_count = new long(1);
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> const& rhs) {
    m_raw_pointer = rhs.m_raw_pointer;
    m_use_count = rhs.m_use_count;
    *m_use_count = *m_use_count + 1;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> && rhs) {
    this->swap(rhs);
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (m_use_count != nullptr) {
        if (*m_use_count > 0)
            *m_use_count = *m_use_count - 1;

        if (*m_use_count <= 0) {
            if (m_raw_pointer != nullptr) { delete m_raw_pointer; }
            delete m_use_count;
        }
    } else if (m_use_count == nullptr && m_raw_pointer != nullptr) {
            delete m_raw_pointer;
    }
}

template <typename T>
T& shared_ptr<T>::operator*() {
    return * this->get();
}

template <typename T>
T* shared_ptr<T>::operator->() {
    return this->get();
}

template <typename T>
T& shared_ptr<T>::operator=(shared_ptr<T> rhs) {
    this->swap(rhs);
    return *(*this);
} 

template <typename T>
T& shared_ptr<T>::operator=(shared_ptr<T> && rhs) {
    this->swap(rhs);
    return *(*this);
} 

template <typename T>
T* shared_ptr<T>::get() const noexcept {
    return m_raw_pointer;
}

template <typename T>
long shared_ptr<T>::use_count() const {
    if (m_use_count != nullptr)
        return *m_use_count;
    else 
        return 0;
}

template <typename U>
void swap(shared_ptr<U> &lhs, shared_ptr<U> &rhs) noexcept {
    using std::swap;
    swap(lhs.m_raw_pointer, rhs.m_raw_pointer);
    swap(lhs.m_use_count, rhs.m_use_count);
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T> &rhs) noexcept {
    using kotur::swap;
    swap(*this, rhs);
}

template <typename T, typename...Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

} // ns kotur
#endif // SHARED_PTR
