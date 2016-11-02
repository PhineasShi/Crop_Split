#include "crop_split.h"

#pragma execution_character_set("utf-8")

Crop_Split::Crop_Split(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initRatios();

	outputPath = "D:/result";
	plateName = "123";

	pointCount = 0;
	ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);			//set the graphicView to drag mode
	this->setMouseTracking(true);
	QButtonGroup *pointerModeGroup = new QButtonGroup(this);
	pointerModeGroup->setExclusive(true);
	pointerModeGroup->addButton(ui.toolButton_selectMode);
	pointerModeGroup->addButton(ui.toolButton_dragMode);

	//连接信号与槽函数
	connect(ui.toolButton_zoomIn, SIGNAL(clicked()), this, SLOT(zoomIn()));
	connect(ui.toolButton_zoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));
	connect(ui.verticalSlider_zoom, SIGNAL(valueChanged(int)), this, SLOT(zoomChange()));
	connect(ui.toolButton_dragMode, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
	connect(ui.toolButton_selectMode, SIGNAL(toggled(bool)), this, SLOT(togglePointerMode()));
	connect(ui.pushButton_openFile, SIGNAL(clicked()), this, SLOT(openFile()));
	connect(ui.pushButton_setPath, SIGNAL(clicked()), this, SLOT(changePath()));
}

Crop_Split::~Crop_Split()
{
}

void Crop_Split::initRatios()
{
	ratios[0] = 0;
	ratios[1] = (double)62 / (440 - 9);
	ratios[2] = (double)(62 + 57) / (440 - 9);
	ratios[3] = (double)(62 + 57 + 12 + 10) / (440 - 9);
	for (int i = 4; i < 8; i++)
	{
		ratios[i] = (double)(62 + 57 + 12 + 10 + 57 * (i - 3)) / (440 - 9);
	}
}

void Crop_Split::showCvImage(cv::Mat input, QGraphicsView *gv, int width, int height)
{
	scene = new QGraphicsScene;			//Instantiate a new scene
	QImage *image;
	if (input.type() == CV_8UC3)							//Convert input Mat image into RGBA format, for furture convertion into QImage
	{
		cv::cvtColor(input, input, CV_RGB2RGBA);			//当Mat为RGB时
	}
	else
	{
		cv::cvtColor(input, input, CV_GRAY2BGRA);			//当Mat为灰度图时
	}
	cv::resize(input, input, cv::Size(width, height));
	image = new QImage((const unsigned char*)(input.data), input.cols, input.rows, QImage::Format_ARGB32);	//将Mat转换为QImage，注意后面的Format
	scene->addPixmap(QPixmap::fromImage(image->scaled(width, height, Qt::KeepAspectRatio)));	//将QImage插入到scene
	gv->setScene(scene);								//设置graphicsView的scene
	gv->show();											//显示graphicsView中的scene
	delete image;
}

//弹出对话框选择图像源文件和源文件
void Crop_Split::openFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, "", "I:/Tutor/Blurred License/Picture");
	if (fileName.isEmpty())
	{
		return;
	}
	imageFileName = QFileInfo(fileName).fileName().split(".").at(0);
	qDebug() << fileName;
	cv_input = cv::imread(fileName.toLocal8Bit().toStdString());		//读入原图，便于展示
//	cv::resize(cv_input, cv_input, cv::Size(640, 480));		//将输入的图片resize到与窗口相同大小
	showCvImage(cv_input, ui.graphicsView, cv_input.cols, cv_input.rows);
}

void Crop_Split::zoomIn()
{
	ui.verticalSlider_zoom->setValue(ui.verticalSlider_zoom->value() + 1);
}
void Crop_Split::zoomOut()
{
	ui.verticalSlider_zoom->setValue(ui.verticalSlider_zoom->value() - 1);
}
void Crop_Split::zoomChange()
{
	qreal scale = ui.verticalSlider_zoom->value() / 10 + 1;
	QMatrix matrix;
	matrix.scale(scale, scale);
	ui.graphicsView->setMatrix(matrix);
}

void Crop_Split::togglePointerMode()
{
	ui.graphicsView->setDragMode(ui.toolButton_selectMode->isChecked()
		? QGraphicsView::NoDrag
		: QGraphicsView::ScrollHandDrag);
	ui.graphicsView->setInteractive(ui.toolButton_selectMode->isChecked());
}

void Crop_Split::mousePressEvent(QMouseEvent *event)
{
	if (ui.toolButton_selectMode->isChecked())
	{
		QPoint scenePoint = ui.graphicsView->mapToScene((event->pos().x() - ui.graphicsView->x()), (event->pos().y() - ui.graphicsView->y())).toPoint();
		switch (pointCount++ % 2)
		{
		case 0:tl = cv::Point(scenePoint.x(), scenePoint.y()); break;
		case 1:br = cv::Point(scenePoint.x(), scenePoint.y());
			rect = cv::Rect(tl, br);
			showROI(rect);
			ui.toolButton_dragMode->setChecked(true);
			break;
		default:
			break;
		}
		//		qDebug() << tl.x << tl.y;
	}
}

void Crop_Split::showROI(cv::Rect roi)
{
	cv::Mat input = cv_input(rect).clone();
	qDebug() << tl.x << tl.y;

	//绘制分割线
	for (int i = 1; i < 8; i++)
	{
		cv::line(input, cv::Point(input.cols*ratios[i], 0), cv::Point(input.cols*ratios[i], input.rows), cv::Scalar(0, 0, 255));
	}
	cv::cvtColor(input, input, CV_RGB2RGBA);			//当Mat为RGB时
	QImage *image = new QImage((const unsigned char*)(input.data), input.cols, input.rows, QImage::Format_ARGB32);	//将Mat转换为QImage，注意后面的Format
	QMessageBox message(QMessageBox::NoIcon, "图片预览", "");
	message.setIconPixmap(QPixmap::fromImage(image->scaled(input.cols * 2, input.rows * 2, Qt::KeepAspectRatio)));
	message.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	message.setButtonText(QMessageBox::Ok, "确定");
	message.setButtonText(QMessageBox::Cancel, "取消");
	message.setDefaultButton(QMessageBox::Save);
	switch (message.exec())
	{
	case QMessageBox::Ok:
		if (setRectName())
		{
			QList<cv::Mat> rectList = split(roi);
			saveRects(rectList);
		}
		break;
	case QMessageBox::Cancel:break;
	default:
		break;
	}
}

QList<cv::Mat> Crop_Split::split(cv::Rect roi)
{
	QList<cv::Mat> rectList;
	cv::Mat imageRoi = cv_input(roi);
	for (int i = 0; i < 7; i++)
	{
		if (i == 2)
			continue;
		cv::Point tl = cv::Point(imageRoi.cols*ratios[i],0);
		cv::Point br = cv::Point(imageRoi.cols*ratios[i+1], imageRoi.rows);
		rectList.push_back(imageRoi(cv::Rect(tl, br)));
	}
	return rectList;
}
bool Crop_Split::setRectName()
{
	bool ok;
	QString name = QInputDialog::getText(this, "输入车牌号", "车牌号", QLineEdit::Normal, imageFileName, &ok);
	if (ok && !name.isEmpty())
	{
		plateName = name ;		
	}
	return ok;
}
void Crop_Split::saveRects(QList<cv::Mat> rectList)
{
	for (int i = 0; i < rectList.length(); i++)
	{
		int num = 1;
		QString path = outputPath +"/"+ plateName[i] + "/" + QString::number(rect.height) + "/";
		QDir dir(path);
		dir.setFilter(QDir::Files);
		dir.setSorting(QDir::Name|QDir::Time);
		QFileInfoList list = dir.entryInfoList();
		if (!list.isEmpty())
		{
			for (int j = 0; j < list.length(); j++)
			{
				num = num > list[j].completeBaseName().toInt() ? num : list[j].completeBaseName().toInt();
			}
		}
		else
		{
			dir.mkpath(path);
		}
		path += QString::number(num)+".jpg";
		qDebug() << path;
		bool writed = cv::imwrite(path.toLocal8Bit().toStdString(), rectList[i]);
	}
}

void Crop_Split::changePath()
{
	bool ok;
	QString name = QFileDialog::getExistingDirectory(NULL, "选择文件夹", outputPath, QFileDialog::ShowDirsOnly);
	QDir dir(outputPath);
	if (ok && !name.isEmpty() && dir.exists())
	{
		outputPath = name;
	}
}