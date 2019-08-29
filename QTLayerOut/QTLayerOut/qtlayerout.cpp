#include "qtlayerout.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>




QTLayerOut::QTLayerOut(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("IMGMaster2019");
	toolBar = new QToolBar();
	toolBar->setMovable(false);     // ���ù����������ƶ�,Ĭ���ǿ��ƶ�
	addToolBar(toolBar);                // �ѹ�������ӵ�����
	AddMenu();
	AddMyTool();
	IniImg();//���ؿհ�ͼƬ



}


void QTLayerOut::AddMenu()
{
	this->setContextMenuPolicy(Qt::NoContextMenu);
	Act_file_open = new QAction(QIcon("../Image/file/Open.png"), tr("��"), this);
	Act_file_open->setShortcuts(QKeySequence::Open);
	connect(Act_file_open, SIGNAL(triggered()), this, SLOT(File_open()));
	QMenu *file = menuBar()->addMenu(tr("�ļ�"));
	file->addAction(Act_file_open);
}
void QTLayerOut::AddMyTool()
{

	Act_file_zoom_in = new QAction(QIcon("../Image/big.ico"), tr("�Ŵ�"), this);
	Act_file_zoom_in->setShortcuts(QKeySequence::ZoomIn);
	connect(Act_file_zoom_in, SIGNAL(triggered()), this, SLOT(File_zoom_in()));

	Act_file_zoom_out = new QAction(QIcon("../Image/small.ico"), tr("��С"), this);
	Act_file_zoom_out->setShortcuts(QKeySequence::ZoomOut);
	connect(Act_file_zoom_out, SIGNAL(triggered()), this, SLOT(File_zoom_out()));

	toolBar->addAction(Act_file_open);         // ��
	toolBar->addAction(Act_file_zoom_in);      // �Ŵ�
	toolBar->addAction(Act_file_zoom_out);     // ��С

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(CLoseButton()));
}
void QTLayerOut::File_open()
{
	QString path = QFileDialog::getOpenFileName(this, tr("ѡ��ͼ��"), ".", tr("Images(*.jpg *.png *.tiff *.img)"));                            // �ļ�ѡ���
	QFileInfo fileinfo;
	QString file_suffix ;
	if (!path.isEmpty())                                    // ��⵱ǰ·���Ƿ���ȷ
	{
		fileinfo = QFileInfo(path);
		file_suffix = fileinfo.suffix();
		if (file_suffix=="jpg"|| file_suffix == "png"|| file_suffix == "tiff")
		{
			flag = 0;
			QImage img;
			img.load(path);
			ShowImage(img);
			addFileItem(path);
			Img_path_Label = path;
		}
		else if (file_suffix == "img")
		{
			//cur_dataset = NULL;
			flag = 1;
			//// �����ݼ�
			GDALAllRegister();
			CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
			const char *filename;
			QByteArray ba = path.toLatin1(); // must
			filename = ba.data();
			poDataset = (GDALDataset *)GDALOpen(filename, GA_ReadOnly);
			if (poDataset == NULL)
			{
				QMessageBox::warning(this, "����", "�������ݴ���");
				return;
			}
			// ��QTreeWidget��ӽڵ�
			addFileItem(path);
			Img_path_Label = path;
		}
	}
}

const char* QTLayerOut::qstringToChar(QString str)
{
	QByteArray ba = str.toLocal8Bit();
	const char *char_ptr = ba.data();    // ��QStringת��Ϊ�ַ���ָ��
	return char_ptr;
}
//QStringList QTLayerOut::getBandName(QString filename)
//{
//	QFile file(filename);
//	QStringList band_name;
//	if (file.open(QIODevice::ReadOnly))
//	{
//		QTextStream in(&file);
//		QString content = in.readAll();
//		// ����band namesλ��
//		int pos = content.indexOf("band names");
//		// �����ַ���
//		QChar ch;
//		while ((ch = content[pos]) != "{")
//			pos++;
//		int beg = pos + 1;
//		while ((ch = content[pos]) != "}")
//			pos++;
//		int end = pos - 1;
//		QString bnstr = content.mid(beg, end - beg + 1);
//		bnstr.replace("\r\n", "\n");    // ���ڲ�ͬ��ʽ����ͳһ����
//		band_name = bnstr.split(QRegExp("[\\n,]"), QString::SkipEmptyParts);   // ����������ʽ����С���⣨�ѽ������
//		// ɾ���б���" "�ַ���
//		auto it = band_name.begin();
//		while (it != band_name.end())
//		{
//			*it = it->trimmed();
//			if (it->isEmpty())
//				it = band_name.erase(it);
//			else
//				it++;
//		}
//		file.close();
//	}
//	return band_name;
//}
////
//QList<float> QTLayerOut::getWavelength(QString filename)
//{
//	QFile file(filename);
//	QList<float> wavelength;
//	QStringList wavlist;
//	if (file.open(QIODevice::ReadOnly))
//	{
//		QTextStream in(&file);
//		QString content = in.readAll();
//		// ����wavelengthλ��
//		// int pos = content.indexOf("default bands");     // ֱ������"wavelength"ƥ�䵽"wavelength units"��
//		int pos = content.lastIndexOf("wavelength");    // �����������ֵ�"wavelength"�����赥λ��ǰ
//		// �����ַ���
//		QChar ch;
//		while ((ch = content[pos]) != "{")
//			pos++;
//		int beg = pos + 1;
//		while ((ch = content[pos]) != "}")
//			pos++;
//		int end = pos - 1;
//		QString wavstr = content.mid(beg, end - beg + 1);
//		wavstr.replace("\r\n", "\n");    // ���ڲ�ͬ��ʽ����ͳһ����
//		wavlist = wavstr.split(QRegExp("[\\n,]"), QString::SkipEmptyParts);   // ����������ʽ����С���⣨�ѽ������
//		// ɾ���б���" "�ַ���
//		auto it = wavlist.begin();
//		while (it != wavlist.end())
//		{
//			*it = it->trimmed();
//			if (it->isEmpty())
//				it = wavlist.erase(it);
//			else
//				it++;
//		}
//		// �ַ�ת������ֵ
//		for (int i = 0; i < wavlist.size(); ++i)
//			wavelength.append(wavlist[i].toFloat());
//		file.close();
//	}
//	return wavelength;
//}
void QTLayerOut::addFileItem(QString filename)
{
	// �����ļ��ڵ�ͼ��

	QIcon file_icon("../Image/icon/layers.ico");
	// ����ļ��ڵ�������ڵ�
	QTreeWidgetItem *file_item = new QTreeWidgetItem(QTLayerOut::FileItem);
	file_item->setText(0, getFilename(filename));      // ������ʾΪ����ļ���
	file_item->setData(0, Qt::UserRole, QVariant(filename));    // ��������Ϊ�����ļ���
	file_item->setIcon(0, file_icon);    // ����ļ��ڵ�ͼ��
	// �����ļ��ڵ�����
	file_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	ui.treeWidget->addTopLevelItem(file_item);
	QIcon band_icon("../Image/icon/square.ico");

	filename = QDir::toNativeSeparators(filename);
	QByteArray ba = filename.toLocal8Bit();
	const char *pszFileName = ba.data();    // ��QStringת��Ϊ�ַ���ָ��

	GDALDataset *poDataset;
	GDALAllRegister();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
	poDataset = (GDALDataset *)GDALOpen(pszFileName, GA_ReadOnly);
	if(poDataset == NULL)
	{
		cout << "nothing" << endl;
	}
	

	GetImageInfo(poDataset, bzinfo);


	GDALRasterBand *poBand;
	int BandNum = poDataset->GetRasterCount();
	poBand = poDataset->GetRasterBand(1);
	for (int i = 0; i < BandNum; i++)
	{
		QTreeWidgetItem *band_item = new QTreeWidgetItem(QTLayerOut::BandItem);
		band_item->setText(0, QString("%1 %2").arg("Band", QString::number(i+1)));
		band_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		band_item->setIcon(0, band_icon);
		file_item->addChild(band_item);
	}
	ui.treeWidget->expandAll();//չ�����нڵ�
		
}

QString QTLayerOut::getFilename(QString full_filename)
{
	// ������·���еõ��ļ���
	int cnt = full_filename.length();
	int pos = full_filename.lastIndexOf("/");
	QString filename = full_filename.right(cnt - 1 - pos);
	return filename;
}
void QTLayerOut::on_pushButton()
{
	int Num_count =BandList->size();

	if (Num_count == 3&&ui.radioButton_2->isChecked())
	{

		if (ui.listWidget->count() != 3)
			return;
		// �ж�����ͬ��һ�����ݼ�
		bool areSame = true;
		for (int i = 0; i < 2; ++i)
		{
			if (RGB_dataset[i + 1] != RGB_dataset[i])
				areSame = false;
		}
		if (!areSame)
		{
			QMessageBox::warning(this, "����", "���β�����ͬһӰ��");
			return;
		}
		const char *dstfile="1.tiff";
		GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
		
		GDALRasterBand *dstBand, *pBand;
		int nImgSizeX = bzinfo.Xsize;
		int nImgSizeY = bzinfo.Ysize;
		GDALAllRegister();
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
		//д���դ����
		ushort *buf = new ushort[nImgSizeX * nImgSizeY];
		//BYTE *pBuffer = (BYTE*)CPLMalloc(sizeof(BYTE)*(nImgSizeX)*(nImgSizeY)*3);
		GDALDataset *dstDataset = pDriver->Create(dstfile, nImgSizeX, nImgSizeY, 3, bzinfo.iDataType, NULL);
		int i;
		for (i=0; i <3; i++)
		{
			int Num = BandList->at(i);
			pBand = bzinfo.DstDataset->GetRasterBand(Num);
			pBand->RasterIO(GF_Read, 0, 0, nImgSizeX, nImgSizeY, buf, nImgSizeX, nImgSizeY, bzinfo.iDataType, 0, 0);
			int j = i + 1;
			dstBand = dstDataset->GetRasterBand(j);
			dstBand->RasterIO(GF_Write, 0, 0, nImgSizeX, nImgSizeY, buf, nImgSizeX, nImgSizeY, bzinfo.iDataType, 0, 0);
			if (i == 2)
			{
				BandList->clear();
				on_pushButton_2_IS = 1;
			}

		}
		delete[]buf;
		GDALClose(bzinfo.DstDataset);
		GDALClose(dstDataset);
		


	}
}
// ��ǰ�ڵ�仯����Ӧ��������νڵ���Ч��
void QTLayerOut::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	// �ڵ�仯ʱ��Ӧ����ע��previous����ΪNULL!
	
		Q_UNUSED(previous);
		if (current == NULL)
		{
			mouseflag = 0;
			return;
		}
		// ��ѡ���ļ��ڵ�����Ч
		if (current->type() != BandItem)
		{

			mouseflag = 1;
			if (mouseflag == 1)
			{
				ImgFileName = current->text(0);
				connect(ui.treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(popMenu(const QPoint&)));//�������Ҽ�
				return;
			}
		}
		// ѡ�񲨶νڵ㣬����Ϊ��ǰ���ݼ�
			QTreeWidgetItem *par_item = current->parent();
			int nDScount = 0;
			GDALDataset **openedDSList = GDALDataset::GetOpenDatasets(&nDScount);   // ��ǰ�����ݼ��б�
			int file_index = 0;
			// ��ѡ�ļ��ڵ����
			file_index =ui.treeWidget->indexOfTopLevelItem(par_item);     
			//cur_dataset = openedDSList[file_index];
			//if (ui.radioButton->isChecked())
			//{
			//	// ��ʾ��ѡ�ҶȲ���
			//	ui.listWidget->clear();
			//	QIcon icon("../Image/icon/gray.png");
			//	QListWidgetItem *header, *band;
			//	header = new QListWidgetItem;
			//	band = new QListWidgetItem;
			//	header->setText("Selected band:");
			//	band->setIcon(icon);
			//	band->setText(current->text(0));
			//	ui.listWidget->addItem(header);
			//	ui.listWidget->addItem(band);
			//}
			if (ui.radioButton_2->isChecked())
			{
				// ��ʾ��ѡRGB����
				int n = ui.listWidget->count();//n��0��ʼ��2 ���������ڵ���������ѡ��
				// �ж���ѡ������
				if (n == 3)
				{
					// ����ѡ��
					ui.listWidget->clear();
					// ����������ݼ�
					RGB_dataset.clear();
					n = 0;
					GetImageInfo(poDataset, bzinfo);
				}
				// �����ѡ���κ�
				int band_index = par_item->indexOfChild(current) + 1;   // GDAL��1��ʼ
				BandList->push_back(band_index);
				// ���沢����������б�
				QStringList color = { "R: ", "G: ", "B: " };
				QIcon icon_R("../Image/icon/red.png");
				QIcon icon_G("../Image/icon/green.png");
				QIcon icon_B("../Image/icon/blue.png");
				QList<QIcon> icon = { icon_R, icon_G, icon_B };
				QListWidgetItem *band = new QListWidgetItem;
				// ��ʾ��ɫ�Ͷ�Ӧ����
				band->setText(color[n] + current->text(0));
				// ���ö�Ӧ��ɫͼ��
				band->setIcon(icon[n]);
				band->setData(Qt::UserRole, QVariant(band_index));
				ui.listWidget->addItem(band);
				RGB_dataset.append(par_item->text(0));


			}

			on_pushButton();
		
}

void QTLayerOut::on_radioButton_2_clicked()
{
	ui.listWidget->clear();
	RGB_dataset.clear();
}
void QTLayerOut::on_radioButton_clicked()
{
	//ui.listWidget->clear();
}

// �ر���ʾ����
void QTLayerOut::on_pushButton_2_clicked()
{
	if (on_pushButton_2_IS==1)
	{
		const char *dstfile = "1.tiff";
		QImage img;
		img.load(dstfile);
		ShowImage(img);
		//addFileItem(dstfile);
		Img_path_Label = dstfile;
	}
	
	

}
void QTLayerOut::IniImg()//���ؿհ�ͼƬ
{
	imgLabel = new QLabel(ui.dockWidget_2);
	imgLabel->setScaledContents(true);  // ����QLabel�Զ���Ӧͼ���С

	// ��ʼͼ��
	QImage image = QImage(580, 620, QImage::Format_RGB32);  // �½�ͼ��
	image.fill(qRgb(255, 255, 255));                        // ȫ��
	imgLabel->setPixmap(QPixmap::fromImage(image));         // ��ʾͼ��
	imgLabel->resize(image.width(), image.height());        // ͼ����imgLabelͬ��С

	// ���ӹ�����,���ͼ���imgLabel�󣬾ͻ���ֹ�����
	QScrollArea* scrollArea = new QScrollArea(this);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setWidget(imgLabel);
	ui.dockWidget_2->setWidget(scrollArea);
}
QImage QTLayerOut::Mat2Img(const cv::Mat& mat)
{
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	else if (mat.type() == CV_8UC3)
	{
		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		return QImage();
	}
}


void QTLayerOut::popMenu(const QPoint&)
{
	QTreeWidgetItem* curItem = ui.treeWidget->currentItem();  //��ȡ��ǰ������Ľڵ�
	if (curItem == NULL)
	{
		return;
	}
	// ��ѡ���ļ��ڵ�
	if (curItem->type() != BandItem)
	{
		QAction *deleteImg;//ɾ��
		deleteImg = new QAction(QIcon("../Image/Del.ico"), tr("ɾ��"), this);
		QAction *OpenImg;////������
		OpenImg = new QAction(QIcon("../Image/open.ico"), tr("��"), this);
		//�ڽ�����ɾ����item
		connect(deleteImg, SIGNAL(triggered()), this, SLOT(deleteItem()));
		connect(OpenImg, SIGNAL(triggered()), this, SLOT(File_open()));

		QPoint pos;
		QMenu menu(ui.treeWidget);
		menu.addAction(OpenImg);
		menu.addAction(deleteImg);
		menu.exec(QCursor::pos());  //�ڵ�ǰ���λ����ʾ

	}
}
void QTLayerOut::deleteItem()
{
	QMessageBox message(QMessageBox::Warning, "��Ϣ",

		"ȷ��ɾ����ѡ�ļ���", QMessageBox::Yes | QMessageBox::No, NULL);
	if (message.exec() == QMessageBox::Yes)
	{
		QTreeWidgetItem * currentItem = ui.treeWidget->currentItem();

		if (currentItem == NULL)
		{
			return;
		}
		//���û�и��ڵ��ֱ��ɾ��
		if (currentItem->parent() == NULL)
		{
			delete ui.treeWidget->takeTopLevelItem(ui.treeWidget->currentIndex().row());
		}
		else
		{
			//����и��ڵ��Ҫ�ø��ڵ��takeChildɾ���ڵ�
			delete currentItem->parent()->takeChild(ui.treeWidget->currentIndex().row());
		}
		//ɾ��������ջ���
		QFileInfo fileinfo;
		fileinfo = QFileInfo(Img_path_Label);
		//�ļ���
		QString  file_name;
		file_name = fileinfo.fileName();
		if (ImgFileName== file_name)
		{
			QImage image = QImage(580, 620, QImage::Format_RGB32);
			image.fill(qRgb(255, 255, 255));
			imgLabel->setPixmap(QPixmap::fromImage(image));
			imgLabel->resize(image.width(), image.height());
			
		}
		mouseflag = 0;
	}
}
void QTLayerOut::mousePressEvent(QMouseEvent *event)
{

}
//�Ŵ�
void  QTLayerOut::File_zoom_in()
{
	QImage Img = Enlarge_Reduce(getImage(), 1);
	ShowImage(Img);	// ͼ�񱣴�			
}
//��С
void  QTLayerOut::File_zoom_out()
{
	QImage Img = Enlarge_Reduce(getImage(), -1);
	ShowImage(Img);	// ͼ�񱣴�	
}

QImage QTLayerOut::Enlarge_Reduce(QImage src, int times)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	Mat matSrc, matDst;
	matSrc = QImage2cvMat(src);
	if (times > 0)
	{
		cv::resize(matSrc, matDst, Size(matSrc.cols * abs(times + 1), matSrc.rows * abs(times + 1)), 0, 0, INTER_LINEAR);
		QImage dst = cvMat2QImage(matDst);
		return dst;
	}
	else if (times < 0)
	{
		cv::resize(matSrc, matDst, Size(matSrc.cols / abs(times - 1), matSrc.rows / abs(times - 1)), 0, 0, INTER_AREA);
		QImage dst =cvMat2QImage(matDst);
		return dst;
	}
	else
	{
		return src;
	}
}


Mat QTLayerOut::QImage2cvMat(QImage image)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	Mat mat;
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}


QImage QTLayerOut::cvMat2QImage(const Mat& mat)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	if (mat.type() == CV_8UC1)					// ��ͨ��
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);				// �Ҷȼ���256
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;					// ����mat����
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}

	else if (mat.type() == CV_8UC3)				// 3ͨ��
	{
		const uchar *pSrc = (const uchar*)mat.data;			// ��������
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);	// R, G, B ��Ӧ 0,1,2
		return image.rgbSwapped();				// rgbSwapped��Ϊ����ʾЧ��ɫ�ʺ�һЩ��
	}
	else if (mat.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)mat.data;			// ��������
															// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);		// B,G,R,A ��Ӧ 0,1,2,3
		return image.copy();
	}
	else
	{
		return QImage();
	}
}
QImage QTLayerOut::getImage()
{
	if (myimage.isNull() != true)
		return myimage;
}
void QTLayerOut::setImage(QImage img)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	myimage = img;
	tempImage = myimage;
}
void QTLayerOut::ShowImage(QImage img)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	setImage(img);
	imgLabel->setPixmap(QPixmap::fromImage(img));
	imgLabel->resize(img.width(), img.height());
}


QImage QTLayerOut::splitBGR(QImage src, int color)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	Mat srcImg, dstImg;
	srcImg = QImage2cvMat(src);
	if (srcImg.channels() == 1)
	{
		QMessageBox message(QMessageBox::Information, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��ͼ��Ϊ�Ҷ�ͼ��"));
		message.exec();
		return src;
	}
	else
	{
		vector<Mat> m;
		split(srcImg, m);
		vector<Mat>Rchannels, Gchannels, Bchannels;
		split(srcImg, Rchannels);
		split(srcImg, Gchannels);
		split(srcImg, Bchannels);
		Rchannels[1] = 0;	Rchannels[2] = 0;
		Gchannels[0] = 0;	Gchannels[2] = 0;
		Bchannels[0] = 0;	Bchannels[1] = 0;
		merge(Rchannels, m[0]);
		merge(Gchannels, m[1]);
		merge(Bchannels, m[2]);

		dstImg = m[color];		// �ֱ��ӦB��G��R
		QImage dst = cvMat2QImage(dstImg);
		return dst;
	}
}
void QTLayerOut::GetImageInfo(GDALDataset *MypoDataset, ImageInfo & St)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	// ��ȡͶӰ����
	St.DstDataset = MypoDataset;
	St.Xsize = MypoDataset->GetRasterXSize();
	St.Ysize = MypoDataset->GetRasterYSize();
	St.nbands = MypoDataset->GetRasterCount();
	St.proj = MypoDataset->GetProjectionRef();//ͶӰ
	MypoDataset->GetGeoTransform(St.adfGeoTransform);//������
	St.iDataType = MypoDataset->GetRasterBand(1)->GetRasterDataType(); //��������
}

void QTLayerOut::CLoseButton()
{
	if (!(QMessageBox::information(this, tr("������"), tr("ȷ�Ϲرճ�����?"), tr("Yes"), tr("No"))))
	{
		QApplication* app;
		app->exit(0);
	}
}

