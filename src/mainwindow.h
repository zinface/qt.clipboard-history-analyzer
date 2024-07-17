
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE
namespace Ui
{
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slot_dataChanged();

    void recheck();

private slots:
    void on_list_historys_itemClicked(QListWidgetItem *item);

    void on_btn_copy_clicked();

private:
    Ui::MainWindow *ui;
    bool m_copyed;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // MAINWINDOW_H

