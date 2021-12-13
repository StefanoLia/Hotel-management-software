#include "mainwindow.h"

MainWindow::MainWindow() : pathImmagini(QDir::currentPath() + "/Immagini/"), r(0), s(0)
{
    H = new Hotel(4,10,10,4,16,10);
    model = (new Contenitore(H));

    QSize x;
    x.setHeight(500);
    x.setWidth(1000);
    resize(x);
    this->setFixedSize(this->width(),this->height());
    setWindowTitle("Home");

    QFont font;
    font.setBold(true);
    font.setPointSize(28);

    QLabel* titolo = new QLabel(this);
    titolo->setText("    Gestione Hotel");
    titolo->setFont(font);
    QGridLayout *mainlayout = new QGridLayout;

    AddFirst(); //aggiunta della prima label con bottone
    AddSecond(); //aggiunta della seconda label con bottone

    mainlayout->addWidget(titolo,0,1);
    mainlayout->addWidget(first,1,0);
    mainlayout->addWidget(second,1,2);

    QPixmap image(pathImmagini + "Hotel.jpg");
    image = image.scaled(this->size(),Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, image);
    this->setPalette(palette);

    setLayout(mainlayout);

    connect(prenotazioni, SIGNAL(clicked()), this, SLOT(openR()));
    connect(struttura, SIGNAL(clicked()), this, SLOT(openS()));
}

MainWindow::~MainWindow()
{
    delete first;
    delete second;
    delete H;
    delete model;
}

void MainWindow::openR()
{
    if(r == 0)
    {
        r = new Reserve(model,H);
        r->show();
        connect(r,SIGNAL(destroyed(QObject*)), this, SLOT(closeR(QObject*)));
    }
}

void MainWindow::openS()
{
    if(s == 0)
    {
        s = new Struttura(model,H);
        s->show();
        connect(s,SIGNAL(destroyed(QObject*)), this, SLOT(closeS(QObject*)));
    }
}

void MainWindow::closeR(QObject *)
{
    r = 0;
}

void MainWindow::closeS(QObject *)
{
    s = 0;
}

void MainWindow::AddFirst()
{
    first = new QGroupBox;
    QVBoxLayout* layout = new QVBoxLayout(first);

    QLabel* label1 = new QLabel(first);
    struttura = new QPushButton(first);
    struttura->setFlat(true);
    struttura->resize(QSize(300,300));

    QPixmap pixmap(pathImmagini + "icona_hotel.png");
    struttura->setIcon(QIcon(pixmap));
    struttura->setIconSize(QSize(250,250));
    QFont font;
    font.setBold(true);
    font.setPointSize(22);

    label1->setText("    Struttura");
    label1->setFont(font);

    layout->addWidget(label1);
    layout->addWidget(struttura);

    label1->setAlignment(Qt::AlignCenter);

    first->setLayout(layout);
}

void MainWindow::AddSecond()
{
    second = new QGroupBox;
    QVBoxLayout* layout = new QVBoxLayout(second);

    QLabel* label2 = new QLabel(second);
    prenotazioni = new QPushButton(second);
    prenotazioni->setFlat(true);
    prenotazioni->resize(QSize(300,300));

    QPixmap pixmap(pathImmagini + "prenota.png");

    prenotazioni->setIcon(QIcon(pixmap));
    prenotazioni->setIconSize(QSize(250,250));
    QFont font;
    font.setBold(true);
    font.setPointSize(22);

    label2->setText("    Prenotazioni");
    label2->setFont(font);

    layout->addWidget(label2);
    layout->addWidget(prenotazioni);

    second->setLayout(layout);
}

void MainWindow::closeEvent (QCloseEvent * event)
{
    QMessageBox reply;
    reply.setText("Sicuro di voler uscire?");
    reply.setWindowTitle("Attenzione");
    reply.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    reply.setDefaultButton(QMessageBox::No);
    reply.show();

    if (reply.exec()==QMessageBox::Yes)
    {
        event->accept();
        if(s != 0)
            s->close();
        if(r != 0)
            r->close();
        delete this;
    }
    else
        event->ignore();
}


