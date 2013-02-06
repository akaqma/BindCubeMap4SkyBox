#include "glwidget.h"

// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent), updated_(true)
{
}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
void GLWidget::initializeGL()
{
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texId_);
    glBindTexture(GL_TEXTURE_2D, texId_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // set QTimer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->setInterval(30);
    timer->setSingleShot(false);
    timer->start();
}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
void GLWidget::BtnSetImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image File"), "",
        tr("Image File (*.jpg *.png *.bmp);;All Files (*)"));

    if(!fileName.isEmpty()) {
        std::string f_str = fileName.toLocal8Bit().constData();

        cv::Mat_<cv::Vec3b> img = cv::imread(f_str, 1);
        if (img.empty()) {
            std::cout << "Load Image Error" << std::endl;
            exit(0);
        }
        cv::flip(img, img, 0);
        setImage(img);
        emit AddImagePath(f_str);
    }
}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
void GLWidget::paintGL()
{
    glViewport(0, 0, width(), height());

    glClearColor(0.96f, 0.96f, 0.96f, 0.96f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId_);

    if (!updated_) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_.width(),
                     img_.height(), 0, GL_BGR, GL_UNSIGNED_BYTE, img_.bits());
        updated_ = true;
    }

    glColor3d(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0);
    glVertex2d(-1.0, -1.0);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(1.0, -1.0);
    glTexCoord2d(1.0, 1.0);
    glVertex2d(1.0, 1.0);
    glTexCoord2d(0.0, 1.0);
    glVertex2d(-1.0, 1.0);

    glEnd();
}


// ----------------------------------------------------------------------
//
// ----------------------------------------------------------------------
void GLWidget::setImage(const cv::Mat_<cv::Vec3b> &img)
{
    img_ = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888);
    if (img_.isNull()) {
        std::cout << "Load Image Error" << std::endl;
        exit(0);
    }

    //img_ = QGLWidget::convertToGLFormat(img_);
    updated_ = false;
}






