#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
namespace Ui {
class Notepadx;
}
class Notepadx : public QMainWindow
{
    Q_OBJECT
public:
    explicit Notepadx(QWidget *parent = nullptr);
    ~Notepadx();
private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void print();
    void exit();
    void copy();
    void cut();
    void paste();
    void undo();
    void redo();
    void selectFont();
    void setFontBold(bool bold);
    void setFontUnderline(bool underline);
    void setFontItalic(bool italic);
    void about();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
private:
    Ui::Notepadx *ui;
    QString currentFile;
};
#endif // mainwindow.h

