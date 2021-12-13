#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFont>
#include <QDir>
#include "reserve.h"
#include "struttura.h"
class MainWindow : public QWidget
{
    Q_OBJECT
private:
    Contenitore* model;
    Hotel* H;
    QString pathImmagini;
    Reserve* r;
    Struttura*s;
    void AddFirst();
    void AddSecond();
    QPushButton* struttura;
    QPushButton* prenotazioni;
    QGroupBox* first;
    QGroupBox* second;
    virtual void closeEvent (QCloseEvent *);
private slots:
    void openR();
    void openS();
    void closeR(QObject*);
    void closeS(QObject*);
public:
    MainWindow();
    ~MainWindow();
};

#endif // MAINWINDOW_H
