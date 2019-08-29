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
	toolBar->setMovable(false);     // 设置工具栏不可移动,默认是可移动
	addToolBar(toolBar);                // 把工具栏添加到窗口
	AddMenu();
	AddMyTool();
	IniImg();//加载空白图片



}


void QTLayerOut::AddMenu()
{
	this->setContextMenuPolicy(Qt::NoContextMenu);
	Act_file_open = new QAction(QIcon("../Image/file/Open.png"), tr("打开"), this);
	Act_file_open->setShortcuts(QKeySequence::Open);
	connect(Act_file_open, SIGNAL(triggered()), this, SLOT(File_open()));
	QMenu *file = menuBar()->addMenu(tr("文件"));
	file->addAction(Act_file_open);
}
void QTLayerOut::AddMyTool()
{

	Act_file_zoom_in = new QAction(QIcon("../Image/big.ico"), tr("放大"), this);
	Act_file_zoom_in->setShortcuts(QKeySequence::ZoomIn);
	connect(Act_file_zoom_in, SIGNAL(triggered()), this, SLOT(File_zoom_in()));

	Act_file_zoom_out = new QAction(QIcon("../Image/small.ico"), tr("缩小"), this);
	Act_file_zoom_out->setShortcuts(QKeySequence::ZoomOut);
	connect(Act_file_zoom_out, SIGNAL(triggered()), this, SLOT(File_zoom_out()));

	toolBar->addAction(Act_file_open);         // 打开
	toolBar->addAction(Act_file_zoom_in);      // 放大
	toolBar->addAction(Act_file_zoom_out);     // 缩小

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(CLoseButton()));
}
void QTLayerOut::File_open()
{
	QString path = QFileDialog::getOpenFileName(this, tr("选择图像"), ".", tr("Images(*.jpg *.png *.tiff *.img)"));                            // 文件选择框
	QFileInfo fileinfo;
	QString file_suffix ;
	if (!path.isEmpty())                                    // 检测当前路径是否正确
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
			//// 打开数据集
			GDALAllRegister();
			CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
			const char *filename;
			QByteArray ba = path.toLatin1(); // must
			filename = ba.data();
			poDataset = (GDALDataset *)GDALOpen(filename, GA_ReadOnly);
			if (poDataset == NULL)
			{
				QMessageBox::warning(this, "错误", "加载数据错误");
				return;
			}
			// 在QTreeWidget添加节点
			addFileItem(path);
			Img_path_Label = path;
		}
	}
}

const char* QTLayerOut::qstringToChar(QString str)
{
	QByteArray ba = str.toLocal8Bit();
	const char *char_ptr = ba.data();    // 将QString转化为字符串指针
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
//		// 查找band names位置
//		int pos = content.indexOf("band names");
//		// 处理字符串
//		QChar ch;
//		while ((ch = content[pos]) != "{")
//			pos++;
//		int beg = pos + 1;
//		while ((ch = content[pos]) != "}")
//			pos++;
//		int end = pos - 1;
//		QString bnstr = content.mid(beg, end - beg + 1);
//		bnstr.replace("\r\n", "\n");    // 对于不同格式换行统一处理
//		band_name = bnstr.split(QRegExp("[\\n,]"), QString::SkipEmptyParts);   // 利用正则表达式，有小问题（已解决）。
//		// 删除列表中" "字符串
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
//		// 查找wavelength位置
//		// int pos = content.indexOf("default bands");     // 直接搜索"wavelength"匹配到"wavelength units"了
//		int pos = content.lastIndexOf("wavelength");    // 搜索到最后出现的"wavelength"，假设单位在前
//		// 处理字符串
//		QChar ch;
//		while ((ch = content[pos]) != "{")
//			pos++;
//		int beg = pos + 1;
//		while ((ch = content[pos]) != "}")
//			pos++;
//		int end = pos - 1;
//		QString wavstr = content.mid(beg, end - beg + 1);
//		wavstr.replace("\r\n", "\n");    // 对于不同格式换行统一处理
//		wavlist = wavstr.split(QRegExp("[\\n,]"), QString::SkipEmptyParts);   // 利用正则表达式，有小问题（已解决）。
//		// 删除列表中" "字符串
//		auto it = wavlist.begin();
//		while (it != wavlist.end())
//		{
//			*it = it->trimmed();
//			if (it->isEmpty())
//				it = wavlist.erase(it);
//			else
//				it++;
//		}
//		// 字符转换成数值
//		for (int i = 0; i < wavlist.size(); ++i)
//			wavelength.append(wavlist[i].toFloat());
//		file.close();
//	}
//	return wavelength;
//}
void QTLayerOut::addFileItem(QString filename)
{
	// 设置文件节点图标

	QIcon file_icon("../Image/icon/layers.ico");
	// 添加文件节点至顶层节点
	QTreeWidgetItem *file_item = new QTreeWidgetItem(QTLayerOut::FileItem);
	file_item->setText(0, getFilename(filename));      // 设置显示为最后文件名
	file_item->setData(0, Qt::UserRole, QVariant(filename));    // 设置数据为完整文件名
	file_item->setIcon(0, file_icon);    // 添加文件节点图标
	// 设置文件节点属性
	file_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	ui.treeWidget->addTopLevelItem(file_item);
	QIcon band_icon("../Image/icon/square.ico");

	filename = QDir::toNativeSeparators(filename);
	QByteArray ba = filename.toLocal8Bit();
	const char *pszFileName = ba.data();    // 将QString转化为字符串指针

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
	ui.treeWidget->expandAll();//展开所有节点
		
}

QString QTLayerOut::getFilename(QString full_filename)
{
	// 从完整路径中得到文件名
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
		// 判断三者同属一个数据集
		bool areSame = true;
		for (int i = 0; i < 2; ++i)
		{
			if (RGB_dataset[i + 1] != RGB_dataset[i])
				areSame = false;
		}
		if (!areSame)
		{
			QMessageBox::warning(this, "错误", "波段不属于同一影像");
			return;
		}
		const char *dstfile="1.tiff";
		GDALDriver *pDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
		
		GDALRasterBand *dstBand, *pBand;
		int nImgSizeX = bzinfo.Xsize;
		int nImgSizeY = bzinfo.Ysize;
		GDALAllRegister();
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
		//写入光栅数据
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
// 当前节点变化后响应，点击波段节点生效。
void QTLayerOut::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	// 节点变化时相应处理，注意previous可能为NULL!
	
		Q_UNUSED(previous);
		if (current == NULL)
		{
			mouseflag = 0;
			return;
		}
		// 若选择文件节点则无效
		if (current->type() != BandItem)
		{

			mouseflag = 1;
			if (mouseflag == 1)
			{
				ImgFileName = current->text(0);
				connect(ui.treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(popMenu(const QPoint&)));//检测鼠标右键
				return;
			}
		}
		// 选择波段节点，设置为当前数据集
			QTreeWidgetItem *par_item = current->parent();
			int nDScount = 0;
			GDALDataset **openedDSList = GDALDataset::GetOpenDatasets(&nDScount);   // 当前打开数据集列表
			int file_index = 0;
			// 所选文件节点序号
			file_index =ui.treeWidget->indexOfTopLevelItem(par_item);     
			//cur_dataset = openedDSList[file_index];
			//if (ui.radioButton->isChecked())
			//{
			//	// 显示所选灰度波段
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
				// 显示所选RGB波段
				int n = ui.listWidget->count();//n从0开始到2 结束，大于等于三重新选择
				// 判断已选波段数
				if (n == 3)
				{
					// 重新选择
					ui.listWidget->clear();
					// 清除波段数据集
					RGB_dataset.clear();
					n = 0;
					GetImageInfo(poDataset, bzinfo);
				}
				// 获得所选波段号
				int band_index = par_item->indexOfChild(current) + 1;   // GDAL从1起始
				BandList->push_back(band_index);
				// 保存并添加至波段列表
				QStringList color = { "R: ", "G: ", "B: " };
				QIcon icon_R("../Image/icon/red.png");
				QIcon icon_G("../Image/icon/green.png");
				QIcon icon_B("../Image/icon/blue.png");
				QList<QIcon> icon = { icon_R, icon_G, icon_B };
				QListWidgetItem *band = new QListWidgetItem;
				// 显示颜色和对应波段
				band->setText(color[n] + current->text(0));
				// 设置对应颜色图标
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

// 关闭显示窗口
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
void QTLayerOut::IniImg()//加载空白图片
{
	imgLabel = new QLabel(ui.dockWidget_2);
	imgLabel->setScaledContents(true);  // 设置QLabel自动适应图像大小

	// 初始图像
	QImage image = QImage(580, 620, QImage::Format_RGB32);  // 新建图像
	image.fill(qRgb(255, 255, 255));                        // 全白
	imgLabel->setPixmap(QPixmap::fromImage(image));         // 显示图像
	imgLabel->resize(image.width(), image.height());        // 图像与imgLabel同大小

	// 增加滚动条,如果图像比imgLabel大，就会出现滚动条
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
	QTreeWidgetItem* curItem = ui.treeWidget->currentItem();  //获取当前被点击的节点
	if (curItem == NULL)
	{
		return;
	}
	// 若选择文件节点
	if (curItem->type() != BandItem)
	{
		QAction *deleteImg;//删除
		deleteImg = new QAction(QIcon("../Image/Del.ico"), tr("删除"), this);
		QAction *OpenImg;////重命名
		OpenImg = new QAction(QIcon("../Image/open.ico"), tr("打开"), this);
		//在界面上删除该item
		connect(deleteImg, SIGNAL(triggered()), this, SLOT(deleteItem()));
		connect(OpenImg, SIGNAL(triggered()), this, SLOT(File_open()));

		QPoint pos;
		QMenu menu(ui.treeWidget);
		menu.addAction(OpenImg);
		menu.addAction(deleteImg);
		menu.exec(QCursor::pos());  //在当前鼠标位置显示

	}
}
void QTLayerOut::deleteItem()
{
	QMessageBox message(QMessageBox::Warning, "信息",

		"确定删除所选文件吗", QMessageBox::Yes | QMessageBox::No, NULL);
	if (message.exec() == QMessageBox::Yes)
	{
		QTreeWidgetItem * currentItem = ui.treeWidget->currentItem();

		if (currentItem == NULL)
		{
			return;
		}
		//如果没有父节点就直接删除
		if (currentItem->parent() == NULL)
		{
			delete ui.treeWidget->takeTopLevelItem(ui.treeWidget->currentIndex().row());
		}
		else
		{
			//如果有父节点就要用父节点的takeChild删除节点
			delete currentItem->parent()->takeChild(ui.treeWidget->currentIndex().row());
		}
		//删除结点后清空画布
		QFileInfo fileinfo;
		fileinfo = QFileInfo(Img_path_Label);
		//文件名
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
//放大
void  QTLayerOut::File_zoom_in()
{
	QImage Img = Enlarge_Reduce(getImage(), 1);
	ShowImage(Img);	// 图像保存			
}
//缩小
void  QTLayerOut::File_zoom_out()
{
	QImage Img = Enlarge_Reduce(getImage(), -1);
	ShowImage(Img);	// 图像保存	
}

QImage QTLayerOut::Enlarge_Reduce(QImage src, int times)
{
	// TODO: 在此处添加实现代码.
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
	// TODO: 在此处添加实现代码.
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
	// TODO: 在此处添加实现代码.
	if (mat.type() == CV_8UC1)					// 单通道
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);				// 灰度级数256
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;					// 复制mat数据
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}

	else if (mat.type() == CV_8UC3)				// 3通道
	{
		const uchar *pSrc = (const uchar*)mat.data;			// 复制像素
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);	// R, G, B 对应 0,1,2
		return image.rgbSwapped();				// rgbSwapped是为了显示效果色彩好一些。
	}
	else if (mat.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)mat.data;			// 复制像素
															// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);		// B,G,R,A 对应 0,1,2,3
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
	// TODO: 在此处添加实现代码.
	myimage = img;
	tempImage = myimage;
}
void QTLayerOut::ShowImage(QImage img)
{
	// TODO: 在此处添加实现代码.
	setImage(img);
	imgLabel->setPixmap(QPixmap::fromImage(img));
	imgLabel->resize(img.width(), img.height());
}


QImage QTLayerOut::splitBGR(QImage src, int color)
{
	// TODO: 在此处添加实现代码.
	Mat srcImg, dstImg;
	srcImg = QImage2cvMat(src);
	if (srcImg.channels() == 1)
	{
		QMessageBox message(QMessageBox::Information, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("该图像为灰度图像。"));
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

		dstImg = m[color];		// 分别对应B、G、R
		QImage dst = cvMat2QImage(dstImg);
		return dst;
	}
}
void QTLayerOut::GetImageInfo(GDALDataset *MypoDataset, ImageInfo & St)
{
	// TODO: 在此处添加实现代码.
	// 获取投影参数
	St.DstDataset = MypoDataset;
	St.Xsize = MypoDataset->GetRasterXSize();
	St.Ysize = MypoDataset->GetRasterYSize();
	St.nbands = MypoDataset->GetRasterCount();
	St.proj = MypoDataset->GetProjectionRef();//投影
	MypoDataset->GetGeoTransform(St.adfGeoTransform);//六参数
	St.iDataType = MypoDataset->GetRasterBand(1)->GetRasterDataType(); //数据类型
}

void QTLayerOut::CLoseButton()
{
	if (!(QMessageBox::information(this, tr("！！！"), tr("确认关闭程序吗?"), tr("Yes"), tr("No"))))
	{
		QApplication* app;
		app->exit(0);
	}
}

