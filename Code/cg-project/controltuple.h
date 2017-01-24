#ifndef CONTROLTUPLE_H
#define CONTROLTUPLE_H

#include "xyztuple.h"

struct ControlTuple
{
    XYZTuple aPoint;
    XYZTuple bPoint;
    double angle;

    XYZTuple eye;
    XYZTuple direction;

    ControlTuple(XYZTuple aPoint,
                 XYZTuple bPoint,
                 double angle,
                 XYZTuple eye,
                 XYZTuple direction);
};

#endif // CONTROLTUPLE_H
