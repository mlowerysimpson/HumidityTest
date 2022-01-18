//HumidityTest.cpp
//this program logs data from a DHT22 temperature / humidity sensor connected to GPIO6 and using a one-wire interface

//this program is based on code from Hyun Wook Choi: https://github.com/ccoong7/DHT22

#include <stdio.h>
#include <wiringPi.h>
#include "../RemoteControlTest/HumiditySensor.h"


int main(void)
{
    const int NUM_SAMPLES = 10;
	HumiditySensor humiditySensor;
	float fBatteryHumidity = 0, fCPUHumidity = 0;//humidity in battery box and CPU box
	float fBatteryTemperature = 0, fCPUTemperature = 0;//temperature in battery box and CPU box

	// GPIO Initialization
	if (wiringPiSetupGpio() == -1)
	{
		printf("[x_x] GPIO Initialization FAILED.\n");
		return -1;
	}
	delay(1000);//initial delay to allow first sample to be ready
	for (unsigned char i = 0; i < NUM_SAMPLES; i++) {
		delay(HUMIDITY_SAMPLE_INTERVAL_SEC * 1000);//thread defined in HumiditySensor class updates every HUMIDITY_SAMPLE_INTERVAL_SEC seconds
		if (humiditySensor.GetHumidity(fCPUHumidity, CPUBOX)) {
			printf("CPU Humidity = %.2f %%, ",fCPUHumidity);
		}
		else {
			printf("CPU Humidity = N.A., ");
		}
		if (humiditySensor.GetTemperature(fCPUTemperature, CPUBOX)) {
			printf("CPU Temperature  = %.2f deg C\n",fCPUTemperature);
		}
		else {
			printf("CPU Temperature = N.A.\n");
		}
		if (humiditySensor.GetHumidity(fBatteryHumidity, BATTERYBOX)) {
			printf("Battery Humidity = %.2f %%, ",fBatteryHumidity);
		}
		else {
			printf("Battery Humidity = N.A., ");
		}
		if (humiditySensor.GetTemperature(fBatteryTemperature, BATTERYBOX)) {
			printf("Battery Temperature  = %.2f deg C\n",fBatteryTemperature);
		}
		else {
			printf("Battery Temperature = N.A.\n");
		}
	}
	return 0;
}