#include "Inc/addlinethread.h"
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <math.h>

AddLineThread::AddLineThread()
{

}


void AddLineThread::ReInitParameters(QPoint topLeft, QPoint bottomRight, int width, int height)
{
    topL = topLeft;
    bottomR = bottomRight;
    widthCnt = width;
    heightCnt = height;
}


void AddLineThread::run(){
//    QPixmap pixmap(bottomR.x() - 1,bottomR.y() - 1);
//    QPainter painter(&pixmap);
//    QPen Red((QColor("#000000")),1);
//    painter.setPen(Red);

//    float offsetWidth = (bottomR.x() - topL.x()) / (static_cast<float>(widthCnt));
//    float offsetHeight = (bottomR.y() - topL.y()) / (static_cast<float>(heightCnt));

//    int i = 1;

//    while(i < widthCnt || i < heightCnt)
//    {
//        if(i < widthCnt)
//            painter.drawLine(topL.x() + round(offsetWidth * i),
//                             topL.y(),
//                             topL.x() + round(offsetWidth * i),
//                             bottomR.y() - 2);


//        if(i < heightCnt)
//            painter.drawLine(topL.x(),
//                             topL.y() + round(offsetHeight * i),
//                             bottomR.x() - 2,
//                             topL.y() + round(offsetHeight * i));

//        i++;
//    }

//    emit finish(pixmap);
}
