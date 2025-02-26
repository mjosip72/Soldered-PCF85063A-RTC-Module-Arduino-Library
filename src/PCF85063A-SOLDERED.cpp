/**
 **************************************************
 *
 * @file        PCF85063A-SOLDERED.cpp
 * @brief       PCF85063A RTC module driver source cpp file
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ Zvonimir Haramustek for soldered.com
 ***************************************************/


#include "PCF85063A-SOLDERED.h"


/**
 * @brief                   Main constructor
 */
PCF85063A::PCF85063A(void)
{
}

/**
 * @brief                   Initialize communication
 */
void PCF85063A::begin()
{
    Wire.begin();
}

/**
 * @brief                   Method to set time
 *
 * @param uint8_t hour      Set the hour
 * @param uint8_t minute    Set the minutes
 * @param uint8_t second    Set the seconds
 */
void PCF85063A::setTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_SECOND_ADDR);
    Wire.write(decToBcd(second));
    Wire.write(decToBcd(minute));
    Wire.write(decToBcd(hour));
    Wire.endTransmission();
}

/**
 * @brief                   Method to set the date
 *
 * @param uint8_t weekday   Set the weekday
 * @param uint8_t day       Set the day
 * @param uint8_t month     Set the month
 * @param uint8_t yr        Set the year
 */
void PCF85063A::setDate(uint8_t weekday, uint8_t day, uint8_t month, uint16_t yr)
{
    year = yr - 1970; // convert to RTC year format 0-99

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_DAY_ADDR);
    Wire.write(decToBcd(day));
    Wire.write(decToBcd(weekday));
    Wire.write(decToBcd(month));
    Wire.write(decToBcd(year));
    Wire.endTransmission();
}

/**
 * @brief                   Reads time and date from the RTC
 */
void PCF85063A::readTime()
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_SECOND_ADDR); // datasheet 8.4.
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDR, 7);

    while (Wire.available())
    {
        second = bcdToDec(Wire.read() & 0x7F); // ignore bit 7
        minute = bcdToDec(Wire.read() & 0x7F);
        hour = bcdToDec(Wire.read() & 0x3F); // ignore bits 7 & 6
        day = bcdToDec(Wire.read() & 0x3F);
        weekday = bcdToDec(Wire.read() & 0x07); // ignore bits 7,6,5,4 & 3
        month = bcdToDec(Wire.read() & 0x1F);   // ignore bits 7,6 & 5
        year = bcdToDec(Wire.read()) + 1970;
    }
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current seconds
 */
uint8_t PCF85063A::getSecond()
{
    return second;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current minutes
 */
uint8_t PCF85063A::getMinute()
{
    return minute;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current hours
 */
uint8_t PCF85063A::getHour()
{
    return hour;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current day
 */
uint8_t PCF85063A::getDay()
{
    return day;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current weekday
 */
uint8_t PCF85063A::getWeekday()
{
    return weekday;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current month
 */
uint8_t PCF85063A::getMonth()
{
    return month;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current year
 */
uint16_t PCF85063A::getYear()
{
    return year;
}

/**
 * @brief                   Enables the alarm of the RTC
 */
void PCF85063A::enableAlarm() // datasheet 8.5.6.
{
    // check Table 2. Control_2
    control_2 = RTC_CTRL_2_DEFAULT | RTC_ALARM_AIE; // enable interrupt
    control_2 &= ~RTC_ALARM_AF;                     // clear alarm flag

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_CTRL_2);
    Wire.write(control_2);
    Wire.endTransmission();
}

/**
 * @brief                       Sets the alarm to all the params
 *
 * @param uint8_t alarm_second  Set the alarm seconds
 * @param uint8_t alarm_minute  Set the alarm minutes
 * @param uint8_t alarm_hour    Set the alarm hours
 * @param uint8_t alarm_day     Set the alarm day
 * @param uint8_t alarm_weekday Set the alarm weekday
 */
void PCF85063A::setAlarm(uint8_t alarm_second, uint8_t alarm_minute, uint8_t alarm_hour, uint8_t alarm_day,
                         uint8_t alarm_weekday)
{
    if (alarm_second < 99)
    { // second
        alarm_second = constrain(alarm_second, 0, 59);
        alarm_second = decToBcd(alarm_second);
        alarm_second &= ~RTC_ALARM;
    }
    else
    {
        alarm_second = 0x0;
        alarm_second |= RTC_ALARM;
    }

    if (alarm_minute < 99)
    { // minute
        alarm_minute = constrain(alarm_minute, 0, 59);
        alarm_minute = decToBcd(alarm_minute);
        alarm_minute &= ~RTC_ALARM;
    }
    else
    {
        alarm_minute = 0x0;
        alarm_minute |= RTC_ALARM;
    }

    if (alarm_hour < 99)
    { // hour
        alarm_hour = constrain(alarm_hour, 0, 23);
        alarm_hour = decToBcd(alarm_hour);
        alarm_hour &= ~RTC_ALARM;
    }
    else
    {
        alarm_hour = 0x0;
        alarm_hour |= RTC_ALARM;
    }

    if (alarm_day < 99)
    { // day
        alarm_day = constrain(alarm_day, 1, 31);
        alarm_day = decToBcd(alarm_day);
        alarm_day &= ~RTC_ALARM;
    }
    else
    {
        alarm_day = 0x0;
        alarm_day |= RTC_ALARM;
    }

    if (alarm_weekday < 99)
    { // weekday
        alarm_weekday = constrain(alarm_weekday, 0, 6);
        alarm_weekday = decToBcd(alarm_weekday);
        alarm_weekday &= ~RTC_ALARM;
    }
    else
    {
        alarm_weekday = 0x0;
        alarm_weekday |= RTC_ALARM;
    }

    enableAlarm();

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_SECOND_ALARM);
    Wire.write(alarm_second);
    Wire.write(alarm_minute);
    Wire.write(alarm_hour);
    Wire.write(alarm_day);
    Wire.write(alarm_weekday);
    Wire.endTransmission();
}


/**
 * @brief                   Reads the alarm of the RTC
 */
void PCF85063A::readAlarm()
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_SECOND_ALARM); // datasheet 8.4.
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDR, 5);

    while (Wire.available())
    {
        alarm_second = Wire.read();   // read RTC_SECOND_ALARM register
        if (RTC_ALARM & alarm_second) // check is AEN = 1 (second alarm disabled)
        {
            alarm_second = 99; // using 99 as code for no alarm
        }
        else
        {                                                       // else if AEN = 0 (second alarm enabled)
            alarm_second = bcdToDec(alarm_second & ~RTC_ALARM); // remove AEN flag and convert to dec number
        }

        alarm_minute = Wire.read(); // minute
        if (RTC_ALARM & alarm_minute)
        {
            alarm_minute = 99;
        }
        else
        {
            alarm_minute = bcdToDec(alarm_minute & ~RTC_ALARM);
        }

        alarm_hour = Wire.read(); // hour
        if (RTC_ALARM & alarm_hour)
        {
            alarm_hour = 99;
        }
        else
        {
            alarm_hour = bcdToDec(alarm_hour & 0x3F); // remove bits 7 & 6
        }

        alarm_day = Wire.read(); // day
        if (RTC_ALARM & alarm_day)
        {
            alarm_day = 99;
        }
        else
        {
            alarm_day = bcdToDec(alarm_day & 0x3F); // remove bits 7 & 6
        }

        alarm_weekday = Wire.read(); // weekday
        if (RTC_ALARM & alarm_weekday)
        {
            alarm_weekday = 99;
        }
        else
        {
            alarm_weekday = bcdToDec(alarm_weekday & 0x07); // remove bits 7,6,5,4 & 3
        }
    }
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current alarm seconds
 */
uint8_t PCF85063A::getAlarmSecond()
{
    return alarm_second;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current alarm minutes
 */
uint8_t PCF85063A::getAlarmMinute()
{
    return alarm_minute;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current alarm hours
 */
uint8_t PCF85063A::getAlarmHour()
{
    return alarm_hour;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current alarm day
 */
uint8_t PCF85063A::getAlarmDay()
{
    return alarm_day;
}

/**
 * @brief                   Small user method
 *
 * @returns uint8_t         Returns the current alarm weekday
 */
uint8_t PCF85063A::getAlarmWeekday()
{
    return alarm_weekday;
}

/**
 * @brief                   Sets the timer countdown
 */
void PCF85063A::timerSet(CountdownSrcClock source_clock, uint8_t value, bool int_enable, bool int_pulse)
{
    uint8_t timer_reg[2] = {0};

    // disable the countdown timer
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_TIMER_MODE);
    Wire.write(0x18); // default
    Wire.endTransmission();

    // clear Control_2
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_CTRL_2);
    Wire.write(0x00); // default
    Wire.endTransmission();

    // reconfigure timer
    timer_reg[1] |= RTC_TIMER_TE; // enable timer
    if (int_enable)
        timer_reg[1] |= RTC_TIMER_TIE; // enable interrupr
    if (int_pulse)
        timer_reg[1] |= RTC_TIMER_TI_TP; // interrupt mode
    timer_reg[1] |= source_clock << 3;   // clock source
    // timer_reg[1] = 0b00011111;

    timer_reg[0] = value;

    // write timer value
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_TIMER_VAL);
    Wire.write(timer_reg[0]);
    Wire.write(timer_reg[1]);
    Wire.endTransmission();
}

/**
 * @brief                   Returns is the timer flag on
 *
 * @returns bool            Returns true if the timer flag is on
 */
bool PCF85063A::checkTimerFlag()
{
    uint8_t _crtl_2 = RTC_TIMER_FLAG;

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_CTRL_2);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDR, 1);
    _crtl_2 &= Wire.read();

    return _crtl_2;
}

/**
 * @brief                   Resets the timer
 */
void PCF85063A::reset() // datasheet 8.2.1.3.
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(RTC_CTRL_1);
    Wire.write(0x58);
    Wire.endTransmission();
}

/**
 * @brief                   Converts decimal to BCD
 */
uint8_t PCF85063A::decToBcd(uint8_t val)
{
    return ((val / 10 * 16) + (val % 10));
}

/**
 * @brief                   Converts BCD to decimal
 */
uint8_t PCF85063A::bcdToDec(uint8_t val)
{
    return ((val / 16 * 10) + (val % 16));
}
