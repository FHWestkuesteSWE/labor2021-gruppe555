
#include <map>
#include "request.h"


class RequestHandler
{
public:



	unsigned int reqnr=0;

	std::map<unsigned int, request*> _reqs;


	bool cleanup();
	unsigned int createnew(char);

	request* getreq(int);
	


};

