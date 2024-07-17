#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QWidget>

namespace Ui {
class HistoryItem;
}

class HistoryItem : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryItem(QWidget *parent = nullptr);
    ~HistoryItem();

    enum HistoryType {
        Text,
        Image,
    };

    QString text() const;
    void setText(const QString &newText);

    QPixmap image() const;
    void setImage(const QPixmap &newImage);

    HistoryType type() const;
    void setType(HistoryType newType);

private:
    Ui::HistoryItem *ui;

    QString m_text;
    QPixmap m_image;
    HistoryType m_type;
};

#endif // HISTORYITEM_H
