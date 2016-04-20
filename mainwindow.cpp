#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // load qimage
    QImage image(":/res/pic.jpg");

    // create mat and convert qimage to mat
    cv::Mat tempMat = QImageToCvMat(image);

    // create grayscale mat
    cv::Mat grayMat(tempMat.size(), CV_8U);

    // convert color space
    cv::cvtColor(tempMat, grayMat, CV_BGR2GRAY);

    // create binary mat
    cv::Mat binaryMat(grayMat.size(), grayMat.type());

    // thresholding
    cv::threshold(grayMat, binaryMat, 100, 255, cv::THRESH_BINARY);

    // convert mat to qpixmap
    QPixmap result = cvMatToQPixmap(binaryMat);

    ui->label->setPixmap(result);
}

MainWindow::~MainWindow()
{
    delete ui;
}

cv::Mat MainWindow::QImageToCvMat(const QImage &inImage, bool inCloneImageData)
{
    switch (inImage.format())
    {
    case QImage::Format_RGB32: // 8-bit, 4 channel
    {
        cv::Mat  mat(inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine());

        return (inCloneImageData ? mat.clone() : mat);
    }
    case QImage::Format_RGB888: // 8-bit, 3 channel
    {
        if (!inCloneImageData)
            qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";

        QImage swapped = inImage.rgbSwapped();

        return cv::Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine()).clone();
    }
    case QImage::Format_Indexed8: // 8-bit, 1 channel
    {
        cv::Mat  mat(inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine());

        return (inCloneImageData ? mat.clone() : mat);
    }

    default:
        qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
    }

    return cv::Mat();
}

cv::Mat MainWindow::QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData)
{
    return QImageToCvMat(inPixmap.toImage(), inCloneImageData);
}

QImage MainWindow::cvMatToQImage(const cv::Mat &inMat)
{
    switch (inMat.type())
    {
    case CV_8UC4: // 8-bit, 4 channel
    {
        QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32);

        return image;
    }
    case CV_8UC3: // 8-bit, 3 channel
    {
        cv::cvtColor(inMat, inMat, CV_BGR2RGB);
        QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888);

        return image;
    }
    case CV_8UC1: // 8-bit, 1 channel
    {
        static QVector<QRgb>  sColorTable;

        // only create our color table once
        if (sColorTable.isEmpty())
        {
            for (int i = 0; i < 256; ++i)
                sColorTable.push_back(qRgb(i, i, i));
        }

        QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8);

        image.setColorTable(sColorTable);

        return image;
    }

    default:
        qDebug() << "cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

QPixmap MainWindow::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(cvMatToQImage(inMat));
}
