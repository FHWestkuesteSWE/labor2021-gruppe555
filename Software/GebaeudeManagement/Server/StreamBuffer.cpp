#include "StreamBuffer.h"
#include <cstring>
#include <string>
#include <cmath>

InstructionBuffer::InstructionBuffer(char* char_stream)
{
	int i = 0; 
	while (char_stream[i] != '\0' && i != 22) i++;

	if(i > 1) this->opcode = char_stream[0];
	if(i > 8) std::memcpy(this->txt_msg_id, &char_stream[1], 8);
	if(i > 11) std::memcpy(this->txt_raum_id, &char_stream[9], 3);
	if(i > 13) std::memcpy(this->txt_obj_type, &char_stream[12], 2);
	if(i > 16) std::memcpy(this->txt_obj_id, &char_stream[14], 3);
	if(i > 20) std::memcpy(this->txt_value, &char_stream[17], 4);
}

InstructionBuffer::~InstructionBuffer()
{
}

std::string InstructionBuffer::get_raum()
{
	std::string temp;
	temp = this->txt_raum_id[0];
	temp += this->txt_raum_id[1];
	temp += this->txt_raum_id[2];
	return temp;
}

InstructionBuffer& InstructionBuffer::operator=(InstructionBufferData& rhs)
{
	this->opcode = rhs.opcode;
	this->txt_msg_id[0] = (rhs.msg_id / 10000000) + 48;
	this->txt_msg_id[1] = ((rhs.msg_id / 1000000) % 10) + 48;
	
	for (int i = 0; i < 8; i++) this->txt_msg_id[i] = ((rhs.msg_id / (int)pow(10, 7 - i)) % 10) + 48;
	for (int i = 0; i < 3; i++) this->txt_raum_id[i] = ((rhs.raum_id / (int)pow(10, 2 - i)) % 10) + 48;
	for (int i = 0; i < 2; i++) this->txt_obj_type[i] = ((rhs.obj_type / (int)pow(10, 1 - i)) % 10) + 48;
	for (int i = 0; i < 3; i++) this->txt_obj_id[i] = ((rhs.obj_id / (int)pow(10, 2 - i)) % 10) + 48;
	
	unsigned int vorkomma = (int)floor(rhs.value);
	unsigned int nachkomma = ((int)floor(rhs.value * 100)) % 100;
	
	for (int i = 0; i < 2; i++) this->txt_value[i] = ((vorkomma / (int)pow(10, 1 - i)) % 10) + 48;
	for (int i = 0; i < 2; i++) this->txt_value[i + 2] = ((nachkomma / (int)pow(10, 1 - i)) % 10) + 48;
	return *this;
}

std::string InstructionBuffer::operator()(void)
{
	std::string temp;
	for (int i = 0; i < sizeof(InstructionBuffer) - 1; i++) {
		temp += ((char*)this)[i];
	}
	return temp;
}

InstructionBufferData::InstructionBufferData()
{
}

InstructionBufferData::~InstructionBufferData()
{
}

InstructionBufferData& InstructionBufferData::operator=(InstructionBuffer& rhs)
{
	this->opcode = rhs.opcode;

	char temp_msg[9] = { rhs.txt_msg_id[0], rhs.txt_msg_id[1], rhs.txt_msg_id[2], rhs.txt_msg_id[3], rhs.txt_msg_id[4],
						rhs.txt_msg_id[5], rhs.txt_msg_id[6], rhs.txt_msg_id[7], '\0' };
	this->msg_id = std::atoi(temp_msg);
	char temp_raum[4] = { rhs.txt_raum_id[0], rhs.txt_raum_id[1], rhs.txt_raum_id[2], '\0' };
	this->raum_id = std::atoi(temp_raum);
	char temp_type[3] = { rhs.txt_obj_type[0], rhs.txt_obj_type[1], '\0' };
	this->obj_type = std::atoi(temp_type);
	char temp_id[4] = { rhs.txt_obj_id[0], rhs.txt_obj_id[1], rhs.txt_obj_id[2], '\0' };
	this->obj_id = std::atoi(temp_id);
	
	char vorkomma[3] = { rhs.txt_value[0], rhs.txt_value[1], '\0' };
	char nachkomma[3] = { rhs.txt_value[2], rhs.txt_value[2], '\0' };
	
	this->value = std::atoi(vorkomma) + std::atoi(nachkomma) / 100.0f;
	return *this;
}

MsgBuffer::MsgBuffer(char* char_stream)
{
	int i = 0;
	while (char_stream[i] != '/0' && i != 1024) i++;

	this->opcode = char_stream[0];
	memcpy(this->txt_msg_id, &char_stream[1], 8);
	if(i > 9) memcpy(this->txt_msg_data, &char_stream[9], i - 9);
}

MsgBuffer::~MsgBuffer()
{
}
