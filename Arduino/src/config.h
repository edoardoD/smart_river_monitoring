
#ifndef __CONFIG__
#define __CONFIG__
#include <arduino.h>
#include <string.h>
/***
 * @brief analog pins setting
 */
#define POT_PIN = A1;
#define SDA_PIN = A4;
#define SCL_PIN = A5;

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
/***
 * @brief enum class to string of system status
*/
String enum_toString(SysTatus status)
{
    switch (status)
    {
        case SysTatus::AUTO:
            return "AUTO";
        case SysTatus::MANUAL:
            return "MANUAL";
        default:
            return "UNKNOWN";
    }
}



#endif