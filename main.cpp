/*

 Cristian Lupescu-Club

 Locatie
 Bar
 Evenimente

 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


class Locatie {
private:
    string numeClub;
    int nrAngajati;
    int* salariiAngajati;
    const int capacitate;
    static int varstaMinima;

public:

    string getNumeClub() {
        return this->numeClub;
    }

    void setNumeClub(string numeClub) {
        if (numeClub.length() > 3) {
            this->numeClub = numeClub;
        }
    }

    int getNrAngajati() {
        return this->nrAngajati;
    }

    void setNrAngajati(int nrAngajati, int* salariiNoi) {
        if (nrAngajati >= 0) {
            this->nrAngajati = nrAngajati;
            if (this->salariiAngajati != NULL) {
                delete[]this->salariiAngajati;
            }

            this->salariiAngajati = new int[nrAngajati];

            for (int i = 0; i < nrAngajati; i++) {
                this->salariiAngajati[i] = salariiNoi[i];
            }

        }
    }

    int getSalariuAngajat(int i) {
        if (i >= 0 && i < nrAngajati) {
            return this->salariiAngajati[i];
        }
        return -1;
    }

    void setSalariuAngajat(int i, int salariu) {
        if (i >= 0 && i < nrAngajati) {
            salariiAngajati[i] = salariu;
        }
    }

    int getCapacitate() const {
        return this->capacitate;
    }

    static int getVarstaMinima() {
        return varstaMinima;
    }

    static void setVarstaMinima(int varstaNoua) {
        varstaMinima = varstaNoua;
    }


    Locatie() :capacitate(200) {

        this->numeClub = "Kulturhaus";
        this->nrAngajati = 4;
        this->salariiAngajati = new int[this->nrAngajati];
        this->salariiAngajati[0] = 3000;
        this->salariiAngajati[1] = 3500;
        this->salariiAngajati[2] = 4000;
        this->salariiAngajati[3] = 6000;

    }

    Locatie(string numeClub) :capacitate(200) {
        this->numeClub = numeClub;
        this->nrAngajati = 0;
        this->salariiAngajati = nullptr;
    }

    Locatie(string numeClub, int nrAngajati, int* salarii, int cap) :capacitate(cap) {
        this->numeClub = numeClub;
        this->nrAngajati = nrAngajati;
        this->salariiAngajati = new int[this->nrAngajati];
        for (int i = 0; i < this->nrAngajati; i++) {
            this->salariiAngajati[i] = salarii[i];
        }
    }

    ~Locatie() {
        delete[] this->salariiAngajati;
    }

    Locatie(const Locatie& l) : capacitate(l.capacitate) {
        this->numeClub = l.numeClub;
        this->nrAngajati = l.nrAngajati;
        this->salariiAngajati = new int[this->nrAngajati];
        for (int i = 0; i < this->nrAngajati; i++) {
            this->salariiAngajati[i] = l.salariiAngajati[i];
        }
    }

    Locatie& operator=(const Locatie& l) {
        if (this != &l) {
            this->numeClub = l.numeClub;
            this->nrAngajati = l.nrAngajati;
            if (this->salariiAngajati != nullptr) {
                delete[] this->salariiAngajati;
            }
            this->salariiAngajati = new int[this->nrAngajati];
            for (int i = 0; i < this->nrAngajati; i++) {
                this->salariiAngajati[i] = l.salariiAngajati[i];
            }
        }
        return *this;
    }

    Locatie& operator+(const Locatie& l) {
        int* aux = new int[this->nrAngajati];
        int intAux = this->nrAngajati;
        for (int i = 0; i < this->nrAngajati; i++) {
            aux[i] = this->salariiAngajati[i];
        }
        this->nrAngajati += l.nrAngajati;
        if (this->salariiAngajati != nullptr) {
            delete[]this->salariiAngajati;
        }
        this->salariiAngajati = new int[this->nrAngajati];
        for (int i = 0; i < intAux; i++) {
            this->salariiAngajati[i] = aux[i];
        }
        for (int i = 0, j = intAux; i < l.nrAngajati && j < this->nrAngajati; i++, j++) {
            this->salariiAngajati[j] = l.salariiAngajati[i];
        }

        return *this;
    }

    bool operator<(const Locatie& l) {
        return this->capacitate < l.capacitate;
    }

    friend ostream& operator<<(ostream& os, const Locatie& l) {
        os << "Nume club: " << l.numeClub << endl;
        os << "Varsta minima pentru intrare: " << l.varstaMinima << endl;
        os << "Capacitate club: " << l.capacitate << endl;
        os << "Numar angajati: " << l.nrAngajati << endl;
        if (l.nrAngajati<=0) {
            os << "Nu exista date salariale" << endl;
        }
        else {
            os << "Salarii: " << endl;
            for (int i = 0; i < l.nrAngajati; i++) {
                os << " - " << l.salariiAngajati[i] << endl;
            }
        }

        return os;
    }

    friend ofstream& operator<<(ofstream& of, const Locatie& l) {
        of << l.numeClub << endl;
        of << l.varstaMinima << endl;
        of << l.capacitate << endl;
        of << l.nrAngajati << endl;
        if (l.nrAngajati==0) {
            of << "Nu exista date salariale" << endl;
        }
        else {
            for (int i = 0; i < l.nrAngajati; i++) {
                of << l.salariiAngajati[i] << endl;
            }
            
        }

        return of;
    }

    friend ifstream& operator>>(ifstream& in, Locatie& l) {
        getline(in, l.numeClub);
        int val = 0;
        in >> val;//varstaMinima
        in >> val;//capacitate
        in >> l.nrAngajati;
        if (l.nrAngajati == 0) {
            return in;
        }
        else {
            for (int i = 0; i < l.nrAngajati; i++) {
                in >> l.salariiAngajati[i];
            }
            return in;
        }
    }

    void afisare() {
        cout << "Nume club: " << this->numeClub << endl;
        cout << "Varsta minima pentru intrare: " << this->varstaMinima << endl;
        cout << "Capacitate club: " << capacitate << endl;
        cout << "Numar angajati: " << this->nrAngajati << endl;
        if (this->salariiAngajati == nullptr) {
            cout << "Nu exista date salariale" << endl;
        }
        else {
            cout << "Salarii: " << endl;
            for (int i = 0; i < this->nrAngajati; i++) {
                cout << " - " << this->salariiAngajati[i] << endl;
            }
        }

    }
};
int Locatie::varstaMinima = 18;

class Bar {
private:
    int nrProduse;
    string* produse;
    int* pretProduse;
    static float TVA;
    const int nrLicenta;

public:

    string getNumeProdus(int i) {
        if (i >= 0 && i < this->nrProduse) {
            return this->produse[i];
        }
        return "";
    }

    void setNumeProdus(int i, string nume) {
        if (i >= 0 && i < this->nrProduse) {
            this->produse[i] = nume;
        }
    }

    int getPretProdus(int i) {
        if (i >= 0 && i < this->nrProduse) {
            return this->pretProduse[i];
        }
        return -1;
    }

    void setPretProdus(int i, int pret) {
        if (i >= 0 && i < this->nrProduse) {
            this->pretProduse[i] = pret;
        }
    }

    int getNrProduse() {
        return this->nrProduse;
    }

    void setNrProduse(int nrNouProduse, string* produseNoi, int* preturiNoi) {
        if (nrNouProduse >= 0) {
            this->nrProduse = nrNouProduse;
            if (this->produse != nullptr && this->pretProduse != nullptr) {
                delete[]this->produse;
                delete[]this->pretProduse;
            }

            this->produse = new string[nrNouProduse];
            this->pretProduse = new int[nrNouProduse];

            for (int i = 0; i < nrNouProduse; i++) {
                this->produse[i] = produseNoi[i];
                this->pretProduse[i] = preturiNoi[i];
            }

        }

    }

    int getNrLicenta() const {
        return this->nrLicenta;
    }

    static float getTVA() {
        return TVA;
    }

    static void setTVA(float TVANou) {
        TVA = TVANou;
    }

    Bar() :nrLicenta(123) {
        this->nrProduse = 3;
        this->produse = new string[nrProduse];
        this->produse[0] = "Bere";
        this->produse[1] = "Vin";
        this->produse[2] = "Vodka";
        this->pretProduse = new int[nrProduse];
        this->pretProduse[0] = 12;
        this->pretProduse[1] = 21;
        this->pretProduse[2] = 15;
    }

    Bar(int nrlicenta) :nrLicenta(nrlicenta) {
        this->nrProduse = 0;
        this->produse = nullptr;
        this->pretProduse = nullptr;
    }

    Bar(int nrProduse, string* produse, int* pretProduse, int nrlicenta) :nrLicenta(nrlicenta) {
        this->nrProduse = nrProduse;
        this->produse = new string[nrProduse];
        for (int i = 0; i < nrProduse; i++) {
            this->produse[i] = produse[i];
        }
        this->pretProduse = new int[nrProduse];
        for (int i = 0; i < nrProduse; i++) {
            this->pretProduse[i] = pretProduse[i];
        }
    }

    ~Bar() {
        delete[] this->produse;
        delete[] this->pretProduse;
    }

    Bar(const Bar& b) : nrLicenta(b.nrLicenta) {
        this->nrProduse = b.nrProduse;
        this->produse = new string[this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++) {
            this->produse[i] = b.produse[i];
        }
        this->pretProduse = new int[this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++) {
            this->pretProduse[i] = b.pretProduse[i];
        }
    }

    Bar& operator=(const Bar& b) {
        if (this != &b) {
            this->nrProduse = b.nrProduse;
            if (this->produse != nullptr) {
                delete[] this->produse;
            }
            this->produse = new string[this->nrProduse];
            for (int i = 0; i < this->nrProduse; i++) {
                this->produse[i] = b.produse[i];
            }
            if (this->pretProduse != nullptr) {
                delete[] this->pretProduse;
            }
            this->pretProduse = new int[this->nrProduse];
            for (int i = 0; i < this->nrProduse; i++) {
                this->pretProduse[i] = b.pretProduse[i];
            }
        }
        return *this;
    }

    Bar operator++() {
        string* auxProduse = new string[this->nrProduse];
        int* auxPreturi = new int[this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++) {
            auxProduse[i] = this->produse[i];
            auxPreturi[i] = this->pretProduse[i];
        }
        this->nrProduse += 1;
        if (this->produse != nullptr) {
            delete[]this->produse;
            delete[]this->pretProduse;
        }
        this->produse = new string[this->nrProduse];
        this->pretProduse = new int[this->nrProduse];
        for (int i = 0; i < (this->nrProduse - 1); i++) {
            this->produse[i] = auxProduse[i];
            this->pretProduse[i] = auxPreturi[i];
        }
        this->produse[this->nrProduse - 1] = "N/A";
        this->pretProduse[this->nrProduse - 1] = NULL;

        return *this;
    }

    Bar operator++(int) {
        Bar temp = *this;

        string* auxProduse = new string[this->nrProduse];
        int* auxPreturi = new int[this->nrProduse];
        for (int i = 0; i < this->nrProduse; i++) {
            auxProduse[i] = this->produse[i];
            auxPreturi[i] = this->pretProduse[i];
        }
        this->nrProduse += 1;
        if (this->produse != nullptr) {
            delete[]this->produse;
            delete[]this->pretProduse;
        }
        this->produse = new string[this->nrProduse];
        this->pretProduse = new int[this->nrProduse];
        for (int i = 0; i < (this->nrProduse - 1); i++) {
            this->produse[i] = auxProduse[i];
            this->pretProduse[i] = auxPreturi[i];
        }
        this->produse[this->nrProduse - 1] = "N/A";
        this->pretProduse[this->nrProduse - 1] = NULL;

        return temp;
    }
    
    friend ostream& operator<<(ostream& os, const Bar& b) {
        os << "Meniu bar" << endl;
        for (int i = 0; i < b.nrProduse; i++) {
            os << b.produse[i] << " " << b.pretProduse[i] << endl;
        }
        os << "Preturile includ TVA" << endl;
        os << "Nr. licenta: " << b.nrLicenta << endl;
        os << "---------------------------" << endl;

        return os;
    }

    friend ofstream& operator<<(ofstream& of, const Bar& b) {
        of << b.nrProduse << endl;
        for (int i = 0; i < b.nrProduse; i++) {
            of << b.produse[i] << endl;
            of<<b.pretProduse[i] << endl;
        }
        of << b.TVA << endl;
        of << b.nrLicenta << endl;

        return of;
    }


    friend istream& operator>>(istream& is, Bar& b) {
        cout << "Introduceti nr produse: " << endl;
        is >> b.nrProduse;
        cout << "Introduceti produsele si pretul lor: " << endl;
        
        if (b.nrProduse > 0) {
            for (int i = 0; i < b.nrProduse; i++) {
                is >> b.produse[i];
                is >> b.pretProduse[i];
            }
        }
        cout << "Introduceti TVA: " << endl;
        is >> b.TVA;

        return is;
    }

    friend ifstream& operator>>(ifstream& in, Bar& b) {
        in >> b.nrProduse;
       
        for (int i = 0; i < b.nrProduse; i++) {
            in >> b.produse[i];
            in >> b.pretProduse[i];
        }
        float val = 0;
        in >> val;//TVA
        in >>val;//nrLicenta
        return in;

    }
    void scriere(const char* fileName) const {
        ofstream file(fileName, ios::binary | ios::out);

        file.write((char*)&nrProduse, sizeof(int));

        for (int i = 0; i < nrProduse; ++i) {
            int produsLungime = produse[i].length() + 1;
            file.write((char*)&produsLungime, sizeof(int));
            file.write(produse[i].c_str(), produsLungime);

            // Check that the index is within bounds before writing
            if (i < nrProduse) {
                file.write((char*)&pretProduse[i], sizeof(int));
            }
        }

        file.write((char*)&TVA, sizeof(float));
        file.write((char*)&nrLicenta, sizeof(int));

        file.close();
    }

    void citire(const std::string& fileName) {
        ifstream file(fileName, ios::binary | ios::in);

        if (produse != nullptr) {
            delete[] produse;
        }
        if (pretProduse != nullptr) {
            delete[] pretProduse;
        }

        file.read((char*)&nrProduse, sizeof(int));

        produse = new string[nrProduse];
        pretProduse = new int[nrProduse];
        for (int i = 0; i < nrProduse; ++i) {
            int numeLungime;
            file.read((char*)&numeLungime, sizeof(int));

            char* nume = new char[numeLungime];
            file.read(nume, numeLungime);
            produse[i] = string(nume);
            delete[] nume;

            if (i < nrProduse) {
                file.read((char*)&pretProduse[i], sizeof(int));
            }
        }

        file.read((char*)&TVA, sizeof(float));
        file.read((char*)&nrLicenta, sizeof(int));

        file.close();
    }




    void afisare() {
        cout << "Meniu bar" << endl;
        for (int i = 0; i < nrProduse; i++) {
            cout << produse[i] << " " << pretProduse[i] << endl;
        }
        cout << "Preturile includ TVA" << endl;
        cout << "Nr. licenta: " << nrLicenta << endl;
        cout << "---------------------------" << endl;
    }

};
float Bar::TVA = 0.19;

void TVAComanda(Bar bar, const string& numeProdus, int cantitate) {
    int poz = -1;
    for (int i = 0; i < bar.getNrProduse(); i++) {
        if (bar.getNumeProdus(i) == numeProdus) {
            poz = i;
            break;
        }
    }
    if (poz != -1) {
        int pret = bar.getPretProdus(poz);
        float pretTotalCuTva = pret * cantitate;
        float sumaTVA = (bar.getTVA() / (1 + bar.getTVA())) * pretTotalCuTva;

        cout << "Pret total comanda: " << pretTotalCuTva << endl;
        cout << "Suma datorata statului pe comanda: " << sumaTVA << endl;
    }
    else {
        cout << "Nu exista produsul respectiv in meniu." << endl;
    }
}


class Evenimente {
private:
    int nrArtisti;
    string* numeArtisti;
    string dataEveniment;
    const int pretBilet;
    static int nrBileteDisponibile;
public:

    int getNrArtisti() {
        return nrArtisti;
    }

    void setNrArtisti(int nrNouArtisti, const string* numeNoiArtisti) {
        if (this->numeArtisti != nullptr) {
            delete[] this->numeArtisti;
        }

        this->numeArtisti = new string[nrNouArtisti];

        for (int i = 0; i < nrNouArtisti; i++) {
            this->numeArtisti[i] = numeNoiArtisti[i];
        }

        this->nrArtisti = nrNouArtisti;
    }

    string getNumeArtist(int i) {
        if (i >= 0 && i < nrArtisti) {
            return numeArtisti[i];
        }
        return "";
    }

    void setNumeArtist(int i, string numeArtist) {
        if (i >= 0 && i < this->nrArtisti) {
            this->numeArtisti[i] = numeArtist;
        }
    }

    string getDataEveniment() {
        return dataEveniment;
    }

    void setDataEveniment(string dataNouaEveniment) {
        this->dataEveniment = dataNouaEveniment;
    }

    int getPretBilet() const {
        return pretBilet;
    }

    static int getNrBileteDisponibile() {
        return nrBileteDisponibile;
    }

    static void setNrBileteDisponibile(int nrBilete) {
        nrBileteDisponibile = nrBilete;
    }


    Evenimente() :pretBilet(100) {
        this->nrArtisti = 1;
        this->numeArtisti = new string[nrArtisti];
        this->numeArtisti[0] = "O-Zone";
        this->dataEveniment = "14-11-2023";
    }

    Evenimente(string dataEveniment) :pretBilet(0) {
        this->nrArtisti = 0;
        this->numeArtisti = nullptr;
    }

    Evenimente(int nrArtisti, string* nume, string dataEveniment, int pret) :pretBilet(pret) {
        this->nrArtisti = nrArtisti;
        this->numeArtisti = new string[nrArtisti];
        for (int i = 0; i < nrArtisti; i++) {
            this->numeArtisti[i] = nume[i];
        }
        this->dataEveniment = dataEveniment;
    }

    ~Evenimente() {
        delete[] this->numeArtisti;
    }

    Evenimente& operator=(const Evenimente& ev) {
        if (this != &ev) {
            if (this->numeArtisti != nullptr) {
                delete[] this->numeArtisti;
            }

            this->nrArtisti = ev.nrArtisti;

            if (ev.numeArtisti != nullptr) {
                this->numeArtisti = new string[ev.nrArtisti];
                for (int i = 0; i < ev.nrArtisti; i++) {
                    this->numeArtisti[i] = ev.numeArtisti[i];
                }
            }
            else {
                this->numeArtisti = nullptr;
            }

            this->dataEveniment = ev.dataEveniment;
        }

        return *this;
    }

    bool operator>(const Evenimente& ev) {
        return this->pretBilet > ev.pretBilet;
    }

    Evenimente operator-(const Evenimente& ev) const {
        Evenimente aux;
        if (this != &ev) {
            aux.nrArtisti = this->nrArtisti - ev.nrArtisti;
        }
        aux.nrArtisti = abs(aux.nrArtisti);
        return aux;
    }




    Evenimente(const Evenimente& ev) : pretBilet(ev.pretBilet) {
        this->nrArtisti = ev.nrArtisti;

        if (ev.numeArtisti != nullptr) {
            this->numeArtisti = new string[ev.nrArtisti];
            for (int i = 0; i < ev.nrArtisti; i++) {
                this->numeArtisti[i] = ev.numeArtisti[i];
            }
        }
        else {
            this->numeArtisti = nullptr;
        }

        this->dataEveniment = ev.dataEveniment;
    }

    friend ostream& operator<<(ostream& os, const Evenimente& e) {
        os << "Nr artisti: " << e.nrArtisti << endl;
        os << "Artisti: " << endl;
        for (int i = 0; i < e.nrArtisti; i++) {
            os << e.numeArtisti[i] << endl;
        }
        os << "Pret: " << e.pretBilet << endl;
        os << e.dataEveniment << endl;


        return os;
    }
    void scriere(const char* fileName){
        ofstream file(fileName, ios::binary | ios::out);

        file.write((char*)&nrArtisti, sizeof(int));

        for (int i = 0; i < nrArtisti; ++i) {
            int numeLungime = numeArtisti[i].length() + 1;
            file.write((char*)&numeLungime, sizeof(int));
            file.write(numeArtisti[i].c_str(), numeLungime);
        }

        int dataLungime = dataEveniment.length() + 1;
        file.write((char*)&dataLungime, sizeof(int));
        file.write(dataEveniment.c_str(), dataLungime);

        file.write((char*)&pretBilet, sizeof(int));
        file.write((char*)&nrBileteDisponibile, sizeof(int));

        file.close();
    }
    void citire(const std::string& fileName) {
        ifstream file(fileName, ios::binary | ios::in);

        if (numeArtisti != nullptr) {
            delete[] numeArtisti;
        }
        file.read((char*)&nrArtisti, sizeof(int));

        numeArtisti = new string[nrArtisti];
        for (int i = 0; i < nrArtisti; ++i) {
            int numeLungime;
            file.read((char*)&numeLungime, sizeof(int));

            char* nume = new char[numeLungime];
            file.read(nume, numeLungime);
            numeArtisti[i] = string(nume);
            delete[] nume;
        }

        int dataLungime;
        file.read((char*)&dataLungime, sizeof(int));
        char* data = new char[dataLungime];
        file.read(data, dataLungime);
        dataEveniment = string(data);
        delete[] data;

        file.read((char*)&pretBilet, sizeof(int));
        file.read((char*)&nrBileteDisponibile, sizeof(int));

        file.close();
    }


    void afisare() {

        if (numeArtisti != nullptr) {
            cout << "Urmeaza un nou eveniment!" << endl;
            cout << "Artisti invitati: " << endl;
            for (int i = 0; i < this->nrArtisti; i++) {
                cout << " - " << this->numeArtisti[i] << endl;
            }
            cout << pretBilet << " lei" << endl;
            cout << this->dataEveniment << endl;
            cout << "/////////////////////////////////////////" << endl;
            cout << endl;
        }
        else {
            cout << "Momentan nu sunt evenimente programate la acest club." << endl;
            cout << "/////////////////////////////////////////" << endl;
            cout << endl;
        }
    }
};
int Evenimente::nrBileteDisponibile = 150;

void cumparaBilete(Evenimente ev, int nrBileteCumparate) {
    if (nrBileteCumparate <= ev.getNrBileteDisponibile()) {
        int bilDisp = ev.getNrBileteDisponibile();
        bilDisp-= nrBileteCumparate;
        ev.setNrBileteDisponibile(bilDisp);
        cout << "Suma totala: " << nrBileteCumparate * ev.getPretBilet() << " lei" << endl;
        cout << "Au mai ramas " << ev.getNrBileteDisponibile() << " bilete!" << endl;
    }
    else {
        cout << "Nu mai sunt destule bilete." << endl;
    }
}

//clasa has-a
class Comenzi {
private:
    Bar bar;
    int cantitate;
    string numeProdus;
    int pretProdus;
    bool produsExista;
public:
    Comenzi() {
        int i = 0;
        this->bar = Bar();
        this->cantitate = 2;
        this->numeProdus = "Bere";
        this->pretProdus = 0;
        this->produsExista = false;
        while (i < this->bar.getNrProduse() && this->bar.getNumeProdus(i) != this->numeProdus) {
            i++;
        }
        if (i < this->bar.getNrProduse()) {
            this->pretProdus = this->bar.getPretProdus(i);
            this->produsExista = true;
        }
    }

    Comenzi(Bar bar, int cantitate, string numeProduse) {
        int i = 0;
        this->bar = bar;
        this->cantitate = cantitate;
        this->numeProdus = numeProduse;
        this->pretProdus = 0;
        this->produsExista = false;
        while (i < this->bar.getNrProduse() && this->bar.getNumeProdus(i) != this->numeProdus) {
            i++;
        }
        if (i < this->bar.getNrProduse()) {
            this->pretProdus = this->bar.getPretProdus(i);
            this->produsExista = true;
        }
    }

    Comenzi(const Comenzi& c) {
        this->bar = c.bar;
        this->cantitate = c.cantitate;
        this->numeProdus = c.numeProdus;
        this->pretProdus = c.pretProdus;
        this->produsExista = c.produsExista;
    }

    ~Comenzi() {}

    Bar getBar() {
        return this->bar;
    }
    void setBar(const Bar& barNou) {
        this->bar = barNou;
    }

    int getCantitate() {
        return this->cantitate;
    }
    void setCantitate(int cantitateNoua) {
        this->cantitate = cantitateNoua;
    }

    string getNume() {
        return this->numeProdus;
    }
    void setNume(string numeNou) {
        this->numeProdus = numeNou;
    }

    int getPret() {
        return this->pretProdus;
    }
    void setPret(int pretNou) {
        this->pretProdus = pretNou;
    }


    Comenzi& operator=(const Comenzi& c) {
        if (this != &c) {
            this->bar = c.bar;
            this->cantitate = c.cantitate;
            this->numeProdus = c.numeProdus;
            this->pretProdus = c.pretProdus;
            this->produsExista = c.produsExista;
        }


        return *this;
    }

    friend ostream& operator<<(ostream& os, const Comenzi& c) {
        if (c.produsExista) {
            os << "Comanda dvs: " << endl;
            os << c.numeProdus << " x" << c.cantitate << " " << c.pretProdus * c.cantitate << " lei" << endl;
        }
        else {
            cout << "Produsul nu exista, afisare indisponibila." << endl;
        }

        return os;
    }

    Comenzi operator*(int i) {
        Comenzi rez(*this);
        rez.setPret(rez.getPret() * i);

        return rez;
    }


    void afisare() {
        if (produsExista) {
            cout << "Comanda dvs: " << endl;
            cout << this->numeProdus << " x" << this->cantitate << " " << this->pretProdus * this->cantitate << " lei" << endl;
        }
        else {
            cout << "Produsul nu exista, afisare indisponibila." << endl;
        }
    }
};

//clase is-a
class TipClub :public Locatie {
private:
    string tipClub;
public:
    TipClub() : Locatie(), tipClub("Nightclub") {}

    TipClub(string numeClub, string tip):Locatie(numeClub),tipClub(tip) {}

    TipClub(string numeClub, int nrAngajati, int* salarii, int cap, string tip):Locatie( numeClub, nrAngajati, salarii, cap), tipClub(tip) {}

    TipClub(const TipClub& tc):Locatie(tc){
        this->tipClub = tc.tipClub;
    }

    string getTipClub() {
        return this->tipClub;
    }

    void setTipClub(string tip) {
        this->tipClub = tip;
    }

    void afisare() {
        cout << "Nume club: "<<getNumeClub() << endl;
        cout << "Tip club: " << this->tipClub<<endl;
    }
};

class InfoEvenimente : public Evenimente {
private:
    string locatie;
public:
    InfoEvenimente() : Evenimente(), locatie("Beluga") {}
    InfoEvenimente(string data, string locatie) :Evenimente(data), locatie(locatie) {}
    InfoEvenimente(int nrArtisti, string* nume, string dataEveniment, int pret, string locatie) :Evenimente(nrArtisti, nume, dataEveniment, pret), locatie(locatie) {}
    InfoEvenimente(const InfoEvenimente& te) : Evenimente(te) {
        this->locatie = te.locatie;
    }

    string getLocatie() {
        return this->locatie;
    }

    void setLocatie(string locatie) {
        this->locatie=locatie;
    }

    

    void afisare() {
        Evenimente::afisare();
        cout << "Locatie: " << this->locatie << endl;
        cout << "//////////////////////////////" << endl;
    }
};

int main() {

    Locatie l1;
    Locatie l2("El Comandante");
    int salarii[] = { 4000, 4500, 5000, 5500, 6500 };
    Locatie l3("Interbelic", 5, salarii, 150);

    Bar b1;
    Bar b2(456);
    string produse[] = { "Bere", "Shot", "Cocktail" };
    int pretProduse[] = { 10, 17, 30 };
    Bar b3(3, produse, pretProduse, 789);

    Evenimente e1;
    Evenimente e2("01-01-2024");
    string nume[] = { "AC/DC", "Iron Maiden", "Metallica" };
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

    TVAComanda(b3, "Bere", 2);
    cout << "-------------------------" << endl;
    cumparaBilete(e3, 5);
    cout << endl << "////////////////////////////////" << endl << endl;

    l1.setNumeClub("Krystal");
    int salariiNoi[] = { 3000, 4000, 5000 };
    l1.setNrAngajati(3, salariiNoi);
    l1.setSalariuAngajat(0, 3500);
    l1.setVarstaMinima(18);

    cout << l1.getNumeClub() << endl;
    cout << "Nr. angajati: " << l1.getNrAngajati() << endl;
    cout << "Salariul din pozitia 0: " << l1.getSalariuAngajat(0) << endl;
    cout << "Capacitate: " << l1.getCapacitate() << endl;
    cout << "Varsta minima intrare: " << l1.getVarstaMinima() << endl;
    cout << "----------------------------------------" << endl << endl;

    string produseNoi[] = { "Rom Cola", "Amaretto sour" };
    int preturiNoi[] = { 25, 30 };
    b1.setNrProduse(2, produseNoi, preturiNoi);
    b1.setNumeProdus(0, "Cuba libre");
    b1.setPretProdus(0, 35);
    b1.setTVA(0.09);

    cout << "Nr. produse: " << b1.getNrProduse() << endl;
    cout << "Comanda dvs.: " << b1.getNumeProdus(0) << "  " << b1.getPretProdus(0) * (1 + b1.getTVA()) << " lei" << endl;
    cout << "Nr licenta: " << b1.getNrLicenta() << endl;
    cout << "------------------------------------------" << endl << endl;

    string numeNoiArtisti[] = { "Parazitii", "Puya" };
    e1.setNrArtisti(2, numeNoiArtisti);
    e1.setNumeArtist(1, "BUG Mafia");
    e1.setDataEveniment("16-12-2023");
    e1.setNrBileteDisponibile(100);

    cout << "Lista invitati: " << endl;
    for (int i = 0; i < e1.getNrArtisti(); i++) {
        cout << e1.getNumeArtist(i) << " ";
    }
    cout << endl << e1.getPretBilet() << " lei" << endl;
    cout << e1.getDataEveniment() << endl;
    cout << "Bilete disponibile: " << e1.getNrBileteDisponibile() << endl;
    cout << "-----------------------------------------" << endl << endl;
    cout << "Verificare constructori copiere" << endl;
    Locatie l4 = l3;
    Bar b4 = b3;
    Evenimente e4 = e3;
    l4.afisare();
    b4.afisare();
    e4.afisare();
    Locatie l5;
    l5 = l1;
    Bar b5;
    b5 = b1;
    Evenimente e5;
    e5 = e1;
    cout << "Verificare operator =" << endl;
    l5.afisare();
    b5.afisare();
    e5.afisare();
    cout << "/////////////////////////" << endl;
    if (l1 < l3) {
        cout << l1.getNumeClub() << " este mai mic decat " << l3.getNumeClub() << endl;
    }
    else {
        cout << l1.getNumeClub() << " este mai mare sau egal cu " << l3.getNumeClub() << endl;
    }

    cout << "//////////////////////////" << endl;
    cout << "Afisare operator+" << endl;
    Locatie l6 = l1 + l3;
    cout << l6 << endl;

    Bar b6;
    b6 = ++b1;
    cout << "Verificare preincrementare" << endl;
    b6.afisare();
    Bar b7;
    b7 = b3++;
    cout << "Verificare postincrementare" << endl;
    b7.afisare();
    b3.afisare();


    if (e3 > e1) {
        cout << "Ev. e3 e mai scump decat ev. e1" << endl;
    }
    else {
        cout << "Ev. e3 e mai ieftin sau la fel de scump ca ev. e1" << endl;
    }

    Evenimente e6;
    Evenimente rez;
    cout << e4.getNrArtisti() << endl;
    cout << e6.getNrArtisti() << endl;
    rez = e6 - e4;
    cout << "Diferenta de artisti dintre e4 si e6: " << rez.getNrArtisti() << endl;

    Comenzi c1;
    c1.afisare();
    Comenzi c2(b3, 3, "Bere");
    c2.afisare();

    Comenzi c3 = c2;
    cout << "Verificare constructor copiere clasa has-a" << endl;
    c3.afisare();
    Comenzi c4(b3, 2, "Cocktail");
    Comenzi c5;
    cout << "afisare c5 inainte de operator=" << endl;
    c5.afisare();
    c5 = c4;
    cout << "afisare dupa operator=, folosind operator<< " << endl;
    cout << c5 << endl;
    cout << "Verificare operator*" << endl;
    cout << c5 * 2 << endl;

    cin >> b3;
    cout << "//////////////" << endl;
    b3.afisare();
    








    int num_loc;
    int num_bar;
    int num_ev;
    /*
    cout << "Cate obiecte de tip Locatie doriti sa creati?" << endl;
    cin >> num_loc;
    Locatie* vectorLocatii=new Locatie[num_loc];
    cout << "Vector obiecte clasa Locatie: " << endl;
    for (int i = 0; i < num_loc; i++) {
        cout << "Locatie " << i + 1 << ": " << endl;
        vectorLocatii[i] = Locatie();
        string numeClub;
        int nrAngajati;
        int* salariiAngajati;
        cout << "Introduceti numele clubului: " << endl;
        cin >> numeClub;
        vectorLocatii[i].setNumeClub(numeClub);
        cout << "Introduceti numarul angajatilor: " << endl;
        cin >> nrAngajati;
        salariiAngajati = new int[nrAngajati];
        vectorLocatii[i].setNrAngajati(nrAngajati, salariiAngajati);
        cout << "Introduceti salariile: " << endl;
        for (int j = 0; j < nrAngajati; j++) {
            cout << "Salariul " << j + 1 << ": " << endl;
            cin >> salariiAngajati[j];
            vectorLocatii[i].setSalariuAngajat(j, salariiAngajati[j]);
        }
    }
    cout << "////////////////////////////////" << endl;
    cout << "Extragere vector" << endl;
    for (int i = 0; i < num_loc; i++) {
        cout << "Locatie" << i + 1 << ": " << endl;
        cout << vectorLocatii[i] << endl;
        cout << "/////////////////////" << endl;
    }

    cout << "Cate obiecte de tip Bar doriti sa creati?" << endl;
    cin >> num_bar;
    Bar* vectorBaruri=new Bar[num_bar];
    cout << "Vector obiecte clasa Bar: " << endl;
    for (int i = 0; i < num_bar; i++) {
        cout << "Bar" << i + 1 << ": " << endl;
        vectorBaruri[i] = Bar();
        int nrProduse;
        cout << "Introduceti numarul produselor: " << endl;
        cin >> nrProduse;
        string* produse = new string[nrProduse];
        int* pretProduse = new int[nrProduse];
        vectorBaruri[i].setNrProduse(nrProduse, produse, pretProduse);
        for (int j = 0; j < nrProduse; j++) {
            cin.ignore();
            cout << "Introduceti produsul " << j + 1 << ": " << endl;
            getline(cin, produse[j]);
            vectorBaruri[i].setNumeProdus(j, produse[j]);
            cout << "Introduceti pretul produsului " << j + 1 << ": " << endl;
            cin >> pretProduse[j];
            vectorBaruri[i].setPretProdus(j, pretProduse[j]);
        }
    }
    cout << "Extragere vector" << endl;
    for (int i = 0; i < num_bar; i++) {
        cout << "Bar" << i + 1 << ": " << endl;
        cout << vectorBaruri[i] << endl;
        cout << "/////////////////////" << endl;
    }


    cout << "Cate obiecte de tip Evenimente doriti sa creati?" << endl;
    cin >> num_ev;
    Evenimente* vectorEvenimente=new Evenimente[num_ev];
    cout << "Vector obiecte clasa Evenimente: " << endl;
    for (int i = 0; i < num_ev; i++) {
        cout << "Eveniment" << i + 1 << ": " << endl;
        vectorEvenimente[i] = Evenimente();
        int nrArtisti;
        string dataEveniment;
        cout << "Introduceti nr artisti: " << endl;
        cin >> nrArtisti;
        string* numeArtisti = new string[nrArtisti];
        vectorEvenimente[i].setNrArtisti(nrArtisti, numeArtisti);
        cin.ignore();
        for (int j = 0; j < nrArtisti; j++) {
            cout << "Introduceti artistul " << j + 1 << ": " << endl;
            getline(cin, numeArtisti[j]);
            vectorEvenimente[i].setNumeArtist(j, numeArtisti[j]);
        }
        cout << "Introduceti data evenimentului: " << endl;
        cin >> dataEveniment;
        vectorEvenimente[i].setDataEveniment(dataEveniment);
    }
    cout << "Extragere vector" << endl;
    for (int i = 0; i < num_ev; i++) {
        cout << "Eveniment" << i + 1 << ": " << endl;
        cout << vectorEvenimente[i] << endl;
        cout << "/////////////////////" << endl;
    }
    
    Bar** matriceBar = new Bar * [num_bar];
    for (int i = 0; i < num_bar; i++) {
        matriceBar[i] = vectorBaruri;
    }
    cout << "Verificare matrice Bar" << endl;
    for (int i = 0; i < num_bar; i++) {
        for (int j = 0; j < num_bar; j++) {
            cout << "matriceBar[" << i << "][" << j << "]: " << endl;
            cout << matriceBar[i][j] << endl;
        }
    }
    */





    cout << "Verificare fisiere text Locatie" << endl;
    int salarii8[] = {2000,3000,4000};
    Locatie l8("Subteran", 3, salarii8, 200);
    ofstream file1("fisierLocatie1.txt", ios::out);
    file1 << l8;
    file1.close();
    ifstream citire1("fisierLocatie1.txt", ios::in);
    Locatie l9;
    citire1 >> l9;
    cout << l9 << endl;
    citire1.close();
    int salarii10[1] = {};
    Locatie l10("Tete a tete", 0, salarii10, 200);
    ofstream file2("fisierLocatie2.txt", ios::out);
    file2 << l10;
    file2.close();
    ifstream citire2("fisierLocatie2.txt", ios::in);
    Locatie l11;
    citire2 >> l11;
    cout << l11<<endl;
    citire2.close();
    cout << "Verificare fisiere text Bar" << endl;
    Bar b8;
    cin >> b8;
    ofstream file("fisierBar.txt", ios::out);
    file << b8;
    file.close();
    ifstream citire("fisierBar.txt", ios::in);
    Bar b9;
    citire >> b9;
    cout << b9 << endl;
    citire.close();


    Bar b10(3, produse, pretProduse, 789);
    b10.scriere("Bar.dat");
    Bar b11;
    cout << "Fisier binar Bar" << endl;
    b11.citire("Bar.dat");
    b11.afisare();
    Evenimente e10(3, nume, "16-12-2023", 300);
    e10.scriere("Evenimente.dat");
    cout << "Fisier binar Evenimente" << endl;
    Evenimente e11;
    e11.citire("Evenimente.dat");
    e11.afisare();


    TipClub tc1;
    tc1.afisare();
    cout << "Getter tipClub" << endl;
    cout << tc1.getTipClub() << endl;
    TipClub tc2("Mojo", "Karaoke");
    tc2.afisare();
    //int salarii[] = { 4000, 4500, 5000, 5500, 6500 };
    TipClub tc3("Subteran", 5, salarii, 300, "Techno");
    TipClub tc4=tc3;
    Locatie* l12 = &tc3;//upcasting
    tc3.setTipClub("EDM");
    cout << "Verificare upcasting" << endl;
    l12->afisare();
    cout << "Verificarea constructorului de copiere a clase TipClub" << endl;
    tc4.afisare();

    InfoEvenimente ie1;
    ie1.afisare();
    cout << "Getter locatie" << endl;
    cout << ie1.getLocatie() << endl;
    cout << endl << "ie2" << endl;
    InfoEvenimente ie2("10-11-2023", "Silver Church");
    ie2.afisare();
    InfoEvenimente ie3(3, nume, "16-12-2023", 300, "Nuba");
    InfoEvenimente ie4 = ie3;
    ie3.setLocatie("Wicked");
    ie3.afisare();
    ie4.afisare();

    



    
    
    

    
    return 0;
}
