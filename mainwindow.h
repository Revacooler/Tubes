#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "halamanutama.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct UserData {
    QString username;
    QString password;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();



private:
    Ui::MainWindow *ui;
    HalamanUtama *halamanutama;        // Objek halaman informasi
    QStackedWidget *stackedWidget;

    // Array untuk menyimpan data user login
    static const int maxUser = 100;
    UserData users[maxUser];
    int userCount;

    void addUser(const QString &username, const QString &password);
    int binarySearchUser(const QString &username);  // Deklarasi fungsi binary search
};

#endif // MAINWINDOW_H
