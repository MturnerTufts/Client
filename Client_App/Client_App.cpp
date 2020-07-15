#pragma once
#include "qdebug.h"
#include <new>
#include "Client_App.h"



Client_App::Client_App(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Client_Info = (LPCLIENT_INFORMATION)new int[sizeof(LPCLIENT_INFORMATION)*15];
	qDebug("size of");
	qDebug() << sizeof(LPCLIENT_INFORMATION);
	tool = new Snipping_Tool();
	tool->Client_Info = Client_Info;
	connect(ui.Connect_Server_But, SIGNAL(clicked()), this, SLOT(server_join()));
	connect(ui.test, SIGNAL(clicked()), this, SLOT(open_snippet()));

}

void Client_App::server_join()
{
	
	ui.Connect_Server_But->setText("testing");
	if (begin_client(Client_Info) == false)
	{
		ui.Connect_Server_But->setText("Could not Connect to Server");

	}
	 else
	 {
		
		 ui.Connect_Server_But->setEnabled(false);
		 ui.Username_Input->setEnabled(false);
		
		 Send_Name();
	
		 
	 }
	

}

void Client_App::Send_Name()
{
	QString name= ui.Username_Input->text();
	char* name_char;
	std::string str_name = name.toStdString();
	name_char = new char[str_name.size() + 1];
	strcpy(name_char, str_name.c_str());

	
	int namelen = name.length();
	ui.Username_Input->setText(QString::number(namelen));
	
	Client_Info->DataBuf.len=Add_To_Buffer(Client_Info, Name_Label, name_char, 2, namelen);
	
	Client_Info->Read = false;
	Set_Read_Write(Client_Info);
	Send_Mes(Client_Info);
	Client_Info->Read = true;
	//Set_Read_Write(Client_Info);
	//Recv_Mes(Client_Info);
	delete[] name_char;
	qDebug(Client_Info->DataBuf.buf);
	delete[]  Client_Info->DataBuf.buf;

}

void Client_App::send_image(int Img_Size, cv::Mat Img, Snipping_Tool* tool)
{
	

}


void Client_App::open_snippet()
{
	
	
	tool->show();
	

}
