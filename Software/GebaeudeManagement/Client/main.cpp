// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

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
        cout << "Was wollen Sie tun: " << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Aktuelle Raumtemperatur ueberpruefen \t(t)" << endl;
        cout << "Aussentueren oeffnen / schliessen \t(a)" << endl;
        cout << "..." << endl;
        cout << "Beenden \t\t\t\t(e)" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "Ihre Wahl: ";
        cin >> wahl;
        switch (wahl) {
        case 't': // req zusammenbauen
            
            c.sendRequest("test", ans);
            cout << ans << "\n";
            break;
        default:;

        }
    } while (wahl != 'e');
}

//ich bin ein kommentar
//ich bin ein zweiterkommentar
