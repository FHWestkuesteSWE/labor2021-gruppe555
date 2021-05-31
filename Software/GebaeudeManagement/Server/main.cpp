#include "BasicServer.h"
#include <iostream>

#ifdef UNITTEST
#include "Unittests.h"
#endif

#define PORT 5000
char pfad[] = "raumdata.txt";

void wait_for_end(bool* flag) {
	while (!(*flag)) {
		char a = 0;
		std::cin >> a;
		if (a == 'e') *flag = true;
	}
}

int main(int argc, char* argv[]) {

	BasicServer s(PORT);
	s.read_config(pfad);

#ifdef UNITTEST
	Unittests::request_response_test(&s);
#else
	
	std::thread t(wait_for_end, &s.end_flag);
	while (!s.end_flag) {
		s.update();
	}
	t.join();
#endif
	return 0;
}
