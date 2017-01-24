#ifndef APPLYRESETWIDGET_H
#define APPLYRESETWIDGET_H

#include <QWidget>
#include <QPushButton>

class ApplyResetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ApplyResetWidget(QWidget *parent = 0);
    QPushButton * getApplyButton();
private:
    void create();
    QPushButton * applyButton;
    QPushButton * resetButton;

signals:

public slots:
};

#endif // APPLYRESETWIDGET_H
