#include <iostream>
#include <string>
using namespace std;

class Produs {
    
   private:
      string ID;
      
   protected:
      int nr_stoc;
      
   public:
      int pret, capRAM;
      string tip;
   
    
   void optiuniID();
   void updateStoc();
   void schimbPret();
   void valTotal();
   void afisDetalii();
   
   
   Produs() {
       ID = "0000000";
       pret = 0;
       nr_stoc = 0;
       capRAM = 0;
       tip = "Nedefinit";
       cout << "Constructor implicit apelat pentru " << ID << endl;
   }
   
   Produs(string id, int pr, int stoc, int ram, string t) {
       ID = id;
       pret = pr;
       nr_stoc = stoc;
       capRAM = ram;
       tip = t;
       cout << "Constructor cu parametri apelat pentru " << ID << endl;
   }
   
   Produs(const Produs &p) {
       ID = p.ID + "_COPIE";
       pret = p.pret;
       nr_stoc = p.nr_stoc;
       capRAM = p.capRAM;
       tip = p.tip;
       cout << "Constructor de copiere apelat pentru " << ID << endl;
   }
   
   
   ~Produs() {
       cout << "Destructor apelat pentru produsul " << ID << endl;
   }
};


void Produs::optiuniID() {
   int n;
   string id;
   cout << "\nID-ul produsului este: " << ID << endl;
   cout << "Doriti sa schimbati ID-ul?\n1. DA\n2. NU" << endl;
   cout << "Optiune: ";
   cin >> n;
   
   if(n == 1) {
      cout << "Introduceti noul ID: ";
      cin >> id;
      ID = id;
   }
   else if(n == 2) { return;}
   else { cout << "Optiunea selectata nu este disponibila." << endl;}
}

void Produs::updateStoc() {
   int op, var;
   cout << "\nIn stoc exista " << nr_stoc << " produs/e." << endl;
   cout << "Alegeti o optiune: " << endl;
   cout << "1. Adaugare stoc" << endl;
   cout << "2. Scadere stoc" << endl;
   cout << "Optiune: ";
   cin >> op;
   
   if(op == 1) {
      cout << "Introduceti cantitatea de adaugat: ";
      cin >> var;
      nr_stoc = nr_stoc + var;
      cout << "Actual sunt " << nr_stoc << " exemplare" << endl;
   }
   else if(op == 2) {
      cout << "Introduceti cantitatea de scazut: ";
      cin >> var;
      if(var <= nr_stoc) {
         nr_stoc = nr_stoc - var;
         cout << "Actual sunt " << nr_stoc << " exemplare" << endl;
      }
      else {
         cout << "Nu exista suficient stoc!" << endl;
      }
   }
   else {
      cout << "Optiunea selectata nu este disponibila." << endl;
   }
}

void Produs::schimbPret() {
   int pr;
   cout << "\nPretul actual: " << pret << " lei" << endl;
   cout << "Introduceti pretul nou: ";
   cin >> pr;
   
   if(pr >= 0) {
      pret = pr;
      cout << "Pretul produsului este acum " << pret << " lei." << endl;
   }
   else {
      cout << "Pretul nu poate fi negativ!" << endl;
   }
}

void Produs::valTotal() {
   cout << "In stoc exista " << nr_stoc << " exemplare, cu pretul " << pret << " lei" << endl;
   cout << "Valoarea totala a produselor este " << nr_stoc * pret << " lei." << endl;
}

void Produs::afisDetalii() {
   cout << "\nDetalii Produs" << endl;
   cout << "ID: " << ID << endl;
   cout << "Tip: " << tip << endl;
   cout << "Pret: " << pret << " lei" << endl;
   cout << "Stoc: " << nr_stoc << " exemplare" << endl;
   cout << "Capacitate RAM: " << capRAM << " GB" << endl;
}

void interfataOP(Produs &p) {
   int x;
   cout << "\n   Optiuni:" << endl;
   cout << "1. Afisare detalii produs" << endl;
   cout << "2. Gestionare pret" << endl;
   cout << "3. Gestionare stoc" << endl;
   cout << "4. Gestionare ID" << endl;
   cout << "5. Calcularea valorii totale a exemplarelor" << endl;
   cout << "6. Iesire" << endl;
   cout << "Alegeti optiunea: ";
   cin >> x;
   
   switch(x) {
      case 1: p.afisDetalii(); break;
      case 2: p.schimbPret(); break;
      case 3: p.updateStoc(); break;
      case 4: p.optiuniID(); break;
      case 5: p.valTotal(); break;
      case 6: return;
      default: cout << "Optiune indisponibila." << endl;
   }
}

void gestioneazaProdus(Produs &p) {
   int continua;
   do {
      interfataOP(p);
      
      cout << "\nDoriti sa efectuati alta operatie pe acest produs?" << endl;
      cout << "1. DA (continua cu acelasi produs)" << endl;
      cout << "2. NU (schimba produsul)" << endl;
      cout << "Optiune: ";
      cin >> continua;
      
   } while(continua == 1);
}

int main() {  
   cout<<"Produse create: "<<endl;
   Produs p1;
   Produs p2("A00112", 4900, 15, 16, "Smartphone");
   Produs p3(p2);
   

   int select;
   
   do {
      cout << "\n\n    Selectati un produs:" << endl;
      cout << "1. P1 (constructor implicit)" << endl;
      cout << "2. P2 (constructor cu parametrii)" << endl;
      cout << "3. P3 (constructor de copiere - P2)" << endl;
      cout << "0. Iesire din program" << endl;
      cout << "Optiune: ";
      cin >> select;
      
      if(select == 0) break;
      
      switch(select) {
         case 1: gestioneazaProdus(p1); break;
         case 2: gestioneazaProdus(p2); break;
         case 3: gestioneazaProdus(p3); break;
         default: cout << "\nOptiune indisponibila." << endl;
      }
      
   } while(true);
   
   
   return 0;
}