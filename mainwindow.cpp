#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    problemDictionary = readParagraphsToMap(":/bpText");
    ui->cb_problemList->addItems(headerOrder);

    loadProblemList();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadProblemList(){

    ui->cb_problemList->clear();
    ui->cb_problemList->addItems(headerOrder);
}

//Ненужная херна теперь
QVector<QString> MainWindow::readFileToVector(const QString &filePath) {
    QVector<QString> linesVector;

    // 1. Point to the file path
    QFile file(filePath);

    // 2. Try to open the file in Read-Only text mode
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file:" << filePath;
        return linesVector; // Returns an empty vector if opening fails
    }

    // 3. Pass the file to a text stream for easy line-by-line reading
    QTextStream in(&file);

    // 4. Loop until you hit the end of the file
    while (!in.atEnd()) {
        QString line = in.readLine();

        // Optional: Skip empty lines if you don't want them in your vector
        if (!line.isEmpty()) {
            linesVector.append(line);
        }
    }

    // 5. Close the file handler
    file.close();

    return linesVector;
}
//Херня кончилась

QHash<QString, QString> MainWindow::readParagraphsToMap(const QString &filePath) {
    QHash<QString, QString> paragraphMap;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open paragraphs file:" << filePath;
        return paragraphMap;
    }

    QTextStream in(&file);

    QString currentHeader = "";
    QString currentParagraph = "";
    bool readingHeader = true; // Tracks if the next line is a header or body text

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // If we hit our separator, save what we have gathered and reset
        if (line == "---") {
            if (!currentHeader.isEmpty()) {
                // Trim trailing newline before saving
                paragraphMap.insert(currentHeader, currentParagraph.trimmed());
                headerOrder.append(currentHeader);
            }
            // Reset for the next section
            currentHeader = "";
            currentParagraph = "";
            readingHeader = true;
            continue;
        }

        if (readingHeader) {
            if (!line.isEmpty()) {
                currentHeader = line;
                readingHeader = false; // The next lines will belong to this header's paragraph
            }
        } else {
            // Accumulate multiple lines for the paragraph, keeping the newlines
            currentParagraph += line + "\n";
        }
    }

    // Safety check: If the file doesn't end with "---", save the last item
    if (!currentHeader.isEmpty() && !currentParagraph.isEmpty()) {
        paragraphMap.insert(currentHeader, currentParagraph.trimmed());
        headerOrder.append(currentHeader);
    }

    file.close();
    return paragraphMap;
}

void MainWindow::on_cb_problemList_currentTextChanged(const QString & arg1){
    ui->tb_problemDescription->clear();
    QString paragraph = problemDictionary.value(ui->cb_problemList->currentText());
    ui->tb_problemDescription->setText(paragraph);

}


