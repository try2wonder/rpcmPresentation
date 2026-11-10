#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "problem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void loadProblemList();

private:
    Ui::MainWindow *ui;
    QVector<problem> problems;
    QVector<QString> readFileToVector(const QString &filePath);
    QVector<QString> bulletpointsVector;
    QHash<QString, QString> problemDictionary; // Key: Header, Value: Paragraph
    QStringList headerOrder;
    QHash<QString, QString> readParagraphsToMap(const QString &filePath);

private slots:
    void on_cb_problemList_currentTextChanged(const QString & arg1);
};
#endif // MAINWINDOW_H
