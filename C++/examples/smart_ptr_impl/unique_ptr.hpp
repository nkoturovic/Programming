#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <utility> // std::move

namespace kotur {

template <typename T>
class unique_ptr {
private:
    T* m_raw_pointer = nullptr;
    
public:
    unique_ptr(T*);
    unique_ptr(unique_ptr<T> const&) = delete; // obrisan copy konsruktor
    unique_ptr(unique_ptr<T> &&); // samo move moze umesto copy
    ~unique_ptr();

    T* get() const noexcept;
    T& operator*();

    T& operator=(const unique_ptr<T>&) = delete;
    T& operator=(unique_ptr<T> &&);
    T* operator->();

    template <typename U>
    friend void swap(unique_ptr<U> &lhs, unique_ptr<U> &rhs) noexcept;

    void swap(unique_ptr<T>&) noexcept;
};

template <typename U>
void swap(unique_ptr<U> &lhs, unique_ptr<U> &rhs) noexcept;

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr) {
    m_raw_pointer = ptr;
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T> && rhs) {
    this->swap(rhs);
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (m_raw_pointer != nullptr)
        delete m_raw_pointer;
}

template <typename T>
T* unique_ptr<T>::get() const noexcept {
    return m_raw_pointer;
}

template <typename T>
T& unique_ptr<T>::operator*() {
    return * this->get();
}

template <typename T>
T* unique_ptr<T>::operator->() {
    return this->get();
}

template <typename T>
T& unique_ptr<T>::operator=(unique_ptr<T> && rhs) {
    this->swap(rhs);
    return *(*this);
} 

template <typename U>
void swap(unique_ptr<U> &lhs, unique_ptr<U> &rhs) noexcept {
    using std::swap;
    swap(lhs.m_raw_pointer, rhs.m_raw_pointer);
}

template <typename T>
void unique_ptr<T>::swap(unique_ptr<T> &rhs) noexcept {
    using kotur::swap;
    swap(*this, rhs);
}

template <typename T, typename...Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(args...));
}

} // ns kotur
#endif // UNIQUE_PTR
