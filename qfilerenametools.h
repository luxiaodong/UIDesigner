#ifndef QFILERENAMETOOLS_H
#define QFILERENAMETOOLS_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class QFileRenameTools;
}

class QFileRenameTools : public QDialog
{
    Q_OBJECT

public:
    explicit QFileRenameTools(QDialog *parent = 0);
    ~QFileRenameTools();

private slots:
    void srcBrowse_clicked();
    void dstBrowse_clicked();
    void preview_click();
    void general_click();

private:
    void traverseFiles(QString dir);
    void filterList1();
    void generalList2();

private:
    QStringList m_srcList; //偏移字符串
    QStringList m_dstList; //生成字符串

private:
    Ui::QFileRenameTools *ui;
};

#endif // QFILERENAMETOOLS_H
