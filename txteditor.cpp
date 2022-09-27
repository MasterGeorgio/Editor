#include "txteditor.h"
#include "ui_txteditor.h"

#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>

TxtEditor::TxtEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TxtEditor)
{

    m_ptAreaEdit = new QPlainTextEdit();
    QString filter = trUtf8("Текстовый файл(*.txt)");

    QAction *actionOpen = new QAction("Открыть", this);
    connect(actionOpen, &QAction::triggered, this, [=](){
        QString s = QFileDialog::getOpenFileName(this, "Открыть",
                                                 QDir::current().path(),
                                                 filter);
        if (!(s.length() > 0))
            return;

        int index = s.indexOf(".txt");
        QFile file(s);

        if (!(index != -1 && s.length() - 4 == index))
            return;
        if (!(file.open(QFile::ReadOnly | QFile::ExistingOnly)))
            return;

        QTextStream stream(&file);
        m_ptAreaEdit->setPlainText(stream.readAll());
        file.close();
    });

    QAction *actionSave = new QAction("Сохранить", this);
    connect(actionSave, &QAction::triggered, this, [=](){
        QString s = QFileDialog::getSaveFileName(this, "Сохранить",
                                                 QDir::current().path(),
                                                 filter);
        int index = s.indexOf(".txt");
        QFile file(s);

        if (!(index != -1))
            return;
        if (!(file.open(QFile::WriteOnly)))
            return;

        QTextStream stream(&file);
        stream << m_ptAreaEdit->toPlainText();
        file.close();
    });

    QAction *actionHelp = new QAction("О программе", this);
    connect(actionHelp, &QAction::triggered, this, [=](){

        QFile file(":help.txt");
        if (!(file.open(QFile::ReadOnly)))
            return;
        QTextStream stream(&file);

        QMessageBox  ms;
        ms.setText(stream.readAll());
        ms.exec();
        file.close();
    });

    QMenu *menuFile = new QMenu("Файл", this);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);

    QMenu *menuHelp = new QMenu("Справка", this);
    menuHelp->addAction(actionHelp);

    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->addMenu(menuFile);
    menuBar->addMenu(menuHelp);

    setMenuBar(menuBar);
    setCentralWidget(m_ptAreaEdit);
}

TxtEditor::~TxtEditor()
{
    delete ui;
}

