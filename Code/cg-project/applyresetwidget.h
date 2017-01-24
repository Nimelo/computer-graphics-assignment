#ifndef APPLYRESETWIDGET_H
#define APPLYRESETWIDGET_H

#include <QWidget>
#include <QPushButton>

class ApplyResetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ApplyResetWidget(QWidget *parent = 0);
    QPushButton * applyButton;
    QPushButton * resetButton;
private:
    void create();
signals:

public slots:
};

#endif // APPLYRESETWIDGET_H
