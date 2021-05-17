#pragma once
#include "DummyAktor.h"
#include "DummySensor.h"

class Raum
{
public:
	Raum(unsigned int raum_id = 0, unsigned int num_aktoren = 0, unsigned int num_sensoren = 0);
	~Raum();

	std::vector<DummyAktor> aktoren;
	std::vector<DummySensor> sensoren;

private:
	int raum_id = 0;
};

