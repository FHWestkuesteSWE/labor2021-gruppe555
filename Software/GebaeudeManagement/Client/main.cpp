#include <iostream>
#include <string>
//#include "BasicClient.h"
#include "AdvancedClient.h"
#include <random>
#include <memory>
#include <vector>


using namespace std;




int main(int argc, char* argv[])
{

    

    boost::asio::io_context io_context;
    tcp::resolver r(io_context);


    char port[] = "5000";
    char ip[] = "127.0.0.1";


    AdvancedClient _c(io_context);

    _c.start(r.resolve(ip, port));

    io_context.run();


    //_c.cleanup();

    return 0;
}




/*
TODO:

 dritten requesttyp


*/