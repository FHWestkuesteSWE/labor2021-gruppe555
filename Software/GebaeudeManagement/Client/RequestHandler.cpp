#include "RequestHandler.h"




bool RequestHandler::cleanup() {

	for (std::map<unsigned int, request*>::iterator it = _reqs.begin(); it != _reqs.end(); ++it)
		delete it->second;

	return true;
}


unsigned int RequestHandler::createnew(char k) {

	request* r = new request();

	r->createreq(k);
	r->setdone(false);
	r->setreqid(reqnr);

	

	_reqs.emplace(reqnr, r);

	reqnr++;

	return reqnr-1;
}

request* RequestHandler::getreq(int n) {

	return _reqs[n];

}