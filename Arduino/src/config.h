
#ifndef __CONFIG__
#define __CONFIG__
#include <arduino.h>
#include <string.h>
/***
 * @brief analog pins setting
 */
constexpr int POT_PIN = A1;
constexpr int SDA_PIN = A4;
constexpr int SCL_PIN = A5;

/***
 * @brief digital pins setting
 */
constexpr int GATE_PIN = 5;
constexpr int BUTTON_PIN = 2;

/***
 * @brief enum class for system status
 */
enum class SysTatus
{
    AUTO,
    MANUAL
};





#endif