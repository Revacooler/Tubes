#ifndef HALAMANUTAMA_H
#define HALAMANUTAMA_H

#include <QWidget>
#include <QObject>

// Jangan include "perpustakaan.h" di sini, cukup forward declaration
  // <<=== INI YANG PENTING!

namespace Ui {
class HalamanUtama;
}

const int maxBuku = 100;

struct Buku {
    QString judul;
    QString pengarang;
    QString tahun;
    QString kategori;
};

class HalamanUtama : public QWidget
{
    Q_OBJECT

public:
    explicit HalamanUtama(QWidget *parent = nullptr, const QString &username = "");
    ~HalamanUtama();

signals:
    void kelolaData();

private slots:
    void on_button_tambahBuku_clicked();
    void on_button_hapusBuku_clicked();
    void on_pushButton_informasi_clicked();

private:
    Ui::HalamanUtama *ui;
    QString currentUser;

    Buku daftarBuku[maxBuku];
    int jumlahBuku;

      // ← Sekarang ini valid karena sudah dideklarasikan
    void tampilkanTampilanAdmin();
    void tampilkanTampilanUser();
    void muatDataKeTabel(int index);
};

#endif // HALAMANUTAMA_H
