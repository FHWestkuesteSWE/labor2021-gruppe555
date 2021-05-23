#define MESSAGELENGTH 1024

#include <vector>
#include <memory>
#include "message.h"

class request {

public:
	request();
	request(char);
	~request();

	int createreq(char wahl);
	int setreqtype(char);

	std::vector<std::shared_ptr<message>> _m;



	bool setreqid();
	int getreqid();

	void setdone(bool);
	bool getdone();

	bool isdone();

private:

	bool done;
	char wahl;
	int reqid;		//reqid = messageid;

protected:

};


