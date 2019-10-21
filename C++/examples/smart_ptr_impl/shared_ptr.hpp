#ifndef SHARED_PTR
#define SHARED_PTR

/* - implementirani su copy i move konstruktor
 * - operator= se oslanja na copy konstruktor i na swap
 * - move operator= se oslanja na move konstruktor i na swap */
 
/* TODO - Proveriti tacnost ovih iskaza */
/* - swap se oslanja na operator=, pa se i
 *   neposredno oslanja na copy konstruktor
 * - swap i operator= uzajamno korite jedan drugog
 * ali se operator= oslanja i na copy konstruktor i
 * odatle dolazi do konacnog izlaska iz uzajamne rekurzije */

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
    m_raw_pointer = rhs.m_raw_pointer;
    m_use_count = rhs.m_use_count;
    *m_use_count = *m_use_count + 1;
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> && rhs) {
    m_raw_pointer = rhs.m_raw_pointer;
    m_use_count = rhs.m_use_count;

    rhs.m_raw_pointer = nullptr;
    rhs.m_use_count = nullptr;
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
    shared_ptr<T> tmp(rhs);
    this->swap(tmp);
    return *(*this);
} 

template <typename T>
long shared_ptr<T>::use_count() const {
    if (m_use_count != nullptr)
        return *m_use_count;
    else 
        return 0;
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T> &rhs) noexcept {
    shared_ptr<T> tmp(rhs);
    rhs = *this;
    *this = tmp;
}

template <typename T, typename...Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(args...));
}

} // ns kotur
#endif // SHARED_PTR
