
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QMimeData>

#include <widgets/historyitem.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_copyed(false)
{
    ui->setupUi(this);

    connect(qApp->clipboard(), &QClipboard::dataChanged, this, &MainWindow::slot_dataChanged);
    connect(ui->c_text, &QCheckBox::clicked, this, &MainWindow::recheck);
    connect(ui->c_image, &QCheckBox::clicked, this, &MainWindow::recheck);

    QList<int> sizes;
    sizes << 250 << 750;
    ui->splitter->setSizes(sizes);
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot_dataChanged()
{
    if (m_copyed)
    {
        m_copyed = false;
        return;
    }
    auto clipboard = qApp->clipboard();
    const QMimeData *data = clipboard->mimeData();
    auto atext = data->hasText();
    auto aimage =  data->hasImage();

    HistoryItem *history = nullptr;
    int rows = ui->list_historys->count();
    if (rows != 0)
    {
        auto item = ui->list_historys->item(rows - 1);
        auto item_widget = ui->list_historys->itemWidget(item);
        history = qobject_cast<HistoryItem *>(item_widget);
    }

    if (atext)
    {
        if (history
                && history->type() == HistoryItem::Text
                && history->text().compare(data->text()) == 0)
        {
            return;
        }

        auto item = new QListWidgetItem;
        auto item_widget = new HistoryItem;
        item_widget->setText(data->text());

        ui->list_historys->addItem(item);
        item->setSizeHint(item_widget->sizeHint());
        ui->list_historys->setItemWidget(item, item_widget);
    }

    QPixmap image = clipboard->pixmap();
    if (aimage && image.isNull() == false)
    {

        if (history
                && history->type() == HistoryItem::Image
                && history->image().toImage() == image.toImage())
        {
            return;
        }

        auto item = new QListWidgetItem;
        auto item_widget = new HistoryItem;
        item_widget->setImage(image);

        ui->list_historys->addItem(item);
        item->setSizeHint(item_widget->sizeHint());
        ui->list_historys->setItemWidget(item, item_widget);
    }

    recheck();
}

void MainWindow::recheck()
{
    auto cts = ui->c_text->checkState();
    auto cis = ui->c_image->checkState();
    if (cts == Qt::Unchecked && cis == Qt::Unchecked)
    {
        int rows = ui->list_historys->count();
        for (int i = 0; i < rows; ++i)
        {
            auto item = ui->list_historys->item(i);
            item->setHidden(false);
        }
    }
    else
    {
        int rows = ui->list_historys->count();
        for (int i = 0; i < rows; ++i)
        {
            auto item = ui->list_historys->item(i);
            auto item_widget = ui->list_historys->itemWidget(item);
            auto history = qobject_cast<HistoryItem *>(item_widget);

            if (cts == Qt::Checked && history->type() == HistoryItem::Text)
            {
                item ->setHidden(false);
                continue;
            }

            if (cis == Qt::Checked && history->type() == HistoryItem::Image)
            {
                item ->setHidden(false);
                continue;
            }

            item->setHidden(true);
        }
    }
}

void MainWindow::on_list_historys_itemClicked(QListWidgetItem *item)
{
    auto item_widget = ui->list_historys->itemWidget(item);
    auto history = qobject_cast<HistoryItem *>(item_widget);
    if (history)
    {
        switch (history->type())
        {
            case HistoryItem::Text:
                ui->tabWidget->setCurrentWidget(ui->tab_text);
                ui->view_text->setPlainText(history->text());
                break;
            case HistoryItem::Image:
                ui->tabWidget->setCurrentWidget(ui->tab_image);
                QPixmap pixmap = history->image().scaled(ui->view_image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->view_image->setPixmap(pixmap);
                break;
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    auto item = ui->list_historys->currentItem();
    if (item)
    {
        auto item_widget = ui->list_historys->itemWidget(item);
        auto history = qobject_cast<HistoryItem *>(item_widget);
        if (history->type() == HistoryItem::Image)
        {
            QPixmap pixmap = history->image().scaled(ui->view_image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->view_image->setPixmap(pixmap);
        }
    }
}


void MainWindow::on_btn_copy_clicked()
{
//    disconnect(qApp->clipboard());

    auto item = ui->list_historys->currentItem();
    if (item)
    {
        m_copyed = true;
        auto item_widget = ui->list_historys->itemWidget(item);
        auto history = qobject_cast<HistoryItem *>(item_widget);
        if (history->type() == HistoryItem::Text)
        {
            qApp->clipboard()->setText(history->text());
        }
        if (history->type() == HistoryItem::Image)
        {
            qApp->clipboard()->setPixmap(history->image());
        }
    }

//    connect(qApp->clipboard(), &QClipboard::dataChanged, this, &MainWindow::slot_dataChanged);
}

