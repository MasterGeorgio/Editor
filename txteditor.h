#ifndef TXTEDITOR_H
#define TXTEDITOR_H

#include <QMainWindow>
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
};
#endif // TXTEDITOR_H
