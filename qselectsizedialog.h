#ifndef QSELECTSIZEDIALOG_H
#define QSELECTSIZEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class QSelectSizeDialog;
}

class QSelectSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QSelectSizeDialog(QWidget *parent = 0);
    ~QSelectSizeDialog();

public slots:
    void clickOk();

public:
    int m_width;
    int m_height;
    QString m_rootClassName;

private:
    Ui::QSelectSizeDialog *ui;
};

#endif // QSELECTSIZEDIALOG_H
