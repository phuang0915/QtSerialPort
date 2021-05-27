#include "QtSerialPort.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

QtSerialPort::QtSerialPort(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	serial = new QSerialPort();

	serial->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);//设置波特率和读写方向
	serial->setDataBits(QSerialPort::Data8);      //数据位为8位
	serial->setFlowControl(QSerialPort::NoFlowControl);//无流控制
	serial->setParity(QSerialPort::NoParity); //无校验位
	serial->setStopBits(QSerialPort::OneStop); //一位停止位

	connect(ui.openButton, &QPushButton::clicked, this, &QtSerialPort::on_openButton_clicked);
	connect(ui.refreshButton, &QPushButton::clicked, this, &QtSerialPort::refresh);
	connect(serial, &QSerialPort::readyRead, this, &QtSerialPort::receiveInfo);
	connect(ui.writeButton, &QPushButton::clicked, [&]
	{


	});
	connect(ui.clearButton, &QPushButton::clicked, [&] {
		ui.textBrowser->clear();
	});

	refresh();//刷新
}


QtSerialPort::~QtSerialPort()
{
	delete serial;
}

void QtSerialPort::refresh()
{
	//获取可用串口
	ui.comboBox->clear();
	const auto infos = QSerialPortInfo::availablePorts();
	for (const QSerialPortInfo &info : infos)
	{
		ui.comboBox->addItem(info.portName());
	}
}

void QtSerialPort::on_openButton_clicked()
{
	if (ui.openButton->text() == QString("Open Port")) {
		ui.openButton->setText("Close Port");
		ui.refreshButton->setEnabled(false);
		ui.comboBox->setEnabled(false);
		ui.writeButton->setEnabled(true);



		serial->setPortName(ui.comboBox->currentText());//当前选择的串口名字



		if (serial->open(QIODevice::ReadWrite))
		{


			QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy-MM-dd-hh-mm-ss");
			file.setFileName(current_date + ".txt");
			if (file.open(QIODevice::WriteOnly | QIODevice::Text))
			{
			}


		}
		else
		{

			QMessageBox::information(nullptr, "Warning", "Cannot open SerialPort",
				QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		}

	}
	else {
		ui.openButton->setText("Open Port");
		ui.refreshButton->setEnabled(true);
		ui.comboBox->setEnabled(true);


		if (serial->isOpen())
		{
			serial->close();
		}
		if (file.isOpen()) {
			file.close();
		}


	}

}

void QtSerialPort::receiveInfo() {

	QByteArray info = serial->readAll();
	qDebug() << "receive info:" << info;
	ui.textBrowser->insertPlainText(info);

	if (ui.textBrowser->toPlainText().length() > 100) {
		ui.textBrowser->clear();
	}


	file.write(info);



}
