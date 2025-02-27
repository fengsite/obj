#include "notepad.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication EditorApp(argc, argv);    
    Notepad Editor;
    Editor.show();

    return EditorApp.exec();

}
#include "notepadx.h"
#include "ui_notepadx.h"
#include <QFontDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

Notepadx::Notepadx(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepadx)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    connect(ui->actionNew, &QAction::triggered, this, &Notepadx::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &Notepadx::open);
    connect(ui->actionSave, &QAction::triggered, this, &Notepadx::save);
    connect(ui->actionSave_as, &QAction::triggered, this, &Notepadx::saveAs);
    connect(ui->actionPrint, &QAction::triggered, this, &Notepadx::print);
    connect(ui->actionExit, &QAction::triggered, this, &Notepadx::exit);
    connect(ui->actionCopy, &QAction::triggered, this, &Notepadx::copy);
    connect(ui->actionCut, &QAction::triggered, this, &Notepadx::cut);
    connect(ui->actionPaste, &QAction::triggered, this, &Notepadx::paste);
    connect(ui->actionUndo, &QAction::triggered, this, &Notepadx::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &Notepadx::redo);
    connect(ui->actionFont, &QAction::triggered, this, &Notepadx::selectFont);
    connect(ui->actionBold, &QAction::triggered, this, &Notepadx::setFontBold);
    connect(ui->actionUnderline, &QAction::triggered, this, &Notepadx::setFontUnderline);
    connect(ui->actionItalic, &QAction::triggered, this, &Notepadx::setFontItalic);
    connect(ui->actionAbout, &QAction::triggered, this, &Notepadx::about);

// Disable menu actions for unavailable features
#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
    ui->actionPrint->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif
}

Notepadx::~Notepadx()
{
    delete ui;
}

void Notepadx::newDocument()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepadx::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepadx::save()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepadx::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepadx::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif // QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
}

void Notepadx::exit()
{
    QCoreApplication::quit();
}

void Notepadx::copy()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}

void Notepadx::cut()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->cut();
#endif
}

void Notepadx::paste()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}

void Notepadx::undo()
{
     ui->textEdit->undo();
}

void Notepadx::redo()
{
    ui->textEdit->redo();
}

void Notepadx::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void Notepadx::setFontBold(bool)
{

}
void Notepadx::setFontUnderline(bool)
{

}
void Notepadx::setFontItalic(bool)
{

}
void Notepadx::about()
{

}


