/*
 
 Cristian Lupescu-Club
 
 Locatie
 Bar
 Evenimente
 
 */

#include <iostream>

using namespace std;


class Locatie{
public:
    string numeClub;
    int nrAngajati;
    int* salariiAngajati;
    const int capacitate;
    static int varstaMinima;
    
    Locatie():capacitate(200){
        
        this->numeClub="Kulturhaus";
        this->nrAngajati=4;
        this->salariiAngajati=new int[this->nrAngajati];
        this->salariiAngajati[0]=3000;
        this->salariiAngajati[1]=3500;
        this->salariiAngajati[2]=4000;
        this->salariiAngajati[3]=6000;

    }
    
    Locatie(string numeClub):capacitate(200){
        this->numeClub=numeClub;
        this->nrAngajati=0;
        this->salariiAngajati=nullptr;
    }
    
    Locatie(string numeClub, int nrAngajati, int* salarii, int cap):capacitate(cap){
        this->numeClub=numeClub;
        this->nrAngajati=nrAngajati;
        this->salariiAngajati=new int[this->nrAngajati];
        for(int i=0; i<this->nrAngajati; i++){
            this->salariiAngajati[i]=salarii[i];
        }
    }
    
    static void setVarstaMinima(int varstaNoua){
        varstaMinima=varstaNoua;
    }
    
    void afisare(){
        cout<<"Nume club: "<<this->numeClub<<endl;
        cout<<"Varsta minima pentru intrare: "<<this->varstaMinima<<endl;
        cout<<"Capacitate club: "<<capacitate<<endl;
        cout<<"Numar angajati: "<<this->nrAngajati<<endl;
        if(this->salariiAngajati==nullptr){
            cout<<"Nu exista date salariale"<<endl;
        }
        else{
            cout<<"Salarii: "<<endl;
            for(int i=0; i<this->nrAngajati; i++){
                cout<<" - "<<this->salariiAngajati[i]<<endl;
            }
        }
        
    }
};
int Locatie::varstaMinima=18;

class Bar{
public:
    int nrProduse;
    string* produse;
    int* pretProduse;
    static float TVA;
    const int nrLicenta;
    
    Bar():nrLicenta(123){
        this->nrProduse=3;
        this->produse=new string[nrProduse];
        this->produse[0]="Bere";
        this->produse[1]="Vin";
        this->produse[2]="Vodka";
        this->pretProduse=new int[nrProduse];
        this->pretProduse[0]=12;
        this->pretProduse[1]=21;
        this->pretProduse[2]=15;
    }
    
    Bar(int nrlicenta):nrLicenta(nrlicenta){
        this->nrProduse=0;
        this->produse=nullptr;
        this->pretProduse=nullptr;
    }
    
    Bar(int nrProduse, string* produse, int* pretProduse, int nrlicenta):nrLicenta(nrlicenta){
        this->nrProduse=nrProduse;
        this->produse=new string[nrProduse];
        for(int i=0; i<nrProduse; i++){
            this->produse[i]=produse[i];
        }
        this->pretProduse=new int[nrProduse];
        for(int i=0; i<nrProduse; i++){
            this->pretProduse[i]=pretProduse[i];
        }
    }
    
    static void TVAComanda(const Bar& bar, const string& numeProdus, int cantitate){
        int poz=-1;
        for(int i=0; i<bar.nrProduse; i++){
            if(bar.produse[i]==numeProdus){
                poz=i;
                break;
            }
        }
        if(poz!=-1){
            float pret=bar.pretProduse[poz];
            float pretTotalCuTva=pret*cantitate;
            float sumaTVA=(TVA/(1+TVA))*pretTotalCuTva;
            
            cout<<"Pret total comanda: "<<pretTotalCuTva<<endl;
            cout<<"Suma datorata statului pe comanda: "<<sumaTVA<<endl;
        }
        else{
            cout<<"Nu exista produsul respectiv in meniu."<<endl;
        }
    }
    
    void afisare(){
        cout<<"Meniu bar"<<endl;
        for(int i=0; i<nrProduse; i++){
            cout<<produse[i]<<" "<<pretProduse[i]<<endl;
        }
        cout<<"Preturile includ TVA"<<endl;
        cout<<"Nr. licenta: "<<nrLicenta<<endl;
        cout<<"---------------------------"<<endl;
    }
    
};
float Bar::TVA=0.19;


class Evenimente{
public:
    int nrArtisti;
    string* numeArtisti;
    string dataEveniment;
    const int pretBilet;
    static int nrBileteDisponibile;
    
    Evenimente():pretBilet(100){
        this->nrArtisti=1;
        this->numeArtisti=new string[nrArtisti];
        this->numeArtisti[0]="O-Zone";
        this->dataEveniment="14-11-2023";
    }
    
    Evenimente(string dataEveniment):pretBilet(0){
        this->nrArtisti=0;
        this->numeArtisti=nullptr;
    }
    
    Evenimente(int nrArtisti, string* nume, string dataEveniment, int pret):pretBilet(pret){
        this->nrArtisti=nrArtisti;
        this->numeArtisti=new string[nrArtisti];
        for(int i=0; i<nrArtisti; i++){
            this->numeArtisti[i]=nume[i];
        }
        this->dataEveniment=dataEveniment;
    }
    
    static void cumparaBilete(const Evenimente &ev, int nrBileteCumparate){
        if(nrBileteCumparate<=nrBileteDisponibile){
            nrBileteDisponibile-=nrBileteCumparate;
            cout<<"Suma totala: "<<nrBileteCumparate*ev.pretBilet<<" lei"<<endl;
            cout<<"Au mai ramas "<<nrBileteDisponibile<<" bilete!"<<endl;
        }
        else{
            cout<<"Nu mai sunt destule bilete."<<endl;
        }
    }
    
    void afisare(){
        
        if(numeArtisti!=nullptr){
        cout<<"Urmeaza un nou eveniment!"<<endl;
        cout<<"Artisti invitati: "<<endl;
        for(int i=0; i<this->nrArtisti; i++){
            cout<<" - "<<this->numeArtisti[i]<<endl;
        }
        cout<<pretBilet<<" lei"<<endl;
        cout<<this->dataEveniment<<endl;
        cout<<"/////////////////////////////////////////"<<endl;
        cout<<endl;
        }
        else{
            cout<<"Momentan nu sunt evenimente programate la acest club."<<endl;
            cout<<"/////////////////////////////////////////"<<endl;
            cout<<endl;
        }
    }
};
int Evenimente::nrBileteDisponibile=150;

int main(){
    
    Locatie l1;
    Locatie l2("El Comandante");
    int salarii[]={4000, 4500, 5000, 5500, 6500};
    Locatie l3("Interbelic", 5, salarii, 150);
    
    Bar b1;
    Bar b2(456);
    string produse[]={"Bere", "Shot", "Cocktail"};
    int pretProduse[]={10, 17, 30};
    Bar b3(3, produse, pretProduse, 789);
    
    Evenimente e1;
    Evenimente e2("01-01-2024");
    string nume[]={"AC/DC", "Iron Maiden", "Metallica"};
    Evenimente e3(3, nume, "16-12-2023", 300);
    
    
    l1.afisare();
    b1.afisare();
    e1.afisare();
    
    Locatie::setVarstaMinima(21);
    
    l2.afisare();
    b2.afisare();
    e2.afisare();
    
    l3.afisare();
    b3.afisare();
    e3.afisare();
    
    Bar::TVAComanda(b3, "Bere", 2);
    cout<<"-------------------------"<<endl;
    Evenimente::cumparaBilete(e3, 5);
    
    return 0;
}
