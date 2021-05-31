#include "Unittests.h"

#ifdef UNITTEST

void Unittests::request_response_test(BasicServer* server)
{
	char response[1024] = {};

	//Randomtest (deckt e und default branch ab)
	for (int i = 0; i < 1000; i++) {
		const int length = (rand() % 1024) + 1;
		std::vector<char> buffer(length);
		for (int j = 0; j < buffer.size(); j++) {
			buffer[j] = rand() % 256;
		}
		std::cout << "Random " << i << ": FIrst Letter:" << buffer.data()[0] << " ";
		server->testrequest((char*)buffer.data(), response);
		std::cout << response << std::endl;
	}
	
	//Variable Buffer length
	for (int i = 1; i < 2000; i++) {
		std::vector<char> buffer(i);
		buffer[0] = (rand() % 26) + 97; //Ascii kleine Buchstaben 97 - 122
		for (int j = 1; j < buffer.size(); j++) {
			buffer[j] = (rand() % 94) + 33; //sinnvoller Ascii bereich 33 - 126
		}
		buffer[buffer.size() - 1] = '\0';

		std::cout << "Variable Length " << i << ": FIrst Letter:" << buffer.data()[0] << " ";
		server->testrequest((char*)buffer.data(), response);
		std::cout << response << std::endl;
	}

	//Sinnvoller Telegrammaufbau Random Zahlen (w)
	for (int i = 1; i < 2000; i++) {
		std::vector<char> buffer(30);
		buffer[0] = 'w';
		for (int j = 1; j < buffer.size(); j++) {
			buffer[j] = (rand() % 10) + 48; //Zahlen
		}
		buffer[9] = '0';
		buffer[10] = '0';
		buffer[buffer.size() - 1] = '\0';

		std::cout << "Write " << i << ": " << buffer.data() << " ";
		server->testrequest((char*)buffer.data(), response);
		std::cout << response << std::endl;
	}

	//Sinnvoller Telegrammaufbau Random Zahlen (r)
	for (int i = 1; i < 2000; i++) {
		std::vector<char> buffer(30);
		buffer[0] = 'r';
		for (int j = 1; j < buffer.size(); j++) {
			buffer[j] = (rand() % 10) + 48; //Zahlen
		}
		buffer[9] = '0';
		buffer[10] = '0';
		buffer[buffer.size() - 1] = '\0';

		std::cout << "Read " << i << ": " << buffer.data() << " ";
		server->testrequest((char*)buffer.data(), response);
		std::cout << response << std::endl;
	}
}

#endif
