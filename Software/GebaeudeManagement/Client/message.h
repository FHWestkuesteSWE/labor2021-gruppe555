#pragma once
#define MESSAGELENGTH 1024

#include <string>

using namespace std;

class message
{
public:
	message();														//Standartkonstrutor
	~message();														//Destrucotr


	bool setopcode(string);
	bool setmessageid(string);
	bool setraum(string);
	bool setsensort(string);
	bool setsensornmr(string);
	bool setwert(string);
	//bool setcustommsgpayload(const char []);

	bool convertmid();

	bool makemsg();


private:

	// Message Typ0 def
	string opcode;
	string messageid;
	string raum;
	string sensort;
	string sensornmr;
	string wert;

	int type;	//MessageType

	//Payload
	char payload[MESSAGELENGTH-1];
	int messageid_as_int;

public:
	char msg_as_c[MESSAGELENGTH];
	string msg_as_s;


};


/*
* Message Types
* 
Typ 0 = w/r (1char) raum#(3chars) sensortyp(2char) sensor#(3char)  wert(2 chars, 2 chars) (für read und write)
Typ 1 = e errormsg (<=1023 chars)
Typ 2 = m msgdata(<=1023 chars)
Typ 3 = l raum#(3chars) //anfrage
Typ 4 = l logdata (<=1023 chars) //antwort für später
*/

