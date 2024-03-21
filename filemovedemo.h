#ifndef FILEMOVEDEMO_H
#define FILEMOVEDEMO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class fileMoveDemo;
}
QT_END_NAMESPACE

struct fileMoveDemoArgs;

class fileMoveDemo : public QMainWindow
{
    Q_OBJECT

public:
    fileMoveDemo(QWidget *parent = nullptr);
    ~fileMoveDemo();

public slots:
    void addPathButton();

private:
    Ui::fileMoveDemo *ui;
    fileMoveDemoArgs *args;
};
#endif // FILEMOVEDEMO_H
