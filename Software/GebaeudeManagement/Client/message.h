#pragma once
#define MESSAGELENGTH 1024

class message
{
public:
	message();														//Standartkonstrutor
	message(char );													//Nur OPCode Message
	message(char[]);												//Custom Message
	message(char, char[8], char[3], char[2], char[3], char[4]);		//Datenabfrage oder Datenvorgabe
	message(char, char[]);											//Error oder Normale Message

	~message();														//Destrucotr


	bool setopcode(const char[]);
	bool setmessageid(const char[]);
	bool setraum(const char[]);
	bool setsensort(const char[]);
	bool setsensornmr(const char[]);
	bool setwert(const char[]);


private:

	// Message def
	char opcode;
	char messageid[8];
	char raum[3];
	char sensort[2];
	char sensornmr[3];
	char wert[4];

	//Payload
	char payload[MESSAGELENGTH];

	int messageid_asint;

};

