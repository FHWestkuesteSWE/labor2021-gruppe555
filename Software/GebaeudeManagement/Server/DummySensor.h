#include <random>

typedef unsigned int enumSensorTypes;
enum SensorTypes {Unbekannt = 0x00, TempSensor = 0x01, FensterKontakt = 0x02};

class DummySensor {

public:
	DummySensor(enumSensorTypes type = 1, int seed = 12);
	~DummySensor();

	float get_sensor_value(void);
	unsigned int get_sensor_type();

private:
	unsigned int sensor_type = 0;
	std::minstd_rand0 g1;

};