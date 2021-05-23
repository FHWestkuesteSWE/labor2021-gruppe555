#pragma once
#define MESSAGELENGTH 1024

class message
{
public:
	message();														//Standartkonstrutor
	message(char,int);													//Nur OPCode Message
	message(char[]);												//Custom Message
	message(char, char[8], char[3], char[2], char[3], char[4]);		//Datenabfrage oder Datenvorgabe
	message(char, char[]);											//Error oder Normale Message

	~message();														//Destrucotr


	bool setopcode(const char);
	bool setmessageid(const char[]);
	bool setraum(const char[]);
	bool setsensort(const char[]);
	bool setsensornmr(const char[]);
	bool setwert(const char[]);
	//bool setcustommsgpayload(const char []);

	bool convertmid();

	bool makemsg();


private:

	// Message Typ0 def
	char opcode;
	char messageid[8];
	char raum[3];
	char sensort[2];
	char sensornmr[3];
	char wert[4];

	int type;	//MessageType

	//Payload
	char payload[MESSAGELENGTH-1];
	int messageid_as_int;

public:
	char msg[MESSAGELENGTH];


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

