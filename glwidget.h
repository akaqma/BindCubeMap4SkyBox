#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QImage>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>

#include <opencv2/opencv.hpp>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    
signals:
    void AddImagePath(const std::string& path);
    
public slots:
    void BtnSetImage();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void setImage(const cv::Mat_<cv::Vec3b> &img);
    
private:
    QImage  img_;
    GLuint  texId_;
    bool    updated_;
};

#endif // GLWIDGET_H
