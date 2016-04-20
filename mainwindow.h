#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QImage>

#include <QDebug>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true);
    cv::Mat QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData = true);
    QImage cvMatToQImage(const cv::Mat &inMat);
    QPixmap cvMatToQPixmap(const cv::Mat &inMat);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
