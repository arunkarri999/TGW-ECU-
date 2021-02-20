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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
