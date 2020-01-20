#include "window.hpp"

Window::Window(QWidget * parent) 
        : QWidget(parent),
          m_layout(this),
          m_label("Exit")
{
    m_layout.addWidget(&m_label);
    m_layout.addWidget(&m_button);
    m_layout.setAlignment(Qt::AlignCenter);

    m_button.setText("Click button to exit");
    connect(&m_button, SIGNAL(clicked()), SLOT(closeApplication()));
}

void Window::closeApplication() {
    QApplication::exit(0);
}

Window::~Window() {}
