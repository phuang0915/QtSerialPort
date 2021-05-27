#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtSerialPort.h"
#include <qfile.h>
#include <QSerialPort>

class QtSerialPort : public QMainWindow
{
	Q_OBJECT

public:
	QtSerialPort(QWidget *parent = Q_NULLPTR);
	~QtSerialPort();

	
public slots:
	void refresh();


private:
	Ui::QtSerialPortClass ui;

	QSerialPort *serial = nullptr;

	// QSharedPointer<QSerialPort> serial =QSharedPointer<QSerialPort>(new QSerialPort(this));
	void on_openButton_clicked();
	void receiveInfo();

	QFile file;
};
