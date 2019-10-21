#ifndef SHARED_PTR
#define SHARED_PTR

#include <unordered_map>

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

    T* get();
    long use_count() const;
    T& operator*();

    T& operator=(shared_ptr<T> const&);
    T& operator=(shared_ptr<T> &&);
    T* operator->();
    void swap(shared_ptr<T>&) noexcept;
    void swap(shared_ptr<T>&&) noexcept;
};

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
    *this = rhs;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> && rhs) {
    *this = std::move(rhs);
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (m_use_count != nullptr) {
        if (m_use_count != 0)
            *m_use_count = *m_use_count - 1;
        else if (*m_use_count == 0 && m_raw_pointer != nullptr) {
            delete m_raw_pointer;
        }
    }
}

template <typename T>
T* shared_ptr<T>::get() {
    return m_raw_pointer;
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
T& shared_ptr<T>::operator=(shared_ptr<T> const& rhs) {
    m_raw_pointer = rhs.m_raw_pointer;
    m_use_count = rhs.m_use_count;
    *m_use_count = *m_use_count + 1;
    return *this->get();
} 

template <typename T>
T& shared_ptr<T>::operator=(shared_ptr<T> && rhs) {
    auto other = shared_ptr<T>(nullptr);
    other.swap(rhs);
    *this = other;
    return *(*this);
}

template <typename T>
long shared_ptr<T>::use_count() const {
    return *m_use_count;
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T> &rhs) noexcept {
    std::swap(m_raw_pointer, rhs.m_raw_pointer);
    std::swap(m_use_count, rhs.m_use_count);
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T> &&rhs) noexcept {
    m_raw_pointer = std::move(rhs.m_raw_pointer);
    m_use_count = std::move(rhs.m_use_count);
}

template <typename T, typename...Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(args...));
}

}
#endif // SHARED_PTR
