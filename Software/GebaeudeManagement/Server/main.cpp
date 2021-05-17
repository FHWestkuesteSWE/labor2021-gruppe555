#include "BasicServer.h"
#include "DummySensor.h"
#include <iostream>

int main(int argc, char* argv[]) {
	//Ich bin ein Testpush
	int port;

	std::cout << argc << std::endl;

	if (argc == 1) {
		port = 5000;
	}
	else {
		port = atoi(argv[1]); // Funktioniert noch nicht
	}


	DummySensor _temp1(20);

	std::cout << _temp1.readValue() << std::endl;

	BasicServer s;
	//blablablabla
	s.start(port);
	return 0;
}


//Ich bin ein kommentar :)()