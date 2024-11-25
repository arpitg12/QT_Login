#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>
#include <QFrame>
#include <QPoint>
#include <QMouseEvent>
#include <dashboardwindow.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void onLoginClicked();
    void onCancelClicked();
    void onForgotPasswordClicked();
    void togglePasswordVisibility();
    void onMinimizeClicked();
    void onMaximizeClicked();
    void onCloseClicked();
    void toggleMaximized();

private:
    void setupUI();
    void setupStyles();
    void loadImages();
    void centerOnScreen();

private:
    // Title bar elements
    QFrame *titleBar;
    QPushButton *minimizeButton;
    QPushButton *maximizeButton;
    QPushButton *closeButton;
    QLabel *titleLabel;

    // Main layout components
    QWidget *centralWidget;
    QFrame *leftFrame;
    QFrame *rightFrame;
    QLabel *backgroundImageLabel;
    QTabWidget *tabWidget;

    // Login form elements
    QLabel *userIconLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordIconLabel;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *cancelButton;
    QLabel *forgotPasswordLabel;
    QPushButton *togglePasswordButton;

    // Background overlay elements
    QLabel *overlayLabel;
    QPixmap backgroundImage;
    QPixmap userIcon;
    QPixmap passwordIcon;
    QPixmap eyeIcon;

    // Window dragging
    bool isDragging;
    QPoint dragPosition;
};

#endif // MAINWINDOW_H