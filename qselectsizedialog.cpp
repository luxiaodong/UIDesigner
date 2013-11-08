#include "qselectsizedialog.h"
#include "ui_qselectsizedialog.h"

QSelectSizeDialog::QSelectSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSelectSizeDialog)
{
    ui->setupUi(this);
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(clickOk()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

QSelectSizeDialog::~QSelectSizeDialog()
{
    delete ui;
}

void QSelectSizeDialog::clickOk()
{
    m_width = ui->spinWidth->value();
    m_height = ui->spinHeight->value();
    m_rootClassName = ui->comboBox->currentText();
    this->accept();
}
