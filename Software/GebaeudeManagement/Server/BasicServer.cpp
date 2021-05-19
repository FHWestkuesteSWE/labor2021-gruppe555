#define _CRT_SECURE_NO_WARNINGS
#include "BasicServer.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <fstream>
#include <list>
#include <ctime>

void BasicServer::session(socket_ptr sock)
{
	try
	{
		for (;;)
		{
			char request[BasicServer::max_length];
			char answer[BasicServer::max_length];
			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(request), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.
			this->processRequest(request,answer, sock);
			boost::asio::write(*sock, boost::asio::buffer(boost::asio::buffer(answer), max_length));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}
BasicServer::BasicServer()
{

}

void BasicServer::start(int port) {
	boost::asio::io_service io_service;

	using namespace std; // For atoi.
	using boost::asio::ip::tcp;
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	for (;;)
	{
		socket_ptr sock(new tcp::socket(io_service));
		a.accept(*sock);
		boost::thread t(boost::bind(&BasicServer::session, this, sock));
	}
}

void BasicServer::processRequest(char req[], char ans[], socket_ptr sock) {
	std::string reply;
	unsigned int raum_id = 0, object_type = 0, object_id = 0;
	float wert = 0.0f;
	std::string raum_id_txt, object_type_txt, object_id_txt;
	std::string wert1, wert2;

	time_t rawtime;
	time(&rawtime);
	std::string zeitstempel = asctime(localtime(&rawtime));

	if (req[0] == 'w' || req[0] == 'r') {
		raum_id_txt = req[1] + req[2] + req[3];
		object_type_txt = req[4] + req[5];
		object_id_txt = req[6] + req[7] + req[8];

		raum_id = atoi(raum_id_txt.c_str());
		object_type = atoi(object_type_txt.c_str());
		object_id = atoi(object_id_txt.c_str());

		if (req[0] == 'w') {
			wert1 = req[9] + req[10];
			wert2 = req[11] + req[11];
			wert = atoi(wert1.c_str()) + atoi(wert2.c_str()) * 0.01f;
		}
	}
	else if (req[0] == 'l') {
		raum_id_txt = req[1] + req[2] + req[3];
		raum_id = atoi(raum_id_txt.c_str());
	}

	switch (req[0]) {
	case 'w': //Write to Component
		if (raum_id > 0 && raum_id <= this->vec_raum.size()) {
			//Raum valid
			int object_cnt = 0, i = 0;
			for (; i < vec_raum[raum_id-1].aktoren.size(); i++) {
				if (vec_raum[raum_id-1].aktoren[i].get_aktor_type() == object_type) object_cnt++;
				if (object_cnt == object_id) break;
			}

			if (object_cnt != object_id) {
				reply = "eAktor konnte nicht gefunden werden.";  break;
			}

			std::string logmsg = zeitstempel + " " + req[0] + " " + raum_id_txt + " " + object_type_txt
				+ " " + object_id_txt + " " + wert1 + "." + wert2;
			std::ofstream f("logRaum" + raum_id_txt + ".txt");

			if (vec_raum[raum_id - 1].aktoren[i].set_aktor_value(wert)) {
				reply = "mAktorwert erfolgreich gesetzt.";
			}
			else {
				reply = "eAktorwert konnte nicht gesetzt werden.";
				logmsg += " Error: no exec";
			}
			f.write(logmsg.c_str(), logmsg.size());
			f.close();
		} 
		else {
			reply = "eRaum nicht vorhanden.";
		}
		break;
	case 'r': //Read from Component
		if (raum_id > 0 && raum_id <= this->vec_raum.size()) {
			//Raum valid
			int object_cnt = 0, i = 0;
			for (; i < vec_raum[raum_id-1].sensoren.size(); i++) {
				if (vec_raum[raum_id-1].sensoren[i].get_sensor_type() == object_type) object_cnt++;
				if (object_cnt == object_id) break;
			}

			if (object_cnt != object_id) {
				reply = "eSensor konnte nicht gefunden werden.";  break;
			}

			float value = vec_raum[raum_id-1].sensoren[i].get_sensor_value();
			char value_txt[5];

			std::string logmsg = zeitstempel + " " + req[0] + " " + raum_id_txt + " " + object_type_txt
				+ " " + object_id_txt + " ";
			std::ofstream f("logRaum" + raum_id_txt + ".txt");

			if(isfinite(value)) {
				value_txt[0] = (int)floor((floor(value) / 10.0f)) + 48;
				value_txt[1] = ((int)floor(value) % 10) + 48;
				value_txt[2] = ((int)floor(10 * value) % 10) + 48;
				value_txt[3] = ((int)floor(100 * value) % 10) + 48;
				value_txt[4] = '\0';

				reply = "w" + raum_id_txt + object_type_txt + object_id_txt + value_txt;
				logmsg += value_txt[0] + value_txt[1] + "." + value_txt[2] + value_txt[3];
			}
			else {
				reply = "eSensorwert konnte nicht gelesen werden.";
				logmsg += "Error: non valid Value.";
			}
			f.write(logmsg.c_str(), logmsg.size());
			f.close();
		}
		else {
			reply = "eRaum nicht vorhanden.";
		}
		break;
	case 'e': //Error from Client?
		break;
	case 'l': //Log Daten ausgeben
		{std::string pfad = "logRaum" + req[1] + req[2] + req[3];
		pfad += ".txt";
		send_log_file(pfad.c_str(), sock);
		break; }
	default:
		reply = "eDatenmuell erhalten!";
	}
	strncpy(ans, reply.c_str(), std::min<int>(max_length, reply.size() + 1));
}

void BasicServer::send_log_file(const char log_file_path[], socket_ptr sock)
{
	std::ifstream f(log_file_path, std::ios::in | std::ios::binary);
	if (!f.is_open()) {
		std::cout << "LogFile not found: " << log_file_path << " \n";
		return;
	}
	std::string line;
	while (std::getline(f, line)) {
		boost::asio::write(*sock, boost::asio::buffer(boost::asio::buffer(_strdup(line.c_str()), max_length)));
	}
}

BasicServer::~BasicServer()
{
}

bool BasicServer::read_config(char path[])
{
	std::ifstream f(path, std::ios::in | std::ios::binary);
	if (!f.is_open()) {
		std::cout << "File not found: " << path << " \n";
		return false;
	}
	std::string line;
	std::list<unsigned int> list_data;

	try {
		while (std::getline(f, line)) {
			std::string substring[3];
			int sub_index = 0;

			std::string::size_type i = 0;
			std::string::size_type j = line.find(' ');

			while (j != std::string::npos) {
				substring[sub_index] = line.substr(i, j - i);
				sub_index++;
				i = ++j;
				j = line.find(' ', j);

				if (j == std::string::npos)
					substring[sub_index] = line.substr(i, line.length());
			}
			for (int it = 0; it < 3; it++) list_data.push_back(std::atoi(substring[it].c_str()));
		}
	}
	catch(std::exception e) {
		std::cout << "Error in Config-File!" << std::endl;
	}
	f.close();

	std::vector<unsigned int> vec_data(list_data.size());
	this->vec_raum.resize(list_data.size() / 3);
	int cnt = 0;
	for (auto list_it : list_data) vec_data[cnt++] = list_it;
	for (int vec_it = 0; vec_it < vec_data.size() / 3; vec_it++) {
		this->vec_raum[vec_it] = Raum(vec_data[3 * vec_it], vec_data[3 * vec_it + 1], vec_data[3 * vec_it + 2]);
	}

	//Log Dateien erstellen
	FILE* fp;
	char filestring[] = "logRaum";
	std::string raum_id_txt;
	std::string raum_pfad;

	for (int i = 0; i < this->vec_raum.size(); i++) {
		raum_id_txt = vec_raum[i].get_raum_id() / 100 + 48;
		raum_id_txt += (vec_raum[i].get_raum_id() / 10) % 10 + 48;
		raum_id_txt += vec_raum[i].get_raum_id() % 10 + 48;
		raum_pfad = filestring + raum_id_txt + ".txt";
		std::ifstream f(raum_pfad, std::ios::in | std::ios::binary);
		if (!f.is_open()) {
			fp = fopen(raum_pfad.c_str(), "w");
			fprintf(fp, "Zeitstempel // OPCode // Raum_Idx // Sensor_Type // Sensor_Idx // Value \n");
			fclose(fp);
		}
		else {
			f.close();
		}
	}
	
	return true;
}
