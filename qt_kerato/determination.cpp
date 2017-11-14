#include "Header.h"


Kerato_determination::Kerato_determination()
{

}

void Kerato_determination::calc_discus(vector<vector_for_graph>& double_app_radius_up, vector<vector_for_graph>& double_app_radius_down, vector<vector_for_graph>& double_app_distance, int center)
{
	//�����������
	int center_y_max = 0;
	int center_y_min = 0; 
	//�����
	int left_y_max = 0;
	int left_y_min = 0;
	//������
	int right_y_max = 0;
	int right_y_min = 0; 
	int center_poryad = 0;
	//�� �������� ��������� ������. ��������� �������� ��� ������ min � max
	int middle_right_y = 0;
	int middle_left_y = 0;
	int middle_center_y = 0;
	//��������� ����������  ����� min � max
	int interval_right_y = 0;
	int	interval_left_y = 0;
	int	interval_center_y = 0;



	int zx = double_app_radius_up.size() - 2;
	int vect_max = double_app_radius_up[double_app_radius_up.size() - 2].x;
	int vect_min = double_app_radius_up[1].x;



	//�������� ���������� �� ������, ��� ������
	if ((center < vect_min + 60) && (center > vect_max - 60))
	{
		MessageBox(0, L"��� ����������� �� ��������", L"�������", MB_OK);
		exit(0);
	}

	//������� ������� ������ � ������ �������
	for (int i = 1; i < double_app_radius_up.size() - 1; i++)
	{
		if (double_app_radius_up[i].x == center)
		{
			center_poryad = i;
		}
	}

	//������� center_y_max, center_y_min
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

	//������� ����� �������
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

	//������� ������ �������
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

	//�� �������� ��������� ������. ��������� �������� ��� ������ min � max
	middle_right_y = ((right_y_max - right_y_min) / 2) + right_y_min;
	middle_left_y = ((left_y_max - left_y_min) / 2) + left_y_min;
	middle_center_y = ((center_y_max - center_y_min) / 2) + center_y_min;

	//��������� ����������  ����� min � max
	interval_right_y = right_y_max - right_y_min;
	interval_left_y = left_y_max - left_y_min;
	interval_center_y = center_y_max - center_y_min;


	//��������� �������
	if ((middle_left_y > middle_center_y + 35) || (middle_right_y > middle_center_y + 35))
	{
		MessageBox(0, L"��� 2 ������ ��� ����", L"�������", MB_OK);
		exit(0);
	}
	if ((interval_center_y > interval_right_y * 2) || (interval_center_y > interval_left_y * 2))
	{
		MessageBox(0, L"��� �����", L"�������", MB_OK);
		exit(0);
	}
	if ((interval_center_y < interval_right_y * 1.5) || (interval_center_y < interval_left_y * 1.5))
	{
		MessageBox(0, L"��� 1 ������", L"�������", MB_OK);
		exit(0);
	}
	MessageBox(0, L"������� �� �������", L"�������", MB_OK);
	exit(0);
}
