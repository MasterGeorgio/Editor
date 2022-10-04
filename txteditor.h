#ifndef TXTEDITOR_H
#define TXTEDITOR_H

#include <QMainWindow>
#include <QTranslator>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QAction>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class TxtEditor; }
QT_END_NAMESPACE

class TxtEditor : public QMainWindow
{
    Q_OBJECT

public:
    TxtEditor(QWidget *parent = nullptr);
    ~TxtEditor();

private:
    Ui::TxtEditor *ui;

    // Area edition
    QPlainTextEdit *m_ptAreaEdit;
    // Выделяем перевод в отдельном поле
    QTranslator qtLanguageTranslator;

    QMap<QString, QAction*> m_mapActions;
    QMap<QString, QMenu*> m_mapMenu;

private:
    void createAction();
};
#endif // TXTEDITOR_H
