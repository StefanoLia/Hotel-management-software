#ifndef CALENDAR_H
#define CALENDAR_H
#include <QApplication>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QDateEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QPoint>
#include <QSpinBox>
#include <QMessageBox>
#include <QTableWidget>
#include <QFile>
#include <QPlainTextEdit>
#include <QDir>
#include "prenotazione.h"
#include "stanza.h"
#include "reservations.h"

class Reserve : public QWidget
{
    Q_OBJECT
private:
    Contenitore* model2;
    Hotel* H2;
    void CreateHorizontalGroupbox();
    void CreateVerticalGroupbox();
    void CreateFirstGroupbox();
    void CreateSecondGroupbox();
    bool hasProblem(); // non const perché modifica la QMessageBox
    QComboBox* menu1;
    QGroupBox* horizontalGroupBox;
    QGroupBox* verticalGropuBox;
    QGroupBox* firstGroupbox;
    QGroupBox* secondGroupbox;
    QDateEdit* inizio;
    QDateEdit* fine;
    QPushButton* prenota;
    QPushButton* verifica;
    QPushButton* visualizza;
    QSpinBox* spinFloor;
    QSpinBox* spinRoom;
    QSpinBox* spinPeople;
    QMessageBox msg;
    QPlainTextEdit* name;
    QString pathImmagini;
    Reservations* R;
    virtual void closeEvent (QCloseEvent *);
private slots:
    void addPrenot();
    void ChangePlaces(QString);
    void ChangeFloor(int);
    void check();
    void NewWindow();
    void closeR(QObject*);
public:
    Reserve();
    Reserve(Contenitore*, Hotel*);
    ~Reserve();
};

#endif // CALENDAR_H
