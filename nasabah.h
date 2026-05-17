#ifndef NASABAH_H
#define NASABAH_H

#include <iostream>
#include <string>

#define BRONZE "\033[38;5;130m"
#define SILVER "\033[37m"
#define GOLD "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[36m"

using namespace std;

inline string formatSaldo(double angka) {

    string hasil = to_string((long long)angka);

    int posisi = hasil.length() - 3;

    while (posisi > 0) {

        hasil.insert(posisi, ",");

        posisi -= 3;
    }

    return hasil;
}

/*
==================================================
                CLASS NASABAH (ABSTRAK)
==================================================
*/

class Nasabah {

protected:

    string nama;
    string spesies;
    string rekening;
    double saldo;

public:

    Nasabah(string nama,
            string spesies,
            string rekening,
            double saldo) {

        this->nama = nama;
        this->spesies = spesies;
        this->rekening = rekening;
        this->saldo = saldo;
    }

    virtual ~Nasabah() {

        cout << CYAN
             << "\n[ INFO ] Data nasabah "
             << nama
             << " selesai disimpan.\n";
    }

    // PURE VIRTUAL FUNCTION
    virtual void tampilkanData() = 0;

    // OPERATOR OVERLOADING
    void operator+=(double jumlah) {

        saldo += jumlah;
    }

    void operator-=(double jumlah) {

        saldo -= jumlah;
    }

    // GETTERS
    string getNama() {

        return nama;
    }

    string getSpesies() {

        return spesies;
    }

    string getRekening() {

        return rekening;
    }

    double getSaldo() {

        return saldo;
    }
};

/*
==================================================
           CLASS REGULER NASABAH
==================================================
*/

class RegulerNasabah : public Nasabah {

public:

    RegulerNasabah(string nama,
                   string spesies,
                   string rekening,
                   double saldo)

        : Nasabah(nama, spesies, rekening, saldo) {}

    void tampilkanData() override {

        // BRONZE
        if (saldo >= 10000 && saldo <= 99999) {

            cout << BRONZE;

            cout << "\n========================================";
            cout << "\n         NASABAH BRONZE";
            cout << "\n========================================";
            cout << "\n Nama         : " << nama;
            cout << "\n Spesies      : " << spesies;
            cout << "\n No Rekening  : " << rekening;
            cout << "\n Saldo        : " << formatSaldo(saldo);
            cout << "\n Level        : Bronze";
            cout << "\n========================================\n";
        }

        // SILVER
        else if (saldo >= 100000 && saldo <= 999999) {

            cout << SILVER;

            cout << "\n========================================";
            cout << "\n         NASABAH SILVER";
            cout << "\n========================================";
            cout << "\n Nama         : " << nama;
            cout << "\n Spesies      : " << spesies;
            cout << "\n No Rekening  : " << rekening;
            cout << "\n Saldo        : " << formatSaldo(saldo);
            cout << "\n Level        : Silver";
            cout << "\n========================================\n";
        }

        cout << RESET;
    }
};

/*
==================================================
           CLASS PREMIUM NASABAH
==================================================
*/

class PremiumNasabah : public Nasabah {

private:

    string level;

public:

    PremiumNasabah(string nama,
                   string spesies,
                   string rekening,
                   double saldo,
                   string level)

        : Nasabah(nama, spesies, rekening, saldo) {

        this->level = level;
    }

    void tampilkanData() override {

        cout << GOLD;

        cout << "\n========================================";
        cout << "\n          NASABAH GOLD";
        cout << "\n========================================";
        cout << "\n Nama         : " << nama;
        cout << "\n Spesies      : " << spesies;
        cout << "\n No Rekening  : " << rekening;
        cout << "\n Saldo        : " << formatSaldo(saldo);
        cout << "\n Level        : Gold";
        cout << "\n========================================\n";

        cout << RESET;
    }
};

#endif