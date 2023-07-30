#ifndef RXSERIAL_H_
#define RXSERIAL_H_

#include <Arduino.h>

class RxSerial {
    public:
        RxSerial( int comPort );
        virtual void Init();
        virtual uint16_t Getchar(void);
    protected:
        HardwareSerial * m_pSerial;
        uint16_t c_minus1 = 0;
        uint16_t c_minus2 = 0;
        uint16_t c_minus3 = 0;
};

#endif