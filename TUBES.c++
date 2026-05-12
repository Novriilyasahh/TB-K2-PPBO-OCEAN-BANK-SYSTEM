#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

/*
==================================================
                CLASS NASABAH
==================================================
*/

class Nasabah {

protected:

    string nama;
    string spesies;
    string rekening;
    double saldo;

public:

    Nasabah() {

        nama = "-";
        spesies = "-";
        rekening = "-";
        saldo = 0;
    }

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

        cout << "\n[ INFO ] Data nasabah "
             << nama
             << " selesai digunakan.\n";
    }

    virtual void tampilkanData() {

        cout << "\n========================================";
        cout << "\n           DATA NASABAH";
        cout << "\n========================================";

        cout << "\n Nama         : " << nama;
        cout << "\n Spesies      : " << spesies;
        cout << "\n No Rekening  : " << rekening;
        cout << "\n Saldo        : " << saldo;

        cout << "\n========================================\n";
    }

    void setor(double jumlah) {

        saldo = saldo + jumlah;
    }

    int tarik(double jumlah) {

        if (jumlah > saldo) {

            return 0;
        }

        saldo = saldo - jumlah;

        return 1;
    }

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

        : Nasabah(nama,
                  spesies,
                  rekening,
                  saldo) {

        this->level = level;
    }

    void tampilkanData() {

        cout << "\n========================================";
        cout << "\n       NASABAH PREMIUM GOLD";
        cout << "\n========================================";

        cout << "\n Nama         : " << nama;
        cout << "\n Spesies      : " << spesies;
        cout << "\n No Rekening  : " << rekening;
        cout << "\n Saldo        : " << saldo;
        cout << "\n Level        : " << level;

        cout << "\n========================================\n";
    }
};

/*
==================================================
                    CLASS BANK
==================================================
*/

class Bank {

private:

    Nasabah* daftarNasabah[100];

    int jumlahNasabah;

public:

    Bank() {

        jumlahNasabah = 0;

        bacaFile();
    }

    ~Bank() {

        simpanFile();

        for (int i = 0; i < jumlahNasabah; i++) {

            delete daftarNasabah[i];
        }
    }

    /*
    ==============================================
                VALIDASI HURUF
    ==============================================
    */

    int validHuruf(string teks) {

        int salah = 0;

        for (int i = 0; teks[i] != '\0'; i++) {

            if (teks[i] >= 'A' &&
                teks[i] <= 'Z') {
            }

            else if (teks[i] >= 'a' &&
                     teks[i] <= 'z') {
            }

            else if (teks[i] == ' ') {
            }

            else {

                salah = 1;
            }
        }

        return salah;
    }

    /*
    ==============================================
                VALIDASI ANGKA
    ==============================================
    */

    int validAngka(string teks) {

        int salah = 0;

        for (int i = 0; teks[i] != '\0'; i++) {

            if (teks[i] != '0' &&
                teks[i] != '1' &&
                teks[i] != '2' &&
                teks[i] != '3' &&
                teks[i] != '4' &&
                teks[i] != '5' &&
                teks[i] != '6' &&
                teks[i] != '7' &&
                teks[i] != '8' &&
                teks[i] != '9') {

                salah = 1;
            }
        }

        return salah;
    }

    /*
    ==============================================
                TAMBAH NASABAH
    ==============================================
    */

    void tambahNasabah() {

    string nama;
    string spesies;
    string rekening;
    string inputSaldo;

    double saldo;

    int salah;
    int ditemukan;

    cout << "\n========================================";
    cout << "\n         TAMBAH NASABAH";
    cout << "\n========================================\n";

    cin.ignore();

    // INPUT NAMA
    while (1) {

        cout << "(0 = Kembali ke Menu Utama)";
        cout << "\nNama Nasabah";
        cout << "\nInput : ";

        getline(cin, nama);

        if (nama == "0") {

            return;
        }

        salah = validHuruf(nama);

        if (salah == 0) {

            break;
        }

        cout << "\n[ ERROR ] Nama hanya boleh huruf!\n";
    }

    // INPUT SPESIES
    while (1) {

        cout << "(0 = Kembali ke Menu Utama)";
        cout << "\nSpesies Laut";
        cout << "\nInput : ";

        getline(cin, spesies);

        if (spesies == "0") {

            return;
        }

        salah = validHuruf(spesies);

        if (salah == 0) {

            break;
        }

        cout << "\n[ ERROR ] Spesies hanya boleh huruf!\n";
    }

    // INPUT REKENING
    while (1) {

        cout << "(0 = Kembali ke Menu Utama)";
        cout << "\nNo Rekening";
        cout << "\nInput : ";

        cin >> rekening;

        if (rekening == "0") {

            return;
        }

        salah = validAngka(rekening);

        if (salah == 1) {

            cout << "\n[ ERROR ] Rekening harus angka!\n";

            continue;
        }

        ditemukan = 0;

        for (int i = 0; i < jumlahNasabah; i++) {

            if (daftarNasabah[i]->getRekening()
                == rekening) {

                ditemukan = 1;
            }
        }

        if (ditemukan == 1) {

            cout << "\n[ ERROR ] Rekening sudah digunakan!\n";

        } else {

            break;
        }
    }

    // INPUT SALDO
    while (1) {

        cout << "(0 = Kembali ke Menu Utama)";
        cout << "\nSaldo Awal";
        cout << "\nInput : ";

        cin >> inputSaldo;

        if (inputSaldo == "0") {

            return;
        }

        salah = validAngka(inputSaldo);

        if (salah == 1) {

            cout << "\n[ ERROR ] Saldo harus angka!\n";

            continue;
        }

        saldo = atof(inputSaldo.c_str());

        if (saldo < 10000 ||
            saldo > 50000000) {

            cout << "\n[ ERROR ]";
            cout << "\nMinimal saldo 10000";
            cout << "\nMaksimal saldo 50000000\n";

        } else {

            break;
        }
    }

    // PREMIUM GOLD
    if (saldo >= 1000000) {

        daftarNasabah[jumlahNasabah]
            = new PremiumNasabah(
                nama,
                spesies,
                rekening,
                saldo,
                "Gold"
            );

    } else {

        daftarNasabah[jumlahNasabah]
            = new Nasabah(
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
    /*
    ==============================================
                    CEK SALDO
    ==============================================
    */

    void cekSaldo() {

        string rekening;

        int salah;
        int ditemukan;

        while (1) {

            ditemukan = 0;

            cout << "(0 = Kembali ke Menu Utama)";
            cout << "\nMasukkan nomor rekening";
            cout << "\nInput : ";
            cin >> rekening;

            if (rekening == "0") {

                return;
            }

            salah = validAngka(rekening);

            while (salah == 1) {

                cout << "\n[ ERROR ] Rekening harus angka!\n";

                cout << "Masukkan rekening lagi : ";
                cin >> rekening;

                if (rekening == "0") {

                    return;
                }

                salah = validAngka(rekening);
            }

            for (int i = 0; i < jumlahNasabah; i++) {

                if (daftarNasabah[i]->getRekening()
                    == rekening) {

                    cout << "\nNama  : "
                         << daftarNasabah[i]->getNama();

                    cout << "\nSaldo : "
                         << daftarNasabah[i]->getSaldo()
                         << endl;

                    ditemukan = 1;
                }
            }

            if (ditemukan == 1) {

                return;
            }

            cout << "\n[ ERROR ] Rekening tidak ditemukan!\n";
        }
    }

    /*
    ==============================================
                    SETOR SALDO
    ==============================================
    */

    void setorSaldo() {

        string rekening;
        string inputJumlah;

        double jumlah;

        int salah;
        int ditemukan;

        while (1) {

            ditemukan = 0;

            cout << "(0 = Kembali ke Menu Utama)";
            cout << "\nMasukkan nomor rekening";
            cout << "\nInput : ";
            cin >> rekening;

            if (rekening == "0") {

                return;
            }

            salah = validAngka(rekening);

            while (salah == 1) {

                cout << "\n[ ERROR ] Rekening harus angka!\n";

                cout << "Masukkan rekening lagi : ";
                cin >> rekening;

                if (rekening == "0") {

                    return;
                }

                salah = validAngka(rekening);
            }

            for (int i = 0; i < jumlahNasabah; i++) {

                if (daftarNasabah[i]->getRekening()
                    == rekening) {

                    ditemukan = 1;

                    cout << "Jumlah setor : ";
                    cin >> inputJumlah;

                    salah = validAngka(inputJumlah);

                    while (salah == 1) {

                        cout << "\n[ ERROR ] Jumlah harus angka!\n";

                        cout << "Masukkan lagi : ";
                        cin >> inputJumlah;

                        salah = validAngka(inputJumlah);
                    }

                    jumlah = atof(inputJumlah.c_str());

                    while (jumlah < 10000 ||
                           jumlah > 50000000) {

                        cout << "\n[ ERROR ]";
                        cout << "\nMinimal setor 10000";
                        cout << "\nMaksimal setor 50000000\n";

                        cout << "Masukkan lagi : ";
                        cin >> inputJumlah;

                        jumlah = atof(inputJumlah.c_str());
                    }

                    daftarNasabah[i]->setor(jumlah);

                    simpanFile();

                    cout << "\n[ SUCCESS ] Setor berhasil!\n";

                    return;
                }
            }

            cout << "\n[ ERROR ] Rekening tidak ditemukan!\n";
        }
    }

    /*
    ==============================================
                    TARIK SALDO
    ==============================================
    */

    void tarikSaldo() {

        string rekening;
        string inputJumlah;

        double jumlah;

        int salah;
        int ditemukan;

        while (1) {

            ditemukan = 0;

            cout << "(0 = Kembali ke Menu Utama)";
            cout << "\nMasukkan nomor rekening";
            cout << "\nInput : ";
            cin >> rekening;

            if (rekening == "0") {

                return;
            }

            salah = validAngka(rekening);

            while (salah == 1) {

                cout << "\n[ ERROR ] Rekening harus angka!\n";

                cout << "Masukkan rekening lagi : ";
                cin >> rekening;

                if (rekening == "0") {

                    return;
                }

                salah = validAngka(rekening);
            }

            for (int i = 0; i < jumlahNasabah; i++) {

                if (daftarNasabah[i]->getRekening()
                    == rekening) {

                    ditemukan = 1;

                    cout << "Jumlah tarik : ";
                    cin >> inputJumlah;

                    salah = validAngka(inputJumlah);

                    while (salah == 1) {

                        cout << "\n[ ERROR ] Jumlah harus angka!\n";

                        cout << "Masukkan lagi : ";
                        cin >> inputJumlah;

                        salah = validAngka(inputJumlah);
                    }

                    jumlah = atof(inputJumlah.c_str());

                    while (jumlah < 10000) {

                        cout << "\n[ ERROR ]";
                        cout << "\nMinimal penarikan adalah 10000!\n";

                        cout << "Masukkan jumlah tarik lagi : ";
                        cin >> inputJumlah;

                        jumlah = atof(inputJumlah.c_str());
                    }

                    if (daftarNasabah[i]->tarik(jumlah)) {

                        simpanFile();

                        cout << "\n[ SUCCESS ] Penarikan berhasil!\n";

                    } else {

                        cout << "\n[ ERROR ] Saldo tidak cukup!\n";
                    }

                    return;
                }
            }

            cout << "\n[ ERROR ] Rekening tidak ditemukan!\n";
        }
    }

    /*
    ==============================================
                LAPORAN KEUANGAN
    ==============================================
    */

    void laporanKeuangan() {

        double total = 0;

        cout << "\n========================================";
        cout << "\n       LAPORAN KEUANGAN";
        cout << "\n========================================";

        for (int i = 0; i < jumlahNasabah; i++) {

            total = total
                    + daftarNasabah[i]->getSaldo();
        }

        cout << "\nJumlah Nasabah : "
             << jumlahNasabah;

        cout << "\nTotal Saldo    : "
             << total;

        cout << "\n========================================\n";
    }

    /*
    ==============================================
                CEK DATA NASABAH
    ==============================================
    */

    void cekDataNasabah() {

        string rekening;

        int salah;
        int ditemukan;

        while (1) {

            ditemukan = 0;

            cout << "(0 = Kembali ke Menu Utama)";
            cout << "\nMasukkan nomor rekening";
            cout << "\nInput : ";
            cin >> rekening;

            if (rekening == "0") {

                return;
            }

            salah = validAngka(rekening);

            while (salah == 1) {

                cout << "\n[ ERROR ] Rekening harus angka!\n";

                cout << "Masukkan rekening lagi : ";
                cin >> rekening;

                if (rekening == "0") {

                    return;
                }

                salah = validAngka(rekening);
            }

            for (int i = 0; i < jumlahNasabah; i++) {

                if (daftarNasabah[i]->getRekening()
                    == rekening) {

                    daftarNasabah[i]->tampilkanData();

                    ditemukan = 1;

                    return;
                }
            }

            cout << "\n[ ERROR ] Data tidak ditemukan!\n";
        }
    }

    /*
    ==============================================
                    STATISTIK
    ==============================================
    */

    void statistikBank() {

        double totalSaldo = 0;
        double saldoTerbesar = 0;
        double rataRata = 0;

        int jumlahPremium = 0;

        string namaTerkaya = "-";

        for (int i = 0; i < jumlahNasabah; i++) {

            totalSaldo =
                totalSaldo +
                daftarNasabah[i]->getSaldo();

            if (daftarNasabah[i]->getSaldo()
                > saldoTerbesar) {

                saldoTerbesar =
                    daftarNasabah[i]->getSaldo();

                namaTerkaya =
                    daftarNasabah[i]->getNama();
            }

            if (daftarNasabah[i]->getSaldo()
                >= 1000000) {

                jumlahPremium++;
            }
        }

        if (jumlahNasabah > 0) {

            rataRata =
                totalSaldo / jumlahNasabah;
        }

        cout << "\n========================================";
        cout << "\n          STATISTIK BANK";
        cout << "\n========================================";

        cout << "\nJumlah Nasabah : "
             << jumlahNasabah;

        cout << "\nTotal Saldo    : "
             << totalSaldo;

        cout << "\nRata-rata      : "
             << rataRata;

        cout << "\nNasabah Gold   : "
             << jumlahPremium;

        cout << "\nNasabah Kaya   : "
             << namaTerkaya;

        cout << "\nSaldo Tertinggi: "
             << saldoTerbesar;

        cout << "\n========================================\n";
    }

    /*
    ==============================================
                    SIMPAN FILE
    ==============================================
    */

    void simpanFile() {

        ofstream file("data_nasabah.txt");

        for (int i = 0; i < jumlahNasabah; i++) {

            file << daftarNasabah[i]->getNama()
                 << "|"
                 << daftarNasabah[i]->getSpesies()
                 << "|"
                 << daftarNasabah[i]->getRekening()
                 << "|"
                 << fixed
                 << setprecision(0)
                 << daftarNasabah[i]->getSaldo()
                 << endl;
        }

        file.close();
    }

    /*
    ==============================================
                    BACA FILE
    ==============================================
    */

    void bacaFile() {

        ifstream file("data_nasabah.txt");

        string nama;
        string spesies;
        string rekening;

        double saldo;

        while (getline(file, nama, '|')) {

            getline(file, spesies, '|');

            getline(file, rekening, '|');

            file >> saldo;

            file.ignore();

            if (saldo >= 1000000) {

                daftarNasabah[jumlahNasabah]
                    = new PremiumNasabah(
                        nama,
                        spesies,
                        rekening,
                        saldo,
                        "Gold"
                    );

            } else {

                daftarNasabah[jumlahNasabah]
                    = new Nasabah(
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
};

/*
==================================================
                ASCII ART
==================================================
*/

void tampilanAwal() {

    cout << "\n";
    cout << "====================================================\n";
    cout << "                 OCEAN BANK SYSTEM\n";
    cout << "====================================================\n";

    cout << "                    ><(((('>\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "         BANK TERAMAN UNTUK MAKHLUK LAUT\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

/*
==================================================
                    MAIN PROGRAM
==================================================
*/

int main() {

    // WARNA TEMA LAUT
    system("color 0B");

    cout << fixed;
    cout << setprecision(0);

    Bank oceanBank;

    int pilihan;

    do {

        system("cls");

        tampilanAwal();

        cout << "\n1. Tambah Nasabah";
        cout << "\n2. Cek Saldo";
        cout << "\n3. Setor Saldo";
        cout << "\n4. Tarik Saldo";
        cout << "\n5. Laporan Keuangan";
        cout << "\n6. Cek Data Nasabah";
        cout << "\n7. Statistik Bank";
        cout << "\n8. Keluar";

        cout << "\n\nPilih menu : ";
        cin >> pilihan;

        while (cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\n[ ERROR ] Input harus angka!\n";

            cout << "Pilih menu lagi : ";
            cin >> pilihan;
        }

        while (pilihan < 1 || pilihan > 8) {

            cout << "\n[ ERROR ] Menu hanya tersedia 1 - 8!\n";

            cout << "Pilih menu lagi : ";
            cin >> pilihan;
        }

        switch (pilihan) {

        case 1:
            oceanBank.tambahNasabah();
            break;

        case 2:
            oceanBank.cekSaldo();
            break;

        case 3:
            oceanBank.setorSaldo();
            break;

        case 4:
            oceanBank.tarikSaldo();
            break;

        case 5:
            oceanBank.laporanKeuangan();
            break;

        case 6:
            oceanBank.cekDataNasabah();
            break;

        case 7:
            oceanBank.statistikBank();
            break;

        case 8:

            cout << "\n====================================================";
            cout << "\n      TERIMA KASIH TELAH MENGGUNAKAN";
            cout << "\n            OCEAN BANK SYSTEM";
            cout << "\n====================================================\n";

            break;
        }

        system("pause");

    } while (pilihan != 8);

    return 0;
}
