#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class Window : public QWidget {
Q_OBJECT
    QVBoxLayout m_layout;
    QLabel m_label;
    QPushButton m_button; 
public:
    Window(QWidget * parent = nullptr);
    ~Window();
private slots:
    void closeApplication();
};

#endif
