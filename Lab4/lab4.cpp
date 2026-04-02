#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class IRezervare {
public:
    virtual float calculeazaDurata() const = 0;
    virtual double calculeazaPret() const = 0;
    virtual ~IRezervare() {}
};

class Rezervare : public IRezervare {
protected:
    string numeRezervare;
    string ora;
    string oraFinal;
    string data;
    int nrPersoane;

    int toMinutes(const string& t) const {
        int h = stoi(t.substr(0, 2));
        int m = stoi(t.substr(3, 2));
        return h * 60 + m;
    }

public:
    string tip;

    Rezervare() : nrPersoane(0) {}

    Rezervare(string numeClient, string dataRez, string oraIntrare, string oraIesire, int nrClienti)
        : numeRezervare(numeClient), data(dataRez), ora(oraIntrare),
          oraFinal(oraIesire), nrPersoane(nrClienti) {}

    virtual ~Rezervare() {}

    float calculeazaDurata() const override {
        return (toMinutes(oraFinal) - toMinutes(ora)) / 60;
    }

    double calculeazaPret() const override = 0;

    int timpRezervare() {
        return calculeazaDurata();
    }

    virtual float pretRezervare() {
        return (float)calculeazaPret();
    }

    void addRezervare(string numeClient, string oraIntrare, string oraIesire, string dataRez, int nrClienti) {
        numeRezervare = numeClient;
        ora = oraIntrare;
        oraFinal = oraIesire;
        data = dataRez;
        nrPersoane = nrClienti;
    }

    void afisare() {
        cout << "Tip: "<< tip<< endl;
        cout << "Client: " << numeRezervare<< endl;
        cout << "Data: "<< data << endl;
        cout << "Ora: "<< ora << " - " << oraFinal << endl;
        cout << "Durata: "<< calculeazaDurata()<< " ore" << endl;
        cout << "Nr. persoane: "<< nrPersoane<< endl;
        cout << "Pret total: " << calculeazaPret() << " lei" << endl;
    }
};

class RezervareZilnica : public Rezervare {
public:
    RezervareZilnica() { tip = "Rezervare zilnica"; }

    RezervareZilnica(string numeClient, string dataRez, string oraIntrare, string oraIesire, int nrClienti)
        : Rezervare(numeClient, dataRez, oraIntrare, oraIesire, nrClienti) {
        tip = "Rezervare zilnica";
    }

    double calculeazaPret() const override {
        double pret = 50;
        if (nrPersoane > 2)
            for (int i = 3; i <= nrPersoane; i++)
                pret += 20;
        return pret;
    }
};

class RezervareEvenimentSpecial : public Rezervare {
public:
    RezervareEvenimentSpecial() { tip = "Rezervare eveniment special"; }

    double calculeazaPret() const override {
        double pret = 200;
        int durata = calculeazaDurata();
        if (durata > 2)
            for (int i = 3; i <= durata; i++)
                pret += 50;
        return pret;
    }
};

class RezervareGrupMare : public Rezervare {
public:
    RezervareGrupMare() { tip = "Rezervare grup mare"; }

    double calculeazaPret() const override {
        double pret = 500;
        if (nrPersoane > 20)
            for (int i = 21; i <= nrPersoane; i++)
                pret += 10;
        if (nrPersoane > 50) pret -= 0.1 * pret;
        return pret;
    }

    float pretRezervare() override {
        double pret = calculeazaPret();
        if (nrPersoane > 30) {
            int exOptiuni;
            do {
                cout << "Optiuni pentru petreceri mari:" << endl;
                cout << "1. Meniu extins (15 lei)"<< endl;
                cout << "2. Acces bar indelungat (30 lei)"<< endl;
                cout << "3. Exit"<< endl;
                cout << "Alegeti optiunea: ";
                cin >> exOptiuni;
                switch (exOptiuni) {
                    case 1: pret += 15; cout << "A fost adaugata optiunea!\n"; break;
                    case 2: pret += 30; cout << "A fost adaugata optiunea!\n"; break;
                    case 3: break;
                    default: cout << "Nu este o optiune valabila.\n";
                }
            } while (exOptiuni != 3);
        }
        return (float)pret;
    }
};

class RezervareVIP : public Rezervare {
public:
    RezervareVIP() { tip = "Rezervare VIP"; }

    double calculeazaPret() const override {
        double pret = 1000;
        if (nrPersoane > 5)
            for (int i = 6; i <= nrPersoane; i++)
                pret += 150;
        return pret;
    }

    float pretRezervare() override {
        double pret = calculeazaPret();
        int optVIP;
        do {
            cout << "\nOptiuni premium VIP:"<< endl
                 << "1. Fotograf profesionist (300 lei)"  << endl
                 << "2. Decorator floral (200 lei)"<< endl
                 << "3. Chef privat (500 lei)" << endl
                 << "4. Finalizare optiuni"<< endl
                 << "Alegeti o optiune: ";
            cin >> optVIP;
            switch (optVIP) {
                case 1: pret += 300; cout << "A fost adaugata optiunea!\n"; break;
                case 2: pret += 200; cout << "A fost adaugata optiunea!\n"; break;
                case 3: pret += 500; cout << "A fost adaugata optiunea!\n"; break;
                case 4: break;
                default: cout << "Nu este o optiune valabila." << endl;
            }
        } while (optVIP != 4);
        return (float)pret;
    }
};

Rezervare* creeazaRezervare(ifstream& listaRez) {
    string tip, nume, data, ora, oraFinal;
    int nrPers;
    listaRez >> tip >> nume >> data >> ora >> oraFinal >> nrPers;
    if (listaRez.fail()) return nullptr;

    Rezervare* rez = nullptr;
    if (tip == "RezervareZilnica") rez = new RezervareZilnica();
    else if (tip == "RezervareEvenimentSpecial") rez = new RezervareEvenimentSpecial();
    else if (tip == "RezervareGrupMare") rez = new RezervareGrupMare();
    else if (tip == "RezervareVIP") rez = new RezervareVIP();
    else return nullptr;

    rez->addRezervare(nume, ora, oraFinal, data, nrPers);
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

    rezervari.push_back(new RezervareZilnica("Tudor Popescu", "2025-02-27", "19:00", "21:30", 4));

    cout << "\nRezervari:\n" << endl;
    for (Rezervare* rez : rezervari) {
        rez->afisare();
        cout << endl << endl;
    }

    for (Rezervare* rez : rezervari) delete rez;
    rezervari.clear();
    return 0;
}