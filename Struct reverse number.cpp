#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_SIZE = 2;

struct Sepatu {
    string id;
    string nama;
    int jumlah;
    double harga;
};

class SistemSepatu {
private:
    Sepatu daftarSepatu[MAX_SIZE];
    int jumlahSepatu;

    void tampilkanMenu() {
        cout << "\nMenu Sistem Sepatu\n";
        cout << "1. Create Sepatu\n";
        cout << "2. Read Sepatu\n";
        cout << "3. Update Sepatu\n";
        cout << "4. Delete Sepatu\n";
        cout << "5. Find Sepatu\n";
        cout << "6. Exit\n";
        cout << "Pilih menu: ";
    }

    void tampilkanSubMenu(const string& aksi) {
        cout << "\n1. " << aksi << "\n";
        cout << "2. Kembali ke Menu Utama\n";
        cout << "Pilih opsi: ";
    }

    bool isDataAvailable() {
        return jumlahSepatu > 0;
    }

    bool isCapacityFull() {
        return jumlahSepatu >= MAX_SIZE;
    }

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

    void createSepatu() {
        if (isCapacityFull()) {
            cout << "Kapasitas penuh. Tidak bisa menambah sepatu baru.\n";
            return;
        }

        Sepatu sepatuBaru;
        cout << "Masukkan ID Sepatu: ";
        clearInputBuffer(); 
        getline(cin, sepatuBaru.id);
        cout << "Masukkan Nama Sepatu: ";
        getline(cin, sepatuBaru.nama);
        cout << "Masukkan Jumlah Sepatu: ";
        while (!(cin >> sepatuBaru.jumlah) || sepatuBaru.jumlah < 0) {
            clearInputBuffer(); 
            cout << "Jumlah tidak valid. Masukkan jumlah sepatu: ";
        }
        cout << "Masukkan Harga Sepatu: ";
        while (!(cin >> sepatuBaru.harga) || sepatuBaru.harga < 0) {
            clearInputBuffer();  
            cout << "Harga tidak valid. Masukkan harga sepatu: ";
        }
        clearInputBuffer(); 

        daftarSepatu[jumlahSepatu++] = sepatuBaru;
        cout << "Sepatu berhasil ditambahkan.\n";
        cout << "Jumlah sepatu saat ini: " << jumlahSepatu << " dari " << MAX_SIZE << endl; 
    }

    void readSepatu() {
        if (!isDataAvailable()) {
            cout << "Tidak ada Stok Sepatu tersimpan.\n";
            return;
        }

        cout << "\nDaftar Sepatu:\n";
        for (int i = 0; i < jumlahSepatu; i++) {
            cout << "ID: " << daftarSepatu[i].id << ", Nama: " << daftarSepatu[i].nama
                 << ", Jumlah: " << daftarSepatu[i].jumlah << ", Harga: " << daftarSepatu[i].harga << endl;
        }
    }

    void updateSepatu() {
        if (!isDataAvailable()) {
            cout << "Tidak ada Stok Sepatu tersimpan.\n";
            return;
        }

        string id;
        cout << "Masukkan ID Sepatu yang ingin diupdate: ";
        clearInputBuffer(); 
        getline(cin, id);

        for (int i = 0; i < jumlahSepatu; i++) {
            if (daftarSepatu[i].id == id) {
                cout << "Masukkan Nama Sepatu Baru: ";
                getline(cin, daftarSepatu[i].nama);
                cout << "Masukkan Jumlah Sepatu Baru: ";
                while (!(cin >> daftarSepatu[i].jumlah) || daftarSepatu[i].jumlah < 0) {
                    clearInputBuffer(); 
                    cout << "Jumlah tidak valid. Masukkan jumlah sepatu: ";
                }
                cout << "Masukkan Harga Sepatu Baru: ";
                while (!(cin >> daftarSepatu[i].harga) || daftarSepatu[i].harga < 0) {
                    clearInputBuffer(); 
                    cout << "Harga tidak valid. Masukkan harga sepatu: ";
                }
                clearInputBuffer(); 
                cout << "Data sepatu berhasil diupdate.\n";
                return;
            }
        }
        cout << "Sepatu dengan ID tersebut tidak ditemukan.\n";
    }

    void deleteSepatu() {
        if (!isDataAvailable()) {
            cout << "Tidak ada Stok Sepatu tersimpan.\n";
            return;
        }

        string id;
        cout << "Masukkan ID Sepatu yang ingin dihapus: ";
        clearInputBuffer(); 
        getline(cin, id);

        for (int i = 0; i < jumlahSepatu; i++) {
            if (daftarSepatu[i].id == id) {
                int jumlahHapus;
                cout << "Jumlah sepatu yang ingin dihapus: ";
                while (!(cin >> jumlahHapus) || jumlahHapus < 0 || jumlahHapus > daftarSepatu[i].jumlah) {
                    clearInputBuffer(); 
                    cout << "Jumlah tidak valid atau melebihi jumlah yang ada. Masukkan jumlah sepatu yang ingin dihapus: ";
                }
                clearInputBuffer();

                daftarSepatu[i].jumlah -= jumlahHapus;

                if (daftarSepatu[i].jumlah == 0) {
                    
                    for (int j = i; j < jumlahSepatu - 1; j++) {
                        daftarSepatu[j] = daftarSepatu[j + 1];
                    }
                    jumlahSepatu--;
                }
                
                cout << "Sepatu berhasil dihapus.\n";
                return;
            }
        }
        cout << "Sepatu dengan ID tersebut tidak ditemukan.\n";
    }

    void findSepatu() {
        if (!isDataAvailable()) {
            cout << "Tidak ada Stok Sepatu tersimpan.\n";
            return;
        }

        string id;
        cout << "Masukkan ID Sepatu yang ingin dicari: ";
        clearInputBuffer(); // 
        getline(cin, id);

        for (int i = 0; i < jumlahSepatu; i++) {
            if (daftarSepatu[i].id == id) {
                cout << "ID: " << daftarSepatu[i].id << ", Nama: " << daftarSepatu[i].nama
                     << ", Jumlah: " << daftarSepatu[i].jumlah << ", Harga: " << daftarSepatu[i].harga << endl;
                return;
            }
        }
        cout << "Sepatu dengan ID tersebut tidak ditemukan.\n";
    }

    void menuCreate() {
        while (true) {
            createSepatu();
            tampilkanSubMenu("Tambah sepatu lain");
            int pilihan;
            while (!(cin >> pilihan) || (pilihan != 1 && pilihan != 2)) { 
                clearInputBuffer(); 
                cout << "Pilihan tidak valid. Coba lagi: ";
            }
            if (pilihan == 2) break; 
        }
    }

    void menuRead() {
        while (true) {
            readSepatu();
            tampilkanSubMenu("Tampilkan sepatu lagi");
            int pilihan;
            while (!(cin >> pilihan) || (pilihan != 1 && pilihan != 2)) { // Validasi input pilihan submenu
                clearInputBuffer(); // Pastikan buffer bersih sebelum input ulang
                cout << "Pilihan tidak valid. Coba lagi: ";
            }
            if (pilihan == 2) break; // Kembali ke menu utama
        }
    }

    void menuUpdate() {
        while (true) {
            updateSepatu();
            tampilkanSubMenu("Update sepatu lain");
            int pilihan;
            while (!(cin >> pilihan) || (pilihan != 1 && pilihan != 2)) { 
                clearInputBuffer(); //
                cout << "Pilihan tidak valid. Coba lagi: ";
            }
            if (pilihan == 2) break; 
        }
    }

    void menuDelete() {
        while (true) {
            deleteSepatu();
            tampilkanSubMenu("Hapus sepatu lain");
            int pilihan;
            while (!(cin >> pilihan) || (pilihan != 1 && pilihan != 2)) { 
                clearInputBuffer(); 
                cout << "Pilihan tidak valid. Coba lagi: ";
            }
            if (pilihan == 2) break; 
        }
    }

    void menuFind() {
        while (true) {
            findSepatu();
            tampilkanSubMenu("Cari sepatu lain");
            int pilihan;
            while (!(cin >> pilihan) || (pilihan != 1 && pilihan != 2)) { 
                clearInputBuffer(); 
                cout << "Pilihan tidak valid. Coba lagi: ";
            }
            if (pilihan == 2) break; 
        }
    }

public:
    SistemSepatu() : jumlahSepatu(0) {}

    void run() {
        int pilihan;
        do {
            tampilkanMenu();
            while (!(cin >> pilihan) || pilihan < 1 || pilihan > 6) { 
                clearInputBuffer(); 
                cout << "Pilihan tidak valid. Coba lagi: ";
            }

            switch (pilihan) {
                case 1: menuCreate(); break;
                case 2: menuRead(); break;
                case 3: menuUpdate(); break;
                case 4: menuDelete(); break;
                case 5: menuFind(); break;
                case 6: cout << "Keluar dari sistem...\n"; break;
            }
        } while (pilihan != 6);
    }
};

int main() {
    SistemSepatu sistem;
    sistem.run();
    return 0;
}