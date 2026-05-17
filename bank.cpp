#include "Bank.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <locale>
#define MERAH "\033[31m"
#define GOLD "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[36m"

using namespace std;

// Constructor
Bank::Bank() {
    jumlahNasabah = 0;
    bacaFile();
}

// Destructor
Bank::~Bank() {
    simpanFile();
    for (int i = 0; i < jumlahNasabah; i++) {
        delete daftarNasabah[i];
    }
}

int Bank::validHuruf(string teks) {
    int salah = 0;
    for (int i = 0; teks[i] != '\0'; i++) {
        if ((teks[i] >= 'A' && teks[i] <= 'Z') || 
            (teks[i] >= 'a' && teks[i] <= 'z') || 
            teks[i] == ' ') {
            // Valid
        } else {
            salah = 1;
        }
    }
    return salah;
}

int Bank::validAngka(string teks) {
    int salah = 0;
    for (int i = 0; teks[i] != '\0'; i++) {
        if (teks[i] < '0' || teks[i] > '9') {
            salah = 1;
        }
    }
    return salah;
}

void Bank::tambahNasabah() {
    // Mencegah error jika array kepenuhan
    if (jumlahNasabah >= 100) {
        cout << MERAH << "\n[ ERROR ] Kapasitas Bank Penuh (Maksimal 100 Nasabah)!\n" << RESET;
        return;
    }

    string nama, spesies, rekening, inputSaldo;
    double saldo;
    int salah, ditemukan;

    cout << "\n========================================";
    cout << "\n         TAMBAH NASABAH";
    cout << "\n========================================\n";

    cin.ignore();

    // INPUT NAMA
while (1) {

    int namaSama = 0;

    cout << "(0 = Kembali)\nNama Nasabah : ";
    getline(cin, nama);

    if (nama == "0") return;

    if (validHuruf(nama) == 1) {

        cout << MERAH
             << "\n[ ERROR ] Nama hanya boleh huruf!\n"
             << RESET;

        continue;
    }

    // CEK NAMA DUPLIKAT
    for (int i = 0; i < jumlahNasabah; i++) {

        if (daftarNasabah[i]->getNama() == nama) {

            namaSama = 1;
        }
    }

    if (namaSama == 1) {

        cout << MERAH
             << "\n[ ERROR ] Nama nasabah sudah digunakan!\n"
             << RESET;

        continue;
    }

    break;
}

    // INPUT SPESIES
    while (1) {
        cout << "(0 = Kembali)\nSpesies Laut : ";
        getline(cin, spesies);
        if (spesies == "0") return;
        if (validHuruf(spesies) == 0) break;
        cout << MERAH << "\n[ ERROR ] Spesies hanya boleh huruf!\n" << RESET;
    }

    // INPUT REKENING
    while (1) {
        cout << "(0 = Kembali)\nNo Rekening  : ";
        cin >> rekening;
        if (rekening == "0") return;
        
        if (validAngka(rekening) == 1) {
            cout << MERAH << "\n[ ERROR ] Rekening harus angka!\n" << RESET;
            continue;
        }

        ditemukan = 0;
        for (int i = 0; i < jumlahNasabah; i++) {
            if (daftarNasabah[i]->getRekening() == rekening) ditemukan = 1;
        }

        if (ditemukan == 1) cout << MERAH << "\n[ ERROR ] Rekening sudah digunakan!\n" << RESET;
        else break;
    }

    // INPUT SALDO
    while (1) {
        cout << "(0 = Kembali)\nSaldo Awal   : ";
        cin >> inputSaldo;
        if (inputSaldo == "0") return;
        
        if (validAngka(inputSaldo) == 1) {
            cout << MERAH << "\n[ ERROR ] Saldo harus angka!\n" << RESET;
            continue;
        }

        saldo = atof(inputSaldo.c_str());
        if (saldo < 10000 || saldo > 50000000) {
            cout << MERAH << "\n[ ERROR ] Minimal 10.000, Maksimal 50.000.000\n" << RESET;
        } else {
            break;
        }
    }

    // INSTANSIASI OBJECT BERDASARKAN SALDO
        if (saldo >= 1000000) {

            daftarNasabah[jumlahNasabah]
                = new PremiumNasabah(
                    nama,
                    spesies,
                    rekening,
                    saldo,
                    "Gold"
                );
        }
        else {

            daftarNasabah[jumlahNasabah]
                = new RegulerNasabah(
                    nama,
                    spesies,
                    rekening,
                    saldo
                );
        }

    jumlahNasabah++;
    simpanFile();
    cout << "\n[ SUCCESS ] Nasabah berhasil ditambahkan!\n";
}

void Bank::cekSaldo() {

    string rekening;

    while (1) {

        cout << "\n(0 = Kembali)";
        cout << "\nMasukkan nomor rekening : ";
        cin >> rekening;

        if (rekening == "0") return;

        if (validAngka(rekening) == 1) {
            cout << MERAH << "\n[ ERROR ] Rekening harus angka!\n" << RESET;
            continue;
        }

        break;
    }

    for (int i = 0; i < jumlahNasabah; i++) {

        if (daftarNasabah[i]->getRekening() == rekening) {

            cout << "\nNama  : " << daftarNasabah[i]->getNama();

            cout << "\nSaldo : "
                 << formatSaldo(daftarNasabah[i]->getSaldo())
                 << endl;

            return;
        }
    }

    cout << MERAH << "\n[ ERROR ] Rekening tidak ditemukan!\n" << RESET;
}

void Bank::setorSaldo() {
    string rekening, inputJumlah;
double jumlah;

while (1) {

    cout << "\n(0 = Kembali)";
    cout << "\nMasukkan nomor rekening : ";
    cin >> rekening;

    if (rekening == "0") return;

    if (validAngka(rekening) == 1) {
        cout << MERAH << "\n[ ERROR ] Rekening harus angka!\n" << RESET;
        continue;
    }

    break;
}
    if (rekening == "0") return;
    for (int i = 0; i < jumlahNasabah; i++) {
        if (daftarNasabah[i]->getRekening() == rekening) {
            cout << "Jumlah setor : ";
            cin >> inputJumlah;

            if (validAngka(inputJumlah) == 1) {
                cout << MERAH << "\n[ ERROR ] Jumlah harus angka!\n" << RESET;
                return;
            }

            jumlah = atof(inputJumlah.c_str());
            if (jumlah < 10000 || jumlah > 50000000) {
                 cout << MERAH << "\n[ ERROR ] Limit setor 10.000 - 50.000.000\n" << RESET;
                 return;
            }

            // PENGGUNAAN OPERATOR OVERLOADING
            *daftarNasabah[i] += jumlah; 
            
            simpanFile();
            cout << "\n[ SUCCESS ] Setor berhasil!\n";
            return;
        }
    }
    cout << MERAH << "\n[ ERROR ] Rekening tidak ditemukan!\n" << RESET;
}

void Bank::tarikSaldo() {
    string rekening, inputJumlah;
    double jumlah;

    while (1) {
        cout << "\n(0 = Kembali)";
        cout << "\nMasukkan nomor rekening : ";
        cin >> rekening;

        if (rekening == "0") return;

        if (validAngka(rekening) == 1) {
            cout << MERAH << "\n[ ERROR ] Rekening harus angka!\n" << RESET;
            continue;
        }

        break;
    }

    if (rekening == "0") return;

    for (int i = 0; i < jumlahNasabah; i++) {
        if (daftarNasabah[i]->getRekening() == rekening) {
            cout << "Jumlah tarik : ";
            cin >> inputJumlah;

            if (validAngka(inputJumlah) == 1) {
                cout << MERAH << "\n[ ERROR ] Jumlah harus angka!\n" << RESET;
                return;
            }

            jumlah = atof(inputJumlah.c_str());
            if (jumlah < 10000) {
                 cout << MERAH << "\n[ ERROR ] Minimal penarikan 10.000!\n" << RESET;
                 return;
            }

            if ((daftarNasabah[i]->getSaldo() - jumlah) >= 10000) {
                // PENGGUNAAN OPERATOR OVERLOADING
                *daftarNasabah[i] -= jumlah;
                
                simpanFile();
                cout << "\n[ SUCCESS ] Penarikan berhasil!\n";
            } else {
                cout << MERAH
                        << "\n[ ERROR ] Saldo minimal tersisa 10.000!\n"
                        << RESET;
            }
            return;
        }
    }
    cout << MERAH << "\n[ ERROR ] Rekening tidak ditemukan!\n" << RESET;
}

void Bank::laporanKeuangan() {
    double total = 0;
    cout << "\n========================================";
    cout << "\n           LAPORAN KEUANGAN";
    cout << "\n========================================";
    
    for (int i = 0; i < jumlahNasabah; i++) {
        total += daftarNasabah[i]->getSaldo();
    }
    
    cout << "\nJumlah Nasabah : " << jumlahNasabah;
    cout << "\nTotal Saldo    : " << fixed << setprecision(0) << total;
    cout << "\n========================================\n";
}

void Bank::cekDataNasabah() {

    string rekening;

    while (1) {

        cout << "\n(0 = Kembali)";
        cout << "\nMasukkan nomor rekening : ";
        cin >> rekening;

        if (rekening == "0") return;

        if (validAngka(rekening) == 1) {

            cout << MERAH
                 << "\n[ ERROR ] Rekening harus angka!\n"
                 << RESET;

            continue;
        }

        break;
    }

    for (int i = 0; i < jumlahNasabah; i++) {

        if (daftarNasabah[i]->getRekening() == rekening) {

            double saldo = daftarNasabah[i]->getSaldo();

            // BRONZE
            if (saldo >= 10000 && saldo <= 99999) {

                cout << BRONZE;

                cout << "\n========================================";
                cout << "\n         NASABAH BRONZE";
                cout << "\n========================================";
                cout << "\n Nama         : " << daftarNasabah[i]->getNama();
                cout << "\n Spesies      : " << daftarNasabah[i]->getSpesies();
                cout << "\n No Rekening  : " << daftarNasabah[i]->getRekening();
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
                cout << "\n Nama         : " << daftarNasabah[i]->getNama();
                cout << "\n Spesies      : " << daftarNasabah[i]->getSpesies();
                cout << "\n No Rekening  : " << daftarNasabah[i]->getRekening();
                cout << "\n Saldo        : " << formatSaldo(saldo);
                cout << "\n Level        : Silver";
                cout << "\n========================================\n";
            }

            // GOLD
            else {

                cout << GOLD;

                cout << "\n========================================";
                cout << "\n          NASABAH GOLD";
                cout << "\n========================================";
                cout << "\n Nama         : " << daftarNasabah[i]->getNama();
                cout << "\n Spesies      : " << daftarNasabah[i]->getSpesies();
                cout << "\n No Rekening  : " << daftarNasabah[i]->getRekening();
                cout << "\n Saldo        : " << formatSaldo(saldo);
                cout << "\n Level        : Gold";
                cout << "\n========================================\n";
            }

            cout << RESET;

            return;
        }
    }

    cout << MERAH
         << "\n[ ERROR ] Data tidak ditemukan!\n"
         << RESET;
}
void Bank::statistikBank() {
    if (jumlahNasabah == 0) {
        cout << "\n[ INFO ] Belum ada data nasabah.\n";
        return;
    }

    double totalSaldo = 0, saldoTerbesar = 0;
    int jumlahPremium = 0;
    string namaTerkaya = "-";

    for (int i = 0; i < jumlahNasabah; i++) {
        totalSaldo += daftarNasabah[i]->getSaldo();

        if (daftarNasabah[i]->getSaldo() > saldoTerbesar) {
            saldoTerbesar = daftarNasabah[i]->getSaldo();
            namaTerkaya = daftarNasabah[i]->getNama();
        }

        if (daftarNasabah[i]->getSaldo() >= 1000000) {
            jumlahPremium++;
        }
    }

    cout << "\n========================================";
    cout << "\n             STATISTIK BANK";
    cout << "\n========================================";
    cout << "\nJumlah Nasabah : " << jumlahNasabah;
    cout << "\nTotal Saldo    : " << fixed << setprecision(0) << totalSaldo;
    cout << "\nRata-rata      : " << totalSaldo / jumlahNasabah;
    cout << "\nNasabah Gold   : " << jumlahPremium;
    cout << "\nNasabah Kaya   : " << namaTerkaya;
    cout << "\nSaldo Tertinggi: " << saldoTerbesar;
    cout << "\n========================================\n";
}

void Bank::simpanFile() {
    ofstream file("data_nasabah.txt");
    for (int i = 0; i < jumlahNasabah; i++) {
        file << daftarNasabah[i]->getNama() << "|"
             << daftarNasabah[i]->getSpesies() << "|"
             << daftarNasabah[i]->getRekening() << "|"
             << fixed << setprecision(0) << daftarNasabah[i]->getSaldo() << endl;
    }
    file.close();
}

void Bank::bacaFile() {
    ifstream file("data_nasabah.txt");
    string nama, spesies, rekening;
    double saldo;

    while (getline(file, nama, '|')) {
        getline(file, spesies, '|');
        getline(file, rekening, '|');
        file >> saldo;
        file.ignore(); // Membersihkan newline

        if (saldo >= 1000000) {

            daftarNasabah[jumlahNasabah]
                = new PremiumNasabah(
                    nama,
                    spesies,
                    rekening,
                    saldo,
                    "Gold"
                );
        }
        else {

            daftarNasabah[jumlahNasabah]
                = new RegulerNasabah(
                    nama,
                    spesies,
                    rekening,
                    saldo
                );
        }
        jumlahNasabah++;
    }
    file.close();
}
