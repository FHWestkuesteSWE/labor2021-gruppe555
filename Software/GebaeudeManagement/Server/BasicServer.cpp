#define _CRT_SECURE_NO_WARNINGS
#include "BasicServer.h"


static bool client_accepted = false;

void BasicServer::session()
{
	boost::asio::ip::tcp::socket* mysock = sockets.back();
	bool* mycallback = &thread_callbacks.back();
	*mycallback = true;
	char silentmsg[1] = { '\0' };

	std::mutex mux;
	std::unique_lock<std::mutex> ul(mux);
	std::condition_variable cv;

	try
	{
		for (;;) {
			char request[BasicServer::max_length];
			char answer[BasicServer::max_length];
			boost::system::error_code error;
			if (mysock->available() != 0) {
				mysock->read_some(boost::asio::buffer(request), error);
				if (error == boost::asio::error::eof) break; // Connection closed cleanly by peer.
				if (error) throw boost::system::system_error(error); // Some other error.
				processRequest(request, answer, mysock);
				boost::asio::write(*mysock, boost::asio::buffer(boost::asio::buffer(answer), strlen(answer)+1));
			}
			boost::asio::write(*mysock, boost::asio::buffer(boost::asio::buffer(silentmsg), 1));
			if (this->end_flag) break;
			cv.wait_for(ul, std::chrono::milliseconds(50));
		}
		*mycallback = false;
		return;
	}
	catch (std::exception& e)
	{
		//W --> Ping Test failed --> Client gone
		if(e.what()[0] != 'w') std::cerr << "Exception in thread: " << " " << e.what() << "\n";
		*mycallback = false;
		return;
	}
}

void BasicServer::clear_up_lists()
{
	int place = 0;
	for (auto it = thread_callbacks.begin(); it != thread_callbacks.end(); it++) {
		if ((*it) == false) {
			//Thread beendet
			auto thread_it = threads.begin();
			auto socket_it = sockets.begin();
			std::advance(thread_it, place);
			std::advance(socket_it, place);
			
			(*thread_it)->join();
			delete (*thread_it);
			delete (*socket_it);

			thread_callbacks.erase(it);
			threads.erase(thread_it);
			sockets.erase(socket_it);

			std::cout << "ASIO: Client removed \n";
			return;
		}
		place++;
	}
}

void BasicServer::asio_callback(const boost::system::error_code& ec)
{
	if (!ec) {
		std::cout << "ASIO: Client accepted" << std::endl;
		client_accepted = true;
	}
	else {
		std::cout << "ASIO Error: " << ec.message() << std::endl;
	}
	
}

BasicServer::BasicServer(int port)
{
	this->a = new boost::asio::ip::tcp::tcp::acceptor(io_service, boost::asio::ip::tcp::tcp::endpoint(boost::asio::ip::tcp::tcp::v4(), port));
	this->sockets.push_back(new boost::asio::ip::tcp::socket(io_service));
	this->a->async_accept(*sockets.front(), asio_callback);
}

void BasicServer::update() {
	
	try {
		if (client_accepted) {
			thread_callbacks.push_back(false);
			threads.push_back(new std::thread(&BasicServer::session, this));
			while (!thread_callbacks.back());

			this->sockets.push_back(new boost::asio::ip::tcp::socket(io_service));
			client_accepted = false;
			this->a->async_accept(*sockets.back(), asio_callback);
		}
		this->clear_up_lists();
		this->io_service.run_for(std::chrono::milliseconds(30));
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
}

void BasicServer::processRequest(char* req, char* ans, boost::asio::ip::tcp::socket* sock) {
	std::string reply;
	time_t rawtime;
	time(&rawtime);
	std::string zeitstempel = asctime(localtime(&rawtime));

	int endl_pos;
	for (endl_pos = 0; endl_pos < this->max_length; endl_pos++) {
		if (req[endl_pos] == '\0') break;
	}
	if (req[endl_pos] != '\0') {
		//No endl bit
		reply = "eNo EndlBit in Message";
		req[0] = 'e';
	}

	void *buf_ptr = nullptr;
	InstructionBufferData* data_ptr = nullptr;

	switch (req[0]) {
	case 'r': buf_ptr = new InstructionBuffer(req); 
			  data_ptr = new InstructionBufferData(); 
			  *data_ptr = *(InstructionBuffer*)buf_ptr; break;
	case 'w': buf_ptr = new InstructionBuffer(req); 
			  data_ptr = new InstructionBufferData(); 
			  *data_ptr = *(InstructionBuffer*)buf_ptr; break;
	case 'l': buf_ptr = new InstructionBuffer(req); 
			  data_ptr = new InstructionBufferData(); 
			  *data_ptr = *(InstructionBuffer*)buf_ptr; break;
	case 'm': buf_ptr = new MsgBuffer(req); break;
	case 'e': buf_ptr = new MsgBuffer(req); break;
	}

	InstructionBuffer* txt_ptr = (InstructionBuffer*)buf_ptr;

	switch (req[0]) {
	case 'w': //Write to Component
		if (data_ptr->raum_id > 0) {
			int raum_it = -1;
			for (int i = 0; i < vec_raum.size(); i++) {
				if (vec_raum[i].get_raum_id() == data_ptr->raum_id) {
					raum_it = i;
					break;
				}
			}
			if (raum_it != -1) {
				//Raum valid
				if (data_ptr->obj_id == 0) {
					reply = "eObjektID darf nicht null sein."; break;
				}

				int object_cnt = 0, aktor_it = -1;
				for (int i = 0; i < vec_raum[raum_it].aktoren.size(); i++) {
					if (vec_raum[raum_it].aktoren[i].get_aktor_type() == data_ptr->obj_type) object_cnt++;
					if (object_cnt == data_ptr->obj_id) {
						//Aktor valid
						aktor_it = i;
						break;
					}
				}

				if (object_cnt != data_ptr->obj_id || aktor_it == -1) {
					reply = "eAktor konnte nicht gefunden werden.";  break;
				}

				std::string logmsg = zeitstempel + " " + req[0] + " " + txt_ptr->txt_raum_id + " " + txt_ptr->txt_obj_type
					+ " " + txt_ptr->txt_obj_id + " " + txt_ptr->txt_value;
				std::string logPfad = "logRaum" + txt_ptr->txt_raum_id[0] + txt_ptr->txt_raum_id[1] + txt_ptr->txt_raum_id[2];
				logPfad += ".txt";
				std::ofstream f(logPfad.c_str());

				if (vec_raum[raum_it].aktoren[aktor_it].set_aktor_value(data_ptr->value)) {
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
		} 
		else {
			reply = "eRaum nicht vorhanden.";
		}
		break;
	case 'r': //Read from Component
		if (data_ptr->raum_id > 0) {
			int raum_it = -1;
			for (int i = 0; i < vec_raum.size(); i++) {
				if (vec_raum[i].get_raum_id() == data_ptr->raum_id) {
					raum_it = i;
					break;
				}
			}
			if (raum_it != -1) {
				//Raum valid
				if (data_ptr->obj_id == 0) {
					reply = "eObjektID darf nicht null sein."; break;
				}

				int object_cnt = 0, sensor_it = -1;
				for (int i = 0; i < vec_raum[raum_it].sensoren.size(); i++) {
					if (vec_raum[raum_it].sensoren[i].get_sensor_type() == data_ptr->obj_type) object_cnt++;
					if (object_cnt == data_ptr->obj_id) {
						sensor_it = i;
						break;
					}
				}

				if (object_cnt != data_ptr->obj_id || sensor_it == -1) {
					reply = "eSensor konnte nicht gefunden werden.";  break;
				}

				float value = vec_raum[raum_it].sensoren[sensor_it].get_sensor_value();

				std::string logmsg = zeitstempel + " " + req[0] + " " + txt_ptr->txt_raum_id + " " + txt_ptr->txt_obj_type
					+ " " + txt_ptr->txt_obj_id + " ";
				std::string logPfad = "logRaum" + txt_ptr->txt_raum_id[0] + txt_ptr->txt_raum_id[1] + txt_ptr->txt_raum_id[2];
				logPfad += ".txt";
				std::ofstream f(logPfad.c_str());

				if (isfinite(value)) {
					data_ptr->value = value;
					*txt_ptr = *data_ptr;

					reply = (char*)txt_ptr;
					logmsg += txt_ptr->txt_value;
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
		}
		else {
			reply = "eRaum nicht vorhanden.";
		}
		break;
	case 'e': //Error from Client?
		break;
	case 'l': //Log Daten ausgeben
#ifndef UNITTEST
	{std::string pfad = "logRaum" + txt_ptr->txt_raum_id[0] + txt_ptr->txt_raum_id[1] + txt_ptr->txt_raum_id[2];
	pfad += ".txt";
	if (!send_log_file(pfad.c_str(), sock)) reply = "eLogFile nicht vorhanden.";
	break; }
#endif // !UNITTEST
	default:
		reply = "eDatenmuell erhalten!";
	}
	strncpy(ans, reply.c_str(), std::min<int>(max_length, (int)reply.size() + 1));
	std::cout << reply << std::endl;

	if (buf_ptr != nullptr) delete buf_ptr;
	if (data_ptr != nullptr) delete data_ptr;
}

bool BasicServer::send_log_file(const char log_file_path[], boost::asio::ip::tcp::socket* sock)
{
	std::ifstream f(log_file_path, std::ios::in | std::ios::binary);
	if (!f.is_open()) {
		std::cout << "LogFile not found: " << log_file_path << " \n";
		return false;
	}
	std::string line;
	while (std::getline(f, line)) {
		boost::asio::write(*sock, boost::asio::buffer(boost::asio::buffer(_strdup(line.c_str()), max_length)));
	}
	return true;
}

BasicServer::~BasicServer()
{
	delete this->a;
	while (threads.size() != 0) {
		this->clear_up_lists();
	}
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
	catch(std::exception& e) {
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

#ifdef UNITTEST
void BasicServer::testrequest(char* request, char* answer)
{
	this->processRequest(request, answer, nullptr);
}
#endif // !UNITTEST