#include "Info.h"
#include "Snipping.h"
#include <stdlib.h>
int Add_To_Buffer(LPCLIENT_INFORMATION C_Info, char* Mes_Label, char* Mes, int Mes_Label_Len, int Mes_Len)
{
	
	int full_length = Mes_Label_Len + Mes_Len + 1;//+1 becuase we are including Mes_label_len at the start;
	C_Info->DataBuf.buf = (char*)new int[full_length];
	char* Mes_Len_char = (char*)std::to_string(Mes_Label_Len).c_str();

	//C_Info->DataBuf.buf = new char[Mes_Label_Len + Mes_Len + 1]; //+1 becuase we are including Mes_label_len at the start
	memcpy(C_Info->DataBuf.buf, std::to_string(Mes_Label_Len).c_str(), 1);
	memcpy(C_Info->DataBuf.buf + 1, Mes_Label, Mes_Label_Len);
	memcpy(C_Info->DataBuf.buf + 1 + Mes_Label_Len, Mes, Mes_Len);
	return full_length;
}

int Add_Img_To_Buffer(LPCLIENT_INFORMATION C_Info, char* Label, int Label_Len, int width, int height, uchar* Img_Data, int Image_Len)
{
	
	int Width_Len = std::to_string(width).length();
	int Height_Len = std::to_string(height).length();
	int full_length =  Image_Len+Label_Len + std::to_string(height).length() + std::to_string(width).length() + 3; // +# becuase we are including the lengths of heihgt, width, and mes_Label at the start
	C_Info->DataBuf.buf = new char[full_length];
	qDebug() << Image_Len;
	memcpy(C_Info->DataBuf.buf, std::to_string(Label_Len).c_str(), 1);
	memcpy(C_Info->DataBuf.buf+ 1, Label, Label_Len);
	memcpy(C_Info->DataBuf.buf+ 1 + Label_Len, std::to_string(Width_Len).c_str(), 1);
	memcpy(C_Info->DataBuf.buf + 1 + Label_Len+1,std::to_string(Height_Len).c_str(), 1);
	memcpy(C_Info->DataBuf.buf + 1 + Label_Len + 1 + 1, std::to_string(width).c_str(),Width_Len);
	memcpy(C_Info->DataBuf.buf + 1 + Label_Len + 1 + 1 + Width_Len, std::to_string(height).c_str(), Height_Len);
	//memcpy(C_Info->DataBuf.buf + 1 + Label_Len + 1 + 1 + Width_Len + Height_Len, std::to_string(height).c_str(), Height_Len);
	//if ( room < Image_Len)
	{
		//memcpy(C_Info->DataBuf.buf + 1 + Label_Len + 1 + 1 + Width_Len + Height_Len, Img_Data, 10);
		
	}
	memcpy(C_Info->DataBuf.buf + 1 + Label_Len + 1 + 1 + Width_Len + Height_Len,Img_Data, Image_Len);
	cv::Mat Imaged = cv::Mat(height,width, CV_8UC3,  Img_Data);
	cv::imshow("test",Imaged);
	//std::string test(Mess);
	//qDebug() << Label_Len;
	//qDebug() << Label;
	//qDebug() << Height_Len;
	//qDebug(QString::fromUtf8(Mess));

	
	
	return full_length;
	


}
