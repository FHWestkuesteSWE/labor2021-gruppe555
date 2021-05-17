#include "DummySensor.h"
#include <random>

int DummySensor::readValue() {
	
	return g1();

}

DummySensor::DummySensor(int seed) {

	g1.seed(seed);

}

DummySensor::DummySensor() {

	g1.seed(11);

}

DummySensor::~DummySensor() {


}