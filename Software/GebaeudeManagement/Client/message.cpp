#include "message.h"
#include <stdio.h>
#include <string>



/*
Desc: Constructor
@param None
@return None
*/
message::message() {



}

/*
Desc: Destructor
@param None
@return None
*/
message::~message() {



}


bool message::setopcode(string t) {
	opcode = t;
	return true;
}

bool message::setmessageid(string t) {
	messageid = t;
	return true;
}

bool message::setraum(string t) {
	raum = t;
	return true;
}

bool message::setsensort(string t) {
	sensort = t;
	return true;
}

bool message::setsensornmr(string t) {
	sensornmr = t;
	return true;
}

bool message::setwert(string t) {
	wert = t;
	return true;
}

/*
Desc: Converts char message id to int
@param None
@return None
*/
bool message::convertmid() {
	messageid_as_int = std::stoi(messageid,0,10);
	return true;
}


/*
Desc: Makes a Message
@param None
@return None
*/
bool message::makemsg() {

	msg_as_s += opcode;
	msg_as_s += messageid;
	msg_as_s += raum;
	msg_as_s += sensort;
	msg_as_s += sensornmr;
	msg_as_s += wert;
	msg_as_s += '\0';


	strncpy_s(msg_as_c, 1024, msg_as_s.c_str(),sizeof(msg_as_s.c_str()));

	return true;
}
