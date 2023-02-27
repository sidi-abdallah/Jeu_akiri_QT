#ifndef AKARIVIEW_H
#define AKARIVIEW_H

#include <QWidget>

class AkariView : public QWidget
{
    Q_OBJECT
public:
    explicit AkariView(QWidget *parent = nullptr);

signals:

protected:
    virtual void paintEvent(QPaintEvent * event) override;


};

#endif // AKARIVIEW_H
