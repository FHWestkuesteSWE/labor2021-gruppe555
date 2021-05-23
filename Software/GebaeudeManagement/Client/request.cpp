#include "request.h"
#include <iostream>
#include <string>

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





	if (wahl == 't') {
		std::shared_ptr<message> m1(new message);
		string input;


		wrtemp:
		cout << "Raumtemperatur setzen oder lesen(w/r): " << "\n";
		cin >> input;
		if (input.compare("w")||input.compare("r") == 0) {
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto wrtemp;
		}
		m1->setopcode(input[0]);
		input.clear();

		troom:
		cout << "In welchem Raum?(###): " << "\n";
		cin >> input;
		if (input.length() > 3) {
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto troom;
		}
		m1->setraum(input.data());
		input.clear();

		
		//welcher sensor wurde schon bestimmt t -> temp
		m1->setsensort("t");


		tsensn:
		cout << "Welche Sensornumer?(###): " << "\n";
		cin >> input;
		if (input.length() > 3) {
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto tsensn;
		}
		m1->setsensornmr(input.data());
		input.clear();

		twert:
		cout << "Auf welchen Wert?(##,##): " << "\n";
		cin >> input;
		if (input.length() > 5) {
			cout << "Falsche Eingabe erkannt!" << "\n";
			goto twert;
		}
		input.erase(3, 1);
		m1->setwert(input.data());
		input.clear();

		m1->makemsg();

		_m.push_back(m1);
		
	}
	else if (wahl == 'r') {
		std::shared_ptr<message> m1(new message);



	}
	else {
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

	delete this;	//love this getto way of deleting stuff

	return true;
}