#pragma once

#include "../interfaces/handle_entity.h"

#define NUM_ENT_ENTRY_BITS         (11 + 2)
#define NUM_ENT_ENTRIES            (1 << NUM_ENT_ENTRY_BITS)
#define INVALID_EHANDLE_INDEX       0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS        16 // (32 - NUM_ENT_ENTRY_BITS)
#define NUM_SERIAL_NUM_SHIFT_BITS (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK             (( 1 << NUM_SERIAL_NUM_BITS) - 1)

class i_handle_entity;

class c_base_handle
{
public:
    c_base_handle();
    c_base_handle(const c_base_handle& other);
    c_base_handle(unsigned long value);
    c_base_handle(int iEntry, int iSerialNumber);

    void init(int iEntry, int iSerialNumber);
    void term();

    // Even if this returns true, Get() still can return return a non-null value.
    // This just tells if the handle has been initted with any values.
    bool is_valid() const;

    int get_entry_index() const;
    int get_serial_number() const;

    int to_int() const;
    bool operator !=(const c_base_handle& other) const;
    bool operator ==(const c_base_handle& other) const;
    bool operator ==(const i_handle_entity* pEnt) const;
    bool operator !=(const i_handle_entity* pEnt) const;
    bool operator <(const c_base_handle& other) const;
    bool operator <(const i_handle_entity* pEnt) const;

    // Assign a value to the handle.
    const c_base_handle& operator=(const i_handle_entity* pEntity);
    const c_base_handle& set(const i_handle_entity* pEntity);

    // Use this to dereference the handle.
    // Note: this is implemented in game code (ehandle.h)
    i_handle_entity* get() const;

protected:
    // The low NUM_SERIAL_BITS hold the index. If this value is less than MAX_EDICTS, then the entity is networkable.
    // The high NUM_SERIAL_NUM_BITS bits are the serial number.
    unsigned long	m_Index;
};

inline c_base_handle::c_base_handle()
{
    m_Index = INVALID_EHANDLE_INDEX;
}

inline c_base_handle::c_base_handle(const c_base_handle& other)
{
    m_Index = other.m_Index;
}

inline c_base_handle::c_base_handle(unsigned long value)
{
    m_Index = value;
}

inline c_base_handle::c_base_handle(int iEntry, int iSerialNumber)
{
    init(iEntry, iSerialNumber);
}

inline void c_base_handle::init(int iEntry, int iSerialNumber)
{
    m_Index = iEntry | (iSerialNumber << NUM_ENT_ENTRY_BITS);
}

inline void c_base_handle::term()
{
    m_Index = INVALID_EHANDLE_INDEX;
}

inline bool c_base_handle::is_valid() const
{
    return m_Index != INVALID_EHANDLE_INDEX;
}

inline int c_base_handle::get_entry_index() const
{
    return m_Index & ENT_ENTRY_MASK;
}

inline int c_base_handle::get_serial_number() const
{
    return m_Index >> NUM_ENT_ENTRY_BITS;
}

inline int c_base_handle::to_int() const
{
    return (int)m_Index;
}

inline bool c_base_handle::operator !=(const c_base_handle& other) const
{
    return m_Index != other.m_Index;
}

inline bool c_base_handle::operator ==(const c_base_handle& other) const
{
    return m_Index == other.m_Index;
}

inline bool c_base_handle::operator ==(const i_handle_entity* pEnt) const
{
    return get() == pEnt;
}

inline bool c_base_handle::operator !=(const i_handle_entity* pEnt) const
{
    return get() != pEnt;
}

inline bool c_base_handle::operator <(const c_base_handle& other) const
{
    return m_Index < other.m_Index;
}

inline bool c_base_handle::operator <(const i_handle_entity* pEntity) const
{
    unsigned long otherIndex = (pEntity) ? pEntity->get_ref_ehandle().m_Index : INVALID_EHANDLE_INDEX;
    return m_Index < otherIndex;
}

inline const c_base_handle& c_base_handle::operator=(const i_handle_entity* pEntity)
{
    return set(pEntity);
}

inline const c_base_handle& c_base_handle::set(const i_handle_entity* pEntity)
{
    if (pEntity) {
        *this = pEntity->get_ref_ehandle();
    }
    else {
        m_Index = INVALID_EHANDLE_INDEX;
    }

    return *this;
}