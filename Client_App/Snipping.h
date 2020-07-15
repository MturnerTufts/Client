#pragma once

#include<iostream>
#include <opencv2/highgui/highgui.hpp>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>
#include <QtWidgets/QMainwindow.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "qbitmap.h"

#include "Info.h"
#include<qwindow.h>
#include "qpixmap.h"


#include <stdio.h>
#include "Client_Setup.h"

class Snipping_Tool : public QWidget {
	
	Q_OBJECT
	
public:
	
	Snipping_Tool();
	void Take_Screen_Shot();
	void mousePressEvent(QMouseEvent* events);
	void mouseReleaseEvent(QMouseEvent* events);
	void mouseMoveEvent(QMouseEvent* events);
	int x_start, y_start, x_end, y_end;
	LPCLIENT_INFORMATION Client_Info;
};

