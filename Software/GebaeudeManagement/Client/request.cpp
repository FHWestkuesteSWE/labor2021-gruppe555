#include "request.h"
#include <iostream>
#include <string>
#include <regex>
#include <random>

using namespace std;

/*
Desc: Constructor
@param None
@return None
*/

request::request() {


}

/*
Desc: Destructor
@param None
@return None
*/

request::~request() {


}

/*
Desc: Constructor
	Sets wahl to specifed request type
@param char k wahl specifier
@return None
*/

request::request(char k) {

	request::wahl = k;
	
}

/*
Desc: Create Request and new Message and store pointer to first message in vector _m
@param char wahl 
@return int -> success or failure
*/

int request::createreq(char wahl) {

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 99999999);



	if (wahl == 't') {
		std::shared_ptr<message> m1(new message);
		string input;
		bool sw=false;

		//Setzen oder lesen

		

		wrtemp:
		cout << "Raumtemperatur setzen oder lesen(w/r): " << "\n";
		cin >> input;
		if ((input.compare("w") != 0) && (input.compare("r") != 0)) {
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto wrtemp;
		}
		if (input.compare("w") != 0) {
			sw = true;
		}
		m1->setopcode(input);
		input.clear();


		//Raum
		regex rraum("[0-9]{3}");

		troom:
		cout << "In welchem Raum?(###): " << "\n";
		cin >> input;
		if (regex_match(input.substr(0,3), rraum)) {
			m1->setraum(input);
			input.clear();
		}else{
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto troom;
		}


		
		//welcher sensor wurde schon bestimmt t -> temp
		m1->setsensort("01");

		//Sensors
		regex rsens("[0-9]{3}");

		tsensn:
		cout << "Welche Sensornumer?(###): " << "\n";
		cin >> input;
		if (regex_match(input.substr(0,3), rsens)) {
			m1->setsensornmr(input);
			input.clear();
		}else{
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto tsensn;
		}



		if (sw == false) {

			//Wert
			regex rwert("[0-9]{2},[0-9]{2}");

			twert:
			cout << "Auf welchen Wert?(##,##): " << "\n";
			cin >> input;
			if (regex_match(input.substr(0, 5), rwert)) {
				input.erase(2, 1);
				m1->setwert(input);
				input.clear();
			}else{
				cout << "Falsche Eingabe erkannt!" << "\n";
				goto twert;
			}


		}


		//messageid

		

		auto random_integer = uni(rng);

		int n_zero = 8;
		string old_string;

		old_string = to_string(random_integer);

		std::string new_string = std::string(n_zero - old_string.length(), '0') + old_string;

		m1->setmessageid(new_string);

		m1->makemsg();


		_m.push_back(m1);

		return true;
		
	}
	else if (wahl == 'r') {
		std::shared_ptr<message> m1(new message);
		string input;
		bool sw = false;

		//Setzen oder lesen

	wrroll:
		cout << "Rollladen oeffnen/schließen oder Status lesen (w/r): " << "\n";
		cin >> input;
		if ((input.compare("w") != 0) && (input.compare("r") != 0)) {
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto wrroll;
		}
		if (input.compare("w") != 0) {
			sw = true;
		}
		m1->setopcode(input);
		input.clear();


		//Raum
		regex rraum("[0-9]{3}");

	rlroom:
		cout << "In welchem Raum?(###): " << "\n";
		cin >> input;
		if (regex_match(input.substr(0, 3), rraum)) {
			m1->setraum(input);
			input.clear();
		}
		else {
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto rlroom;
		}



		//welcher sensor wurde schon bestimmt t -> temp
		m1->setsensort("02");

		//Sensors
		regex rsens("[0-9]{3}");

	rlsensn:
		cout << "Welcher Rollladen?(###): " << "\n";
		cin >> input;
		if (regex_match(input.substr(0, 3), rsens)) {
			m1->setraum(input);
			input.clear();
		}
		else {
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto rlsensn;
		}


		if (sw == false) {

			//Wert
			regex rwert("[01]");

		rlwert:
			cout << "Auf welchen Wert? 1/0 (#): " << "\n";
			cin >> input;
			if (regex_match(input.substr(0, 1), rwert)) {
				m1->setwert(input);
				input.clear();
			}else{
				cout << "Falsche Eingabe erkannt!" << "\n";
				goto rlwert;
			}


		}


		//messageid

		

		auto random_integer = uni(rng);

		int n_zero = 8;
		string old_string;

		old_string = to_string(random_integer);

		std::string new_string = std::string(n_zero - old_string.length(), '0') + old_string;

		m1->setmessageid(new_string);


		m1->makemsg();

		_m.push_back(m1);

		return true;


	}
	else if (wahl == 'l') {


	}else{
		return -1;
	}

}



/*
Desc: 
	
@param 
@return 
*/

int request::setreqtype(char k) {


	
	return 0;
}


/*
Desc: setdone -> set the done marker

@param bool k
@return none
*/

void request::setdone(bool k) {

	done = k;

}

/*
Desc: getdone -> get the done marker

@param none
@return done
*/

bool request::getdone() {

	return done;

}

/*
Desc: setdone -> set the done marker

@param bool k
@return none
*/

bool request::isdone() {

	delete this;	//love this ghetto way of deleting stuff

	return true;
}




bool request::setreqid(int k) {

	reqid = k;

	return true;
}
int request::getreqid() {

	return reqid;
}


string request::getmsg(int n) {



	string out;
	std::shared_ptr<message> m;

	//if (_m.size() >= n) {
		m = _m[n];
		out = m->msg_as_s;
	//}



	m.reset();
	return out;
}