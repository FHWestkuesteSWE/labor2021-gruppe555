#include <iostream>
#include <string>
//#include "BasicClient.h"
#include "AdvancedClient.h"
#include "request.h"
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


    //BasicClient c(argv[1], argv[2]);
    //BasicClient c(ip,port);







    char wahl;
    do {
        std::cout << "Gebauedeleitsystem FHW 3000\n";
        cout << "Was wollen Sie tun: " << "\n";
        cout << "----------------------------------------------------" << "\n";
        cout << "Aktuelle Raumtemperatur ueberpruefen / setzen \t(t)" << "\n";
        cout << "Rollladen oeffnen / schliessen \t(r)" << "\n";
        cout << "LogDaten vom Server holen \t(l)" << "\n";
        cout << "..." << "\n";
        cout << "Beenden \t\t\t\t(e)" << "\n";
        cout << "----------------------------------------------------" <<"\n";
        cout << "Ihre Wahl: ";
        cin >> wahl;
        switch (wahl) {
            case 't': { // req zusammenbauen

                request* n1 = new request();

                n1->createreq('t');

                std::shared_ptr<message> msg1(n1->_m.front());

                _c.start_write(msg1->msg);

                delete n1;
                //c.sendRequest(req, ans);
                //cout << ans << "\n";
                break;
            }
            default: {

            }

        }
    } while (wahl != 'e');

    //cleanup();
    return 0;
}




/*
TODO:
-Client Async mit callback
-message zusammenfügen
-zweiten requesttyp
-cleanup
-vector<shared_ptr<request>> _r;

*/