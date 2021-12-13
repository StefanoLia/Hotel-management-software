#ifndef STRUTTURA_H
#define STRUTTURA_H
#include "contenitore.h"
#include <QWidget>
#include <QTableWidget>
#include <QFile>
#include <QLabel>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QComboBox>
#include <QString>
#include <QSpinBox>
#include <QCheckBox>
#include <QDir>

class Struttura : public QWidget
{
    Q_OBJECT
private:
    Contenitore* model;
    Hotel* H;
    void CreateLeftGroup();
    void CreateRightGroup();
    void CreateFRightGroup();
    void CreateBox4();
    QGroupBox* box1;
    QGroupBox* box2;
    QGroupBox* box3;
    QGroupBox* box4;
    QSpinBox* spinFloor;
    QSpinBox* spinRoom;
    QCheckBox* inagibile;
    QComboBox* stanze;
    QLabel* text;
    QLabel* posti1;
    QLabel* posti2;
    QMessageBox mess;
    QString pathImmagini;
    virtual void closeEvent (QCloseEvent *);
private slots:
    void ChangePlaces(QString);
    void ChangeFloor(int);
    void Inagible();
    void Usable(int);
public:
    Struttura();
    Struttura(Contenitore* c1, Hotel* c2);
    ~Struttura();
};

#endif // STRUTTURA_H
