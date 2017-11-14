#include "Header.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	
	// создаем кнопку
	ofd_button = new QPushButton("START for 1", this);
	ofd_button->setGeometry(QRect(QPoint(20, 20),QSize(70, 30)));
	graph_button = new QPushButton("GRAPH", this);
	graph_button->setGeometry(QRect(QPoint(20, 60), QSize(70, 30)));
	close_button = new QPushButton("CLOSE", this);
	close_button->setGeometry(QRect(QPoint(20, 100), QSize(70, 30)));
	// устанавливаем размер и положение кнопки
	//m_button->setGeometry(QRect(QPoint(100, 100),
		//QSize(200, 50)));
	//QHBoxLayout *layout = new QHBoxLayout(this);
	//layout->addWidget(ofd_button);
	//layout->addWidget(star_tButton);
	//layout->addWidget(graph_button);
	//layout->addWidget(close_button);
	// подключаем сигнал к соответствующему слоту
	//connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));
	connect(ofd_button, SIGNAL(released()), this, SLOT(openFile()));
	connect(graph_button, SIGNAL(released()), this, SLOT(handleButton()));
	connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void MainWindow::handleButton()
{
	// меняем текст
	graph_button->setText("Example");
	// изменяем размер кнопки
	graph_button->resize(100, 100);
}

void MainWindow::openFile()
	{
		QString filename = QFileDialog::getOpenFileName(
			this,
			"Open Document",
			QDir::currentPath(),
			"All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");

		if (!filename.isNull())
		{
			qDebug() << "selected file path : " << filename.toUtf8();
		}
	}

MainWindow::~MainWindow()
{

}