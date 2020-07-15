#include "Info.h"





bool Start_Winsock();
bool Client_Socket_setup(LPCLIENT_INFORMATION C_Info);
bool Set_Read_Write(LPCLIENT_INFORMATION C_Info);
void Recv_Mes(LPCLIENT_INFORMATION C_Info);
void Send_Mes(LPCLIENT_INFORMATION C_Info);
bool begin_client(LPCLIENT_INFORMATION C_Info);
void FreeSocketInformation(LPCLIENT_INFORMATION C_Info);
void Send_Img(LPCLIENT_INFORMATION C_Info);