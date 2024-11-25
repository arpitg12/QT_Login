#include "mainwindow.h"
#include "dashboardwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsEffect>
#include <QScreen>
#include <QApplication>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QMouseEvent>
#include <QMessageBox>

void MainWindow::onMinimizeClicked()
{
    this->showMinimized(); // Minimize the window
}

void MainWindow::onMaximizeClicked()
{
    toggleMaximized(); // Toggle between maximized and normal size
}

void MainWindow::onCloseClicked()
{
    this->close(); // Close the application
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isDragging(false)
{
    loadImages();
    setupUI();
    setupStyles();
    centerOnScreen();
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadImages()
{
    // Load and prepare the background image with business people silhouettes
 // Load the images
backgroundImage = QPixmap("../assests/img/stockImage2.jpg");
userIcon = QPixmap("../assests/img/user_icon.png");
passwordIcon = QPixmap("../assests/img/key_icon.png");
eyeIcon = QPixmap("../assests/img/eye.jpg");

// Scale the background image to cover the widget size
  QSize widgetSize = QSize(400, 450); // Adjust to the container's size
  backgroundImage = backgroundImage.scaled(widgetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);


// Create a clean background without any overlay or blur
    QImage image = backgroundImage.toImage();
    backgroundImage = QPixmap::fromImage(image);
  


// Use the processed background image (e.g., for painting or setting in a QLabel)

}

void MainWindow::setupUI()
{
    // Set window properties
    setWindowTitle("QuantoTrade");
    setFixedSize(800, 450);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Create central widget with main layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainVLayout = new QVBoxLayout(centralWidget);
    mainVLayout->setSpacing(0);
    mainVLayout->setContentsMargins(0, 0, 0, 0);

    // Title bar
    titleBar = new QFrame;
    titleBar->setFixedHeight(30);
    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(10, 0, 0, 0);

    // Window title
    titleLabel = new QLabel("QuantoTrade");
    titleLabel->setStyleSheet("color: #333; font-weight: bold; font-size: 12px;");

    // Window controls
    QWidget *windowControls = new QWidget;
    QHBoxLayout *controlsLayout = new QHBoxLayout(windowControls);
    controlsLayout->setSpacing(0);
    controlsLayout->setContentsMargins(0, 0, 0, 0);

    minimizeButton = new QPushButton("−");
    maximizeButton = new QPushButton("□");
    closeButton = new QPushButton("×");

    for(auto btn : {minimizeButton, maximizeButton, closeButton}) {
        btn->setFixedSize(45, 30);
        controlsLayout->addWidget(btn);
    }
maximizeButton->setEnabled(false); // Disable maximize button

    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(windowControls);

    // Main content
    QWidget *contentWidget = new QWidget;
    QHBoxLayout *contentLayout = new QHBoxLayout(contentWidget);
    contentLayout->setSpacing(0);
    contentLayout->setContentsMargins(0, 0, 0, 0);

    // Left frame with background
    leftFrame = new QFrame;
    leftFrame->setFixedWidth(400);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftFrame);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    // Create background with overlay
   backgroundImageLabel = new QLabel;
    backgroundImageLabel->setFixedSize(400, 450);
    backgroundImageLabel->setAlignment(Qt::AlignCenter); // Center the image
    backgroundImageLabel->setPixmap(backgroundImage);
    backgroundImageLabel->setScaledContents(false); 

    // // Modern gradient overlay
    // QString overlayStyle = "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    //                        "stop:0 rgba(41, 128, 185, 0.7),"
    //                        "stop:1 rgba(44, 62, 80, 0.8));";
    // overlayLabel = new QLabel(backgroundImageLabel);
    // overlayLabel->setGeometry(0, 0, 400, 450);
    // overlayLabel->setStyleSheet(overlayStyle);

    leftLayout->addWidget(backgroundImageLabel);

    // Right frame with login form
    rightFrame = new QFrame;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightFrame);
    rightLayout->setContentsMargins(40, 20, 40, 20);

    // Tab widget
    tabWidget = new QTabWidget;

    // Login tab
    QWidget *loginTab = new QWidget;
    QVBoxLayout *loginLayout = new QVBoxLayout(loginTab);
    loginLayout->setSpacing(25); // Increased spacing

    // Username field with icon
    QWidget *userWidget = new QWidget;
    QHBoxLayout *userLayout = new QHBoxLayout(userWidget);
    userLayout->setContentsMargins(0, 20, 0, 0);

    userIconLabel = new QLabel;
    userIconLabel->setPixmap(userIcon.scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("User Name");

    userLayout->addWidget(userIconLabel);
    userLayout->addWidget(usernameEdit);

    // Password field with icon and toggle button
    QWidget *passWidget = new QWidget;
    QHBoxLayout *passLayout = new QHBoxLayout(passWidget);
    passLayout->setContentsMargins(0, 0, 0, 0);

    passwordIconLabel = new QLabel;
    passwordIconLabel->setPixmap(passwordIcon.scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    togglePasswordButton = new QPushButton;
    togglePasswordButton->setIcon(QIcon(eyeIcon));
    togglePasswordButton->setFixedSize(30, 30);

    passLayout->addWidget(passwordIconLabel);
    passLayout->addWidget(passwordEdit);
    passLayout->addWidget(togglePasswordButton);

    // Forgot password link
    forgotPasswordLabel = new QLabel("<a href='#'>Forgot Password?</a>");
    forgotPasswordLabel->setAlignment(Qt::AlignRight);
    forgotPasswordLabel->setCursor(Qt::PointingHandCursor);

    // Buttons with modern styling
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setSpacing(15);

    loginButton = new QPushButton("Login");
    loginButton->setFixedSize(150, 40);
    loginButton->setCursor(Qt::PointingHandCursor);
    loginButton->setObjectName("loginButton");  // Set object name here

    cancelButton = new QPushButton("Cancel");
    cancelButton->setFixedSize(150, 40);
    cancelButton->setCursor(Qt::PointingHandCursor);
    cancelButton->setObjectName("cancelButton");  // Set object name here

    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Add all elements to login layout
    loginLayout->addStretch();
    loginLayout->addWidget(userWidget);
    loginLayout->addWidget(passWidget);
    loginLayout->addWidget(forgotPasswordLabel);
    loginLayout->addSpacing(20);
    loginLayout->addLayout(buttonLayout);
    loginLayout->addStretch();

    // Add tabs
    tabWidget->addTab(loginTab, "Login");
    tabWidget->addTab(new QWidget, "Workspace");

    rightLayout->addWidget(tabWidget);

    // Add widgets to layouts
    contentLayout->addWidget(leftFrame);
    contentLayout->addWidget(rightFrame);

    mainVLayout->addWidget(titleBar);
    mainVLayout->addWidget(contentWidget);

    // Connect signals
    connect(minimizeButton, &QPushButton::clicked, this, &MainWindow::showMinimized);
    connect(maximizeButton, &QPushButton::clicked, this, &MainWindow::toggleMaximized);
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(cancelButton, &QPushButton::clicked, this, &MainWindow::onCancelClicked);
    connect(forgotPasswordLabel, &QLabel::linkActivated, this, &MainWindow::onForgotPasswordClicked);
    connect(togglePasswordButton, &QPushButton::clicked, this, &MainWindow::togglePasswordVisibility);

    // Make window draggable
    titleBar->installEventFilter(this);
}

void MainWindow::toggleMaximized()
{
    if (isMaximized()) {
        showNormal();
        maximizeButton->setText("□");
    } else {
        showMaximized();
        maximizeButton->setText("❐");
    }
}

void MainWindow::setupStyles()
{
    // Apply stylesheet
    setStyleSheet(R"(
        QMainWindow {
            background: white;
        }
        QWidget#centralWidget {
            background: white;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        /* Title bar styles */
        QPushButton#minimizeButton, QPushButton#maximizeButton {
            background: transparent;
            border: none;
            color: #666;
            font-size: 16px;
        }
        QPushButton#closeButton {
            background: transparent;
            border: none;
            color: #666;
            font-size: 16px;
        }
        QPushButton#minimizeButton:hover, QPushButton#maximizeButton:hover {
            background: #e0e0e0;
            color: #333;
        }
        QPushButton#closeButton:hover {
            background: #e81123;
            color: white;
        }
        /* Tab styles */
        QTabWidget::pane {
            border: none;
            background: white;
        }
        QTabBar::tab {
            padding: 8px 30px;
            background: transparent;
            border: none;
            font-size: 13px;
        }
        QTabBar::tab:selected {
            color: #2196F3;
            border-bottom: 2px solid #2196F3;
        }
        QTabBar::tab:!selected {
            color: #666;
        }
        /* Input field styles */
        QLineEdit {
            border: none;
            border-bottom: 1px solid #DDD;
            padding: 8px 0;
            font-size: 14px;
            selection-background-color: #2196F3;
        }
        QLineEdit:focus {
            border-bottom: 2px solid #2196F3;
        }
        QLineEdit::placeholder {
            color: #999;
        }
        /* Button styles */
        QPushButton#loginButton {
            background-color: #2196F3; /* Login button color in hex (blue) */
            color: white;
            border: none;
            border-radius: 4px;
            font-size: 14px;
            font-weight: bold;
            padding: 8px 16px; /* Add padding for better appearance */
        }
        QPushButton#loginButton:hover {
            background-color: #1976D2; /* Darker blue on hover */
        }
        QPushButton#cancelButton {
            background-color: #FF0000; /* Cancel button color in hex (red) */
            color: white;
            border: none;
            border-radius: 4px;
            font-size: 14px;
            font-weight: bold;
            padding: 8px 16px; /* Add padding for better appearance */
        }
        QPushButton#cancelButton:hover {
            background-color: darkred; /* Darker red on hover */
        }
        QPushButton#togglePasswordButton {
            border: none;
            background: transparent;
        }
        QPushButton#togglePasswordButton:hover {
            background-color: #f0f0f0;
            border-radius: 15px;
        }
        /* Link style */
        QLabel[href] {
            color: #2196F3;
        }
        QLabel[href]:hover {
            color: #1976D2;
        }
    )");

    // Set object names
    minimizeButton->setObjectName("minimizeButton");
    maximizeButton->setObjectName("maximizeButton");
    closeButton->setObjectName("closeButton");
    centralWidget->setObjectName("centralWidget");
}

void MainWindow::centerOnScreen()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void MainWindow::onLoginClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    // Example of simple authentication logic
    if (username == "a" && password == "1") {

            DashboardWindow *dashboard = new DashboardWindow(username);
            dashboard->show();
            this->close();

        // Proceed with login actions
    } else {
        QMessageBox::warning(this, "Login", "Incorrect username or password.");
    }
}

void MainWindow::onCancelClicked()
{
    close();
}

void MainWindow::onForgotPasswordClicked()
{
    // Implement forgot password functionality
}

void MainWindow::togglePasswordVisibility()
{
    if (passwordEdit->echoMode() == QLineEdit::Password) {
        passwordEdit->setEchoMode(QLineEdit::Normal);
        togglePasswordButton->setIcon(QIcon("../assests/img/eye_off.jpg"));
    } else {
        passwordEdit->setEchoMode(QLineEdit::Password);
        togglePasswordButton->setIcon(QIcon("../assests/img/eye.jpg"));
    }
}

// Add mouse event handlers to enable window dragging
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft(); // Use globalPosition and convert to QPoint
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging) {
        move(event->globalPosition().toPoint() - dragPosition); // Use globalPosition and convert to QPoint
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        event->accept();
    }
}
