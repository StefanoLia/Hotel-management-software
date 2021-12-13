#ifndef RESERVATIONS_H
#define RESERVATIONS_H
#include <QWidget>
#include <QTableWidget>
#include <QFile>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include "contenitore.h"
#include "hotel.h"
#include <string>
using std::string;

class Reservations : public QWidget
{
    Q_OBJECT
private:
    int RigaSelezionata() const;
    void Read();
    void CreateList();
    void CreateButtons();
    Contenitore* C;
    Hotel* H;
    QTableWidget* tableWidget;
    QPushButton* ordina;
    QPushButton* aggiorna;
    QPushButton* rimuovi;
    QPushButton* removev;
    QGroupBox* box1;
    QGroupBox* box2;
    QGridLayout*mainLayout;
    QMessageBox mess;
    QMessageBox msg;
    virtual void closeEvent (QCloseEvent*);
private slots:
    void updates();
    void Sort();
    void Remove();
    void RemoveEv();
    void cambia(int,int);
public:
    Reservations(Contenitore*, Hotel*);
    ~Reservations();
};

#endif // RESERVATIONS_H
