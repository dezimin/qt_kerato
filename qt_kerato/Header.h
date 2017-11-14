#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QHBoxLayout>


#include <iostream>
#include <cmath>
#include <Windows.h>
#include <direct.h>
#include <cstring>
#include <stdio.h>
#include <list>
#include <comdef.h>
#include <fstream>
#include <cstdlib>

#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <opencv2\features2d.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\video.hpp>

#define PI 3.14159265 

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
//#include "qt_header.h"
#include <windows.h>
#include <shellapi.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>

#else // _WIN32

#define	FW_NORMAL	400
#define	FW_BOLD		700

#endif // _WIN32


using namespace std;
using namespace cv;



struct point_for_dist
{
	int pfd_x;
	int pfd_y;
};

struct vector_for_graph
{
	int x; 
	int y; //Значение радиуса или дистанции в точке x
};

struct data_for_approx
{
	double x, y, xy, x2, y2;
};

struct point_str {
	double x_a;
	double y_a;
	double x_b;
	double y_b;
	double x_c;
	double y_c;
};

struct out_str {
	double radius_1;
	double radius_2;
	double interval;
};

struct size_mat
{
	int xmax_up;
	int ymax_up;
	int xmax_down;
	int ymax_down;
};

struct lines_param
{
	int zx;
	int zy;
};

struct value_for_radius
{
	int x1;
	int y1;

	int x2;
	int y2;

	int x3;
	int y3;
};


namespace Ui 
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

	private slots:
	void handleButton();
	void openFile();

private:
	QPushButton *ofd_button;
	QPushButton *close_button;
	QPushButton *graph_button;
};


class Kerato_image_proc 
{

private:

public:
	//Image_proc(Mat image_in, Mat image_source);
	Kerato_image_proc();
	int auto_k_for_frame(Mat image_source, int dy, int dx, bool select);
	void delete_auto_frame(Mat image_source, int center);
	int calc_center(Mat image_source);
	void delete_frame(Mat image_source, short int fx1, short int fx2);
	void brightness_delete(Mat image_source);
	void delete_noise(Mat image_source);
	void main_binar(Mat image_source);
	void binar(Mat image_source);
	void delete_noise_mini(Mat image_source);
	void sobel(Mat image_source);
	void two_line(Mat image_source);
	void finishing(Mat image_source);
	void two_line_complete(Mat image_source);
	void lines_to_mat(Mat image_source, Mat image_proc, int zx, int zy);
	bool stop_auto_frame_light(Mat image_source, int zx, int zy, bool select);
	short int juke_step(Mat image, short int prev_step, short int trashold, int zx, int zy, bool select);
	short int juke_step_two_line(Mat image, short int prev_step, short int trashold, int zx, int zy, bool select);
	void end_filter(Mat image_source);
	void line_allocation(Mat image_source);
};

class Kerato_calculate
{

private:

public:
	Kerato_calculate(Mat image_source);
	void start_func_kerato(Mat image_source, size_mat size_mat_str, vector<point_str> vpstr_up, vector<point_str> vpstr_down, vector<out_str> vostr, short int trashold, char n[2], _bstr_t name_image, int center);
	void line_to_vector(Mat image_source, vector<lines_param>& line, int zx, int zy, short int trashold);
	bool test_line_for_vector(vector<lines_param>& line, int zx, int zy);
	void split_image(Mat image_source, vector<lines_param>& line_1, vector<lines_param>& line_2, short int trashold);
	short int step_juke(int zx, int zy, Mat image_source, short int trashold, short int prev_step);
	void vector_to_vector_for_radius(vector<lines_param>& line_1, vector<lines_param>& line_2, vector<value_for_radius>& vfru, vector<value_for_radius>& vfrd);
	void calc_radius_by_3_points(vector<value_for_radius>& vfr, vector<vector_for_graph>& radius_line);
	void calc_radius(vector<value_for_radius>& vfru, vector<value_for_radius>& vfrd, vector<vector_for_graph>& radius_up, vector<vector_for_graph>& radius_down);
	void calc_distance(Mat image_source, vector<value_for_radius>& vfru, vector<value_for_radius>& vfrd, vector<vector_for_graph>& distance);
	void print_result(vector<vector_for_graph>& radius_up, vector<vector_for_graph>& radius_down, vector<vector_for_graph> distance);
	void calc_approxim(vector<vector_for_graph>& orig_vector, vector<vector_for_graph>& app_vector);
	void calc_double_approxim(vector<vector_for_graph>& radius_up, vector<vector_for_graph>& radius_down, vector<vector_for_graph>& distance, vector<vector_for_graph>& double_app_radius_up, vector<vector_for_graph>& double_app_radius_down, vector<vector_for_graph>& double_app_distance);
	void create_graph(Mat image_source, vector<vector_for_graph>& double_app_radius_up, vector<vector_for_graph>& double_app_radius_down, vector<vector_for_graph>& double_app_distance, char n[2], _bstr_t name_image, int center);
};

class Kerato_determination
{

private:

public:
	Kerato_determination();
	void calc_discus(vector<vector_for_graph>& double_app_radius_up, vector<vector_for_graph>& double_app_radius_down, vector<vector_for_graph>& double_app_distance, int center);
};

//class Win : public QWidget
//{
//	Q_OBJECT
//protected:
//	QTextCodec * codec;
//	QFrame *frame;
//	QLabel *inputLabel;
//	QLineEdit *inputEdit;
//	QLabel *outputLabel;
//	QLineEdit *outputEdit;
//	QPushButton *ofd_Button;
//	QPushButton *start_Button;
//	QPushButton *graph_Button;
//	QPushButton *exit_Button;
//public:
//	Win(QWidget *parent = 0);
//	public slots:
//	void ofd();
//	void start();
//	void graph();
//};