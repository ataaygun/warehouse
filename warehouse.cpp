#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

// ---------- Urun sinifi ----------
class Urun {
private:
    int urunNo;
    string ad;
    string rafKonumu;   // ornek: "A1", "B3" gibi raf/lokasyon kodu
    int stokAdedi;

public:
    Urun(int no, const string& urunAdi, const string& raf, int adet)
        : urunNo(no), ad(urunAdi), rafKonumu(raf), stokAdedi(adet) {}

    int getUrunNo() const { return urunNo; }
    string getAd() const { return ad; }
    string getRafKonumu() const { return rafKonumu; }
    int getStokAdedi() const { return stokAdedi; }

    void rafKonumuGuncelle(const string& yeniRaf) {
        rafKonumu = yeniRaf;
    }

    void girisYap(int adet) {
        stokAdedi += adet;
    }

    bool cikisYap(int adet) {
        if (adet > stokAdedi) {
            return false; // yetersiz stok
        }
        stokAdedi -= adet;
        return true;
    }

    void bilgiGoster() const {
        cout << left << setw(8) << urunNo
             << setw(20) << ad
             << setw(10) << rafKonumu
             << stokAdedi << " adet" << endl;
    }
};

// ---------- Hareket kaydi (giris/cikis loglari icin) ----------
struct Hareket {
    int urunNo;
    string urunAdi;
    string tur;   // "GIRIS" ya da "CIKIS"
    int adet;
};

// ---------- Depo sinifi ----------
class Depo {
private:
    vector<Urun> urunler;
    vector<Hareket> hareketler;
    int siradakiUrunNo = 1;

    Urun* urunBul(int no) {
        for (auto& u : urunler) {
            if (u.getUrunNo() == no) return &u;
        }
        return nullptr;
    }

public:
    void urunEkle() {
        string ad, raf;
        int adet;

        cout << "\nUrun adi: ";
        cin.ignore();
        getline(cin, ad);

        cout << "Raf konumu (ornek: A1, B3): ";
        getline(cin, raf);

        cout << "Baslangic stok adedi: ";
        cin >> adet;

        if (adet < 0) {
            cout << "Stok adedi negatif olamaz!\n";
            return;
        }

        int yeniNo = siradakiUrunNo++;
        urunler.push_back(Urun(yeniNo, ad, raf, adet));
        cout << "Urun basariyla eklendi! Urun No: " << yeniNo << endl;
    }

    void girisYap() {
        int no, adet;
        cout << "\nUrun No: ";
        cin >> no;

        Urun* u = urunBul(no);
        if (!u) {
            cout << "Urun bulunamadi!\n";
            return;
        }

        cout << "Giris yapilacak adet: ";
        cin >> adet;

        if (adet <= 0) {
            cout << "Gecersiz adet!\n";
            return;
        }

        u->girisYap(adet);
        hareketler.push_back({u->getUrunNo(), u->getAd(), "GIRIS", adet});
        cout << "Giris kaydedildi. Yeni stok: " << u->getStokAdedi() << " adet" << endl;
    }

    void cikisYap() {
        int no, adet;
        cout << "\nUrun No: ";
        cin >> no;

        Urun* u = urunBul(no);
        if (!u) {
            cout << "Urun bulunamadi!\n";
            return;
        }

        cout << "Cikis yapilacak adet: ";
        cin >> adet;

        if (adet <= 0) {
            cout << "Gecersiz adet!\n";
            return;
        }

        if (u->cikisYap(adet)) {
            hareketler.push_back({u->getUrunNo(), u->getAd(), "CIKIS", adet});
            cout << "Cikis kaydedildi. Kalan stok: " << u->getStokAdedi() << " adet" << endl;
        } else {
            cout << "Yetersiz stok! Mevcut stok: " << u->getStokAdedi() << " adet" << endl;
        }
    }

    void rafKonumuGuncelle() {
        int no;
        string yeniRaf;
        cout << "\nUrun No: ";
        cin >> no;

        Urun* u = urunBul(no);
        if (!u) {
            cout << "Urun bulunamadi!\n";
            return;
        }

        cout << "Yeni raf konumu: ";
        cin.ignore();
        getline(cin, yeniRaf);

        u->rafKonumuGuncelle(yeniRaf);
        cout << "Raf konumu guncellendi: " << yeniRaf << endl;
    }

    void urunSorgula() {
        int no;
        cout << "\nUrun No: ";
        cin >> no;

        Urun* u = urunBul(no);
        if (!u) {
            cout << "Urun bulunamadi!\n";
            return;
        }

        cout << u->getAd() << " - Raf: " << u->getRafKonumu()
             << " - Stok: " << u->getStokAdedi() << " adet" << endl;
    }

    void dusukStokUyarisi(int esikDeger) {
        cout << "\n--- Stogu " << esikDeger << " adedin altinda olan urunler ---\n";
        bool bulunduMu = false;

        for (const auto& u : urunler) {
            if (u.getStokAdedi() < esikDeger) {
                u.bilgiGoster();
                bulunduMu = true;
            }
        }

        if (!bulunduMu) {
            cout << "Stogu kritik seviyede olan urun yok.\n";
        }
    }

    void tumUrunleriListele() const {
        if (urunler.empty()) {
            cout << "\nHenuz hicbir urun eklenmemis.\n";
            return;
        }

        cout << "\n" << left << setw(8) << "Urun No"
             << setw(20) << "Ad" << setw(10) << "Raf" << "Stok" << endl;
        cout << "--------------------------------------------\n";
        for (const auto& u : urunler) {
            u.bilgiGoster();
        }
    }

    void hareketGecmisi() const {
        if (hareketler.empty()) {
            cout << "\nHenuz hicbir giris/cikis hareketi yok.\n";
            return;
        }

        cout << "\n" << left << setw(8) << "Urun No"
             << setw(20) << "Ad" << setw(8) << "Tur" << "Adet" << endl;
        cout << "--------------------------------------------\n";
        for (const auto& h : hareketler) {
            cout << left << setw(8) << h.urunNo
                 << setw(20) << h.urunAdi
                 << setw(8) << h.tur
                 << h.adet << endl;
        }
    }
};

// ---------- Menu ----------
void menuGoster() {
    cout << "\n===== DEPO (WAREHOUSE) YONETIM SISTEMI =====\n";
    cout << "1. Yeni Urun Ekle\n";
    cout << "2. Depoya Giris Yap (Mal Kabul)\n";
    cout << "3. Depodan Cikis Yap (Sevkiyat)\n";
    cout << "4. Raf Konumu Guncelle\n";
    cout << "5. Urun Sorgula\n";
    cout << "6. Tum Urunleri Listele\n";
    cout << "7. Dusuk Stok Uyarisi (5 adet altinda)\n";
    cout << "8. Giris/Cikis Hareket Gecmisi\n";
    cout << "0. Cikis\n";
    cout << "Seciminiz: ";
}

int main() {
    Depo depo;
    int secim;

    do {
        menuGoster();

        if (!(cin >> secim)) {
            cout << "Gecersiz giris! Lutfen bir sayi girin.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (secim) {
            case 1: depo.urunEkle(); break;
            case 2: depo.girisYap(); break;
            case 3: depo.cikisYap(); break;
            case 4: depo.rafKonumuGuncelle(); break;
            case 5: depo.urunSorgula(); break;
            case 6: depo.tumUrunleriListele(); break;
            case 7: depo.dusukStokUyarisi(5); break;
            case 8: depo.hareketGecmisi(); break;
            case 0: cout << "\nProgramdan cikiliyor. Iyi gunler!\n"; break;
            default: cout << "Gecersiz secim, tekrar deneyin.\n";
        }

    } while (secim != 0);

    return 0;
}
