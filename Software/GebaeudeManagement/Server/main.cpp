#include "BasicServer.h"

int main(int argc, char* argv[]) {
	//Ich bin ein Testpush
	int port;
	if (argc == 0) {
		port = 5000;
	}
	else {
		port = atoi(argv[1]); // Funktioniert noch nicht
	}

	BasicServer s;
	//blablablabla
	s.start(port);
	return 0;
}


//Ich bin ein kommentar :)()