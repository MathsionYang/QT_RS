#pragma once
#include <QtWidgets>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include "ui_qtlayerout.h"
#include "gdal_priv.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "loadimg.h"

using namespace cv;
using namespace std; 
#pragma execution_character_set("utf-8")	

typedef struct
{
	GDALDataset *DstDataset = NULL;
	int Xsize = 0;
	int Ysize = 0;
	int nbands = 0;
	double* adfGeoTransform = new double[6]; //�洢����6����
	const char* proj = NULL;//�洢ͶӰ
	GDALDataType iDataType = GDT_Byte;

}ImageInfo;
class QTLayerOut : public QMainWindow
{
	Q_OBJECT

public:
	QTLayerOut(QWidget *parent = Q_NULLPTR);
	QAction *Act_file_open;//��
	QAction *Act_file_zoom_in;//�Ŵ�
	QAction *Act_file_zoom_out;//��С
	ImageInfo bzinfo;
private:
	enum TreeItemType { FileItem = 1001, BandItem };
	GDALDataset *cur_dataset;   // ��ǰ���ݼ�
	bool flag;//flag = 1 �򿪸�ʽΪimg.���򳣼���ʽͼ��
	GDALDataset *poDataset;
	QStringList RGB_dataset;    // �������ζ�Ӧ���ݼ�
	//int BandList[3] ={0};//�洢����ѡ��Ĳ������
	vector<int> BandList[3];
	const char* qstringToChar(QString str);
	void addFileItem(QString filename);
	QString getFilename(QString full_filename);
	QImage QTLayerOut::Mat2Img(const cv::Mat& mat);
	Mat Timg;
	bool on_pushButton_2_IS = 0;//���򿪺ϳ�ң��Ӱ��ʱ��ֵΪ1�ɵ����ť
	bool mouseflag=1;
	bool RightMouse;
private:
	Ui::QTLayerOutClass ui;
	
	QImage myimage;
	QImage tempImage;

	QToolBar *toolBar;
	QLabel *imgLabel;                           // ͼ����ʾ��
	QLabel *label_filename;    // ״̬����ʾ�ļ���
	void  AddMenu();
	void AddMyTool();
	QString ImgFileName;//TreeWidget�ļ���
	QString Img_path_Label;//��ǰ������ʾ���ļ���
private slots:
	void File_open();
	void CLoseButton();
	void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
	void on_radioButton_2_clicked();
	void on_radioButton_clicked();
	void on_pushButton_2_clicked();
	void IniImg();
	void popMenu(const QPoint&);
	void deleteItem();
	void mousePressEvent(QMouseEvent *event);
	void File_zoom_in();
	void File_zoom_out();
	//void ShowImg(QString path);
public:
	QImage Enlarge_Reduce(QImage src, int times);
	Mat QImage2cvMat(QImage image);
	QImage cvMat2QImage(const Mat& mat);
	QImage getImage();
	void setImage(QImage img);
	void ShowImage(QImage img);
	QImage splitBGR(QImage src, int color);
	void GetImageInfo(GDALDataset *MypoDataset, ImageInfo & St);
	void on_pushButton();
};
