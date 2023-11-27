#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "asmOpenCV.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cv::Mat image = cv::imread("/home/thomas/Documents/Dev/c++/ImPViewer/lena.jpg");

    // Check if the image is loaded successfully
    if (image.empty()){
        ui->label->setText("Error: Couldn't open the image file");
    } else {
        // Convert OpenCV mat to Qt Image
        QImage img = ASM::cvMatToQImage( image );
        //QImage img(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_Grayscale8);

        if (img.isNull()) {
                ui->label->setText("Error: Couldn't convert the image to QImage.");
        } else {
            // Display the image on the QLabel
            ui->label->setPixmap(QPixmap::fromImage(img));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_importButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp);;All Files (*)"));

    cv::Mat image = cv::imread(filePath.toStdString());
    // Check if the image is loaded successfully
    if (image.empty()){
        ui->label->setText("Error: Couldn't open the image file");
    } else {
        // Convert OpenCV mat to Qt Image
        QImage img = ASM::cvMatToQImage( image );
        //QImage img(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_Grayscale8);

        if (img.isNull()) {
                ui->label->setText("Error: Couldn't convert the image to QImage.");
        } else {
            // Display the image on the QLabel
            ui->label->setPixmap(QPixmap::fromImage(img));
        }
    }
}


void MainWindow::on_blurButton_clicked()
{
    QPixmap mimage(ui->label->pixmap(Qt::ReturnByValue));
    QImage image = mimage.toImage();

    // qDebug() << "taile" << image.size();

    cv::Mat CVimage (image.height(),  image.width(), CV_8UC4, image.bits(),  image.bytesPerLine());
    cv::Mat blurredMat(image.height(),  image.width(), CV_8UC4);
    cv::medianBlur(CVimage, blurredMat, 11);

    QImage blurredImage = ASM::cvMatToQImage(blurredMat);
    ui->label->setPixmap(QPixmap::fromImage(blurredImage));

}


void MainWindow::on_bwConvertionButton_clicked()
{
    QPixmap mimage(ui->label->pixmap(Qt::ReturnByValue));
    QImage image = mimage.toImage();


    cv::Mat CVimage (image.height(),  image.width(), CV_8UC4, image.bits(),  image.bytesPerLine());
    cv::Mat greyImage(image.height(), image.width(), CV_8UC4);

    cv::cvtColor(CVimage, greyImage, cv::COLOR_BGR2GRAY);

    QImage bwImage = ASM::cvMatToQImage(greyImage);
    ui->label->setPixmap(QPixmap::fromImage(bwImage));
}

