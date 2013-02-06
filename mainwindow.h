#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    static const int CUBE_NUM = 6;
    static const int WIN_H = 512;
    static const int WIN_W = 512;

    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void ReceiveImagePath0(const std::string& path) { filepath_ [0] = path; }
    void ReceiveImagePath1(const std::string& path) { filepath_ [1] = path; }
    void ReceiveImagePath2(const std::string& path) { filepath_ [2] = path; }
    void ReceiveImagePath3(const std::string& path) { filepath_ [3] = path; }
    void ReceiveImagePath4(const std::string& path) { filepath_ [4] = path; }
    void ReceiveImagePath5(const std::string& path) { filepath_ [5] = path; }

    void BindCubeMap();

private:
    void BindImage(const std::string& f_str);

    Ui::MainWindow *ui;
    std::string filepath_[CUBE_NUM];
};

#endif // MAINWINDOW_H
