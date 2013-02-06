#include "mainwindow.h"
#include "ui_mainwindow.h"


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
void MainWindow::BindImage(const std::string &f_str)
{
    cv::Mat result_img = cv::Mat(WIN_H, WIN_W*6, CV_8UC3);
    cv::Mat mono_img = cv::Mat(WIN_H, WIN_W, CV_8UC3);

    static const int cubeIndex[CUBE_NUM] = {0, 2, 4, 5, 3, 1};

    for (int i = 0; i < CUBE_NUM; ++i) {
        cv::Mat org_img = cv::imread(filepath_[cubeIndex[i]].c_str());
        cv::resize(org_img, mono_img, mono_img.size());

        if(i == 2 || i == 3) {
//            cv::flip(mono_img, mono_img, -1);
//            cv::flip(mono_img, mono_img, -1);
            transpose(mono_img, mono_img);
            cv::flip(mono_img, mono_img, 1);
        }

        cv::Rect roi_rect;
        roi_rect.x = WIN_W * i;
        roi_rect.width = WIN_W;
        roi_rect.height = WIN_H;
        cv::Mat roi(result_img, roi_rect);
        mono_img.copyTo(roi);
    }
    cv::imwrite(f_str.c_str(), result_img);

}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
void MainWindow::BindCubeMap()
{
    bool isFillImage = true;
    for (int i = 0; i < CUBE_NUM; ++i) {
        if(filepath_[i].empty()) {
            std::stringstream sfm;
            sfm << "Not set full.";

            QMessageBox msgBox(this);
            msgBox.setText(tr(sfm.str().c_str()));
            msgBox.exec();
            isFillImage = false;
            break;
        }
    }

    if (isFillImage) {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Image File"), "",
            tr("Image File (*.jpg *.png *.bmp);;All Files (*)"));


        if(!fileName.isEmpty()) {
            std::string f_str = fileName.toLocal8Bit().constData();
            BindImage(f_str);
            QMessageBox msgBox(this);
            msgBox.setText(tr("Saved image."));
            msgBox.exec();
        }
    }
}
