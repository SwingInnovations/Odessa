#ifndef CANVASTHREAD_H
#define CANVASTHREAD_H

#include <QObject>
#include <QMutex>
#include <QVector>
#include <QImage>
#include <QDebug>
#include <QQueue>

#include "brush.h"

/**
 * @brief The CanvasThread class
 * Primarily used for async drawing operations. Enqueue's points and emits resulting image.
 */
class CanvasWorker : public QObject
{
    Q_OBJECT
public:
    enum ThreadCommand : uint
    {
        NONE = 0,
        DRAW,
    };

    /**
     * @brief The CanvasJobParam struct
     * Contains job information that the canvas may need.
     */
    struct CanvasJobParam
    {
        //What should the worker thread do
        ThreadCommand m_command;

        //
        Brush         m_currentBrush;
        //What point to be drawn.
        QPoint        m_point;
    };

    struct CanvasJobResultParam
    {
        int         m_status;   //Status code for Job
        //Image stored from worker thread.
        QImage      m_image;
    };

    CanvasWorker(QObject* parent = 0);
    ~CanvasWorker() override;

    int GetJobSize();

signals:
    //When rendered image is ready, output here.
    void RenderedImage(const QImage& image);
    void JobComplete(CanvasJobResultParam ResultParam);
public slots:
    void RenderJobs();
    void EnqueueJob(CanvasJobParam JobParam);
private:
    bool            m_isProjectInit;
    bool            m_isDrawing;    //Indicate we are currently drawing.
    QImage          m_tempDrawnImage;   //Temporary Drawing Image.
    QRect           m_drawArea;
    //Thread Management objects
    QMutex          m_mutex;

    //Canvas management;
    ThreadCommand               m_currentCommand;

    //Keep track of our jobs
    QQueue<CanvasJobParam>      m_drawQueue;
};
Q_DECLARE_METATYPE(CanvasWorker::CanvasJobParam);
Q_DECLARE_METATYPE(CanvasWorker::CanvasJobResultParam);

#endif // CANVASTHREAD_H
