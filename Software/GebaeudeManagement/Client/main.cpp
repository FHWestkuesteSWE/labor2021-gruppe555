#include <iostream>
#include "BasicClient.h"

using namespace std;
int main(int argc, char* argv[])
{

    char port[] = "5000";
    char ip[] = "127.0.0.1";
    //BasicClient c(argv[1], argv[2]);
    BasicClient c(ip,port);
    char req[1024];
    char ans[1024];
    char wahl;
    do {
        std::cout << "Gebauedeleitsystem FHW 3000\n";
        cout << "Was wollen Sie tun: " << "\n";
        cout << "----------------------------------------------------" << "\n";
        cout << "Aktuelle Raumtemperatur ueberpruefen \t(t)" << "\n";
        cout << "Aussentueren oeffnen / schliessen \t(a)" << "\n";
        cout << "..." << "\n";
        cout << "Beenden \t\t\t\t(e)" << "\n";
        cout << "----------------------------------------------------" <<"\n";
        cout << "Ihre Wahl: ";
        cin >> wahl;
        switch (wahl) {
        case 't': // req zusammenbauen
            
            c.sendRequest(req, ans);
            cout << ans << "\n";
            break;
        default:;

        }
    } while (wahl != 'e');
}

