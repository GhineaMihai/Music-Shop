#include "qtUI.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <iomanip>
#include <string.h>
#include <string>
#include <QShortcut>
using namespace std;

qtUI::qtUI(QWidget* parent)
    : QMainWindow(parent)
{

    QWidget* centralWidget = new QWidget(this);

    QVBoxLayout* buttonsLayout = new QVBoxLayout();
    m_addBtn = new QPushButton("&Add", centralWidget);
    connect(m_addBtn, &QPushButton::released, this, &qtUI::addclicked);
    m_deleteBtn = new QPushButton("&Delete", centralWidget);
    connect(m_deleteBtn, &QPushButton::released, this, &qtUI::removeclicked);
    m_physicalBtn = new QPushButton("&Physical", centralWidget);
    connect(m_physicalBtn, &QPushButton::released, this, &qtUI::physicalclicked);
    m_digitalBtn = new QPushButton("&Digital", centralWidget);
    connect(m_digitalBtn, &QPushButton::released, this, &qtUI::digitalclicked);

    buttonsLayout->addSpacing(4);
    buttonsLayout->addWidget(m_addBtn);
    buttonsLayout->addWidget(m_deleteBtn);
    buttonsLayout->addWidget(m_physicalBtn);
    buttonsLayout->addWidget(m_digitalBtn);
    buttonsLayout->addStretch(10);

    QHBoxLayout* centralLayout = new QHBoxLayout;
    m_masterList = new QListWidget(centralWidget);

    QVBoxLayout* buttonBoxes = new QVBoxLayout();
    QLabel* addLabel = new QLabel("Add: complete all the boxes with the appropriate data and then press Add", centralWidget);
    QLabel* nameLabel = new QLabel("Record (string):", centralWidget);
    NameBox = new QLineEdit(centralWidget);
    QLabel* artistLabel = new QLabel("Artist (string):", centralWidget);
    ArtistBox = new QLineEdit(centralWidget);
    QLabel* priceLabel = new QLabel("Price (float):", centralWidget);
    PriceBox = new QLineEdit(centralWidget);
    QLabel* typeLabel = new QLabel("Type (physical: cd, vynil, tape or digital: 12 characters (letters or digits)):", centralWidget);
    TypeBox = new QLineEdit(centralWidget);
    QLabel* removeLabel = new QLabel("Remove: Select the item and press Remove", centralWidget);

    buttonBoxes->addWidget(addLabel);
    buttonBoxes->addWidget(nameLabel);
    buttonBoxes->addWidget(NameBox);
    buttonBoxes->addWidget(artistLabel);
    buttonBoxes->addWidget(ArtistBox);
    buttonBoxes->addWidget(priceLabel);
    buttonBoxes->addWidget(PriceBox);
    buttonBoxes->addWidget(typeLabel);
    buttonBoxes->addWidget(TypeBox);
    buttonBoxes->addWidget(removeLabel);

    y = 0;
    idd = 0;
    this->R = new Repository();
    R->load();
    ifstream f;
    f.open("Load.csv");
    string id, name, artist, price, type;
    while (getline(f, id, ','))
    {
        string y;
        y.append(id);
        y.append(". ");
        getline(f, name, ',');
        y.append(name);
        y.append(", ");
        getline(f, artist, ',');
        y.append(artist);
        y.append(", ");
        getline(f, price, ',');
        y.append(price);
        y.append(", ");
        getline(f, type, '\n');
        y.append(type);
        int n = y.length();
        char char_array[255];
        strcpy(char_array, y.c_str());
        new QListWidgetItem(char_array, m_masterList);
        idd++;
    }
    idd++;
    centralLayout->addWidget(m_masterList);
    centralLayout->addLayout(buttonsLayout);
    centralLayout->addLayout(buttonBoxes);

    //

    QHBoxLayout* bottomLayout = new QHBoxLayout;
    m_preview = new QListWidget(centralWidget);
    bottomLayout->addWidget(m_preview);

    //

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(centralLayout);
    mainLayout->addLayout(bottomLayout);

    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);
    QShortcut* ctrlz = new QShortcut(this);
    ctrlz->setKey(Qt::CTRL + Qt::Key_Z);
    connect(ctrlz, SIGNAL(activated()), this, SLOT(undo()));
    QShortcut* ctrly = new QShortcut(this);
    ctrly->setKey(Qt::CTRL + Qt::Key_Y);
    connect(ctrly, SIGNAL(activated()), this, SLOT(redo()));
}

void qtUI::addclicked()
{
    y = 1;
    QString name = this->NameBox->text();
    string stringname;
    stringname = name.toStdString();
    QString artist = this->ArtistBox->text();
    string stringartist;
    stringartist = artist.toStdString();
    QString price = this->PriceBox->text();
    string stringprice;
    stringprice = price.toStdString();
    QString type = this->TypeBox->text();
    string stringtype;
    stringtype = type.toStdString();
    QString id;
    id = QString::number(idd);
    if (stringtype == "cd" || stringtype == "vynil" || stringtype == "tape")
    {
        Physical* z = new Physical(idd, stringname, stringartist, stof(stringprice), stringtype);
        this->R->add(z);
        QString result = id + ". " + name + ", " + artist + ", " + price + ", " + type;
        new QListWidgetItem(result, m_masterList);
        idd++;
        qDebug() << result;
    }
    if (std::size(stringtype) == 12)
    {
        Digital* z = new Digital(idd, stringname, stringartist, stof(stringprice), stringtype);
        this->R->add(z);
        QString result = id + ". " + name + ", " + artist + ", " + price + ", " + type;
        new QListWidgetItem(result, m_masterList);
        idd++;
    }


}

void qtUI::removeclicked()
{
    y = 2;
    if (QListWidgetItem* it = this->m_masterList->takeItem(this->m_masterList->currentRow()))
    {
        QString s = it->text();
        removed = it->text();
        string string = s.toStdString();
        int a = string[0] - '0';
        this->R->remove(a);
        delete it;
        idd--;
    }

}

void qtUI::physicalclicked()
{
    if (m_preview->count() == 0)
    {
        for (int i = 0; i < this->R->firstEmpty; i++)
        {
            if (this->R->data[i]->m_type == "cd" || this->R->data[i]->m_type == "vynil" || this->R->data[i]->m_type == "tape")
            {
                QString item = m_masterList->item(i)->text();
                new QListWidgetItem(item, m_preview);
            }

        }

    }
    else
    {
        m_preview->clear();
        physicalclicked();
    }
}

void qtUI::digitalclicked()
{
    if (m_preview->count() == 0)
    {
        for (int i = 0; i < this->R->firstEmpty; i++)
        {
            if (this->R->data[i]->m_type != "cd" && this->R->data[i]->m_type != "vynil" && this->R->data[i]->m_type != "tape")
            {
                QString item = m_masterList->item(i)->text();
                new QListWidgetItem(item, m_preview);
            }

        }

    }
    else
    {
        m_preview->clear();
        digitalclicked();
    }
}

void qtUI::undo()
{
    if (y == 1)
    {
        idd--;
        removed = this->m_masterList->item(this->m_masterList->count() - 1)->text();
        this->R->undoadd();
        delete this->m_masterList->takeItem(this->m_masterList->count() - 1);
        y = 5;
    }
    if (y == 2)
    {
        this->R->undoremove();
        new QListWidgetItem(removed, m_masterList);
        y = 6;
    }
}

void qtUI::redo()
{
    if (y == 5)
    {
        this->R->redoadd();
        new QListWidgetItem(removed, m_masterList);
        y = 1;
    }
    if (y == 6)
    {
        idd--;
        removed = this->m_masterList->item(this->m_masterList->count() - 1)->text();
        this->R->redoremove();
        delete this->m_masterList->takeItem(this->m_masterList->count() - 1);
        y = 2;
    }

}

qtUI::~qtUI()
{
    this->R->save();
}