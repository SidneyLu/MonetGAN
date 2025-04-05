#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTransform>

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);
    void setPixmap(const QPixmap &pixmap);
    void fitInView();

    private slots:
        void zoomIn();
    void zoomOut();
    void rotateImage();

private:
    void initUI();
    void loadImage();
    void scaleView(qreal factor);
    void adjustViewSize();

    QToolBar *toolBar;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *item;
    QPixmap pixmap;
    qreal scaleFactor;
    QSize originalSize; // 新增：保存原始图像尺寸
};

#endif // IMAGEVIEWER_H