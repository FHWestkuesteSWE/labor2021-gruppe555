#include "Raum.h"

Raum::Raum(unsigned int raum_id, unsigned int num_aktoren, unsigned int num_sensoren)
{
	this->raum_id = raum_id;
	this->aktoren.resize(num_aktoren);
	this->sensoren.resize(num_sensoren);

	for (auto it : aktoren) {it = DummyAktor();}
	for (auto it : sensoren) {it = DummySensor();}
}

Raum::~Raum()
{
}

int Raum::get_raum_id()
{
	return this->raum_id;
}
