/*
    Created by Orin in 2020
    All copyrights reserved.
*/

#ifndef REGISTEREIGHTBIT_H
#define REGISTEREIGHTBIT_H

#include "definitions.h"

class RegisterEightBit
{
public:
    RegisterEightBit() {}
    void SetValue(uint8_t value);
    uint8_t GetValue() const;
    void Increment();
    void Decrement();

private:
    uint8_t m_Value;
};

inline void RegisterEightBit::SetValue(uint8_t value)
{
    m_Value = value;
}

inline uint8_t RegisterEightBit::GetValue() const
{
    return m_Value;
}

inline void RegisterEightBit::Increment()
{
    m_Value++;
}

inline void RegisterEightBit::Decrement()
{
    m_Value--;
}

#endif