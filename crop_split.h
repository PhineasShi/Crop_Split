#ifndef CROP_SPLIT_H
#define CROP_SPLIT_H

#include <QtWidgets/QMainWindow>
#include "ui_crop_split.h"

#include <qmath.h>
#include <QFileDialog>
#include <QFrame>
#include <QGraphicsView>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QInputDialog>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

class Crop_Split : public QMainWindow
{
	Q_OBJECT

public:
	Crop_Split(QWidget *parent = 0);
	~Crop_Split();
	

public slots:
	void zoomIn();
	void zoomOut();
	void openFile();

protected:
	void mousePressEvent(QMouseEvent *event);
private:
	Ui::Crop_SplitClass ui;
	QGraphicsScene *scene;
	cv::Mat cv_input;
	cv::Point tl;
	cv::Point br;
	cv::Rect rect;
	int pointCount;
	double ratios[9];
	
	QString *placeHolder;		//The first QString is cursed with _q_value equals 0*ffffffff
	QString imageFileName;
	QString outputPath;
	QString plateName;

	void showCvImage(cv::Mat input, QGraphicsView *gv, int width, int height);
	void showROI(cv::Rect roi);
	QList<cv::Mat> split(cv::Rect roi);
	bool setRectName();
	void initRatios();
	void saveRects(QList<cv::Mat> rectList);
private slots:
	void zoomChange();
	void togglePointerMode();
	void changePath();
};

#endif // CROP_SPLIT_H
