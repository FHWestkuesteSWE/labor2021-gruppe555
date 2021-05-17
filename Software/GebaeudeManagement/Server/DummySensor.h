#include <random>

class DummySensor {

public:
	int readValue(void);



	DummySensor(int);
	DummySensor();
	~DummySensor();

private:
	std::minstd_rand0 g1;

};