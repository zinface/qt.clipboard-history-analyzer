#include "historyitem.h"
#include "ui_historyitem.h"

#include <QDateTime>

HistoryItem::HistoryItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryItem)
{
    ui->setupUi(this);
}

HistoryItem::~HistoryItem()
{
    delete ui;
}

QString HistoryItem::text() const
{
    return m_text;
}

void HistoryItem::setText(const QString &newText)
{
    m_text = newText;
    setType(Text);

    ui->lab_type->setText("文本");
    ui->lab_time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

QPixmap HistoryItem::image() const
{
    return m_image;
}

void HistoryItem::setImage(const QPixmap &newImage)
{
    m_image = newImage;
    setType(Image);

    ui->lab_type->setText("图片");
    ui->lab_time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

HistoryItem::HistoryType HistoryItem::type() const
{
    return m_type;
}

void HistoryItem::setType(HistoryType newType)
{
    m_type = newType;
}
