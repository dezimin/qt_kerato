#include "Header.h"


Kerato_determination::Kerato_determination()
{

}

void Kerato_determination::calc_discus(vector<vector_for_graph>& double_app_radius_up, vector<vector_for_graph>& double_app_radius_down, vector<vector_for_graph>& double_app_distance, int center)
{
	//Центральные
	int center_y_max = 0;
	int center_y_min = 0; 
	//Левые
	int left_y_max = 0;
	int left_y_min = 0;
	//Правые
	int right_y_max = 0;
	int right_y_min = 0; 
	int center_poryad = 0;
	//Мы получили первичные данные. Вычисляем середину для каждых min и max
	int middle_right_y = 0;
	int middle_left_y = 0;
	int middle_center_y = 0;
	//Вычисляем расстояние  между min и max
	int interval_right_y = 0;
	int	interval_left_y = 0;
	int	interval_center_y = 0;



	int zx = double_app_radius_up.size() - 2;
	int vect_max = double_app_radius_up[double_app_radius_up.size() - 2].x;
	int vect_min = double_app_radius_up[1].x;



	//Проверка расстояния до концов, для работы
	if ((center < vect_min + 60) && (center > vect_max - 60))
	{
		MessageBox(0, L"Это изображение не подходит", L"Решение", MB_OK);
		exit(0);
	}

	//Находим позицию центра в данном векторе
	for (int i = 1; i < double_app_radius_up.size() - 1; i++)
	{
		if (double_app_radius_up[i].x == center)
		{
			center_poryad = i;
		}
	}

	//Находим center_y_max, center_y_min
	center_y_min = double_app_radius_up[center_poryad].y;

	for (int i = center_poryad - 30; i < center_poryad + 30; i++)
	{
		if (center_y_max < double_app_radius_up[i].y)
		{
			center_y_max = double_app_radius_up[i].y;
		}
		if (center_y_min > double_app_radius_up[i].y)
		{
			center_y_min = double_app_radius_up[i].y;
		}
	}

	//Находим левую границу
	left_y_min = double_app_radius_up[1].y;

	for (int i = 1; i < 30; i++)
	{
		if (left_y_max < double_app_radius_up[i].y)
		{
			left_y_max = double_app_radius_up[i].y;
		}
		if (left_y_min > double_app_radius_up[i].y)
		{
			left_y_min = double_app_radius_up[i].y;
		}
	}

	//Находим правую границу
	right_y_min = double_app_radius_up[double_app_radius_up.size() - 30].y;

	for (int i = double_app_radius_up.size() - 30; i < double_app_radius_up.size(); i++)
	{
		if (right_y_max < double_app_radius_up[i].y)
		{
			right_y_max = double_app_radius_up[i].y;
		}
		if (right_y_min > double_app_radius_up[i].y)
		{
			right_y_min = double_app_radius_up[i].y;
		}
	}

	//Мы получили первичные данные. Вычисляем середину для каждых min и max
	middle_right_y = ((right_y_max - right_y_min) / 2) + right_y_min;
	middle_left_y = ((left_y_max - left_y_min) / 2) + left_y_min;
	middle_center_y = ((center_y_max - center_y_min) / 2) + center_y_min;

	//Вычисляем расстояние  между min и max
	interval_right_y = right_y_max - right_y_min;
	interval_left_y = left_y_max - left_y_min;
	interval_center_y = center_y_max - center_y_min;


	//Принимаем решение
	if ((middle_left_y > middle_center_y + 35) || (middle_right_y > middle_center_y + 35))
	{
		MessageBox(0, L"Это 2 стадия или выше", L"Решение", MB_OK);
		exit(0);
	}
	if ((interval_center_y > interval_right_y * 2) || (interval_center_y > interval_left_y * 2))
	{
		MessageBox(0, L"Это норма", L"Решение", MB_OK);
		exit(0);
	}
	if ((interval_center_y < interval_right_y * 1.5) || (interval_center_y < interval_left_y * 1.5))
	{
		MessageBox(0, L"Это 1 стадия", L"Решение", MB_OK);
		exit(0);
	}
	MessageBox(0, L"Решение не найдено", L"Решение", MB_OK);
	exit(0);
}
