#pragma once

#include "base_handle.h"
#include "../sdk.h"

// -------------------------------------------------------------------------------------------------- //
// Game-code CBaseHandle implementation.
// -------------------------------------------------------------------------------------------------- //

inline i_handle_entity* c_base_handle::get() const
{
    return csgo::entity_list->get_client_entity_from_handle(*this);
}

// -------------------------------------------------------------------------------------------------- //
// c_handle.
// -------------------------------------------------------------------------------------------------- //
template< class T >
class c_handle : public c_base_handle {
public:
    c_handle();
    c_handle(int iEntry, int iSerialNumber);
    c_handle(const c_base_handle& handle);
    c_handle(T* pVal);

    // The index should have come from a call to ToInt(). If it hasn't, you're in trouble.
    static c_handle<T> FromIndex(int index);

    T* get() const;
    void	set(const T* pVal);

    operator T* ();
    operator T* () const;

    bool	operator !() const;
    bool	operator==(T* val) const;
    bool	operator!=(T* val) const;
    const c_base_handle& operator=(const T* val);

    T* operator->() const;
};


// ----------------------------------------------------------------------- //
// Inlines.
// ----------------------------------------------------------------------- //

template<class T>
c_handle<T>::c_handle()
{
}


template<class T>
c_handle<T>::c_handle(int iEntry, int iSerialNumber)
{
    init(iEntry, iSerialNumber);
}


template<class T>
c_handle<T>::c_handle(const c_base_handle& handle)
    : c_base_handle(handle)
{
}


template<class T>
c_handle<T>::c_handle(T* pObj)
{
    term();
    set(pObj);
}


template<class T>
inline c_handle<T> c_handle<T>::FromIndex(int index)
{
    c_handle<T> ret;
    ret.m_Index = index;
    return ret;
}


template<class T>
inline T* c_handle<T>::get() const
{
    return (T*)c_base_handle::get();
}


template<class T>
inline c_handle<T>::operator T* ()
{
    return get();
}

template<class T>
inline c_handle<T>::operator T* () const
{
    return get();
}


template<class T>
inline bool c_handle<T>::operator !() const
{
    return !get();
}

template<class T>
inline bool c_handle<T>::operator==(T* val) const
{
    return get() == val;
}

template<class T>
inline bool c_handle<T>::operator!=(T* val) const
{
    return get() != val;
}

template<class T>
void c_handle<T>::set(const T* pVal)
{
   c_base_handle::set(reinterpret_cast<const i_handle_entity*>(pVal));
}

template<class T>
inline const c_base_handle& c_handle<T>::operator=(const T* val)
{
    set(val);
    return *this;
}

template<class T>
T* c_handle<T>::operator -> () const
{
    return set();
}