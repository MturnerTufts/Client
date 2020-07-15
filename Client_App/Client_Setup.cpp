#pragma once
#include "Client_Setup.h"
#include <opencv2\core\base.hpp>



bool Start_Winsock()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		printf("failed to start winsock");
		return false;
	}
	printf("Winsock started");
	return true;
}

bool Client_Socket_setup(LPCLIENT_INFORMATION C_Info)
{
	C_Info->Read = true;
\
	ULONG Non_Block = 1;
	C_Info->client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (C_Info->client_socket == INVALID_SOCKET)
	{
		printf("client_socket failed with code %d");
		return false;
	}

	C_Info->server.sin_family = AF_INET;
	C_Info->server.sin_port = htons(iPort);
	C_Info->server.sin_addr.s_addr = inet_addr("10.0.0.65");

	if (connect(C_Info->client_socket, (struct sockaddr*)&C_Info->server, sizeof(C_Info->server)) == SOCKET_ERROR)
	{
		printf("coudln't conect to server");
		return false;
	}
	if (ioctlsocket(C_Info->client_socket, FIONBIO, &Non_Block) == SOCKET_ERROR)
	{
		return false;
	}
		return true;

}

bool Set_Read_Write(LPCLIENT_INFORMATION C_Info)
{
	FD_ZERO(&C_Info->ReadSet);
	FD_ZERO(&C_Info->WriteSet);
	if (C_Info->Read == true)
		FD_SET(C_Info->client_socket, &C_Info->ReadSet);
	else
		FD_SET(C_Info->client_socket, &C_Info->WriteSet);
	if ((C_Info->Total_fd = select(0, &C_Info->ReadSet, &C_Info->WriteSet, NULL, NULL)))
	{
		printf("select returned an error");
		return false;
	}
	return true;

}
void Recv_Mes(LPCLIENT_INFORMATION C_Info)
{
	DWORD Flags = 0;
	
	
	if (FD_ISSET(C_Info->client_socket, &C_Info->ReadSet) && C_Info->Total_fd > 0)
		C_Info->Total_fd--;
	if (WSARecv(C_Info->client_socket, &(C_Info->DataBuf), 1, &C_Info->BytesRECV, &Flags, NULL, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			FreeSocketInformation(C_Info);//cleanup memory
		}
	}
	else
	{
		if (C_Info->BytesRECV == 0)
		{
			FreeSocketInformation(C_Info);
		}
	}
	//Send_Mes(C_Info);

}

void Send_Mes(LPCLIENT_INFORMATION C_Info)
{
	DWORD Flags = 0;
	if (FD_ISSET(C_Info->client_socket, &C_Info->WriteSet) && C_Info->Total_fd > 0)
	{
	//	C_Info->Total_fd--;
		if (WSASend(C_Info->client_socket, &(C_Info->DataBuf), 1, &C_Info->BytesSEND, Flags, NULL, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("WSASEND failed");
				FreeSocketInformation(C_Info);
			}

		}
		else
		{
			printf("\n");
			printf("it sent");
			printf("\n");
		}
		C_Info->BytesRECV = 0;
		printf("bytes sent: ");
		printf("\n");
	}
	
}

bool begin_client(LPCLIENT_INFORMATION C_Info)
{
	if (Start_Winsock() && Client_Socket_setup(C_Info) == false)
		return false;
	return true;
	//Set_Read_Write(C_Info);
/*	while (true)
	{
		printf("next step");
		Set_Read_Write(C_Info);
		Send_Recv(C_Info);
		Send_Mes(C_Info);

	}
	*/
	return true;
	
}


void FreeSocketInformation(LPCLIENT_INFORMATION C_Info)
{
	closesocket(C_Info->client_socket);
	delete[] C_Info;
}

void Send_Img(LPCLIENT_INFORMATION C_Info)
{
	
}




