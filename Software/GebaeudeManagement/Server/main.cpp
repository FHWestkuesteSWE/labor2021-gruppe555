#include "BasicServer.h"
#include <iostream>

#define PORT 5000
char pfad[] = "raumdata.txt";

int main(int argc, char* argv[]) {

	BasicServer s;
	s.read_config(pfad);
	s.start(PORT);
	return 0;
}
