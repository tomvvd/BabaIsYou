#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QWidget>

namespace Ui {
class EndWindow;
}

class EndWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EndWindow(QWidget *parent = nullptr);
    ~EndWindow();

private:
    Ui::EndWindow *ui;
};

#endif // ENDWINDOW_H
