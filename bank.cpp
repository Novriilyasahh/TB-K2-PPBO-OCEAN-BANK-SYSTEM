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
#define HIJAU "\033[32m"

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
    cout << "\n            TAMBAH NASABAH";
    cout << "\n========================================\n";

    cin.ignore();

    // INPUT NAMA
    while (1) {

        int namaSama = 0;

        cout << "(0 = Kembali)\nNama Nasabah : ";
        getline(cin, nama);

        if (nama == "0") return;

        // FIX 1: cek input kosong / hanya spasi
        if (nama.empty() || nama.find_first_not_of(' ') == string::npos) {
            cout << MERAH << "\n[ ERROR ] Nama tidak boleh kosong!\n" << RESET;
            continue;
        }

        if (validHuruf(nama) == 1) {
            cout << MERAH << "\n[ ERROR ] Nama hanya boleh huruf!\n" << RESET;
            continue;
        }

        // CEK NAMA DUPLIKAT
        for (int i = 0; i < jumlahNasabah; i++) {
            if (daftarNasabah[i]->getNama() == nama) {
                namaSama = 1;
            }
        }

        if (namaSama == 1) {
            cout << MERAH << "\n[ ERROR ] Nama nasabah sudah digunakan!\n" << RESET;
            continue;
        }

        break;
    }

    // INPUT SPESIES
    while (1) {
        cout << "(0 = Kembali)\nSpesies Laut : ";
        getline(cin, spesies);
        if (spesies == "0") return;

        // FIX 1: cek input kosong / hanya spasi
        if (spesies.empty() || spesies.find_first_not_of(' ') == string::npos) {
            cout << MERAH << "\n[ ERROR ] Spesies tidak boleh kosong!\n" << RESET;
            continue;
        }

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
        daftarNasabah[jumlahNasabah] = new PremiumNasabah(nama, spesies, rekening, saldo, "Gold");
    } else {
        daftarNasabah[jumlahNasabah] = new RegulerNasabah(nama, spesies, rekening, saldo);
    }

    jumlahNasabah++;
    simpanFile();
    cout << HIJAU << "\n[ SUCCESS ] Nasabah berhasil ditambahkan!\n" << RESET;
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

    cout << "\n========================================";
    cout << "\n           CEK SALDO NASABAH";
    cout << "\n========================================\n";
    
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

    cout << "\n========================================";
    cout << "\n          SETOR SALDO NASABAH";
    cout << "\n========================================\n";

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
            if (jumlah < 10000) {
                cout << MERAH << "\n[ ERROR ] Minimal setor 10.000!\n" << RESET;
                return;
            }

            // FIX 3: cek batas maksimal saldo setelah setor
            if ((daftarNasabah[i]->getSaldo() + jumlah) > 50000000) {
                cout << MERAH << "\n[ ERROR ] Total saldo tidak boleh melebihi 50.000.000!\n" << RESET;
                return;
            }

            // PENGGUNAAN OPERATOR OVERLOADING
            *daftarNasabah[i] += jumlah; 
            
            simpanFile();
            cout << HIJAU << "\n[ SUCCESS ] Setor berhasil!\n" << RESET;
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

    cout << "\n========================================";
    cout << "\n          TARIK SALDO NASABAH";
    cout << "\n========================================\n";
    
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
                cout << HIJAU << "\n[ SUCCESS ] Penarikan berhasil!\n" << RESET;
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
                cout << "\n           NASABAH BRONZE";
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
                cout << "\n           NASABAH SILVER";
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
                cout << "\n            NASABAH GOLD";
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
    int jumlahGold = 0;
    int jumlahSilver = 0;
    int jumlahBronze = 0;

    for (int i = 0; i < jumlahNasabah; i++) {
        totalSaldo += daftarNasabah[i]->getSaldo();

        if (daftarNasabah[i]->getSaldo() > saldoTerbesar) {
            saldoTerbesar = daftarNasabah[i]->getSaldo();
        }

        double saldo = daftarNasabah[i]->getSaldo();

        // BRONZE
        if (saldo >= 10000 && saldo <= 99999) {
            jumlahBronze++;
        }

        // SILVER
        else if (saldo >= 100000 && saldo <= 999999) {
            jumlahSilver++;
        }

        // GOLD
        else if (saldo >= 1000000) {
            jumlahGold++;
        }
    }

    cout << "\n========================================";
    cout << "\n            STATISTIK BANK";
    cout << "\n========================================";
    cout << "\nJumlah Nasabah : " << jumlahNasabah;
    cout << "\nTotal Saldo    : " << fixed << setprecision(0) << totalSaldo;
    cout << "\nRata-rata      : " << totalSaldo / jumlahNasabah;
    cout << GOLD << "\nNasabah Gold   : " << jumlahGold << RESET; 
    cout << SILVER << "\nNasabah Silver : " << jumlahSilver << RESET;
    cout << BRONZE << "\nNasabah Bronze : " << jumlahBronze << RESET;
    cout << "\nSaldo Tertinggi: " << saldoTerbesar;
    cout << "\n========================================\n";
}

// FIX 2: simpanFile dirapikan + buat file kategori terpisah
void Bank::simpanFile() {
    // File utama semua nasabah
    ofstream file("data_nasabah.txt");
    file << "========================================\n";
    file << "         DATA NASABAH OCEAN BANK\n";
    file << "========================================\n";
    for (int i = 0; i < jumlahNasabah; i++) {
        double saldo = daftarNasabah[i]->getSaldo();
        string level;
        if (saldo >= 1000000)       level = "Gold";
        else if (saldo >= 100000)   level = "Silver";
        else                        level = "Bronze";

        file << "[" << (i + 1) << "] "
             << daftarNasabah[i]->getNama() << "|"
             << daftarNasabah[i]->getSpesies() << "|"
             << daftarNasabah[i]->getRekening() << "|"
             << fixed << setprecision(0) << saldo << "|"
             << level << "\n";
    }
    file << "========================================\n";
    file << "Total Nasabah : " << jumlahNasabah << "\n";
    file << "========================================\n";
    file.close();

    // File kategori nasabah (bronze, silver, gold)
    ofstream fileKategori("data_kategori.txt");
    fileKategori << "========================================\n";
    fileKategori << "      KATEGORI NASABAH OCEAN BANK\n";
    fileKategori << "========================================\n";

    // --- GOLD ---
    fileKategori << "\n[GOLD] (Saldo >= 1.000.000)\n";
    fileKategori << "----------------------------------------\n";
    int countGold = 0;
    for (int i = 0; i < jumlahNasabah; i++) {
        if (daftarNasabah[i]->getSaldo() >= 1000000) {
            fileKategori << "  Nama     : " << daftarNasabah[i]->getNama() << "\n";
            fileKategori << "  Spesies  : " << daftarNasabah[i]->getSpesies() << "\n";
            fileKategori << "  Rekening : " << daftarNasabah[i]->getRekening() << "\n";
            fileKategori << "  Saldo    : " << fixed << setprecision(0) << daftarNasabah[i]->getSaldo() << "\n";
            fileKategori << "  ..............................\n";
            countGold++;
        }
    }
    if (countGold == 0) fileKategori << "  (Tidak ada nasabah Gold)\n";

    // --- SILVER ---
    fileKategori << "\n[SILVER] (Saldo 100.000 - 999.999)\n";
    fileKategori << "----------------------------------------\n";
    int countSilver = 0;
    for (int i = 0; i < jumlahNasabah; i++) {
        double s = daftarNasabah[i]->getSaldo();
        if (s >= 100000 && s <= 999999) {
            fileKategori << "  Nama     : " << daftarNasabah[i]->getNama() << "\n";
            fileKategori << "  Spesies  : " << daftarNasabah[i]->getSpesies() << "\n";
            fileKategori << "  Rekening : " << daftarNasabah[i]->getRekening() << "\n";
            fileKategori << "  Saldo    : " << fixed << setprecision(0) << s << "\n";
            fileKategori << "  ..............................\n";
            countSilver++;
        }
    }
    if (countSilver == 0) fileKategori << "  (Tidak ada nasabah Silver)\n";

    // --- BRONZE ---
    fileKategori << "\n[BRONZE] (Saldo 10.000 - 99.999)\n";
    fileKategori << "----------------------------------------\n";
    int countBronze = 0;
    for (int i = 0; i < jumlahNasabah; i++) {
        double s = daftarNasabah[i]->getSaldo();
        if (s >= 10000 && s <= 99999) {
            fileKategori << "  Nama     : " << daftarNasabah[i]->getNama() << "\n";
            fileKategori << "  Spesies  : " << daftarNasabah[i]->getSpesies() << "\n";
            fileKategori << "  Rekening : " << daftarNasabah[i]->getRekening() << "\n";
            fileKategori << "  Saldo    : " << fixed << setprecision(0) << s << "\n";
            fileKategori << "  ..............................\n";
            countBronze++;
        }
    }
    if (countBronze == 0) fileKategori << "  (Tidak ada nasabah Bronze)\n";

    fileKategori << "\n========================================\n";
    fileKategori << "Gold   : " << countGold << " nasabah\n";
    fileKategori << "Silver : " << countSilver << " nasabah\n";
    fileKategori << "Bronze : " << countBronze << " nasabah\n";
    fileKategori << "========================================\n";
    fileKategori.close();
}

void Bank::bacaFile() {
    // bacaFile tetap baca format lama (pipe-separated) supaya data lama tetap terbaca
    // format baru di simpanFile pakai prefix "[N] " jadi kita skip baris non-data
    ifstream file("data_nasabah.txt");
    string baris;

    while (getline(file, baris)) {
        // Cari baris yang diawali "[angka] " (format baru)
        if (baris.empty() || baris[0] != '[') continue;

        // Hapus prefix "[N] "
        size_t tutup = baris.find(']');
        if (tutup == string::npos) continue;
        string data = baris.substr(tutup + 2); // skip "] "

        // Parse pipe-separated
        stringstream ss(data);
        string nama, spesies, rekening, saldoStr, level;
        if (!getline(ss, nama, '|'))     continue;
        if (!getline(ss, spesies, '|'))  continue;
        if (!getline(ss, rekening, '|')) continue;
        if (!getline(ss, saldoStr, '|')) continue;
        // level bisa diabaikan, ditentukan dari saldo

        double saldo = atof(saldoStr.c_str());

        if (saldo >= 1000000) {
            daftarNasabah[jumlahNasabah] = new PremiumNasabah(nama, spesies, rekening, saldo, "Gold");
        } else {
            daftarNasabah[jumlahNasabah] = new RegulerNasabah(nama, spesies, rekening, saldo);
        }
        jumlahNasabah++;
    }
    file.close();
}
