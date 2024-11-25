#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>

class DashboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor accepts a username to personalize the window
    explicit DashboardWindow(const QString& username, QWidget *parent = nullptr);
    // Destructor to clean up resources
    ~DashboardWindow();

private slots:
    // Slot to update time every second
    void updateTime();

private:
    // Timer to update the time label periodically
    QTimer *timer;
    // QLabel to display the current time
    QLabel *timeLabel;
    // QString to store the username
    QString username;
};

#endif // DASHBOARDWINDOW_H
