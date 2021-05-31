#include "DummySensor.h"
#include <random>

float DummySensor::get_sensor_value() 
{
	return (float)g1();
}

unsigned int DummySensor::get_sensor_type()
{
	return this->sensor_type;
}

DummySensor::DummySensor(enumSensorTypes type, int seed)
{
	this->sensor_type = type;
	g1.seed(seed);
}

DummySensor::~DummySensor()
{
}