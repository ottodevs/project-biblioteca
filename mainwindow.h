#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <prestamo.h>
#include <usuario.h>
#include <solvencia.h>
#include <libro.h>
#include <utils.h>
#include <manualusuario.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initGUI();
    void initConnect();
    void includeHome();
    void includeHead();
    void closeEvent(QCloseEvent *);

private slots:

    void slotHome();
    void slotPrestamo();
    void slotEntregaPrestamo();
    void slotConsultaPrestamo();
    void slotRenovacion();
    void slotNewUser();
    void slotEditUser();
    void slotSearchUser();
    void slotDeleteUser();
    void slotSolvencia();
    void slotCloseWindow();
    void slotNewBook();
    void slotSearchBook();
    void slotDeleteBook();
    void slotEditBook();
    void slotCargarLibros();
    void slotManualUsuario();
    void slotAbout();

private:
    Ui::MainWindow *ui;

    QLabel *lblTitulo;
    QLabel *lblEscudo;

    Prestamo *prestamo;
    Usuarios *user;
    Solvencia *solvencia;
    Libro *libro;
    Utils *util;

    ManualUsuario *manualUsuario;


};

#endif // MAINWINDOW_H
