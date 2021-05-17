#include "BasicServer.h"

int main(int argc, char* argv[]) {

	int port;
	if (argc == 1) {
		port = 5000;
	}
	else {
		port = atoi(argv[1]); // Funktioniert noch nicht
	}


	DummySensor _temp1(20);

	std::cout << _temp1.readValue() << std::endl;

	BasicServer s;
	s.start(port);
	return 0;
}
