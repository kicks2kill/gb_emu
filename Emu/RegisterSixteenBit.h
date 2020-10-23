/*
    Created by Orin in 2020
    All copyrights reserved.
*/

#ifndef REGISTERSIXTEENBIT_H
#define REGISTERSIXTEENBIT_H

#include "definitions.h"
#include "RegisterEightBit.h"

class RegisterSixteenBit
{
public:
    RegisterSixteenBit() {}
    void SetLow(uint8_t low);
    uint8_t GetLow() const;
    void SetHigh(uint8_t high);
    uint8_t GetHigh() const;
    RegisterEightBit* GetLowRegister();
    RegisterEightBit* GetHighRegister();
    void SetValue(uint16_t value);
    uint16_t GetValue() const;
    void Increment();
    void Decrement();

private:
    RegisterEightBit m_Low;
    RegisterEightBit m_High;
};

inline void RegisterSixteenBit::SetLow(uint8_t low)
{
    m_Low.SetValue(low);
}

inline uint8_t RegisterSixteenBit::GetLow() const 
{
    return m_Low.GetValue();
}

inline void RegisterSixteenBit::SetHigh(uint8_t high)
{
    m_Low.SetValue(high);
}

inline uint8_t RegisterSixteenBit::GetHigh() const 
{
    return m_High.GetValue();
}


inline RegisterEightBit* RegisterSixteenBit::GetHighRegister()
{
    return &m_High;
}


inline RegisterEightBit* RegisterSixteenBit::GetLowRegister()
{
    return &m_Low;
}

inline void RegisterSixteenBit::SetValue(uint16_t value)
{
    m_Low.SetValue((uint8_t) (value & 0xFF));
    m_High.SetValue((uint8_t) ((value >> 8) & 0xFF));
}

inline uint16_t RegisterSixteenBit::GetValue() const
{
    uint8_t high = m_High.GetValue();
    uint8_t low = m_Low.GetValue();

    return (high << 8) + low;
}

inline void RegisterSixteenBit::Increment()
{
    uint16_t value = this->GetValue();
    value++;
    this->SetValue(value);
}

inline void RegisterSixteenBit::Decrement()
{
    uint16_t value = this->GetValue();
    value--;
    this->SetValue(value);
}

#endif