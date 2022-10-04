#include "txteditor.h"
#include "ui_txteditor.h"

#include <QApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>

TxtEditor::TxtEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TxtEditor)
{

    m_ptAreaEdit = new QPlainTextEdit();

    createAction();

    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->addMenu(m_mapMenu["File"]);
    menuBar->addMenu(m_mapMenu["View"]);
    menuBar->addMenu(m_mapMenu["Help"]);

    setMenuBar(menuBar);
    setCentralWidget(m_ptAreaEdit);

    // Сделаем первоначальную инициализацию перевода для окна приложения
    qtLanguageTranslator.load("QtLanguage_ru", ".");
    qApp->installTranslator(&qtLanguageTranslator);
}

TxtEditor::~TxtEditor()
{
    delete ui;
}

void TxtEditor::createAction(){
    QString filter = trUtf8("Текстовый файл(*.txt)");

    m_mapActions["NewDoc"] = new QAction(tr("Создать новый"), this);
    connect(m_mapActions["NewDoc"], &QAction::triggered, this, [=](){
        m_ptAreaEdit->setPlainText("");
        m_ptAreaEdit->setReadOnly(false);
    });
    m_mapActions["NewDoc"]->setShortcut(Qt::CTRL + Qt::Key_N);

    m_mapActions["Open"] = new QAction(tr("Открыть"), this);
    connect(m_mapActions["Open"], &QAction::triggered, this, [=](){
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
        m_ptAreaEdit->setReadOnly(false);
        file.close();
    });
    m_mapActions["Open"]->setShortcut(Qt::CTRL + Qt::Key_O);

    m_mapActions["OpenRead"] = new QAction(tr("Открыть только для чтения"), this);
    connect(m_mapActions["OpenRead"], &QAction::triggered, this, [=](){
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

        m_ptAreaEdit->setReadOnly(true);

        QTextStream stream(&file);
        m_ptAreaEdit->setPlainText(stream.readAll());
        file.close();
    });

    m_mapActions["Save"] = new QAction(tr("Сохранить"), this);
    connect(m_mapActions["Save"], &QAction::triggered, this, [=](){
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
    m_mapActions["Save"]->setShortcut(Qt::CTRL + Qt::Key_S);

    m_mapActions["Info"] = new QAction(tr("О программе"), this);
    connect(m_mapActions["Info"], &QAction::triggered, this, [=](){

        QFile file(":help.txt");
        if (!(file.open(QFile::ReadOnly)))
            return;
        QTextStream stream(&file);

        QMessageBox  ms;
        ms.setText(stream.readAll());
        ms.exec();
        file.close();
    });
    m_mapActions["Exit"] = new QAction(tr("Выход"), this);
    connect(m_mapActions["Exit"], &QAction::triggered, this, [=](){
        qApp->exit();
    });
    m_mapActions["Exit"]->setShortcut(Qt::CTRL + Qt::Key_Q);

    m_mapActions["Rus"] = new QAction(tr("Русский"), this);
    connect(m_mapActions["Rus"], &QAction::triggered, this, [=](){
        // Загружаем перевод
        qtLanguageTranslator.load("QtLanguage_ru");
        qApp->installTranslator(&qtLanguageTranslator);
    });
    m_mapActions["Eng"] = new QAction(tr("Английский"), this);
    connect(m_mapActions["Eng"], &QAction::triggered, this, [=](){
        qtLanguageTranslator.load("QtLanguage_en");
        qApp->installTranslator(&qtLanguageTranslator);

        for(QAction* m: m_mapActions)
            m->setText(m->text());
    });

    m_mapMenu["File"] = new QMenu(tr("Файл"), this);
    m_mapMenu["File"]->addAction(m_mapActions["NewDoc"]);
    m_mapMenu["File"]->addAction(m_mapActions["Open"]);
    m_mapMenu["File"]->addAction(m_mapActions["OpenRead"]);
    m_mapMenu["File"]->addAction(m_mapActions["Save"]);

    m_mapMenu["View"] = new QMenu(("Вид"), this);
    m_mapMenu["View"]->addAction(m_mapActions["Rus"]);
    m_mapMenu["View"]->addAction(m_mapActions["Eng"]);

    m_mapMenu["Help"] = new QMenu(tr("Справка"), this);
    m_mapMenu["Help"]->addAction(m_mapActions["Info"]);
    m_mapMenu["Help"]->addAction(m_mapActions["Exit"]);

}

