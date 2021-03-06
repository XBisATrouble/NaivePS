#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <QDebug>
#include <QStandardPaths>
#include <QTranslator>
#include "graphicsview.h"
#include "dialog_gaussianblur.h"
#include "tools.h"
#include "histogram.h"
#include "medianfilter.h"
#include "gaussianblur.h"
#include "dialog_linear_gray.h"
#include "dialog_log_grey.h"
#include "dialog_power_grey.h"
#include "dialog_exp_transform.h"
#include "dialog_two_threshold_transform.h"
#include "dialog_stretch_transform.h"
#include "capturescreen.h"

#define WINDOW_TITLE    "NaivePS"
#define WINDOW_CRITICAL "Error - NaivePS"
#define WINDOW_WARNING  "Notice - NaivePS"
#define WINDOW_ABOUT    "About - NaivePS"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateRightImage(QPixmap &pixmap);
    void cleanImage();

    void setActionStatus(bool);
    void createToolBar();
    void createAction();

private slots:

    // 从子对话框中接收数据
    void receiveGaussianFactor(int radius, double sigma);
    void receiveLinearGreyParameter(double, double);
    void receivePowerGreyParamter(double, double, double);
    void receiveLogGreyParamter(double, double);
    void receiveExpGreyParamter(double, double, double);
    void receiveTwoThresholdParamter(int, int, int);
    void receiveStretchParamter(int, int, double,double,double,double,double);

    // On action triggered
    void on_actionOpen_triggered();
    void on_actionClose_triggered();        // Clear both left and right Scene
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();      // Save as
    void on_actionExit_triggered();         // Exit the program

    void on_actionRestore_triggered();      // Restore to the original image
    void on_actionHistogram_triggered();
    void on_actionGrayscale_triggered();    // Grayscale
    void on_actionAdjust_brightness_triggered();

    void on_actionMovie_frame_triggered();
    void on_actionClassic_frame_triggered();
    void on_actionFlower_frame_triggered();
    void on_actionMetal_triggered();
    void on_actionCool_triggered();
    void on_actionWarm_triggered();

    void on_actionSimple_triggered();
    void on_actionGauss_triggered();
    void on_actionMeida_Filter_triggered();
    void on_actionLaplace_triggered();

    void on_actionLeft_triggered();         // Rotate Left: 90^
    void on_actionRight_triggered();        // Rotate Right:90^
    void on_zoomAction_triggered();         // Zoom action with dialog
    void on_actionHorizontal_triggered();
    void on_actionVertical_triggered();

    void on_actionLinear_level_transformation_triggered();
    void on_actionPower_transformation_triggered();
    void on_actionLogarithm_grey_level_transformation_triggered();
    void on_actionExp_transfrom_triggered();
    void on_actionTwo_thresholds_transform_triggered();
    void on_actionStretch_transformation_triggered();
    void on_actionBinaryzation_triggered();

    void on_actionContour_extraction_triggered();
    void on_actionPrewitt_triggered();
    void on_actionSobel_triggered();

    void on_actionDilate_triggered();
    void on_actionExpansion_triggered();
    void on_actionOpening_triggered();
    void on_actionClosing_triggered();
    // void on_actionThinning_triggered();

    void on_actionRGB2HSV_triggered();
    void on_actionRGB2HSL_triggered();
    void on_actionRGB2Cmyk_triggered();

    void on_actionAbout_triggered();        // Show "About" dialog

    void on_actionChinese_triggered();
    void on_actionEnglish_triggered();
    void on_actionT_triggered();
//    void on_actionEdge_Detection_triggered();
    void on_actionArea_triggered();
    void on_actionConnected_domain_triggered();
    void on_actionCircumference_triggered();
    void on_actionFinal_triggered();
    void on_actionScreenShot_triggered();
    void on_actionAdjust_triggered();       // Adjust to fit the window size
    void on_actionNormal_triggered();       // Restore the right image to original size

    void startCatureImage();
    void onCompleteCature(QPixmap captureImage);//完成截图

    void on_actionLeft90_triggered();

    void on_actionRight90_triggered();

    void on_actionHighpass_triggered();

    void on_actionLowpass_triggered();

private:
    QAction *finalEx;
    QAction *screenShot;

    Ui::MainWindow  *ui;
    QGraphicsScene  *leftScene;
    QGraphicsScene  *rightScene;
    QGraphicsPixmapItem* leftPixmapItem;
    QGraphicsPixmapItem* rightPixmapItem;

    QLabel          *size;

    QFileInfo *info;

    QString getUserName();
    QString getUserPath();
};

#endif // MAINWINDOW_H
