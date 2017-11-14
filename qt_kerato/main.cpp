#include "Header.h"
using namespace std;





int main(int argc, char *argv[])
{

	//QApplication app(argc, argv);

	//MainWindow mainWindow;
	//mainWindow.resize(100, 150);
	//mainWindow.show();
	//return app.exec();

	Mat image_source;

	wchar_t currDirfordir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currDirfordir);
	wcscat(currDirfordir, L"\\pat_in\\");
	_bstr_t name_dir(currDirfordir);
	_bstr_t name_image("1_2.jpg");
	strcat(name_dir, name_image);
	const char* image_dir = name_dir;
	image_source = imread(image_dir, CV_LOAD_IMAGE_GRAYSCALE);
	
	int center = 0;
	vector<vector_for_graph> double_app_radius_up, double_app_radius_down, double_app_distance;
	
	//Производим предварительную обработку изображения
	Kerato_image_proc obj_image_proc;
	center = obj_image_proc.calc_center(image_source);
	obj_image_proc.delete_auto_frame(image_source, center);
	obj_image_proc.brightness_delete(image_source);
	obj_image_proc.binar(image_source);
	obj_image_proc.two_line(image_source);
	
	
	short int trashold = 40;
	char n[2] = "1";
	vector<out_str> vostr;
	vector<point_str> vpstr_up, vpstr_down;
	vector<lines_param> line_1, line_2;
	vector<value_for_radius> vfru, vfrd;
	vector<vector_for_graph> radius_up, radius_down, distance, appr_radius_up, appr_radius_down, appr_distance, double_appr_radius_up, double_appr_radius_down, double_appr_distance;
	size_mat size_mat_str = { image_source.cols , image_source.rows ,  image_source.cols , image_source.rows };

	//Производим вычисления параметров
	Kerato_calculate obj_calculate(image_source);
	obj_calculate.split_image(image_source, line_1, line_2, trashold);
	obj_calculate.vector_to_vector_for_radius(line_1, line_2, vfru, vfrd);
	obj_calculate.calc_radius(vfru, vfrd, radius_up, radius_down);
	obj_calculate.calc_distance(image_source, vfru, vfrd, distance);
	obj_calculate.calc_double_approxim(radius_up, radius_down, distance, double_app_radius_up, double_app_radius_down, double_app_distance);
	obj_calculate.create_graph(image_source, double_app_radius_up, double_app_radius_down, double_app_distance, n, name_image, center);

	//Принимаем решение
	Kerato_determination obj_determination;
	obj_determination.calc_discus(double_app_radius_up, double_app_radius_down, double_app_distance, center);
	
	exit(0);
	
	

}
