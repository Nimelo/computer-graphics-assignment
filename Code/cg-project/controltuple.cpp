#include "controltuple.h"

ControlTuple::ControlTuple(XYZTuple aPoint,
             XYZTuple bPoint,
             double angle,
             XYZTuple eye,
             XYZTuple direction) :
             aPoint(aPoint),
             bPoint(bPoint),
             angle(angle),
             eye(eye),
             direction(direction)
{

}
