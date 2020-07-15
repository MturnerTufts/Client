#pragma once
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include <Windows.h>
#include "qdebug.h"
#include<stdio.h>
#include "Info.h"
#include <stdlib.h>
#include <string>
#include<iostream>
#include<iostream>

#pragma comment(lib,"ws2_32.lib")

#define DATA_BUFSIZE 8888
#define iPort 8080

#define Name_Label "NL"
#define Img_Label "IL"

typedef struct _SOCKET_INFORMATION
{
	
	WSABUF DataBuf;
	
	sockaddr_in server;
	SOCKET client_socket;
	FD_SET ReadSet;
	FD_SET WriteSet;
	DWORD BytesSEND;
	DWORD BytesRECV;
	DWORD Total_fd;
	bool Read;
	std::string Name;
	CHAR Buffer[DATA_BUFSIZE];


}Client_Information, * LPCLIENT_INFORMATION;
int Add_To_Buffer(LPCLIENT_INFORMATION C_Info, char* Mes_Label, char* Mes, int Mes_Label_Len, int Mes_Len);
int Add_Img_To_Buffer(LPCLIENT_INFORMATION C_Info, char* Label, int Label_Len, int width, int height, uchar* Img_Data, int Image_Len);