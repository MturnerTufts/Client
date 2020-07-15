#pragma once
#include "Client_Setup.h"
#include <QtWidgets/QMainWindow>
#include "Info.h"
#include "Snipping.h"
#include "ui_Client_App.h"

class Client_App : public QMainWindow
{
    Q_OBJECT

public:
    Client_App(QWidget* parent = Q_NULLPTR);
    LPCLIENT_INFORMATION Client_Info;
private:
    Ui::Client_AppClass ui;
    void Send_Name();
    Snipping_Tool* tool;
private slots:
    void server_join();
    void open_snippet();
    void send_image(int Img_Size, cv::Mat Img, Snipping_Tool* tool);

};