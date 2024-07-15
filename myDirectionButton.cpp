#include "myDirectionButton.h"

#include<QDebug>
#include<QPainter>
#include<QMouseEvent>


myDirectionButton::myDirectionButton(QWidget *parent)
    : QWidget(parent)
{
    m_scale = 1.0;
    m_pressedBtn = NONE;
    m_hoverBtn = NONE;
    m_clrOut0 = QColor(200, 200, 200, 100);
    m_clrOut1 = QColor(200, 255, 200, 200);
    m_clrIn0 = QColor(255, 255, 255);
    m_clrIn1 = QColor(100, 255, 100);
    m_buttons.resize(8);
    m_arrows.resize(8);

    setMouseTracking(true);

    setMinimumSize(100, 100);
}

void myDirectionButton::createButtons()
{
    //Z-装饰箭头向上
    QPainterPath arrowZN;
    arrowZN.moveTo(0, -85);
    arrowZN.lineTo(20, -75);
    arrowZN.lineTo(10, -75);
    arrowZN.lineTo(10, -55);
    arrowZN.lineTo(-10, -55);
    arrowZN.lineTo(-10, -75);
    arrowZN.lineTo(-20, -75);
    arrowZN.closeSubpath();

    //Y+装饰箭头，逆时针
    QPainterPath arrowYP;
    arrowYP.moveTo(-77.5, -90);
    arrowYP.lineTo(-65, -85);
    arrowYP.lineTo(-70, -85);
    arrowYP.lineTo(-70, -78.2624);
    arrowYP.arcTo(QRectF(-105, -105, 210, 210), 131.81, 12.24);
    arrowYP.lineTo(-85, -85);
    arrowYP.lineTo(-90, -85);
    arrowYP.closeSubpath();

    //A+装饰箭头，逆时针
    QPainterPath arrowAP;
    arrowAP.moveTo(54.0833, -90);
    arrowAP.arcTo(QRectF(-105, -105, 210, 210), 59, -12.63);
    arrowAP.lineTo(75.9939, -79.5294);
    arrowAP.arcTo(QRectF(-110, -110, 220, 220), 46.36, -11.27);
    arrowAP.lineTo(90, -79.3725);
    arrowAP.lineTo(83.0666, -86.6022);
    arrowAP.lineTo(86.4645, -90);
    arrowAP.closeSubpath();

    //Z-按钮路径
    QPainterPath btnZN;
    btnZN.moveTo(33.5434, -37.0789);
    btnZN.arcTo(QRectF(-50, -50, 100, 100), 47.87, 84.27);
    btnZN.lineTo(-65.4074, -68.9429);
    btnZN.arcTo(QRectF(-95, -95, 190, 190), 133.49, -86.98);
    btnZN.closeSubpath();

    //Y+按钮路径
    QPainterPath btnYP;
    btnYP.moveTo(-95, -95);
    btnYP.lineTo(-31.225, -95);
    btnYP.arcTo(QRectF(-100, -100, 200, 200), 108.19, 53.61);
    btnYP.closeSubpath();

    //回原按钮
    QPainterPath home;
    home.addEllipse(-45, -45, 90, 90);

    QTransform trans;
    //路径转换
    trans.translate(rect().center().x(), rect().center().y());
    trans.scale(m_scale, m_scale);
    m_arrows[ZN] = trans.map(arrowZN);
    m_buttons[ZN] = trans.map(btnZN);
    m_buttons[YP] = trans.map(btnYP);
    m_arrows[YP] = trans.map(arrowYP);
    m_arrows[RP] = trans.map(arrowAP);
    m_homeBtn = trans.map(home);

    trans.rotate(-90);
    m_arrows[XN] = trans.map(arrowZN);
    m_buttons[XN] = trans.map(btnZN);
    m_buttons[YN] = trans.map(btnYP);

    trans.rotate(-90);
    m_arrows[ZP] = trans.map(arrowZN);
    m_buttons[ZP] = trans.map(btnZN);
    m_buttons[RN] = trans.map(btnYP);

    trans.rotate(-90);
    m_arrows[XP] = trans.map(arrowZN);
    m_buttons[XP] = trans.map(btnZN);
    m_buttons[RP] = trans.map(btnYP);
    trans.reset();


    //添加YA两个方向装饰箭头
    trans.translate(rect().center().x(), rect().center().y());
    trans.scale(m_scale, -m_scale);
    m_arrows[YN] = trans.map(arrowYP);
    m_arrows[RN] = trans.map(arrowAP);
    trans.reset();
}

void myDirectionButton::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    //绘制按钮区
    painter.setBrush(m_clrOut0);
    for(int i = 0; i < m_buttons.count(); i++) {
        painter.drawPath(m_buttons.at(i));
    }

    //绘制回原按钮
    painter.drawPath(m_homeBtn);

    //绘制装饰箭头
    painter.setBrush(m_clrIn0);
    for(int i = 0; i < m_arrows.count(); i++) {
        painter.drawPath(m_arrows.at(i));
    }

    //根据状态绘制不同颜色
    switch (m_pressedBtn)
    {
        case ZN:
        case ZP:
        case XN:
        case XP:
        case YP:
        case YN:
        case RP:
        case RN:
            painter.setBrush(m_clrOut1);
            painter.drawPath(m_buttons[m_pressedBtn]);
            painter.setBrush(m_clrIn1);
            painter.drawPath(m_arrows[m_pressedBtn]);
            break;
        case HOME:
            painter.setBrush(m_clrIn1);
            painter.drawPath(m_homeBtn);
            break;
        default:
            {
                switch (m_hoverBtn) {
                    case ZN:
                    case ZP:
                    case XN:
                    case XP:
                    case YP:
                    case YN:
                    case RP:
                    case RN:
                        painter.setBrush(m_clrOut1.lighter());
                        painter.drawPath(m_buttons[m_hoverBtn]);
                        painter.setBrush(m_clrIn1.lighter());
                        painter.drawPath(m_arrows[m_hoverBtn]);
                        break;
                    case HOME:
                        painter.setBrush(m_clrIn1.lighter());
                        painter.drawPath(m_homeBtn);
                        break;
                    default:
                        break;
                }
            }
            break;
    }

    //绘制文字
    painter.translate(size().width() / 2, size().height() / 2);
    painter.scale(m_scale, m_scale);
    QFont font = painter.font();
    font.setPixelSize(28);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawText(QRectF(-45, -45, 90, 90), Qt::AlignCenter, "HOME");

    font.setPixelSize(15);
    painter.setFont(font);
    painter.drawText(QRectF(-10, -75, 20, 20), Qt::AlignCenter, "Z-");
    painter.drawText(QRectF(-75, -10, 20, 20), Qt::AlignCenter, "X-");
    painter.drawText(QRectF(-10, 55, 20, 20), Qt::AlignCenter, "Z+");
    painter.drawText(QRectF(55, -10, 20, 20), Qt::AlignCenter, "X+");
    painter.drawText(QRectF(-85, -85, 15, 10), Qt::AlignCenter, "Y+");
    painter.drawText(QRectF(-85, 75, 15, 10), Qt::AlignCenter, "Y-");
    painter.drawText(QRectF(66, 80, 15, 10), Qt::AlignCenter, "R-");
    painter.drawText(QRectF(66, -90, 15, 10), Qt::AlignCenter, "R+");
}

void myDirectionButton::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    //默认绘图区域200X200,窗口变化时缩放
    int edge = qMin(size().width(), size().height());
    m_scale = edge / 200.0;

    createButtons();
}

void myDirectionButton::mouseReleaseEvent(QMouseEvent *)
{
    if(m_pressedBtn != HOME) {
        setPressed(NONE);
    }
}

void myDirectionButton::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    if(m_pressedBtn != NONE) {
        return;
    }

    QPoint p = event->pos();

    int state = NONE;

    if(m_homeBtn.contains(p))    {
        state = HOME;
    }
    else
    {
        for(int index = 0; index < m_buttons.count(); index++)        {
            if(m_buttons[index].contains(p))            {
                state = index;
            }
        }
    }

    if(m_hoverBtn != state)    {
        m_hoverBtn = state;
        update();
    }
}

void myDirectionButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint p = event->pos();

        //Home键比较特殊，鼠标弹释放时不会自动恢复颜色，因为他要标记Home过程
        //外部设备Home结束后才能取消Home状态
        if(m_homeBtn.contains(p))
        {
            setPressed(HOME);
            return;
        }

        for(int index = 0; index < m_buttons.count(); index++)
        {
            if(m_buttons[index].contains(p))
            {
                setPressed(index);
                return ;
            }
        }
    }
}

void myDirectionButton::setPressed(int button)
{
    if(button != m_pressedBtn)
    {
        m_pressedBtn = button;
        emit signalPressed(button);
        update();
    }


}


