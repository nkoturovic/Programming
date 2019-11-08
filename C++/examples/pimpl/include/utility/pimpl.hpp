#ifndef RS_PIMPL_H
#define RS_PIMPL_H 

#include <experimental/propagate_const>
#include <memory>

namespace rs::utility {

template<typename T>
class pimpl {
private:
    std::experimental::propagate_const<std::unique_ptr<T>> m_uptr_to_impl;
public:

    template<typename ...Args> pimpl( Args&& ... );
    pimpl();

    pimpl(const pimpl &other);
    pimpl(pimpl &&other);

    pimpl& operator=(const pimpl &other);
    pimpl& operator=(pimpl &&other);

    virtual ~pimpl();

    T* get();
    T* operator->();
    T& operator*();

    const T* get() const;
    const T* operator->() const;
    const T& operator*() const;

    template <typename U>
    friend void swap(pimpl<U> &lhs, pimpl<U> &rhs) noexcept;

    void swap(pimpl<T>&) noexcept;
 };

template<typename T>
pimpl<T>::pimpl() : m_uptr_to_impl{nullptr} { }
 
template<typename T>
template<typename ...Args>
pimpl<T>::pimpl( Args&& ...args )
    : m_uptr_to_impl(std::forward<Args>(args)...) { }

template<typename T>
pimpl<T>::pimpl(const pimpl &other) : m_uptr_to_impl(other->clone()) {}

template<typename T>
pimpl<T>::pimpl(pimpl &&other) {
    m_uptr_to_impl = std::move(other.m_uptr_to_impl);
}

template<typename T>
pimpl<T>& pimpl<T>::operator=(const pimpl<T> &other) { 
    pimpl<T> tmp(other);
    this->swap(tmp);
    return *this;
}

template<typename T>
pimpl<T>& pimpl<T>::operator=(pimpl<T> &&other) { 
    pimpl<T> tmp(std::move(other));
    tmp.swap(*this);
    return *this;
}
 
template<typename T>
pimpl<T>::~pimpl() = default;

template<typename T>
T* pimpl<T>::get() { return m_uptr_to_impl.get(); }

template<typename T>
const T* pimpl<T>::get() const { return m_uptr_to_impl.get(); }
 
template<typename T>
T* pimpl<T>::operator->() { return this->get(); }

template<typename T>
const T* pimpl<T>::operator->() const { return this->get(); }
 
template<typename T>
T& pimpl<T>::operator*() { return *this->get(); }

template<typename T>
const T& pimpl<T>::operator*() const { return *this->get(); }

template <typename T>
void swap(pimpl<T> &lhs, pimpl<T> &rhs) noexcept {
    using std::swap;
    swap(lhs.m_uptr_to_impl, rhs.m_uptr_to_impl);
}

template <typename T>
void pimpl<T>::swap(pimpl<T> &rhs) noexcept {
    using rs::utility::swap;
    swap(*this, rhs);
}

} // namespace rs

#endif // RS_PIMPL_H
