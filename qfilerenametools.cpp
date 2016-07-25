#include "qfilerenametools.h"
#include "ui_qfilerenametools.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>

QFileRenameTools::QFileRenameTools(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::QFileRenameTools)
{
    ui->setupUi(this);

    connect( ui->srcBrowse, SIGNAL(pressed()), this, SLOT( srcBrowse_clicked())  );
    connect( ui->dstBrowse, SIGNAL(pressed()), this, SLOT( dstBrowse_clicked())  );

    connect( ui->preview, SIGNAL(pressed()), this, SLOT( preview_click())  );
    connect( ui->general, SIGNAL(pressed()), this, SLOT( general_click())  );
}

QFileRenameTools::~QFileRenameTools()
{
    delete ui;
}

void QFileRenameTools::srcBrowse_clicked()
{
    QString root = QFileDialog::getExistingDirectory(this);
    if(root.isEmpty() == false)
    {
        ui->srcRoot->setText(root);
        this->preview_click();
    }
}

void QFileRenameTools::dstBrowse_clicked()
{
    QString root = QFileDialog::getExistingDirectory(this);
    if(root.isEmpty() == false)
    {
        ui->dstRoot->setText(root);
    }
}

void QFileRenameTools::filterList1()
{
    QString suffixStr = ui->suffix->text();
    QString hasStr = ui->has->text();
    QString notHasStr = ui->nothas->text();

    if (suffixStr.isEmpty() == false)
    {
        QStringList temp = m_srcList.filter( suffixStr );
        m_srcList = temp;
    }

    if (hasStr.isEmpty() == false)
    {
        QStringList temp = m_srcList.filter( hasStr );
        m_srcList = temp;
    }

    if (notHasStr.isEmpty() == false)
    {
        QStringList temp;
        foreach(QString single, m_srcList)
        {
            if(single.contains(notHasStr) == false)
            {
                temp.append(single);
            }
        }

        m_srcList = temp;
    }

    QStringList temp;
    foreach(QString single, m_srcList)
    {
        temp.append( single.remove( QString(ui->srcRoot->text() + QString("/"))) );
    }

    ui->srcList->clear();
    ui->srcList->addItems(temp);
}

void QFileRenameTools::generalList2()
{
    m_dstList.clear();
    ui->dstList->clear();
    QString format = ui->format->text();
    if(format.isEmpty() == true )
    {
        format = "%02d";
    }

    QString srcStr = ui->srcStr->text();
    QString dstStr = ui->dstStr->text();

    //QStringList list1; 一个文件夹里 目录索引
    QString next_format_prefix = "xxxxxxxxx";
    int j  = 1;
    for(int i = 0; i < ui->srcList->count(); ++i)
    {
        QListWidgetItem* item = ui->srcList->item(i);
        QString str1 = item->text();

        QString back_suffix = "";
        QStringList back_suffix_list =str1.split('.');
        if( back_suffix_list.count() > 0 )
        {
            back_suffix = QString(".") + back_suffix_list.last();
        }

        str1.replace('/', '_');

        if( srcStr.isEmpty() == false )
        {
            str1.replace(srcStr, dstStr);
        }

        str1.replace(QString("__"),QString('-'));

        QString current_format_prefix = "";
        QStringList temp = str1.split('_');
        if(temp.count() > 1)
        {
            for(int i = 0; i < temp.count() - 1; ++i)
            {
                current_format_prefix += temp.at(i);
                current_format_prefix += QString('_');
            }
        }

        if( next_format_prefix == current_format_prefix )
        {
            j++;
        }
        else
        {
            j = 1;
            next_format_prefix = current_format_prefix;
        }

        QString str2;
        str2.sprintf( QString(current_format_prefix + format + back_suffix).toStdString().c_str(), j);
        ui->dstList->addItem( str2 );
    }

    m_dstList.clear();
    for(int i = 0; i < ui->dstList->count(); ++i)
    {
        QListWidgetItem* item = ui->dstList->item(i);
        QString str = item->text();
        m_dstList.append(str);
    }
}

void QFileRenameTools::preview_click()
{
    QString root = ui->srcRoot->text();
    if(root.isEmpty() == false)
    {
        m_srcList.clear();
        this->traverseFiles(root);
        this->filterList1();
        this->generalList2();
    }
}

void QFileRenameTools::general_click()
{
    QString srcRoot = ui->srcRoot->text();
    QString dstRoot = ui->dstRoot->text();

    if(dstRoot.isEmpty() == true)
    {
        dstRoot = srcRoot;
    }

    if( m_srcList.count() == m_dstList.count() )
    {
        for(int i = 0; i < m_srcList.count(); ++i)
        {
            QFile::copy( m_srcList.at(i), QString( dstRoot + QString("/") + m_dstList.at(i)));
        }
    }
}

void QFileRenameTools::traverseFiles(QString filePath)
{
    QDir dir(filePath);
    dir.setFilter(QDir::Files | QDir::Dirs);
    dir.setSorting(QDir::Name);

    QFileInfoList fileInfoList = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.exists())
        {
            if(fileInfo.isDir())
            {
                this->traverseFiles(fileInfo.absoluteFilePath());
            }
            else if(fileInfo.isFile())
            {
                m_srcList.append( fileInfo.absoluteFilePath() );
            }
        }
    }
}

