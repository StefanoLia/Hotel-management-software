#include "reservations.h"
#include "prenotazione.h"
#include <QCloseEvent>


Reservations::Reservations(Contenitore* c1, Hotel* c2) : C(c1), H(c2)
{
    CreateList();// creazione della tabella
    CreateButtons(); // creazione dei bottoni

    resize(QSize(1200,400));
    this->setFixedSize(this->width(),this->height());
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(tableWidget,0,0,1,1);//Aggiunta dei layout
    mainLayout->addWidget(box1,0,1);

    mess.setWindowTitle("Conferma"); //titolo alla QMessageBox

    setLayout(mainLayout);
    setWindowTitle("Gestisci Prenotazioni");
    //connect
    connect(aggiorna, SIGNAL(clicked()), this, SLOT(updates()));
    connect(ordina, SIGNAL(clicked()), this, SLOT(Sort()));
    connect(rimuovi, SIGNAL(clicked()), this, SLOT(Remove()));
    connect(removev, SIGNAL(clicked()), this, SLOT(RemoveEv()));
    connect(tableWidget,SIGNAL(cellClicked(int,int)),this, SLOT(cambia(int,int)));
}

Reservations::~Reservations()
{
    delete tableWidget;
    delete box1;
    delete mainLayout;
}

void Reservations::closeEvent (QCloseEvent *event)
{
    event->accept();
    delete this;
}

void Reservations::cambia(int a, int b)
{
    if(tableWidget->item(a,b)->isSelected())
        tableWidget->selectRow(a);
}

void Reservations::updates() //aggiorna la lista
{
    C->Aggiorna();
    tableWidget->setRowCount(C->CountReservations());
    Read();
}

void Reservations::Sort()//ordina la lista in ordine di inizio
{
    C->sort();
    Read();
}

void Reservations::RemoveEv() //rimuove tutto il contenuto della lista
{
    if(C->Vuota())
    {
        msg.setWindowTitle("Attenzione");
        msg.setText("Nessun contenuto da rimuovere");
        msg.show();
        return;
    }
    mess.setText("Sicuro di voler eliminare tutto?");
    mess.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    mess.setDefaultButton(QMessageBox::No);
    mess.show();
    if(mess.exec()==QMessageBox::Yes)
    {
        C->RemoveEv();
        int temp = tableWidget->rowCount();
        for(int i = 0; i < temp; i++)
            tableWidget->removeRow(0);
    }
}

void Reservations::CreateList()
{
    tableWidget = new QTableWidget;
    tableWidget->setColumnCount(8);
    tableWidget->setRowCount(C->CountReservations());
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableWidget->setHorizontalHeaderLabels(QString("Tipologia;Cliente;Piano;Numero;Persone;Inizio;Fine;Prezzo").split(";"));//scrivo gli header
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    Read();
    tableWidget->resize(QSize(900,600));
}


void Reservations::Remove() // rimuove una o più prenotazioni selezionate dalla tabella
{
    if(C->Vuota())
    {
        msg.setWindowTitle("Attenzione");
        msg.setText("Nessun contenuto da rimuovere");
        msg.show();
        return;
    }
    int row = RigaSelezionata();
    if(row == -1)
    {
        msg.setWindowTitle("Attenzione");
        msg.setText("Nessuna riga selezionata");
        msg.show();
        return;
    }
    if(tableWidget->selectionModel()->selectedRows().count() > 1)
        mess.setText("Sicuro di volere rimuovere le prenotazioni selezionate?");
    else
        mess.setText("Sicuro di voler eliminare la prenotazione?");
    mess.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    mess.setDefaultButton(QMessageBox::No);
    mess.show();
    if(mess.exec()==QMessageBox::Yes)
    {
        while(tableWidget->selectionModel()->selectedRows().count() > 0)
        {
            row = RigaSelezionata();
            QString c = tableWidget->item(row,1)->text();
            int piano = tableWidget->item(row,2)->text().toInt();
            int num = tableWidget->item(row,3)->text().toInt();
            int persone = tableWidget->item(row,4)->text().toInt();
            QString i = tableWidget->item(row,5)->text();
            QString f = tableWidget->item(row,6)->text();
            QDate inizio = QDate::fromString(i,"dd/MM/yyyy");
            QDate fine = QDate::fromString(f,"dd/MM/yyyy");
            Prenotazione p(c,inizio,fine,persone);
            C->Togli_prenotazione(H->GetStanza(piano,num),p);
            tableWidget->removeRow(row);
        }
        Read();
    }
}

void Reservations::CreateButtons()
{
    box1 = new QGroupBox;
    QVBoxLayout* layout = new QVBoxLayout(box1);// creazione del layout

    ordina = new QPushButton(tr("Ordina"), box1);
    aggiorna = new QPushButton(tr("Aggiorna"), box1);
    rimuovi = new QPushButton(tr("Rimuovi"), box1);
    removev = new QPushButton(tr("Rimuovi Tutto"), box1);

    layout->addWidget(ordina);
    layout->addWidget(aggiorna);
    layout->addWidget(rimuovi);
    layout->addWidget(removev);

    box1->setLayout(layout);
}

void Reservations::Read() //aggiunge gli elementi alla tabella
{
    int i = 0;
    for(Contenitore::iteratore it = C->begin() ;it != C->end(); it++)
    {
        tableWidget->setItem(i,0, new QTableWidgetItem(C->GetS(it)->Nome()));// aggiunta dei dati alla tabella
        tableWidget->setItem(i,1, new QTableWidgetItem(C->GetP(it).GetNome()));
        tableWidget->setItem(i,2, new QTableWidgetItem(QString::number(C->GetS(it)->GetPiano())));
        tableWidget->setItem(i,3, new QTableWidgetItem(QString::number(C->GetS(it)->GetNum())));
        tableWidget->setItem(i,4, new QTableWidgetItem(QString::number(C->GetP(it).GetNumPersone())));
        tableWidget->setItem(i,5, new QTableWidgetItem(C->GetP(it).getInizio().toString("dd/MM/yyyy")));
        tableWidget->setItem(i,6, new QTableWidgetItem(C->GetP(it).getFine().toString("dd/MM/yyyy")));
        tableWidget->setItem(i,7, new QTableWidgetItem(QString::number((C->GetS(it)->CostoPrenotazione(C->GetP(it).GetNumPersone(),
                                                                                                       C->GetP(it).getInizio().daysTo(C->GetP(it).getFine()))))));

        i++;
    }
}

int Reservations::RigaSelezionata() const // ritorna la riga selezionata della tabella
// se nessuna riga è selezionata ritorna -1
{
    for(int i = 0; i < tableWidget->rowCount(); i++)
    {
            if(tableWidget->item(i,0)->isSelected())
                return i;
    }
    return -1;
}

