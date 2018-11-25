#include "canvasthread.h"
#include <QThread>

CanvasWorker::CanvasWorker(QObject *parent) : QObject (parent)
{
    m_currentCommand = NONE;
    m_isDrawing = false;
    qDebug() << "Created Canvas Thread" << endl;
}

CanvasWorker::~CanvasWorker()
{
    m_mutex.lock();
    //TODO Zero out data here;
    m_currentCommand = NONE;
    m_mutex.unlock();
}

int CanvasWorker::GetJobSize()
{
    int JobSize;

    m_mutex.lock();
    JobSize = m_drawQueue.size();
    m_mutex.unlock();

    return JobSize;
}

void CanvasWorker::RenderJobs()
{
    CanvasJobParam Job1, Job2;
    m_mutex.lock();
    Job1 = m_drawQueue.dequeue();
    Job2 = m_drawQueue.head();
    m_mutex.unlock();

    Brush StartBrush = Job1.m_currentBrush;
    Brush EndBrush = Job2.m_currentBrush;

    QImage StencilBase = StartBrush.getStencil().toImage();
    StencilBase.invertPixels(QImage::InvertRgb);
    StencilBase.createAlphaMask();
    StencilBase.convertToFormat(QImage::Format_RGB888);
    QImage StencilImage = QImage(StencilBase);
    QColor color = StartBrush.getColor();
    color.setAlpha(StartBrush.getOpacity());
    StencilImage.fill(color);
    StencilImage.setAlphaChannel(StencilBase);

    //Flag we are ready for more draw operations.
    m_mutex.lock();
    m_isDrawing = false;
    m_mutex.unlock();
}

void CanvasWorker::EnqueueJob( CanvasWorker::CanvasJobParam JobParam )
{
    int JobSize;
    m_mutex.lock();
    m_drawQueue.enqueue(JobParam);
    JobSize = m_drawQueue.size();
    m_mutex.unlock();

    if(JobSize >= 2 && !m_isDrawing)
    {
        m_mutex.lock();
        m_isDrawing = true;
        m_mutex.unlock();

        RenderJobs();
    }
}
