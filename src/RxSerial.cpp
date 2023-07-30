#include "RxSerial.h"

RxSerial::RxSerial(int comPort)
{
    switch (comPort)
    {
    case 0:
        m_pSerial = &Serial;
        break;
    case 1:
        m_pSerial = &Serial1;
        break;
    case 2:
        m_pSerial = &Serial2;
        break;

    default:
        m_pSerial = &Serial;
        break;
    }
}

void RxSerial::Init()
{
    m_pSerial->begin(9600, SERIAL_8O2);
}

uint16_t RxSerial::Getchar()
{
    if (m_pSerial->available())
    {
        uint16_t c = m_pSerial->read() | 0x100;
        // 9th bit emulation, check for sequence 0xfe, 0xff, 0x7e --> first ex packet after startup will not be decoded
        if ((c & 0x00ff) == 0x007e && (c_minus1 & 0x00ff) == 0x00ff)
        {
            c_minus2 &= ~0x100;
            c_minus1 &= ~0x100;
            c &= ~0x100;
        }

        if ((c & 0x00ff) == 0x00fe) {
            c &= ~0x100;
        }
        c_minus2 = c_minus1;
        c_minus1 = c;
        //Serial.println(c, HEX);
        return c_minus2;
    }
    return 0;
}