#include <mainwindow.h>
#include "dashboardwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QDateTime>
#include <QIcon>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

DashboardWindow::DashboardWindow(const QString& username, QWidget *parent)
    : QMainWindow(parent), username(username)
{
    // Set window title and size
    setWindowTitle("User: " + username);
    resize(1500, 40);

    // Create menu bar
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Create the "QT" menu
    QMenu *qtMenu = menuBar->addMenu("QT");

    // Add actions to the "QT" menu
    QAction *saveWorkspaceAction = new QAction("Save Workspace", this);
    QAction *loadWorkspaceAction = new QAction("Load Workspace", this);
    QAction *changePasswordAction = new QAction("Change Password", this);
    QAction *logoutAction = new QAction("Logout", this);

    // Add actions to the "QT" menu
    qtMenu->addAction(saveWorkspaceAction);
    qtMenu->addAction(loadWorkspaceAction);
    qtMenu->addAction(changePasswordAction);
    qtMenu->addAction(logoutAction);

    QMenu *viewMenu = menuBar->addMenu("VIEW");

    // Add actions to "VIEW" menu
    QAction *horizontalDashboardAction = new QAction("Horizontal Dashboard", this);
    QAction *manualBuyWindowAction = new QAction("Manual Buy Window", this);
    QAction *manualSellWindowAction = new QAction("Manual Sell Window", this);
    QAction *manualTradeAction = new QAction("Manual Trade", this);
    QAction *verticalDashboardAction = new QAction("Vertical Dashboard", this);

    // Add actions to the "VIEW" menu
    viewMenu->addAction(horizontalDashboardAction);
    viewMenu->addAction(manualBuyWindowAction);
    viewMenu->addAction(manualSellWindowAction);
    viewMenu->addAction(manualTradeAction);
    viewMenu->addAction(verticalDashboardAction);

    menuBar->addMenu("SETTINGS");
    menuBar->addMenu("ABOUT US");

    // Create widget for right side items
    QWidget* rightWidget = new QWidget(this);
    QHBoxLayout* rightLayout = new QHBoxLayout(rightWidget);
    rightLayout->setSpacing(10);
    rightLayout->setContentsMargins(0, 0, 10, 0);

    // Create notification icon with superscript count
    QLabel* notificationLabel = new QLabel(this);
    notificationLabel->setFixedSize(40, 40);
    notificationLabel->setText("🔔");

    // Add notification count
    QLabel* countLabel = new QLabel("0", this);
    countLabel->setFixedSize(22, 18);
    countLabel->setAlignment(Qt::AlignCenter);
    countLabel->setStyleSheet(R"(

        QLabel {
            background-color: transparent;
            color: white;
            border-radius: 7px;
            font-size: 10px;
        }
    )");

    // Stack notification icon and count
    QWidget* notificationWidget = new QWidget(this);
    QGridLayout* notifLayout = new QGridLayout(notificationWidget);
    notifLayout->addWidget(notificationLabel, 0, 0, Qt::AlignCenter);
    notifLayout->addWidget(countLabel, 0, 0, Qt::AlignRight | Qt::AlignTop);
    notifLayout->setContentsMargins(0, 0, 0, 0);

    // Add refresh icon
    QLabel* refreshLabel = new QLabel("⟳", this);

    // Add time label
    timeLabel = new QLabel(this);

    // Add lock icon
    QLabel* lockLabel = new QLabel("🔒", this);

    // Add all widgets to right layout
    rightLayout->addWidget(notificationWidget);
    rightLayout->addWidget(refreshLabel);
    rightLayout->addWidget(timeLabel);
    rightLayout->addWidget(lockLabel);

    // Set corner widget
    menuBar->setCornerWidget(rightWidget, Qt::TopRightCorner);

    // Setup timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DashboardWindow::updateTime);
    timer->start(1000);  // Update every second

    // Initial time update
    updateTime();

    // Set stylesheet
    setStyleSheet(R"(
        QMainWindow {
            background-color: white;
        }
        QMenuBar {
            background-color: rgb(0, 120, 215);
            color: white;
            min-height: 25px;
        }
        QMenuBar::item {
            background-color: rgb(0, 120, 215);
            color: white;
            padding: 5px 10px;
        }
        QLabel {
            color: white;
        }
        QMenuBar QLabel {
            padding: 0px 5px;
            font-size: 14px;
        }
    )");
}

DashboardWindow::~DashboardWindow()
{
    if (timer) {
        timer->stop();
        delete timer;
    }
}

void DashboardWindow::updateTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString formattedTime = currentTime.toString("dd-MMM-yyyy hh:mm:ss");
    timeLabel->setText(formattedTime);
}
