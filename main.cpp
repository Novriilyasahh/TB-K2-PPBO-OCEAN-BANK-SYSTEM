#include <iostream>
#include <cstdlib>
#include "Bank.h"
#define MERAH "\033[31m"
#define GOLD "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[36m"

using namespace std;

void tampilanAwal() {
    cout << "\n";
    cout << "====================================================\n";
    cout << "                 OCEAN BANK SYSTEM\n";
    cout << "====================================================\n";
    cout << "                     ><(((('>\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "         BANK TERAMAN UNTUK MAKHLUK LAUT\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

int main() {
    // WARNA TEMA LAUT
    system("color 0B");
    cout << CYAN;

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

        switch (pilihan) {
            case 1: oceanBank.tambahNasabah(); break;
            case 2: oceanBank.cekSaldo(); break;
            case 3: oceanBank.setorSaldo(); break;
            case 4: oceanBank.tarikSaldo(); break;
            case 5: oceanBank.laporanKeuangan(); break;
            case 6: oceanBank.cekDataNasabah(); break;
            case 7: oceanBank.statistikBank(); break;
            case 8:
                cout << "\n====================================================";
                cout << "\n      TERIMA KASIH TELAH MENGGUNAKAN";
                cout << "\n            OCEAN BANK SYSTEM";
                cout << "\n====================================================\n";
                break;
            default:
                cout << "\n[ ERROR ] Menu hanya tersedia 1 - 8!\n";
        }
        
        if(pilihan != 8) {
             cout << "\n";
             system("pause");
        }

    } while (pilihan != 8);

    return 0;
}