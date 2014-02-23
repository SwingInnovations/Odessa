#include "brush.h"

Brush::Brush()
{
    myBrush = QBrush();
    myPen = QPen();
    myPen.setCapStyle(Qt::RoundCap);
}
