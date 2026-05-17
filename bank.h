#ifndef BANK_H
#define BANK_H

#include "Nasabah.h"

class Bank {
private:
    Nasabah* daftarNasabah[100];
    int jumlahNasabah;

public:
    Bank();
    ~Bank();

    int validHuruf(string teks);
    int validAngka(string teks);
    
    void tambahNasabah();
    void cekSaldo();
    void setorSaldo();
    void tarikSaldo();
    void laporanKeuangan();
    void cekDataNasabah();
    void statistikBank();
    
    void simpanFile();
    void bacaFile();
};

#endif