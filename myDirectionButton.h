#ifndef MYDIRECTIONBUTTON_H
#define MYDIRECTIONBUTTON_H

#include<QWidget>

class myDirectionButton : public QWidget
{
    Q_OBJECT

public:
    enum PRESSED {
        ZN,
        XN,
        ZP,
        XP,
        YP,
        YN,
        RN,
        RP,
        HOME,
        NONE
    };

    myDirectionButton(QWidget *parent = nullptr);

    void setPressed(int button);

signals:
    void signalPressed(int button);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int m_pressedBtn;
    int m_hoverBtn;
    QColor m_clrOut0;
    QColor m_clrOut1;
    QColor m_clrIn0;
    QColor m_clrIn1;
    double m_scale;

    QPainterPath m_homeBtn;             //回原按钮，比较特殊，单独拿出来
    QVector<QPainterPath>m_buttons;     //按钮区域
    QVector<QPainterPath>m_arrows;      //装饰箭头


    void createButtons();               //创建按钮路径

};

#endif // MYDIRECTIONBUTTON_H
