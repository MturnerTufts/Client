
#include "Snipping.h"



Snipping_Tool::Snipping_Tool()
{

	this->setWindowOpacity(.1);
	this->setStyleSheet("QWidget{background:#000000}");
	QWidget* widget = new QWidget();
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	GetWindowRect(hDesktop, &desktop);
	
	this->setGeometry(0, 0, desktop.right, desktop.bottom
);
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	

	this->show();
	this->hide();
	
}

void Snipping_Tool::mousePressEvent(QMouseEvent* events)
{
	POINT start;
	GetCursorPos(&start);
	qDebug() << "Mouse pressed";
	x_start = start.x;
	y_start = start.y;
}

void Snipping_Tool::mouseReleaseEvent(QMouseEvent* events)
{
	POINT end;
	GetCursorPos(&end);
	x_end = end.x;
	y_end = end.y;
	qDebug() << "Mouse unpressied";
	qDebug() << x_start;
	qDebug() << y_start;
	qDebug() << x_end;
	qDebug() << y_end;
	Snipping_Tool::Take_Screen_Shot();
	
	
}

void Snipping_Tool::mouseMoveEvent(QMouseEvent* events)
{
	POINT end;
	GetCursorPos(&end);
	x_end = end.x;
	y_end = end.y;
	qDebug() << "mouse is moving";
}

void Snipping_Tool::Take_Screen_Shot()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	HBITMAP bitmap;
	BITMAPINFO bInfo;
	cv::Mat Screen_Shot;
	HDC hdcSys = GetDC(NULL);
	HDC hdcMem = CreateCompatibleDC(hdcSys);
	GetWindowRect(hDesktop, &desktop);
	void* ptrBitmapPixels;

	HDC hdc{};
	ZeroMemory(&bInfo, sizeof(BITMAPINFO));
	bInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bInfo.bmiHeader.biWidth = x_end;
	bInfo.bmiHeader.biHeight = -(y_end);

	bInfo.bmiHeader.biPlanes = 1;
	bInfo.bmiHeader.biBitCount = 32;

	bitmap = CreateDIBSection(hdc, &bInfo, DIB_RGB_COLORS, &ptrBitmapPixels, NULL, 0);
	SelectObject(hdcMem, bitmap);
	cv::Mat Mat_Image = cv::Mat(y_end, x_end, CV_8UC4, ptrBitmapPixels, 0);
	BitBlt(hdcMem, 0, 0, x_end, y_end, hdcSys, 0, 0, SRCCOPY);

	cv::Mat Final_Image(Mat_Image, cv::Range(y_start, y_end), cv::Range(x_start, x_end));
	//cv::Mat Final_Image = cv::Mat(Mat_Image, cv::Range(x_start, x_end), cv::Range(y_start, y_end));	
	this->hide();


	//char* Img_ptr = (char*)Final_Image.data;

	if (remove("Image.jpg") == 0)
		printf("Deleted successfully");
	else
		printf("Unable to delete the file"); //rewrite these lines
	cv::imwrite("Image.jpg", Final_Image);

	//cv::Mat* Img_ptr = &Final_Image;
	
		cv::Mat Image_Rel = cv::imread("Image.jpg");
		
		int Img_Size = Image_Rel.total() * Image_Rel.elemSize();
		//int Img_Size = Image_Rel.total();
		int height = Image_Rel.size().height;
		int width = Image_Rel.size().width;




		//Client_Info->DataBuf.len = Add_Img_To_Buffer(Client_Info, Img_Label, 2, height, width, Mess, 0);
	
			
			Client_Info->DataBuf.len=Add_Img_To_Buffer(Client_Info, Img_Label, 2, width, height, Image_Rel.data, Img_Size);
			
			Client_Info->Read = false;

			Set_Read_Write(Client_Info);
			
			Send_Mes(Client_Info);
			cv::waitKey(0);
			delete[] Client_Info->DataBuf.buf;
			qDebug() << "next step";
			Client_Info->Read = true;
			Set_Read_Write(Client_Info);

			Client_Info->Read = false;

			Set_Read_Write(Client_Info);
		//qDebug() << Client_Info->DataBuf.buf;
			//cv::imshow("test", Image_Rel);
	
	
 //cv::Mat F(image, cv::Range(y_start, y_end), cv::Range(x_start, x_end));
	
	
	

	
}
