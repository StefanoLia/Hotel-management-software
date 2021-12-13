#include "struttura.h"
#include <QCloseEvent>

Struttura::Struttura(Contenitore* c1, Hotel* c2) : model(c1), H(c2),
    pathImmagini(QDir::currentPath() + "/Immagini/")
{
   QSize x;
   x.setHeight(400);
   x.setWidth(1000);
   resize(x);
   this->setFixedSize(this->width(),this->height());
   setWindowTitle("Struttura Hotel");

   CreateLeftGroup();
   CreateFRightGroup();
   CreateRightGroup();
   CreateBox4();

   QGridLayout* mainLayout = new QGridLayout(this);//aggiunta dei widget
   mainLayout->addWidget(box1,0,0);
   mainLayout->addWidget(box3,0,1);
   mainLayout->addWidget(box2,1,1);
   mainLayout->addWidget(box4,1,0);

   setLayout(mainLayout);

   QPixmap image(pathImmagini + "sfondo2.jpg");
   image = image.scaled(this->size(),Qt::KeepAspectRatioByExpanding);
   QPalette palette;
   palette.setBrush(QPalette::Background, image);
   this->setPalette(palette);

   connect(stanze, SIGNAL(activated(QString)), this, SLOT(ChangePlaces(QString)));
   connect(spinFloor, SIGNAL(valueChanged(int)), this, SLOT(ChangeFloor(int)));
   connect(inagibile, SIGNAL(clicked()), this, SLOT(Inagible()));
   connect(spinRoom, SIGNAL(valueChanged(int)), this, SLOT(Usable(int)));

}

Struttura::~Struttura()
{
    delete box1; delete box2; delete box3; delete box4;
}

void Struttura::closeEvent (QCloseEvent *event)
{
    event->accept();
    model->WriteUnusableRoom();
    delete this;
}

void Struttura::Usable(int)
{
    if(H->GetStanza(spinFloor->text().toInt(), spinRoom->text().toInt())->GetStanzaInagibile())
        inagibile->setChecked(0);
    else
        inagibile->setChecked(1);
}

void Struttura::Inagible()
{
    mess.setWindowTitle("Attenzione");
    if(stanze->currentText() == " ")
    {
        mess.setText("Errore. Selezionare una stanza");
        mess.show();
        return;
    }
    if(model->Controlla(spinFloor->text().toInt(), spinRoom->text().toInt()))
    {
        mess.setText("La stanza e' gia' stata prenotata. Aspettare la "
                      "fine della prenotazione per renderla inagibile o cancellare "
                      "le/a prenotazioni/e");
        mess.show();
        return;
    }
    else if(inagibile->isChecked())
    {
        H->GetStanza(spinFloor->text().toInt(), spinRoom->text().toInt())->SetStanzaAgibile(false);
    }
    else
    {
        H->GetStanza(spinFloor->text().toInt(), spinRoom->text().toInt())->SetStanzaAgibile(true);
    }
}

void Struttura::ChangeFloor(int)
{
    if(stanze->currentText() == "Suite")
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


void Struttura::ChangePlaces(QString)
{
    if(stanze->currentText() == "Suite")
    {
        posti2->setText(H->GetStanza(3,7)->PostiDisponibili());
        text->setText("Le Suite di questo Hotel si trovano al terzo piano (dal numero "
                     "7 al 10) e al quarto piano (dal numero 1 al 6)");

        spinFloor->setReadOnly(0);
        spinFloor->setMinimum(3);
        spinFloor->setMaximum(4);
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
    else if(stanze->currentText() == "Royal Suite")
    {
        posti2->setText(H->GetStanza(4,7)->PostiDisponibili());
        text->setText("Le Royal Suite di questo Hotel si trovano al quarto piano (dal 7 "
                    "al 10)");

        spinFloor->setMinimum(4);
        spinFloor->setMaximum(4);
        spinFloor->setReadOnly(1);
        spinRoom->setMinimum(7);
        spinRoom->setMaximum(10);
    }
    else if(stanze->currentText() == "Camera Doppia")
    {
        posti2->setText(H->GetStanza(2,2)->PostiDisponibili());
        text->setText("Le Camere Doppie di questo Hotel si trovano al secondo piano (dal numero "
                      "1 al 10) e al terzo piano (dal numero 1 al 6)");

        spinFloor->setReadOnly(0);
        spinFloor->setMaximum(3);
        spinFloor->setMinimum(2);
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
    else if(stanze->currentText() == "Camera Singola")
    {
        posti2->setText(H->GetStanza(1,1)->PostiDisponibili());
        text->setText("Le Camere Singole di questo Hotel si trovano al primo piano (dal numero"
                    "1 al 10)");

        spinFloor->setReadOnly(1);
        spinFloor->setMaximum(1);
        spinFloor->setMinimum(1);
        spinRoom->setMinimum(1);
        spinRoom->setMaximum(10);
    }
}

void Struttura::CreateBox4() //crea il secondo riquadro a sinistra
{
    box4 = new QGroupBox("Rendi inagibile una stanza");
    QGridLayout* layout = new QGridLayout(box4);

    QLabel* label1 = new QLabel("Piano", box4);
    spinFloor = new QSpinBox(box4);

    QLabel* label2 = new QLabel("Stanza", box4);
    spinRoom = new QSpinBox(box4);

    inagibile = new QCheckBox(box4);
    inagibile->setText("Stanza Inagibile");

    layout->addWidget(label1,0,0);
    layout->addWidget(spinFloor,0,1);
    layout->addWidget(label2,1,0);
    layout->addWidget(spinRoom,1,1);
    layout->addWidget(inagibile,2,1);

    box4->setLayout(layout);
}



void Struttura::CreateFRightGroup()
{
    box3 = new QGroupBox("Posti");
    QHBoxLayout* layout = new QHBoxLayout(box3);
    posti1 = new QLabel(box3);
    posti2 = new QLabel(box3);

    posti1->setText("Posti Disponibili: ");
    QSize x;
    x.setWidth(200);
    x.setHeight(800);
    posti2->resize(x);

    layout->addWidget(posti1);
    layout->addWidget(posti2);

    box3->setLayout(layout);
}

void Struttura::CreateLeftGroup()
{
    box1 = new QGroupBox("Seleziona una stanza");
    QVBoxLayout* vertical = new QVBoxLayout(box1);
    stanze = new QComboBox(box1);

    stanze->addItem(" ");
    stanze->addItem("Suite");
    stanze->addItem("Royal Suite");
    stanze->addItem("Camera Doppia");
    stanze->addItem("Camera Singola");

    vertical->addWidget(stanze);

    box1->setLayout(vertical);
}

void Struttura::CreateRightGroup()
{
    box2 = new QGroupBox("Info");
    QVBoxLayout* layout = new QVBoxLayout(box2);

    text = new QLabel(box2);
    text->setWordWrap(true);

    layout->addWidget(text);

    box2->setLayout(layout);
}








