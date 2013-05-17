#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "video.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <qstring.h>
#include <sstream>
#include <QImage>
#include <QPixmap>
#include <QVariant>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QList>
#include <QBitmap>
#include <QPainter>
#include <QColor>
#include <QBuffer>
#include <QMessageBox>
#include <qtimer.h>
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

video *cur;
QTimer *timer;
double counter = 0;
QList<QColor> avgColorList;
QList<QColor> avgColorQuadListtl;
QList<QColor> avgColorQuadListtr;
QList<QColor> avgColorQuadListbl;
QList<QColor> avgColorQuadListbr;
QList<QColor> brightnessList;
QList<QColor> differenceList;
QList<QColor> moodList;
bool working = false;
QString filename;
QImage imageSave;
QColor difference;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if (cur != NULL) video_quit(cur);
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::timerDone() {
    if (!working) {
        working = true;
        int result;
        while((result = video_next(cur)) < -1);
        if(result != -1) {
            if (result == 0) {
                counter++;
                ui->statusBar->showMessage(QString("%1").arg(counter) + " frames processed.");
                QImage img(cur->pDat->data[0], cur->width, cur->height, QImage::Format_ARGB32);
                QBitmap bmp;
                bmp.fromData(QSize(cur->width, cur->height), cur->pDat->data[0]);

                QColor color;

                QColor avgColor;
                double avgColorRed = 0;
                double avgColorGreen = 0;
                double avgColorBlue = 0;

                QColor avgColortl;
                double avgColorRedtl = 0;
                double avgColorGreentl = 0;
                double avgColorBluetl = 0;
                QColor avgColortr;
                double avgColorRedtr = 0;
                double avgColorGreentr = 0;
                double avgColorBluetr = 0;
                QColor avgColorbl;
                double avgColorRedbl = 0;
                double avgColorGreenbl = 0;
                double avgColorBluebl = 0;
                QColor avgColorbr;
                double avgColorRedbr = 0;
                double avgColorGreenbr = 0;
                double avgColorBluebr = 0;

                QColor brightness;
                double avg = 0;

                double diffRed = 0;
                double diffGreen = 0;
                double diffBlue = 0;

                double moodRed = 0;
                double moodGreen = 0;
                double moodBlue = 0;

                for (int w = 0; w < img.width(); w++) {
                    for (int h = 0; h < img.height(); h++) {
                        color = img.pixel(QPoint(w,h));
                        if (w < img.width() / 2 && h < img.height() / 2) {
                            avgColorRedtl += color.red();
                            avgColorGreentl += color.green();
                            avgColorBluetl += color.blue();
                        } else if (w > img.width() / 2 && h < img.height() / 2) {
                            avgColorRedtr += color.red();
                            avgColorGreentr += color.green();
                            avgColorBluetr += color.blue();
                        } else if (w < img.width() / 2 && h > img.height() / 2) {
                            avgColorRedbl += color.red();
                            avgColorGreenbl += color.green();
                            avgColorBluebl += color.blue();
                        } else if (w > img.width() / 2 && h > img.height() / 2) {
                            avgColorRedbr += color.red();
                            avgColorGreenbr += color.green();
                            avgColorBluebr += color.blue();
                        }
                        avgColorRed += color.red();
                        avgColorGreen += color.green();
                        avgColorBlue += color.blue();
                        avg += ((color.red() + color.green() + color.blue()) / 3);

                        if (!imageSave.isNull() && (int)counter % 2) {
                            QColor subtractColor = imageSave.pixel(QPoint(w,h));
                            diffRed += color.red();
                            diffGreen += color.green();
                            diffBlue += color.blue();
                        }

                        // MoodBar
                        if (h < img.height() / 3) {
                            moodRed += color.red();
                        } else if (h > (img.height() / 3) *2) {
                            moodBlue += color.green();
                        } else {
                            moodGreen += color.blue();
                        }
                    }
                }

                // Average Color (Whole Image)
                avgColor.setRed(avgColorRed / (img.width() * img.height()));
                avgColor.setGreen(avgColorGreen / (img.width() * img.height()));
                avgColor.setBlue(avgColorBlue / (img.width() * img.height()));
                avgColorList << avgColor;

                QImage avgColorDisplayImage(avgColorList.size(),20,QImage::Format_RGB32);
                QPainter a(&avgColorDisplayImage);
                for (int i = 0; i < avgColorList.size(); i+=1) {
                    QPen chPen(avgColorList.at(i), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
                    a.setPen(chPen);
                    a.drawLine(i, 0, i, 20);

                }
                ui->averageDisplay->setPixmap(QPixmap::fromImage(avgColorDisplayImage));
                ui->averageDisplay->setMaximumSize(ui->pushButton_2->window()->width() - 50, 20);

                // Average Color (Quad)
                avgColortl.setRed(avgColorRedtl / ((img.width() / 2) * (img.height() / 2)));
                avgColortl.setGreen(avgColorGreentl / ((img.width() / 2) * (img.height() / 2)));
                avgColortl.setBlue(avgColorBluetl / ((img.width() / 2) * (img.height() / 2)));

                avgColortr.setRed(avgColorRedtr / ((img.width() / 2) * (img.height() / 2)));
                avgColortr.setGreen(avgColorGreentr / ((img.width() / 2) * (img.height() / 2)));
                avgColortr.setBlue(avgColorBluetr / ((img.width() / 2) * (img.height() / 2)));

                avgColorbl.setRed(avgColorRedbl / ((img.width() / 2) * (img.height() / 2)));
                avgColorbl.setGreen(avgColorGreenbl / ((img.width() / 2) * (img.height() / 2)));
                avgColorbl.setBlue(avgColorBluebl / ((img.width() / 2) * (img.height() / 2)));

                avgColorbr.setRed(avgColorRedbr / ((img.width() / 2) * (img.height() / 2)));
                avgColorbr.setGreen(avgColorGreenbr / ((img.width() / 2) * (img.height() / 2)));
                avgColorbr.setBlue(avgColorBluebr / ((img.width() / 2) * (img.height() / 2)));
                if (avgColortl.isValid() && avgColortr.isValid() && avgColorbl.isValid() && avgColorbr.isValid()) {
                    avgColorQuadListtl << avgColortl;
                    avgColorQuadListtr << avgColortr;
                    avgColorQuadListbl << avgColorbl;
                    avgColorQuadListbr << avgColorbr;
                }
                QImage avgColorQuadDisplayImage(avgColorQuadListtl.size(),40,QImage::Format_RGB32);
                QPainter q(&avgColorQuadDisplayImage);

                for (int i = 0; i < avgColorQuadListtl.size(); i++) {
                    QPen chPen(avgColorQuadListtl.at(i), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
                    q.setPen(chPen);
                    q.drawLine(i, 0, i, 10);
                    chPen.setColor(avgColorQuadListtr.at(i));
                    q.setPen(chPen);
                    q.drawLine(i, 10, i, 20);
                    chPen.setColor(avgColorQuadListbl.at(i));
                    q.setPen(chPen);
                    q.drawLine(i, 20, i, 30);
                    chPen.setColor(avgColorQuadListbr.at(i));
                    q.setPen(chPen);
                    q.drawLine(i, 30, i, 40);
                }
                ui->averageQuadDisplay->setPixmap(QPixmap::fromImage(avgColorQuadDisplayImage));
                ui->averageQuadDisplay->setMaximumSize(ui->pushButton_2->window()->width() - 50,40);

                // Brightness (Grayscale)
                avg = avg /  (img.width() * img.height());
                brightness.setRed(avg);
                brightness.setGreen(avg);
                brightness.setBlue(avg);

                brightnessList << brightness;
                QImage brightnessDisplayImage(brightnessList.size(),20,QImage::Format_RGB32);
                QPainter b(&brightnessDisplayImage);
                for (int i = 0; i < brightnessList.size(); i++) {
                    QPen chPen(brightnessList.at(i), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
                    b.setPen(chPen);
                    b.drawLine(i, 0, i, 20);
                }
                ui->brightnessDisplay->setPixmap(QPixmap::fromImage(brightnessDisplayImage));
                ui->brightnessDisplay->setMaximumSize(ui->pushButton_2->window()->width() - 50, 20);

                // Difference
                QColor colorSubtract = avgColorList.at(avgColorList.length() - 1);
                difference.setRed(abs(avgColorRed-diffRed) / (img.width() * img.height()));
                difference.setGreen(abs(avgColorGreen-diffGreen) / (img.width() * img.height()));
                difference.setBlue(abs(avgColorBlue-diffBlue) / (img.width() * img.height()));
                if (difference.isValid()) differenceList << difference;

                QImage differenceDisplayImage(differenceList.size(),20,QImage::Format_RGB32);
                QPainter d(&differenceDisplayImage);
                for (int i = 0; i < differenceList.size(); i++) {
                    QPen chPen(differenceList.at(i), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
                    d.setPen(chPen);
                    d.drawLine(i, 0, i, 20);
                }
                ui->differenceDisplay->setPixmap(QPixmap::fromImage(differenceDisplayImage));
                ui->differenceDisplay->setMaximumSize(ui->pushButton_2->window()->width() - 50, 20);

                // MoodBar
                QColor moodBarColor;
                double total = 255;
                double faktorMax = (((img.height() / 3) * img.width()) * 255);
                double faktor = total / faktorMax;
                moodBarColor.setRed(moodRed * faktor);
                moodBarColor.setGreen(moodGreen * faktor);
                moodBarColor.setBlue(moodBlue * faktor);
                if (moodBarColor.isValid()) moodList << moodBarColor;
                QImage moodDisplayImage(moodList.size(),20,QImage::Format_RGB32);
                QPainter g(&moodDisplayImage);
                for (int j = 0; j < moodList.size(); j++) {
                    QPen chPen(moodList.at(j), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
                    g.setPen(chPen);
                    g.drawLine(j, 0, j, 20);
                }
                ui->moodDisplay->setPixmap(QPixmap::fromImage(moodDisplayImage));
                ui->moodDisplay->setMaximumSize(ui->pushButton_2->window()->width() - 50, 20);

                // Video view
                ui->label->setPixmap(QPixmap::fromImage(img));
                ui->label->show();

                ui->pushButton_2->update();
                ui->label->update();
                if ((int)counter % 2) imageSave = img;
                qApp->processEvents();
            }
        } else {
            ui->pushButton_2->setText("Start Analysis");
            ui->pushButton->setEnabled(false);
            working = false;
            timer->stop();
        }
        working = false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->pushButton_2->text() == "Start Analysis") {
        ui->pushButton->setEnabled(true);
        counter = 0;
        avgColorList.clear();
        avgColorQuadListtl.clear();
        avgColorQuadListtr.clear();
        avgColorQuadListbl.clear();
        avgColorQuadListbr.clear();
        brightnessList.clear();
        differenceList.clear();
        moodList.clear();
        working = false;
        timer = new QTimer(this);
        counter = 0;

        filename = QFileDialog::getOpenFileName(this, tr("Open any Video File"), ".", tr("All Files (*.*)"));

        if (!filename.isNull()) {
                cur = video_init(filename.toLatin1().data(), 0, 0, PIX_FMT_RGBA32);
                if (cur == NULL) {
                    ui->pushButton->setEnabled(false);
                    timer->stop();
                    ui->pushButton_2->setText("Start Analysis");
                    QMessageBox msgBox;
                    msgBox.critical(this,"Error", "This is not a video or image file.\nCould not initialize video.");
                } else {
                    ui->saveButton->setEnabled(true);
                    connect( timer, SIGNAL(timeout()), this, SLOT(timerDone()) );
                    timer->start(10);
                    ui->pushButton_2->setText("Stop Analysis");
                }
        }
    } else {
        ui->pushButton->setEnabled(false);
        timer->stop();
        ui->pushButton_2->setText("Start Analysis");
    }
}

void MainWindow::on_saveButton_clicked()
{
    ui->averageDisplay->pixmap()->save(filename + "-averageDisplay.bmp", "BMP");
    ui->averageQuadDisplay->pixmap()->save(filename + "-averageQuadDisplay.bmp", "BMP");
    ui->brightnessDisplay->pixmap()->save(filename + "-brightnessDisplay.bmp", "BMP");
}

void MainWindow::on_pushButton_clicked()
{
    for(int i = 0; i < ui->spinBox->value(); i++) {
        video_next(cur);
    }
}
