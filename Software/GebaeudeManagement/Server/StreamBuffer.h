#pragma once
#include <string>

class InstructionBufferData;

class InstructionBuffer {
public:
	InstructionBuffer(char* char_stream);
	~InstructionBuffer();

	char opcode = 0;
	char txt_msg_id[8] = {0};
	char txt_raum_id[3] = {0};
	char txt_obj_type[2] = {0};
	char txt_obj_id[3] = {0};
	char txt_value[4] = {0};
	char endl_bit = '\0';

	std::string get_raum();

	InstructionBuffer& operator=(InstructionBufferData& rhs);
	std::string operator()(void);
};

class InstructionBufferData {
public:
	InstructionBufferData();
	~InstructionBufferData();

	char opcode = 0;
	int msg_id = 0;
	int raum_id = 0;
	int obj_type = 0;
	int obj_id = 0;
	float value = 0.0f;

	InstructionBufferData& operator=(InstructionBuffer& rhs);
};

class MsgBuffer {
public:
	MsgBuffer(char* char_stream);
	~MsgBuffer();

	char opcode = 0;
	char txt_msg_id[8] = {0};
	char txt_msg_data[1015] = {0};
};