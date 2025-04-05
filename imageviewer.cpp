#include "imageviewer.h"
#include <QVBoxLayout>
#include <QApplication>

ImageViewer::ImageViewer(QWidget *parent) : QWidget(parent)
{
    initUI();
    scaleFactor = 1.0;
    originalSize = QSize();
}

void ImageViewer::setPixmap(const QPixmap &pixmap)
{
    this->pixmap = pixmap;
    originalSize = pixmap.size();
    loadImage();
    adjustViewSize();
}

void ImageViewer::fitInView()
{
    view->fitInView(item, Qt::KeepAspectRatio);
}

void ImageViewer::zoomIn()
{
    scaleView(1.2);
    adjustViewSize(); // 缩放后调整视图大小
}

void ImageViewer::zoomOut()
{
    scaleView(1 / 1.2);
    adjustViewSize(); // 缩放后调整视图大小
}

void ImageViewer::rotateImage()
{
    item->setRotation(item->rotation() + 90);
    adjustViewSize(); // 旋转后调整视图大小
}

void ImageViewer::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mainLayout->addWidget(toolBar);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    mainLayout->addWidget(view);

    view->setAlignment(Qt::AlignCenter);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    // 禁用滚动条（可选）
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QAction *zoomInAction = toolBar->addAction(tr("放大"));
    QAction *zoomOutAction = toolBar->addAction(tr("缩小"));
    QAction *rotateAction = toolBar->addAction(tr("旋转"));

    connect(zoomInAction, &QAction::triggered, this, &ImageViewer::zoomIn);
    connect(zoomOutAction, &QAction::triggered, this, &ImageViewer::zoomOut);
    connect(rotateAction, &QAction::triggered, this, &ImageViewer::rotateImage);
}

void ImageViewer::loadImage()
{
    scene->clear();
    item = scene->addPixmap(pixmap);
}

void ImageViewer::scaleView(qreal factor)
{
    scaleFactor *= factor;
    view->scale(factor, factor);
}

void ImageViewer::adjustViewSize()
{
    if (!originalSize.isValid() || !item) return;

    // 计算旋转后的尺寸
    QTransform rotationTransform;
    rotationTransform.rotate(item->rotation());
    QSize rotatedSize = rotationTransform.mapRect(QRect(QPoint(0, 0), originalSize)).size();

    // 应用缩放因子
    QSize scaledSize = rotatedSize * scaleFactor;

    // 设置视图尺寸（保留工具栏高度）
    const int toolBarHeight = toolBar->height();
    setFixedSize(scaledSize.width(), scaledSize.height() + toolBarHeight);

    // 调整视图位置
    view->setFixedSize(scaledSize);
    view->setAlignment(Qt::AlignCenter);
    view->centerOn(item);
}