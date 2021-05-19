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
Desc: Constructor
@param None
@return None
*/
message::message(char opc,int typ) {

	opcode = opc;
	type = typ;

}

/*
Desc: Constructor
@param None
@return None
*/
message::message(char[]) {



}

/*
Desc: Constructor
@param None
@return None
*/
message::message(char, char[8], char[3], char[2], char[3], char[4]) {



}

/*
Desc: Constructor
@param None
@return None
*/
message::message(char, char[]) {



}

/*
Desc: Destructor
@param None
@return None
*/
message::~message() {



}


bool message::setopcode(const char t[]) {
	strncpy(&opcode, t, 1);
	return true;
}

bool message::setmessageid(const char t[]) {
	strncpy(messageid, t, 8);
	return true;
}

bool message::setraum(const char t[]) {
	strncpy(raum,t,3);
	return true;
}

bool message::setsensort(const char t[]) {
	strncpy(sensort,t,2);
	return true;
}

bool message::setsensornmr(const char t[]) {
	strncpy(sensornmr, t, 3);
	return true;
}

bool message::setwert(const char t[]) {
	strncpy(wert, t, 4);
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
	msg[0] = opcode;
	if (type == 0) {
		strncpy(&msg[1], messageid, 8);
		strncpy(&msg[1 + 8], raum, 3);
		strncpy(&msg[1 + 8 + 3], sensort, 2);
		strncpy(&msg[1 + 8 + 3 + 2], sensornmr, 3);
		strncpy(&msg[1 + 8 + 3 + 2 + 3], wert, 4);
		for (int i = 22; i < MESSAGELENGTH; i++)
			msg[i] = 0;
	}

	return true;
}
