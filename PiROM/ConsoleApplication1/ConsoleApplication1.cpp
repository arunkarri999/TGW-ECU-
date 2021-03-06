// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <PiEEPROM.h>

#ifdef __cplusplus
extern "C" {
#endif

    uint8_t _eeprom[EEPROM_SIZE] = {};

    int eeprom_is_ready()
    {
        return 1;
    }

    /**
     * Read one byte from EEPROM address __p.
     */
    uint8_t eeprom_read_byte(const uint8_t* __p)
    {
        size_t addr = (size_t)__p;

        if (addr < EEPROM_SIZE)
        {
            return *(_eeprom + addr);
        }

        return 0;
    }

    /**
 * Read one 32-bit double word (little endian) from EEPROM address __p.
 */
    uint32_t eeprom_read_dword(const uint32_t* __p)
    {
        size_t addr = (size_t)__p;

        if (addr < EEPROM_SIZE - (sizeof(uint32_t) - sizeof(uint8_t)))
        {
            return (uint32_t) * (_eeprom + addr);
        }

        return 0;
    }

    /**
     * Read one float value (little endian) from EEPROM address __p.
     */
    float eeprom_read_float(const float* __p)
    {
        size_t addr = (size_t)__p;

        if (addr < EEPROM_SIZE - (sizeof(float) - sizeof(uint8_t)))
        {
            return (float)*(_eeprom + addr);
        }

        return 0;
    }

    /**
 * Read a block of __n bytes from EEPROM address __src to SRAM __dst.
 */
    void eeprom_read_block(void* __dst, const void* __src, size_t __n)
    {
        size_t addr = (size_t)__src;

        if (addr < EEPROM_SIZE - (__n - sizeof(uint8_t)))
        {
            memcpy(__dst, (_eeprom + addr), __n);
        }
    }
    /**
 * Write a byte __value to EEPROM address __p.
 */
    void eeprom_write_byte(uint8_t* __p, uint8_t __value)
    {
        size_t addr = (size_t)__p;

        if (addr < EEPROM_SIZE)
        {
            memcpy((_eeprom + addr), &__value, sizeof(uint8_t));
        }
    }

    /**
 * Write a word __value to EEPROM address __p.
 */
    void eeprom_write_word(uint16_t* __p, uint16_t __value)
    {
        size_t addr = (size_t)__p;

        if (addr < EEPROM_SIZE - (sizeof(uint16_t) - sizeof(uint8_t)))
        {
            memcpy((_eeprom + addr), &__value, sizeof(uint16_t));
        }
    }

    /**
     * Write a 32-bit double word __value to EEPROM address __p.
     */
    void eeprom_write_dword(uint32_t* __p, uint32_t __value)
    {
        size_t addr = (size_t)__p;

        if (addr < EEPROM_SIZE - (sizeof(uint32_t) - sizeof(uint8_t)))
        {
            memcpy((_eeprom + addr), &__value, sizeof(uint32_t));
        }
    }

    /**
 * Write a float __value to EEPROM address __p.
 */
    void eeprom_write_float(float* __p, float __value)
    {
        size_t addr = (size_t)__p;

        if (addr < EEPROM_SIZE - (sizeof(float) - sizeof(uint8_t)))
        {
            memcpy((_eeprom + addr), &__value, sizeof(float));
        }
    }

    /**
     * Write a block of __n bytes to EEPROM address __dst from __src.
     * The argument order is mismatch with common functions like strcpy().
     */
    void eeprom_write_block(const void* __src, void* __dst, size_t __n)
    {
        size_t addr = (size_t)__dst;

        if (addr < EEPROM_SIZE - (__n - sizeof(uint8_t)))
        {
            memcpy((_eeprom + addr), __src, __n);
        }
    }


#ifdef __cplusplus
}
#endif

/*
 * PiEEPROM.h - AVR EEPROM like implementation for Raspberry Pi

* /

#ifndef __PiEEPROM_H__
#define __PiEEPROM_H__ 1

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EEPROM_SIZE 1024    // 1KB of EEPROM memory

    extern uint8_t _eeprom[EEPROM_SIZE];

    int eeprom_is_ready();
    /**
     * Loops until the eeprom is no longer busy.
     * Returns Nothing.
     */
#define eeprom_busy_wait() do {} while (!eeprom_is_ready())


     /**
      * Read one byte from EEPROM address __p.
      */
    uint8_t eeprom_read_byte(const uint8_t* __p);

    /**
     * Read one 16-bit word (little endian) from EEPROM address __p.
     */
    uint16_t eeprom_read_word(const uint16_t* __p);

    /**
     * Read one 32-bit double word (little endian) from EEPROM address __p.
     */
    uint32_t eeprom_read_dword(const uint32_t* __p);

    /**
     * Read one float value (little endian) from EEPROM address __p.
     */
    float eeprom_read_float(const float* __p);

    /**
     * Read a block of __n bytes from EEPROM address __src to SRAM __dst.
     */
    void eeprom_read_block(void* __dst, const void* __src, size_t __n);



    /**
     * Write a byte __value to EEPROM address __p.
     */
    void eeprom_write_byte(uint8_t* __p, uint8_t __value);

    /**
     * Write a word __value to EEPROM address __p.
     */
    void eeprom_write_word(uint16_t* __p, uint16_t __value);

    /**
     * Write a 32-bit double word __value to EEPROM address __p.
     */
    void eeprom_write_dword(uint32_t* __p, uint32_t __value);

    /**
     * Write a float __value to EEPROM address __p.
     */
    void eeprom_write_float(float* __p, float __value);

    /**
     * Write a block of __n bytes to EEPROM address __dst from __src.
     * The argument order is mismatch with common functions like strcpy().
     */
    void eeprom_write_block(const void* __src, void* __dst, size_t __n);



    /**
     * Update a byte __value to EEPROM address __p.
     */
#define eeprom_update_byte eeprom_write_byte

     /**
      * Update a word __value to EEPROM address __p.
      */
#define eeprom_update_word eeprom_write_word

      /**
       * Update a 32-bit double word __value to EEPROM address __p.
       */
#define eeprom_update_dword eeprom_write_dword

       /**
        * Update a float __value to EEPROM address __p.
        */
#define eeprom_update_float eeprom_write_float

        /**
         * Update a block of __n bytes to EEPROM address __dst from __src.
         * The argument order is mismatch with common functions like strcpy().
         */
#define eeprom_update_block eeprom_write_block

#ifdef __cplusplus
}
#endif

#endif /* __PiEEPROM_H__ */



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
