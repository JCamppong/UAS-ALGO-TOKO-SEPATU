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
        cout << "\nMenu Sistem Sepatu\n"
             << "1. Create Sepatu\n"
             << "2. Read Sepatu\n"
             << "3. Update Sepatu\n"
             << "4. Find Sepatu\n"
             << "5. Delete Sepatu\n"
             << "6. Exit\n"
             << "Pilih menu: ";
    }

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

    bool isDataAvailable() const {
        return jumlahSepatu > 0;
    }

    bool isCapacityFull() const {
        return jumlahSepatu >= MAX_SIZE;
    }

    void createSepatu() {
        int opsi;
        while (true) {
            cout << "Apakah Anda ingin membuat sepatu baru? (1: Ya, 0: Kembali): ";
            cin >> opsi;
            clearInputBuffer();
            if (opsi == 0) return;
            while (opsi == 1 && !isCapacityFull()) {
                Sepatu sepatuBaru;
                cout << "ID Sepatu (0: Kembali): "; getline(cin, sepatuBaru.id);
                if (sepatuBaru.id == "0") return;
                cout << "Nama Sepatu: "; getline(cin, sepatuBaru.nama);
                cout << "Jumlah Sepatu: "; while (!(cin >> sepatuBaru.jumlah) || sepatuBaru.jumlah < 0) { clearInputBuffer(); cout << "Jumlah tidak valid. Masukkan lagi: "; }
                cout << "Harga Sepatu: "; while (!(cin >> sepatuBaru.harga) || sepatuBaru.harga < 0) { clearInputBuffer(); cout << "Harga tidak valid. Masukkan lagi: "; }
                clearInputBuffer();
                daftarSepatu[jumlahSepatu++] = sepatuBaru;
                cout << "Sepatu berhasil ditambahkan.\n";
                cout << "Tambah sepatu lain? (1: Ya, 0: Kembali): ";
                cin >> opsi;
                clearInputBuffer();
            }
            if (isCapacityFull()) {
                cout << "Kapasitas penuh.\n";
                return;
            }
        }
    }

    void readSepatu() const {
        if (!isDataAvailable()) {
            cout << "Tidak ada stok.\n";
            return;
        }
        cout << "\nDaftar Sepatu:\n";
        for (int i = 0; i < jumlahSepatu; ++i) {
            cout << "ID: " << daftarSepatu[i].id << ", Nama: " << daftarSepatu[i].nama
                 << ", Jumlah: " << daftarSepatu[i].jumlah << ", Harga: " << daftarSepatu[i].harga << endl;
        }
    }

    void updateSepatu() {
        if (!isDataAvailable()) {
            cout << "Tidak ada stok.\n";
            return;
        }
        string id;
        while (true) {
            cout << "Masukkan ID Sepatu yang ingin diupdate (0: Kembali): ";
            getline(cin, id);
            if (id == "0") return;
            for (int i = 0; i < jumlahSepatu; ++i) {
                if (daftarSepatu[i].id == id) {
                    int pilihan;
                    do {
                        cout << "Apa yang ingin Anda update?\n1. Nama\n2. Jumlah\n3. Harga\n4. Selesai\nPilih: ";
                        cin >> pilihan; clearInputBuffer();
                        switch (pilihan) {
                            case 1: cout << "Nama Baru: "; getline(cin, daftarSepatu[i].nama); break;
                            case 2: cout << "Jumlah Baru: "; while (!(cin >> daftarSepatu[i].jumlah) || daftarSepatu[i].jumlah < 0) { clearInputBuffer(); cout << "Jumlah tidak valid. Masukkan lagi: "; } clearInputBuffer(); break;
                            case 3: cout << "Harga Baru: "; while (!(cin >> daftarSepatu[i].harga) || daftarSepatu[i].harga < 0) { clearInputBuffer(); cout << "Harga tidak valid. Masukkan lagi: "; } clearInputBuffer(); break;
                            case 4: cout << "Update selesai.\n"; break;
                            default: cout << "Pilihan tidak valid.\n";
                        }
                    } while (pilihan != 4);
                    break;
                }
            }
            cout << "Update sepatu lain? (1: Ya, 0: Kembali): ";
            int opsi; cin >> opsi; clearInputBuffer();
            if (opsi == 0) return;
        }
    }

    void findSepatu() {
        if (!isDataAvailable()) {
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
                    cout << "ID: " << daftarSepatu[i].id << ", Nama: " << daftarSepatu[i].nama
                         << ", Jumlah: " << daftarSepatu[i].jumlah << ", Harga: " << daftarSepatu[i].harga << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "ID tidak ditemukan.\n";
            }
            cout << "Cari sepatu lain? (1: Ya, 0: Kembali): ";
            int opsi; cin >> opsi; clearInputBuffer();
            if (opsi == 0) return;
        }
    }

    void deleteSepatu() {
        if (!isDataAvailable()) {
            cout << "Tidak ada stok.\n";
            return;
        }
        int pilihan;
        do {
            cout << "Pilih opsi:\n1. Hapus sepatu berdasarkan ID\n2. Hapus semua data\n0. Kembali\nPilih: ";
            cin >> pilihan; clearInputBuffer();
            if (pilihan == 0) return;
            if (pilihan == 1) {
                while (true) {
                    cout << "ID Sepatu yang ingin dihapus (0: Kembali): "; string id; getline(cin, id);
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
                    } else if (isDataAvailable()) {
                        cout << "Ada sepatu lain yang ingin dihapus? (1: Ya, 0: Kembali): ";
                        int opsi; cin >> opsi; clearInputBuffer();
                        if (opsi == 0) return;
                    } else {
                        return; // Tidak ada data lagi, keluar dari loop
                    }
                }
            } else if (pilihan == 2) {
                jumlahSepatu = 0;
                cout << "Semua data berhasil dihapus.\n";
                return;
            }
        } while (pilihan != 0);
    }

    bool login() {
        string username, password;
        const string correctUsername = "hisyam";
        const string correctPassword = "richi";
        for (int attempt = 0; attempt < 3; ++attempt) {
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
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
            cin >> pilihan; clearInputBuffer();
            switch (pilihan) {
                case 1: createSepatu(); break;
                case 2: readSepatu(); break;
                case 3: updateSepatu(); break;
                case 4: findSepatu(); break;
                case 5: deleteSepatu(); break;
                case 6: cout << "Keluar dari sistem...\n"; break;
                default: cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 6);
    }
};

int main() {
    SistemSepatu sistem;
    sistem.run();
    return 0;
}
