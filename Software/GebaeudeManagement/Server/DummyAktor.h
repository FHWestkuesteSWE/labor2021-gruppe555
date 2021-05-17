#pragma once

typedef unsigned int enumAktorTypes;
enum AktorTypes{Unknown = 0x00, Heizung = 0x01, FensterMotor = 0x02};

class DummyAktor
{
public:
	DummyAktor(enumAktorTypes type = Unknown);
	~DummyAktor();

	unsigned int get_aktor_type();
	bool set_aktor_value(float wert);

private:
	int aktor_type = 0;
	float aktor_value = 0;
};

