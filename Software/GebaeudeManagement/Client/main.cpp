#include <iostream>
#include <string>
//#include "BasicClient.h"
#include "AdvancedClient.h"
#include "request.h"
#include "RequestHandler.h"
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

    
    RequestHandler _h;
    

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
            case 't': { // Temp
                int l = 0;
                l = _h.createnew(wahl);
                request* now = _h.getreq(l);
                _c.start_write(now->getmsg(0));
         
                
                break;
            }
            case 'r': { // Rollladen
                int l = 0;
                l = _h.createnew(wahl);
                request* now = _h.getreq(l);
                _c.start_write(now->getmsg(0));


                
                break;
            }
            case 'l': { // Logdaten




                break;
            }
            default: {
                cout << "Kein Kommando erkannt. Bitte erneut versuchen! :)" << "\n";
            }

        }
    } while (wahl != 'e');



    _h.cleanup();

    return 0;
}




/*
TODO:
-async recieve testen
-zweiten + dritten requesttyp
-messageid

*/