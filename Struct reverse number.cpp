#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int MAX_SIZE = 3;

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

    void tampilkanMenu() const {
        cout << "\n===================================\n";
        cout << "           Menu Sistem             \n";
        cout << "===================================\n";
        cout << "| 1. Create Sepatu                |\n";
        cout << "| 2. Read Sepatu                  |\n";
        cout << "| 3. Update Sepatu                |\n";
        cout << "| 4. Find Sepatu                  |\n";
        cout << "| 5. Delete Sepatu                |\n";
        cout << "| 6. Exit                         |\n";
        cout << "===================================\n";
        cout << "Pilih menu: ";
    }

    void clearInputBuffer() const {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

    bool isCapacityFull() const {
        return jumlahSepatu >= MAX_SIZE;
    }

    int getValidInt(int min, int max) const {
        int input;
        while (!(cin >> input) || input < min || input > max) {
            cout << "Input tidak valid. Masukkan angka antara " << min << " dan " << max << ": ";
            clearInputBuffer();
        }
        clearInputBuffer();
        return input;
    }

    double getValidDouble(double min, double max) const {
        double input;
        while (!(cin >> input) || input < min || input > max) {
            cout << "Input tidak valid. Masukkan angka antara " << min << " dan " << max << ": ";
            clearInputBuffer();
        }
        clearInputBuffer();
        return input;
    }

    void createSepatu() {
        if (isCapacityFull()) {
            cout << "Kapasitas penuh. Tidak dapat menambah sepatu baru.\n";
            return;
        }

        do {
            Sepatu sepatuBaru;
            cout << "ID Sepatu (0: Kembali): "; getline(cin, sepatuBaru.id);
            if (sepatuBaru.id == "0") return;
            cout << "Nama Sepatu: "; getline(cin, sepatuBaru.nama);
            cout << "Jumlah Sepatu: "; sepatuBaru.jumlah = getValidInt(0, numeric_limits<int>::max());
            cout << "Harga Sepatu: "; sepatuBaru.harga = getValidDouble(0, 10000000000000000);
            daftarSepatu[jumlahSepatu++] = sepatuBaru;
            cout << "Sepatu berhasil ditambahkan.\n";

            if (isCapacityFull()) {
                cout << "Kapasitas penuh. Tidak dapat menambah sepatu baru.\n";
                return;
            }

            cout << "Tambah sepatu lain? (1: Ya, 0: Kembali): ";
        } while (getValidInt(0, 1) != 0);
    }

    void readSepatu() const {
        if (jumlahSepatu == 0) {
            cout << "Tidak ada stok.\n";
            return;
        }
        cout << "\n===========================================================================\n";
        cout << "| No |    ID    |         Nama          | Jumlah |    Harga    |    Laba    |\n";
        cout << "=============================================================================\n";
        for (int i = 0; i < jumlahSepatu; ++i) {
            double laba = daftarSepatu[i].jumlah * daftarSepatu[i].harga;
            cout << "| " << setw(2) << left << (i + 1)
                 << " | " << setw(8) << left << daftarSepatu[i].id
                 << " | " << setw(18) << left << daftarSepatu[i].nama
                 << " | " << setw(6) << right << daftarSepatu[i].jumlah
                 << " | " << setw(10) << right << daftarSepatu[i].harga
                 << " | " << setw(10) << right << laba
                 << " |\n";
        }
        cout << "============================================================================\n";
    }

    void updateSepatu() {
        if (jumlahSepatu == 0) {
            cout << "Tidak ada stok.\n";
            return;
        }

        while (true) {
            cout << "Masukkan ID Sepatu yang ingin diupdate (0: Kembali): ";
            string id; getline(cin, id);
            if (id == "0") return;

            for (int i = 0; i < jumlahSepatu; ++i) {
                if (daftarSepatu[i].id == id) {
                    int pilihan;
                    do {
                        cout << "\nApa yang ingin Anda update?\n";
                        cout << "1. Nama\n";
                        cout << "2. Jumlah\n";
                        cout << "3. Harga\n";
                        cout << "4. Selesai\n";
                        cout << "Pilih: ";
                        pilihan = getValidInt(1, 4);

                        switch (pilihan) {
                            case 1:
                                cout << "Nama Baru: "; getline(cin, daftarSepatu[i].nama); break;
                            case 2:
                                cout << "Jumlah Baru: "; daftarSepatu[i].jumlah = getValidInt(0, numeric_limits<int>::max()); break;
                            case 3:
                                cout << "Harga Baru: "; daftarSepatu[i].harga = getValidDouble(0, 1000000000000000); break;
                            case 4: cout << "Update selesai.\n"; break;
                            default: cout << "Pilihan tidak valid.\n";
                        }
                    } while (pilihan != 4);
                    break;
                }
            }
            cout << "Update sepatu lain? (1: Ya, 0: Kembali): ";
            if (getValidInt(0, 1) == 0) return;
        }
    }

    void findSepatu() const {
        if (jumlahSepatu == 0) {
            cout << "Tidak ada stok.\n";
            return;
        }

        while (true) {
            cout << "Masukkan ID Sepatu yang ingin dicari (0: Kembali): ";
            string id; getline(cin, id);
            if (id == "0") return;

            bool found = false;
            for (int i = 0; i < jumlahSepatu; ++i) {
                if (daftarSepatu[i].id == id) {
                    double laba = daftarSepatu[i].jumlah * daftarSepatu[i].harga;
                    cout << "ID: " << daftarSepatu[i].id << ", Nama: " << daftarSepatu[i].nama
                         << ", Jumlah: " << daftarSepatu[i].jumlah << ", Harga: " << daftarSepatu[i].harga
                         << ", Laba: " << laba << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "ID tidak ditemukan.\n";
            }
            cout << "Cari sepatu lain? (1: Ya, 0: Kembali): ";
            if (getValidInt(0, 1) == 0) return;
        }
    }

    void deleteSepatu() {
        if (jumlahSepatu == 0) {
            cout << "Tidak ada stok.\n";
            return;
        }

        while (true) {
            cout << "Pilih opsi:\n";
            cout << "1. Hapus sepatu berdasarkan ID\n";
            cout << "2. Hapus semua data\n";
            cout << "0. Kembali\n";
            cout << "Pilih: ";
            int pilihan = getValidInt(0, 2);

            if (pilihan == 0) return;

            if (pilihan == 1) {
                while (true) {
                    cout << "ID Sepatu yang ingin dihapus (0: Kembali): ";
                    string id; getline(cin, id);
                    if (id == "0") return;

                    bool found = false;
                    for (int i = 0; i < jumlahSepatu; ++i) {
                        if (daftarSepatu[i].id == id) {
                            for (int j = i; j < jumlahSepatu - 1; ++j) {
                                daftarSepatu[j] = daftarSepatu[j + 1];
                            }
                            --jumlahSepatu;
                            cout << "Sepatu berhasil dihapus.\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "ID tidak ditemukan.\n";
                    }
                    if (jumlahSepatu > 0) {
                        cout << "Ada sepatu lain yang ingin dihapus? (1: Ya, 0: Kembali): ";
                        if (getValidInt(0, 1) == 0) return;
                    } else {
                        cout << "Tidak ada data lagi.\n";
                        return;
                    }
                }
            } else if (pilihan == 2) {
                jumlahSepatu = 0;
                cout << "Semua data berhasil dihapus.\n";
                return;
            }
        }
    }

    bool login() const {
        string username, password;
        const string correctUsername = "hisyam";
        const string correctPassword = "richi";
        for (int attempt = 0; attempt < 3; ++attempt) {
            cout << "\n===================================\n";
        cout << "           Login SamChie Store      \n";
        cout << "===================================\n";
        cout << " Username :          \n"; cin >> username  ;
        cout << " Password :          \n"; cin >> password  ;
            clearInputBuffer();
            if (username == correctUsername && password == correctPassword) return true;
            cout << "Login gagal. Coba lagi.\n";
        }
        return false;
    }

public:
    SistemSepatu() : jumlahSepatu(0) {}

    void run() {
        if (!login()) {
            cout << "Login gagal setelah 3 percobaan. Program berakhir.\n";
            return;
        }

        int pilihan;
        do {
            tampilkanMenu();
            pilihan = getValidInt(1, 6);
            switch (pilihan) {
                case 1: createSepatu(); break;
                case 2: readSepatu(); break;
                case 3: updateSepatu(); break;
                case 4: findSepatu(); break;
                case 5: deleteSepatu(); break;
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
