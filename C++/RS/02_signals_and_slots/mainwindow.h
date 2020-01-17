#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int m_value = 0;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int value(int new_value);

private:
    Ui::MainWindow *ui;

private slots:
    void print_value(int val);
    void update_label(int val);

    void on_pushButton_clicked();

signals:
    void value_changed(int new_value);
};
#endif // MAINWINDOW_H
