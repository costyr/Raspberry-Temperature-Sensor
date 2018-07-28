/**
 * 
 */

#include <stdio.h>
#include <time.h>
#include "rpi-sht1x/RPi_SHT1x.h"
#include "SHT11Sensor.h"

SHT11Sensor::SHT11Sensor(std::function<void(float)> aTempCallBack,
                         std::function<void(float)> aHumidityCallBack)
    : mTempCallBack(aTempCallBack),
      mHumidityCallBack(aHumidityCallBack)
{
}

void SHT11Sensor::Init()
{
    // Wait at least 11ms after power-up (chapter 3.1)
    delay(20);

    // Set up the SHT1x Data and Clock Pins
    SHT1x_InitPins();

    // Reset the SHT1x
    SHT1x_Reset();
}

void SHT11Sensor::Read()
{
    unsigned char noError = 1;

    // Request Temperature measurement
    noError = SHT1x_Measure_Start(SHT1xMeaT);
    if (!noError)
        return;

    value temp_val;

    // Read Temperature measurement
    noError = SHT1x_Get_Measure_Value((unsigned short int *)&temp_val.i);
    if (!noError)
        return;

    /*value humi_val;

    // Request Humidity Measurement
    noError = SHT1x_Measure_Start(SHT1xMeaRh);
    if (!noError)
        return;

    // Read Humidity measurement
    noError = SHT1x_Get_Measure_Value((unsigned short int *)&humi_val.i);
    if (!noError)
        return;
/*
    // Convert intergers to float and calculate true values
    temp_val.f = (float)temp_val.i;
    humi_val.f = (float)humi_val.i;

    // Calculate Temperature and Humidity
    SHT1x_Calc(&humi_val.f, &temp_val.f);

    if (temp_val.f != mTemperature)
    {
        mTemperature = temp_val.f;
        mTempCallBack(mTemperature);
    }

    if (humi_val.f != mHumidity)
    {
        mHumidity = humi_val.f;
        mHumidityCallBack(mHumidity);
    }*/
}
