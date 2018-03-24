#include "capturescreen.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QDebug>

// 彩色鼠标按钮图片的十六进制数据
static const unsigned char uc_mouse_image[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,  0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52
    ,0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x2D,  0x08, 0x06, 0x00, 0x00, 0x00, 0x52, 0xE9, 0x60
    ,0xA2, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59,  0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B
    ,0x13, 0x01, 0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00,  0x01, 0x40, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85
    ,0xED, 0xD5, 0x21, 0x6E, 0xC3, 0x30, 0x14, 0xC6,  0xF1, 0xFF, 0x9B, 0xC6, 0x36, 0x30, 0x38, 0xA9
    ,0x05, 0x01, 0x05, 0x81, 0x05, 0x03, 0x39, 0xCA,  0x60, 0x8F, 0xD2, 0x03, 0xEC, 0x10, 0x3B, 0x46
    ,0xC1, 0xC0, 0xC6, 0x0A, 0x3B, 0x96, 0xB1, 0x80,  0x82, 0xC1, 0x56, 0x2A, 0xFF, 0x06, 0xE2, 0x36
    ,0x75, 0x9A, 0xB4, 0xCA, 0xEC, 0x4E, 0x9A, 0xE4,  0x2F, 0xB2, 0x42, 0x22, 0xFF, 0xF2, 0xFC, 0x9C
    ,0x18, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52,  0x52, 0x52, 0x52, 0xFE, 0x55, 0xE4, 0xC6, 0xA0
    ,0xDC, 0xC4, 0x71, 0x87, 0xC1, 0xC1, 0x68, 0x01,  0xCC, 0x06, 0xC2, 0x51, 0xD0, 0x29, 0xB0, 0x18
    ,0x00, 0xDF, 0xC6, 0x40, 0x33, 0x37, 0x84, 0x30,  0x4C, 0x80, 0x85, 0xCE, 0x7B, 0x2E, 0x2A, 0x91
    ,0x84, 0x24, 0xBE, 0x25, 0xDE, 0x25, 0x5E, 0x2F,  0x6E, 0xAE, 0xD0, 0x37, 0x92, 0x10, 0xF0, 0x09
    ,0x54, 0x40, 0xE9, 0xEE, 0x15, 0xC6, 0xA2, 0x77,  0xFE, 0xE0, 0xE5, 0x85, 0x8F, 0x16, 0x58, 0xDF
    ,0x35, 0x06, 0x5B, 0xD3, 0xB9, 0xD4, 0x11, 0xD0,  0xA5, 0x8F, 0xDE, 0x57, 0x75, 0x83, 0x73, 0x50
    ,0x06, 0xF6, 0x72, 0x0A, 0x47, 0x40, 0x57, 0x0D,  0x38, 0xDE, 0xC0, 0x04, 0x6F, 0x68, 0x05, 0x36
    ,0xF5, 0xE1, 0x08, 0x3D, 0xCD, 0xEA, 0xEA, 0x5A,  0xD8, 0xBE, 0x5A, 0x46, 0xB0, 0x05, 0x1E, 0xAC
    ,0xF1, 0xC2, 0xD1, 0xCC, 0x01, 0x6D, 0x74, 0x02,  0xDB, 0x3B, 0xBF, 0xD3, 0x73, 0x07, 0x87, 0x2F
    ,0xEF, 0x53, 0x07, 0x38, 0x82, 0x2F, 0xF6, 0xFB,  0xB8, 0x81, 0x73, 0x41, 0x69, 0x28, 0x3A, 0x7A
    ,0x5C, 0xDD, 0x73, 0xCF, 0x3A, 0x86, 0xA3, 0x05,  0x87, 0xEA, 0xCC, 0x60, 0xA1, 0x06, 0x75, 0x89
    ,0xFE, 0x77, 0x92, 0x76, 0x68, 0x23, 0xEF, 0x88,  0xD3, 0x4C, 0xA8, 0x10, 0x7A, 0xD4, 0xEF, 0x8E
    ,0xBE, 0x8B, 0x68, 0x79, 0x3A, 0xB1, 0x72, 0xE1,  0xAE, 0xBC, 0x13, 0x0D, 0xDE, 0xBD, 0x3D, 0xF3
    ,0x08, 0x15, 0xD4, 0xDF, 0x4C, 0x06, 0x36, 0xF7,  0x9E, 0x09, 0xED, 0xE9, 0x99, 0x97, 0x3E, 0x42
    ,0xFF, 0x30, 0x42, 0x4B, 0xA1, 0x8D, 0xD8, 0xE9,  0x2A, 0xBD, 0xED, 0x41, 0x25, 0x2A, 0x89, 0x37
    ,0x1F, 0xBD, 0xEA, 0x61, 0x8B, 0x5F, 0xDD, 0xC1,  0xFA, 0x01, 0xD8, 0xA3, 0x8F, 0xFB, 0xCA, 0x70
    ,0x16, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,  0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

// 矩形选中区边框宽度;
static const int SELECT_RECT_BORDER_WIDTH = 1;

// 选中矩形8个拖拽点小矩形的宽高;
static const int STRETCH_RECT_WIDTH = 6;
static const int STRETCH_RECT_HEIGHT = 6;

CaptureScreen::CaptureScreen(QWidget *parent)
    : QWidget(parent)
    , m_currentCaptureState(InitCapture)
{
    initWindow();
    initStretchRect();
    loadBackgroundPixmap();
    show();
}

CaptureScreen::~CaptureScreen()
{

}

void CaptureScreen::initWindow()
{
    this->setMouseTracking(true);
    // 由于存在类似QQ这样界面始终显示在最顶层，设置属性 Qt::WindowStaysOnTopHint;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
    this->setMouseTracking(true);
}

void CaptureScreen::initStretchRect()
{
    m_stretchRectState = NotSelect;
    m_topLeftRect = QRect(0 , 0 , 0 , 0);
    m_topRightRect = QRect(0, 0, 0, 0);
    m_bottomLeftRect = QRect(0, 0, 0, 0);
    m_bottomRightRect = QRect(0, 0, 0, 0);

    m_leftCenterRect = QRect(0, 0, 0, 0);
    m_topCenterRect = QRect(0, 0, 0, 0);
    m_rightCenterRect = QRect(0, 0, 0, 0);
    m_bottomCenterRect = QRect(0, 0, 0, 0);
}

// 获取当前屏幕图片;
void CaptureScreen::loadBackgroundPixmap()
{
    m_loadPixmap = QPixmap::grabWindow(QApplication::desktop()->winId()); //抓取当前屏幕的图片;
    m_screenwidth = m_loadPixmap.width();
    m_screenheight = m_loadPixmap.height();
}

void CaptureScreen::mousePressEvent(QMouseEvent *event)
{
    m_stretchRectState = getStrethRectState(event->pos());
    if (event->button() == Qt::LeftButton)
    {
        if (m_currentCaptureState == InitCapture)
        {
            m_currentCaptureState = BeginCaptureImage;
            m_beginPoint = event->pos();
        }
        // 是否在拉伸的小矩形中;
        else if (m_stretchRectState != NotSelect)
        {
            m_currentCaptureState = BeginMoveStretchRect;
            // 当前鼠标在拖动选中区顶点时,设置鼠标当前状态;
            setStretchCursorStyle(m_stretchRectState);
            m_beginMovePoint = event->pos();
        }
        // 是否在选中的矩形中;
        else if (isPressPointInSelectRect(event->pos()))
        {
            m_currentCaptureState = BeginMoveCaptureArea;
            m_beginMovePoint = event->pos();
        }
    }

    return QWidget::mousePressEvent(event);
}

void CaptureScreen::mouseMoveEvent(QMouseEvent* event)
{
    if (m_currentCaptureState == BeginCaptureImage)
    {
        m_endPoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea)
    {
        m_endMovePoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect)
    {
        m_endMovePoint = event->pos();
        update();
        // 当前鼠标在拖动选中区顶点时,在鼠标未停止移动前，一直保持鼠标当前状态;
        return QWidget::mouseMoveEvent(event);
    }


    // 根据鼠标是否在选中区域内设置鼠标样式;
    StretchRectState stretchRectState = getStrethRectState(event->pos());
    if (stretchRectState != NotSelect)
    {
        setStretchCursorStyle(stretchRectState);
    }
    else if (isPressPointInSelectRect(event->pos()))
    {
        setCursor(Qt::SizeAllCursor);
    }
    else if (!isPressPointInSelectRect(event->pos()) && m_currentCaptureState != BeginMoveCaptureArea)
    {
        QPixmap pixmap;
        pixmap.loadFromData(uc_mouse_image, sizeof(uc_mouse_image));
        QCursor cursor;
        cursor = QCursor(pixmap, 15, 23);
        setCursor(cursor);
    }

    return QWidget::mouseMoveEvent(event);
}

void CaptureScreen::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_currentCaptureState == BeginCaptureImage)
    {
        m_currentCaptureState = FinishCaptureImage;
        m_endPoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea)
    {
        m_currentCaptureState = FinishMoveCaptureArea;
        m_endMovePoint = event->pos();
        update();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect)
    {
        m_currentCaptureState = FinishMoveStretchRect;
        m_endMovePoint = event->pos();
        update();
    }

    return QWidget::mouseReleaseEvent(event);
}

// 当前鼠标坐标是否在选取的矩形区域内;
bool CaptureScreen::isPressPointInSelectRect(QPoint mousePressPoint)
{
    QRect selectRect = getRect(m_beginPoint, m_endPoint);
    if (selectRect.contains(mousePressPoint))
    {
        return true;
    }

    return false;
}

void CaptureScreen::paintEvent(QPaintEvent *event)
{
    m_painter.begin(this);          //进行重绘;

    QColor shadowColor = QColor(0, 0, 0, 120);                      //阴影颜色设置;
    m_painter.drawPixmap(0, 0, m_loadPixmap);                       //将背景图片画到窗体上;
    m_painter.fillRect(m_loadPixmap.rect(), shadowColor);           //画影罩效果;

    switch (m_currentCaptureState)
    {
     case InitCapture:
        break;
    case BeginCaptureImage:
    case FinishCaptureImage:
    case BeginMoveCaptureArea:
    case FinishMoveCaptureArea:
    case BeginMoveStretchRect:
    case FinishMoveStretchRect:
        m_currentSelectRect = getSelectRect();
        drawCaptureImage();
    default:
        break;
    }

    m_painter.end();  //重绘结束;
}

// 根据当前截取状态获取当前选中的截图区域;
QRect CaptureScreen::getSelectRect()
{
    QRect selectRect(0, 0, 0, 0);
    if (m_currentCaptureState == BeginCaptureImage || m_currentCaptureState == FinishCaptureImage)
    {
        selectRect = getRect(m_beginPoint, m_endPoint);
    }
    else if (m_currentCaptureState == BeginMoveCaptureArea || m_currentCaptureState == FinishMoveCaptureArea)
    {
        selectRect = getMoveRect();
    }
    else if (m_currentCaptureState == BeginMoveStretchRect || m_currentCaptureState == FinishMoveStretchRect)
    {
        selectRect = getStretchRect();
    }

    if (m_currentCaptureState == FinishCaptureImage || m_currentCaptureState == FinishMoveCaptureArea || m_currentCaptureState == FinishMoveStretchRect)
    {
        m_currentCaptureState = FinishCaptureImage;
    }

    return selectRect;
}

// 绘制当前选中的截图区域;
void CaptureScreen::drawCaptureImage()
{
    m_capturePixmap = m_loadPixmap.copy(m_currentSelectRect);
    m_painter.drawPixmap(m_currentSelectRect.topLeft(), m_capturePixmap);
    m_painter.setPen(QPen(QColor(0, 180, 255), SELECT_RECT_BORDER_WIDTH));    //设置画笔;
    m_painter.drawRect(m_currentSelectRect);
    drawStretchRect();
}

// 绘制选中矩形各拖拽点小矩形;
void CaptureScreen::drawStretchRect()
{
    QColor color = QColor(0, 174, 255);
    // 四个角坐标;
    QPoint topLeft = m_currentSelectRect.topLeft();
    QPoint topRight = m_currentSelectRect.topRight();
    QPoint bottomLeft = m_currentSelectRect.bottomLeft();
    QPoint bottomRight = m_currentSelectRect.bottomRight();
    // 四条边中间点坐标;
    QPoint leftCenter = QPoint(topLeft.x(), (topLeft.y() + bottomLeft.y()) / 2);
    QPoint topCenter = QPoint((topLeft.x() + topRight.x()) / 2, topLeft.y());
    QPoint rightCenter = QPoint(topRight.x(), leftCenter.y());
    QPoint bottomCenter = QPoint(topCenter.x(), bottomLeft.y());

    m_topLeftRect = QRect(topLeft.x() - STRETCH_RECT_WIDTH / 2, topLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topRightRect = QRect(topRight.x() - STRETCH_RECT_WIDTH / 2, topRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomLeftRect = QRect(bottomLeft.x() - STRETCH_RECT_WIDTH / 2, bottomLeft.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomRightRect = QRect(bottomRight.x() - STRETCH_RECT_WIDTH / 2, bottomRight.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_leftCenterRect = QRect(leftCenter.x() - STRETCH_RECT_WIDTH / 2, leftCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_topCenterRect = QRect(topCenter.x() - STRETCH_RECT_WIDTH / 2, topCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_rightCenterRect = QRect(rightCenter.x() - STRETCH_RECT_WIDTH / 2, rightCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
    m_bottomCenterRect = QRect(bottomCenter.x() - STRETCH_RECT_WIDTH / 2, bottomCenter.y() - STRETCH_RECT_HEIGHT / 2, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

    m_painter.fillRect(m_topLeftRect, color);
    m_painter.fillRect(m_topRightRect, color);
    m_painter.fillRect(m_bottomLeftRect, color);
    m_painter.fillRect(m_bottomRightRect, color);
    m_painter.fillRect(m_leftCenterRect, color);
    m_painter.fillRect(m_topCenterRect, color);
    m_painter.fillRect(m_rightCenterRect, color);
    m_painter.fillRect(m_bottomCenterRect, color);
}

void CaptureScreen::keyPressEvent(QKeyEvent *event)
{
    // Esc 键退出截图;
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
    // Eeter键完成截图;
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        signalCompleteCature(m_capturePixmap);
        close();
    }
}

// 根据beginPoint , endPoint 获取当前选中的矩形;
QRect CaptureScreen::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);
    // 避免宽或高为零时拷贝截图有误;
    // 可以看QQ截图，当选取截图宽或高为零时默认为2;
    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}

// 获取移动后,当前选中的矩形;
QRect CaptureScreen::getMoveRect()
{
    // 通过getMovePoint方法先检查当前是否移动超出屏幕;
    QPoint movePoint = getMovePoint();
    QPoint beginPoint = m_beginPoint + movePoint;
    QPoint endPoint = m_endPoint + movePoint;
    // 结束移动选区时更新当前m_beginPoint , m_endPoint,防止下一次操作时截取的图片有问题;
    if (m_currentCaptureState == FinishMoveCaptureArea)
    {
        m_beginPoint = beginPoint;
        m_endPoint = endPoint;
        m_beginMovePoint = QPoint(0, 0);
        m_endMovePoint = QPoint(0, 0);
    }
    return getRect(beginPoint, endPoint);
}

QPoint CaptureScreen::getMovePoint()
{
    QPoint movePoint = m_endMovePoint - m_beginMovePoint;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    // 检查当前是否移动超出屏幕;

    //移动选区是否超出屏幕左边界;
    if (currentRect.topLeft().x() + movePoint.x() < 0)
    {
        movePoint.setX(0 - currentRect.topLeft().x());
    }
    //移动选区是否超出屏幕上边界;
    if (currentRect.topLeft().y() + movePoint.y() < 0)
    {
        movePoint.setY(0 - currentRect.topLeft().y());
    }
    //移动选区是否超出屏幕右边界;
    if (currentRect.bottomRight().x() + movePoint.x() > m_screenwidth)
    {
        movePoint.setX(m_screenwidth - currentRect.bottomRight().x());
    }
    //移动选区是否超出屏幕下边界;
    if (currentRect.bottomRight().y() + movePoint.y() > m_screenheight)
    {
        movePoint.setY(m_screenheight - currentRect.bottomRight().y());
    }

    return movePoint;
}

// 获取当前鼠标位于哪一个拖拽顶点;
StretchRectState CaptureScreen::getStrethRectState(QPoint point)
{
    StretchRectState stretchRectState = NotSelect;
    if (m_topLeftRect.contains(point))
    {
        stretchRectState = TopLeftRect;
    }
    else if (m_topCenterRect.contains(point))
    {
        stretchRectState = TopCenterRect;
    }
    else if (m_topRightRect.contains(point))
    {
        stretchRectState = TopRightRect;
    }
    else if (m_rightCenterRect.contains(point))
    {
        stretchRectState = RightCenterRect;
    }
    else if (m_bottomRightRect.contains(point))
    {
        stretchRectState = BottomRightRect;
    }
    else if (m_bottomCenterRect.contains(point))
    {
        stretchRectState = BottomCenterRect;
    }
    else if (m_bottomLeftRect.contains(point))
    {
        stretchRectState = BottomLeftRect;
    }
    else if (m_leftCenterRect.contains(point))
    {
        stretchRectState = LeftCenterRect;
    }

    return stretchRectState;
}

// 设置鼠标停在拖拽定点处的样式;
void CaptureScreen::setStretchCursorStyle(StretchRectState stretchRectState)
{
    switch (stretchRectState)
    {
    case NotSelect:
        setCursor(Qt::ArrowCursor);
        break;
    case TopLeftRect:
    case BottomRightRect:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRightRect:
    case BottomLeftRect:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case LeftCenterRect:
    case RightCenterRect:
        setCursor(Qt::SizeHorCursor);
        break;
    case TopCenterRect:
    case BottomCenterRect:
        setCursor(Qt::SizeVerCursor);
        break;
    default:
        break;
    }
}

// 获取拖拽后的矩形选中区域;
QRect CaptureScreen::getStretchRect()
{
    QRect stretchRect;
    QRect currentRect = getRect(m_beginPoint, m_endPoint);
    switch (m_stretchRectState)
    {
    case NotSelect:
        stretchRect = getRect(m_beginPoint, m_endPoint);
        break;
    case TopLeftRect:
        {
            stretchRect = getRect(currentRect.bottomRight(), m_endMovePoint);
        }
        break;
    case TopRightRect:
        {
            QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
            QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
            stretchRect = getRect(beginPoint, endPoint);
        }
        break;
    case BottomLeftRect:
        {
            QPoint beginPoint = QPoint(m_endMovePoint.x() , currentRect.topLeft().y());
            QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
            stretchRect = getRect(beginPoint, endPoint);
        }
        break;
    case BottomRightRect:
        {
            stretchRect = getRect(currentRect.topLeft(), m_endMovePoint);
        }
        break;
    case LeftCenterRect:
        {
            QPoint beginPoint = QPoint(m_endMovePoint.x(), currentRect.topLeft().y());
            stretchRect = getRect(beginPoint, currentRect.bottomRight());
        }
        break;
    case TopCenterRect:
    {
        QPoint beginPoint = QPoint(currentRect.topLeft().x(), m_endMovePoint.y());
        stretchRect = getRect(beginPoint, currentRect.bottomRight());
    }
        break;
    case RightCenterRect:
    {
        QPoint endPoint = QPoint(m_endMovePoint.x(), currentRect.bottomRight().y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    case BottomCenterRect:
    {
        QPoint endPoint = QPoint(currentRect.bottomRight().x(), m_endMovePoint.y());
        stretchRect = getRect(currentRect.topLeft(), endPoint);
    }
        break;
    default:
    {
        stretchRect = getRect(m_beginPoint , m_endPoint );
    }
        break;
    }

    // 拖动结束更新 m_beginPoint , m_endPoint;
    if (m_currentCaptureState == FinishMoveStretchRect)
    {
        m_beginPoint = stretchRect.topLeft();
        m_endPoint = stretchRect.bottomRight();
    }

    return stretchRect;
}
