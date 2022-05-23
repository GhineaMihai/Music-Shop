#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Repository.h"
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QMainWindow>

class qtUI : public QMainWindow
{
    Q_OBJECT

public:
    qtUI(QWidget* parent = nullptr);
    ~qtUI();
private:
    QLineEdit* m_searchEdit;
    QComboBox* m_sortBox;

    QPushButton* m_searchBtn;
    QPushButton* m_addBtn;
    QPushButton* m_deleteBtn;
    QPushButton* m_physicalBtn;
    QPushButton* m_digitalBtn;
    QListWidget* m_masterList;
    QListWidget* m_currentList;
    QListWidget* m_preview;
    QLineEdit* NameBox;
    QLineEdit* ArtistBox;
    QLineEdit* PriceBox;
    QLineEdit* TypeBox;
    Repository* R;
    QString removed;
    int idd;
    int y;

private slots:
    void addclicked();
    void removeclicked();
    void physicalclicked();
    void digitalclicked();
    void undo();
    void redo();
};
#endif // MAINWINDOW_H
