#include "reserve.h"
#include "reservations.h"

Reserve::Reserve(Contenitore* c1, Hotel* c2) :
    model2(c1), H2(c2),  pathImmagini(QDir::currentPath() + "/Immagini/"), R(0)
{
    CreateFirstGroupbox();
    CreateSecondGroupbox();
    CreateHorizontalGroupbox();
    CreateVerticalGroupbox();

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(firstGroupbox,0,0);//Aggiunta dei layout
    mainLayout->addWidget(secondGroupbox,1,0);
    mainLayout->addWidget(horizontalGroupBox,0,1);
    mainLayout->addWidget(verticalGropuBox,1,1);

    setLayout(mainLayout);//impostazione del layout finale

    QPixmap image(pathImmagini + "sfondo.jpg");
    image = image.scaled(this->size(),Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, image);
    this->setPalette(palette);

    resize(QSize(950,400)); // modifica della size
    this->setFixedSize(this->width(),this->height());

    //connect
    connect(menu1, SIGNAL(activated(QString)), this, SLOT(ChangePlaces(QString)));
    connect(spinFloor, SIGNAL(valueChanged(int)), this, SLOT(ChangeFloor(int)));
    connect(prenota, SIGNAL(clicked()), this, SLOT(addPrenot()));
    connect(verifica, SIGNAL(clicked()), this, SLOT(check()));
    connect(visualizza, SIGNAL(clicked()), this, SLOT(NewWindow()));

    setWindowTitle("Prenota");
}

void Reserve::NewWindow()
{
    if(R == 0)
    {
        R = new Reservations(model2, H2); // costruzione e apertura della nuova pagina
        R->show();
        connect(R,SIGNAL(destroyed(QObject*)), this, SLOT(closeR(QObject*)));
    }
}

void Reserve::closeR(QObject*)
{
    R = 0;
}

Reserve::~Reserve()
{
    delete firstGroupbox; delete secondGroupbox; delete horizontalGroupBox;
    delete verticalGropuBox;
}

void Reserve::closeEvent (QCloseEvent *event)
{
    event->accept();
    model2->WriteReservations();//salvo le prenotazioni prima di uscire
    if(R != 0)
        R->close();
    delete this;
}

//METODO PRIVATO
bool Reserve::hasProblem()
{
    if(menu1->currentText() == " ")
        msg.setText("Errore. Selezionare una stanza.");
    else if(!(H2->GetStanza(spinFloor->text().toInt(), spinRoom->text().toInt())->GetStanzaInagibile()))
        msg.setText("Spiacenti. La stanza selezionata e' inagibile.");
    else if(inizio->date() >= fine->date())
        msg.setText("Errore. Prenotare per almeno una notte");
    else if(name->toPlainText() == "")
        msg.setText("Errore. Non e' stato inserito nessun nome.");
    else
        return 0;
    return 1;
}

//PRIVATE SLOTS

void Reserve::addPrenot()
{
    Prenotazione p(name->toPlainText(), inizio->date(), fine->date(), spinPeople->text().toInt());
    msg.setWindowTitle("Conferma");
    if(hasProblem())
    {
        msg.show();
        return;
    }
    if(model2->Aggiungi_prenotazione(H2->GetStanza(spinFloor->text().toInt(), spinRoom->text().toInt()),p))
        msg.setText("La tua prenotazione e' stata effettuata.");
    else
        msg.setText("La prenotazione ha avuto un problema. Verifica prima la disponibilita' della stanza.");
    msg.show();
}

void Reserve::ChangeFloor(int) // imposta le stanze disponibili a seconda della tipologia
// della stanza quando viene cambiato il piano
{
    if(menu1->currentText() == "Suite")
    {
        if(spinFloor->text() == "3")
        {
             spinRoom->setMinimum(7);
             spinRoom->setMaximum(10);
        }
        else if(spinFloor->text() == "4")
        {
             spinRoom->setMinimum(1);
             spinRoom->setMaximum(6);
        }
    }
    else
    {
        if(spinFloor->text() == "2")
        {
             spinRoom->setMinimum(1);
             spinRoom->setMaximum(10);
        }
        else if(spinFloor->text() == "3")
        {
             spinRoom->setMinimum(1);
             spinRoom->setMaximum(6);
        }
    }
}

void Reserve::ChangePlaces(QString) // a seconda della tipologia della stanza viene impostato
// il massimo e minimo delle stanza,piani,persone disponibili
{
    if(menu1->currentText() == "Suite")
    {
        spinFloor->setReadOnly(0);
        spinFloor->setMinimum(3);
        spinFloor->setMaximum(4);
        spinPeople->setMaximum(4);
        if(spinFloor->text() == "3")
        {
            spinRoom->setMinimum(7);
            spinRoom->setMaximum(10);
        }
        else if(spinFloor->text() == "4")
        {
            spinRoom->setMinimum(1);
            spinRoom->setMaximum(6);
        }
    }
    else if(menu1->currentText() == "Royal Suite")
    {
        spinFloor->setMinimum(4);
        spinFloor->setMaximum(4);
        spinFloor->setReadOnly(1);
        spinPeople->setMaximum(4);
        spinRoom->setMinimum(7);
        spinRoom->setMaximum(10);
    }
    else if(menu1->currentText() == "Camera Doppia")
    {
        spinFloor->setMaximum(3);
        spinFloor->setMinimum(2);
        spinFloor->setReadOnly(0);
        spinPeople->setMaximum(2);
        if(spinFloor->text() == "2")
        {
            spinRoom->setMinimum(1);
            spinRoom->setMaximum(10);
        }
        else if(spinFloor->text() == "3")
        {
            spinRoom->setMinimum(1);
            spinRoom->setMaximum(6);
        }
    }
    else if(menu1->currentText() == "Camera Singola")
    {
        spinPeople->setMaximum(1);
        spinFloor->setMaximum(1);
        spinFloor->setMinimum(1);
        spinFloor->setReadOnly(1);
        spinRoom->setMinimum(1);
        spinRoom->setMaximum(10);
    }
}

void Reserve::check()
{
    Prenotazione p(name->toPlainText(), inizio->date(), fine->date(), spinPeople->text().toInt());//creazione
    //dell'oggetto prenotazione
    msg.setWindowTitle("Attenzione");
    if(hasProblem())
    {
        msg.show();
        return;
    }
    else if(model2->VerificaDisponibilita(H2->GetStanza(spinFloor->text().toInt(), spinRoom->text().toInt()),p))
        msg.setText("E' possibile effettuare la prenotazione");
    else
        msg.setText("Non e' possibile effettuare la prenotazione");
    msg.show();
}

void Reserve::CreateHorizontalGroupbox()
{
    horizontalGroupBox = new QGroupBox(tr("       Scegli la data"));
    QHBoxLayout* layout = new QHBoxLayout(horizontalGroupBox);

    inizio = new QDateEdit(horizontalGroupBox);//Creazione dei QDateEdit
    fine = new QDateEdit(horizontalGroupBox);
    QCalendarWidget* c1 = new QCalendarWidget(inizio);
    QCalendarWidget* c2 = new QCalendarWidget(fine);
    inizio->setMinimumDate(QDate::currentDate());
    fine->setMinimumDate(QDate::currentDate());
    inizio->setCalendarPopup(true);
    inizio->setCalendarWidget(c1);
    fine->setCalendarPopup(true);
    fine->setCalendarWidget(c2);


    QLabel* w1 = new QLabel(horizontalGroupBox);//Creazione scritte
    QLabel* w2 = new QLabel(horizontalGroupBox);
    w1->setText("             Da");
    w2->setText("             al");

    layout->addWidget(w1);
    layout->addWidget(inizio);
    layout->addWidget(w2);
    layout->addWidget(fine);

    horizontalGroupBox->setLayout(layout);
}

void Reserve::CreateVerticalGroupbox()
{
    verticalGropuBox = new QGroupBox;
    QVBoxLayout* layout2 = new QVBoxLayout(verticalGropuBox);

    prenota = new QPushButton(tr("Prenota"), verticalGropuBox);
    verifica = new QPushButton(tr("Verifica Disponibilita'"), verticalGropuBox);
    visualizza = new QPushButton(tr("Visualizza Prenotazioni"), verticalGropuBox);

    layout2->addWidget(prenota);
    layout2->addWidget(verifica);
    layout2->addWidget(visualizza);

    verticalGropuBox->setLayout(layout2);
}

void Reserve::CreateFirstGroupbox()
{
    firstGroupbox = new QGroupBox(tr("Tipologie stanze"));
    QGridLayout* layout3 = new QGridLayout(firstGroupbox);

    menu1 = new QComboBox(firstGroupbox);
    menu1->addItem(" ");
    menu1->addItem("Suite");
    menu1->addItem("Royal Suite");
    menu1->addItem("Camera Doppia");
    menu1->addItem("Camera Singola");

    QLabel* people = new QLabel("Numero Persone: ", firstGroupbox);
    spinPeople = new QSpinBox(firstGroupbox);
    spinPeople->setMinimum(1);

    QLabel *nome = new QLabel("Nome del cliente: ", firstGroupbox);
    name = new QPlainTextEdit(firstGroupbox);

    name->resize(QSize(2,2));
    layout3->addWidget(menu1,0,0);
    layout3->addWidget(people,1,0);
    layout3->addWidget(spinPeople,1,1);
    layout3->addWidget(nome,2,0);
    layout3->addWidget(name,2,1);

    firstGroupbox->setLayout(layout3);
}

void Reserve::CreateSecondGroupbox()
{
    secondGroupbox = new QGroupBox(tr("Seleziona Piano e stanza"));
    QGridLayout* layout4 = new QGridLayout(secondGroupbox);

    QLabel* label1 = new QLabel("Piano", secondGroupbox);
    spinFloor = new QSpinBox(secondGroupbox);

    QLabel* label2 = new QLabel("Stanza", secondGroupbox);
    spinRoom = new QSpinBox(secondGroupbox);

    layout4->addWidget(label1,0,0);
    layout4->addWidget(spinFloor,0,1);
    layout4->addWidget(label2,1,0);
    layout4->addWidget(spinRoom,1,1);

    secondGroupbox->setLayout(layout4);
}

