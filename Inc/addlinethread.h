#ifndef ADDLINETHREAD_H
#define ADDLINETHREAD_H
#include <QThread>
#include <QPoint>

/**
 * @brief TODO: в разработке =)
 */
class AddLineThread : public QThread
{
    Q_OBJECT
public:
    AddLineThread();

    void ReInitParameters(QPoint topLeft, QPoint bottomRight, int width, int height);

//signals:
//    void finish(QPixmap pixmap);

protected:
    void run() override;

private:
    QPoint topL, bottomR;
    int widthCnt, heightCnt;
};

#endif // ADDLINETHREAD_H
