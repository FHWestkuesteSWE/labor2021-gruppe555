#include <iostream>
#include <string>
#include "BasicClient.h"
#include "request.h"


using namespace std;


int main(int argc, char* argv[])
{

    char port[] = "5000";
    char ip[] = "127.0.0.1";
    //BasicClient c(argv[1], argv[2]);
    BasicClient c(ip,port);
    //char req[1024];
    //char ans[1024];
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