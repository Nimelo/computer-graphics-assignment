#ifndef CONTROLTUPLE_H
#define CONTROLTUPLE_H

#include "xyztuple.h"

struct ControlTuple
{
    XYZTuple rotation;
    XYZTuple eye;
    XYZTuple direction;

    ControlTuple(XYZTuple rotation, XYZTuple eye, XYZTuple direction);
};

#endif // CONTROLTUPLE_H
