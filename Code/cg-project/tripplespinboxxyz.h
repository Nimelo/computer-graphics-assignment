#ifndef TRIPPLESPINBOXXYZ_H
#define TRIPPLESPINBOXXYZ_H

#include <QWidget>
#include <QSpinBox>

class TrippleSpinBoxXYZ : public QWidget
{
    Q_OBJECT
public:
    TrippleSpinBoxXYZ(const char * groupBoxText);
private:
    explicit TrippleSpinBoxXYZ(QWidget *parent = 0);

    void create(const char * groupBoxText);
    QSpinBox * createQSpinBox();

    QSpinBox * xSpinBox;
    QSpinBox * ySpinBox;
    QSpinBox * zSpinBox;

signals:

public slots:
};

#endif // TRIPPLESPINBOXXYZ_H
