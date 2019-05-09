#ifndef DIALOGWINDOW
#define DIALOGWINDOW
#include <QtWidgets>
#include <QDialog>

class DialogWindow: public QDialog
{
    Q_OBJECT

public slots:
    void setCancel(bool a = true);
    void setCanvas(int, int);

public:
    int x,y;
    bool cancel;
    DialogWindow(QWidget *parent = 0 );
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
};

#endif // DIALOGWINDOW

