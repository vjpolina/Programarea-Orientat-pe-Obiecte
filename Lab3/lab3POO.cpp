#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

 
class Rezervare {
protected:
    string numeRezervare;
    string ora;
    string data;
    int nrPersoane;

public:
    string tip;

    virtual float pretRezervare() = 0;

   //  int timpRezervare() {
   //     float oraFin;
   //     cout << "Indicati ora iesirii (format ORA.MINUTE): ";
   //     cin >> oraFin;
   //     float oraStart = stof(ora);
   //     return (int)(oraFin - oraStart);
   //  }

    Rezervare() {}
    virtual ~Rezervare() {}

    void addRezervare(string numeClient, string oraIntrare, string dataRez, int nrClienti) {
        numeRezervare = numeClient;
        ora           = oraIntrare;
        data          = dataRez;
        nrPersoane    = nrClienti;
    }

    void afisare(float pret) {
        cout << "Tip: " << tip << endl;
        cout << "Client: " << numeRezervare << endl;
        cout << "Data: " << data << endl;
        cout << "Ora intrare: " << ora << endl;
        cout << "Nr. persoane: " << nrPersoane << endl;
        cout << "Pret total: " << pret << " lei" << endl;
    }
};

class RezervareZilnica : public Rezervare {
public:
    RezervareZilnica() { tip = "Rezervare zilnica"; }

    float pretRezervare() override {
        float pret = 50;
        if (nrPersoane > 2) {
            for (int i = 3; i <= nrPersoane; i++) {
                pret += 20;
            }
        }
        return pret;
    }
};

class RezervareEvenimentSpecial : public Rezervare {
public:
    RezervareEvenimentSpecial() { tip = "Rezervare eveniment special"; }

    float pretRezervare() override {
        float pret = 200;
        return pret;
      //  int durata = timpRezervare();
      //  if (durata > 2) {
      //       for (int i = 3; i <= durata; i++) {
      //           pret += 50;
      //       }
      //  }
      //  return pret;
    }
};

class RezervareGrupMare : public Rezervare {
public:
    RezervareGrupMare() { tip = "Rezervare grup mare"; }

    float pretRezervare() override {
        float pret = 500;

        if (nrPersoane > 20) {
            for (int i = 21; i <= nrPersoane; i++) {
                pret += 10;
            }
        }

        if (nrPersoane > 30) {
            int exOptiuni;
            cout << "Optiuni pentru petreceri mari:" << endl;
            cout << "1. Meniu extins (15 lei)" << endl;
            cout << "2. Acces bar indelungat (30 lei)" << endl;
            cout << "3. Exit" << endl;

            do {
                cin >> exOptiuni;
                switch (exOptiuni) {
                    case 1: pret += 15; break;
                    case 2: pret += 30; break;
                    case 3: break;
                    default: cout << "Nu este o optiune valabila." << endl;
                }
            } while (exOptiuni != 3);
        }

        if (nrPersoane > 50) pret -= 0.1 * pret;

        return pret;
    }
};


class RezervareVIP : public Rezervare {
public:
    RezervareVIP() { tip = "Rezervare VIP"; }

    float pretRezervare() override {
        float pret = 1000;

        if (nrPersoane > 5) {
            for (int i = 6; i <= nrPersoane; i++) {
                pret += 150;
            }
        }

        int optVIP;
        cout << "\nOptiuni premium VIP:\n1. Fotograf profesionist (300 lei)" << endl
        << "2. Decorator floral (200 lei)\n3. Chef privat (500 lei)" << endl << "4. Finalizare optiuni" << endl;

        do {
            cin >> optVIP;
            switch (optVIP) {
                case 1: pret += 300; break;
                case 2: pret += 200; break;
                case 3: pret += 500; break;
                case 4: break;
                default: cout << "Nu este o optiune valabila." << endl;
            }
        } while (optVIP != 4);

        return pret;
    }
};


Rezervare* creeazaRezervare(ifstream& listaRez) {
   string tip, nume, data, ora;
   int nrPers;

   listaRez >> tip >> nume >> data >> ora >> nrPers;

   if (listaRez.fail()) return nullptr;

   Rezervare* rez = nullptr;
   if      (tip == "RezervareZilnica") rez = new RezervareZilnica();
   else if (tip == "RezervareEvenimentSpecial") rez = new RezervareEvenimentSpecial();
   else if (tip == "RezervareGrupMare") rez = new RezervareGrupMare();
   else if (tip == "RezervareVIP") rez = new RezervareVIP();
   else return nullptr;

    rez->addRezervare(nume, ora, data, nrPers);
    return rez;
}
 
int main() {
   vector<Rezervare*> rezervari;

   ifstream listaRez("Rezervari.txt");
      if (!listaRez.is_open()) {
      cout << "Eroare: fisierul 'Rezervari.txt' nu a fost gasit." << endl;
      return 1;
   }

   while (!listaRez.eof()) {
       Rezervare* rez = creeazaRezervare(listaRez);
       if (rez) rezervari.push_back(rez);
   }
   listaRez.close();

    cout << "\nRezervari: \n" << endl;
    for (Rezervare* rez : rezervari) {
        float pret = rez->pretRezervare();
        rez->afisare(pret);
        cout<<endl<<endl;
    }

    for (Rezervare* rez : rezervari) delete rez;
    rezervari.clear();

    return 0;
}