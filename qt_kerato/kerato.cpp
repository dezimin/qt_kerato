#include "Header.h"

	Kerato_calculate::Kerato_calculate(Mat image_source)
	{
		//image_curves_up = image_source;
		//image_curves_down = image_source;

		//null_mat(image_curves_up);
		//null_mat(image_curves_down);

	/*	imshow("result", image_curves_up);
		waitKey(0);
		imshow("result", image_curves_down);
		waitKey(0);*/
	}
	
	short int Kerato_calculate::step_juke(int zx, int zy, Mat image, short int trashold, short int prev_step)
	{
		//Ходы по горизонтали и вертикали
		//if ((0 < zy < image.rows) && (0 < zx < image.cols) && (image.at<unsigned char>(zx, (zy - 1)) > trashold) && ((zy - 1) > 0))
		if (0 <= zy < image.rows)
		{
			if (0 <= zx < image.cols)
			{
				if ((prev_step == 3) && (zy == (image.rows - 1)))
				{
					return 0;
				}
				
				if ((image.at<unsigned char>(zy, (zx + 1)) > trashold) && (prev_step != 8))
				{
					return 3;
				}
				if ((image.at<unsigned char>((zy - 1), zx) > trashold) && (prev_step != 5))
				{
					return 4;
				}
				if ((image.at<unsigned char>((zy + 1), zx) > trashold) && (prev_step != 4))
				{
					return 5;
				}
				if ((image.at<unsigned char>((zy - 1), (zx + 1)) > trashold) && (prev_step != 7))
				{
					return 1;
				}
				if ((image.at<unsigned char>((zy + 1), (zx + 1)) > trashold) && (prev_step != 6))
				{
					return 2;
				}
				/*if ((image.at<unsigned char>((zy - 1), (zx - 1)) > trashold) && (prev_step != 2))
				{
					return 6;
				}
				if ((image.at<unsigned char>((zy + 1), (zx - 1)) > trashold) && (prev_step != 1))
				{
					return 7;
				}
				if ((image.at<unsigned char>(zy, (zx - 1)) > trashold) && (prev_step != 3))
				{
					return 8;
				}*/
			}
		}
		return 0;
	}
	
	void Kerato_calculate::vector_to_vector_for_radius(vector<lines_param>& line_1, vector<lines_param>& line_2, vector<value_for_radius>& vfru, vector<value_for_radius>& vfrd)
	{
		int gf = 0;
		std::ifstream in;
		//in.open("E:\\MEGA\\Work\\qt_Kerato_calculate\\qt_Kerato_calculate\\qt_Kerato_calculate\\qt_Kerato_calculate\\distance.ini");
		in.open("distance.ini");
		in >> gf;
		for (int q = 180; q < line_1.size(); q++)
		{
			value_for_radius vu;
			vu.x3 = line_1[q].zx;
			vu.y3 = line_1[q].zy;
			vu.x2 = line_1[q - gf].zx;
			vu.y2 = line_1[q - gf].zy;
			vu.x1 = line_1[q - (gf * 2)].zx;
			vu.y1 = line_1[q - (gf * 2)].zy;
			vfru.push_back(vu);
		}
		for (int q = 180; q < line_2.size(); q++)
		{
			value_for_radius vd;
			vd.x3 = line_2[q].zx;
			vd.y3 = line_2[q].zy;
			vd.x2 = line_2[q - gf].zx;
			vd.y2 = line_2[q - gf].zy;
			vd.x1 = line_2[q - (gf * 2)].zx;
			vd.y1 = line_2[q - (gf * 2)].zy;
			vfrd.push_back(vd);
		}
		in.close();
	}

	void Kerato_calculate::calc_radius_by_3_points(vector<value_for_radius>& vfr, vector<vector_for_graph>& radius_line)
	{
		vector_for_graph z;
		double ab, bc, ac, p, s, radius;
		for (int r = 0; r < vfr.size(); r++)
		{
			/*double ma_1 = (vfru[i].y_b - vpstr_up[i].y_a) / (vpstr_up[i].x_b - vpstr_up[i].x_a);
			double mb_1 = (vpstr_up[i].y_c - vpstr_up[i].y_b) / (vpstr_up[i].x_c - vpstr_up[i].x_b);
			double x_z_1 = (ma_1 * mb_1 * (vpstr_up[i].y_a - vpstr_up[i].y_c) + mb_1 * (vpstr_up[i].x_a + vpstr_up[i].x_b) - ma_1 * (vpstr_up[i].x_b + vpstr_up[i].x_c)) / (2 * (mb_1 - ma_1));
			double y_z_1 = (-1 / ma_1) * (x_z_1 - ((vpstr_up[i].x_a + vpstr_up[i].x_b) / 2)) + ((vpstr_up[i].y_a + vpstr_up[i].y_b) / 2);
			double rad_1 = sqrt(pow((vpstr_up[i].x_a - x_z_1), 2) + pow((vpstr_up[i].y_a - y_z_1), 2));
			double ma_1 = 0;
			double mb_1 = 0;
			double x_z_1 = 0;
			double y_z_1 = 0;
			int rad_1 = 0; */

			ab = 0;
			bc = 0;
			ac = 0;
			p = 0;
			s = 0;
			radius = 0;

			//3A 2B 1C
			ab = sqrt(pow((vfr[r].x2 - vfr[r].x3), 2) + pow((vfr[r].y2 - vfr[r].y3), 2));
			bc = sqrt(pow((vfr[r].x1 - vfr[r].x2), 2) + pow((vfr[r].y1 - vfr[r].y2), 2));
			ac = sqrt(pow((vfr[r].x1 - vfr[r].x3), 2) + pow((vfr[r].y1 - vfr[r].y3), 2));
			p = (ab + bc + ac) / 2;
			s = sqrt(p*(p - ab)*(p - bc)*(p - ac));
			radius = (ab * bc * ac) / (4 * s);

			/*if ((x2 - x1) == 0)
			{
			continue;
			}
			ma_1 = ((y2 - y1) / (x2 - x1));
			if ((x3 - x2) == 0)
			{
			continue;
			}
			mb_1 = ((y3 - y2) / (x3 - x2));
			if ((mb_1 - ma_1) == 0)
			{
			continue;
			}
			x_z_1 = ((ma_1 * mb_1 * (y1 - y3)) + (mb_1 * (x1 + x2)) - (ma_1 * (x2 + x3))) / (2 * (mb_1 - ma_1));
			if ((ma_1) == 0)
			{
			continue;
			}
			y_z_1 = (-1 / ma_1) * (x_z_1 - ((x1 + x2) / 2)) + ((y1 + y2) / 2);
			if (pow((x1 - x_z_1), 2) + pow((y1 - y_z_1), 2) == 0)
			{
			continue;
			}
			double rad_1 = sqrt(pow((x1 - x_z_1), 2) + pow((y1 - y_z_1), 2));*/

			z.x = vfr[r].x2;
			z.y = radius;
			radius_line.push_back(z);
		}
	}
	
	void Kerato_calculate::calc_radius(vector<value_for_radius>& vfru, vector<value_for_radius>& vfrd, vector<vector_for_graph>& radius_up, vector<vector_for_graph>& radius_down)
	{
		//vector_for_graph up, down;
		//double ab, bc, ac, p, s, radius;
		////Вычисление радиуса верхней кривой.
		//for (int r = 0; r < vfru.size(); r++)
		//{
		//	/*double ma_1 = (vfru[i].y_b - vpstr_up[i].y_a) / (vpstr_up[i].x_b - vpstr_up[i].x_a);
		//	double mb_1 = (vpstr_up[i].y_c - vpstr_up[i].y_b) / (vpstr_up[i].x_c - vpstr_up[i].x_b);
		//	double x_z_1 = (ma_1 * mb_1 * (vpstr_up[i].y_a - vpstr_up[i].y_c) + mb_1 * (vpstr_up[i].x_a + vpstr_up[i].x_b) - ma_1 * (vpstr_up[i].x_b + vpstr_up[i].x_c)) / (2 * (mb_1 - ma_1));
		//	double y_z_1 = (-1 / ma_1) * (x_z_1 - ((vpstr_up[i].x_a + vpstr_up[i].x_b) / 2)) + ((vpstr_up[i].y_a + vpstr_up[i].y_b) / 2);
		//	double rad_1 = sqrt(pow((vpstr_up[i].x_a - x_z_1), 2) + pow((vpstr_up[i].y_a - y_z_1), 2));*/
		//	/*double ma_1 = 0;
		//	double mb_1 = 0;
		//	double x_z_1 = 0;
		//	double y_z_1 = 0;
		//	int rad_1 = 0; 
		//	ab = 0;
		//	bc = 0;
		//	ac = 0;
		//	p = 0;
		//	s = 0;
		//	radius = 0;
		//	double y1 = vfru[r].up_y1;
		//	double y2 = vfru[r].up_y2;
		//	double y3 = vfru[r].up_y3;
		//	double x1 = vfru[r].up_x1;
		//	double x2 = vfru[r].up_x2;
		//	double x3 = vfru[r].up_x3;
		//	
		//	//3A 2B 1C
		//	ab = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));
		//	bc = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
		//	ac = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
		//	p = (ab + bc + ac) / 2;
		//	s = sqrt(p*(p - ab)*(p - bc)*(p - ac));
		//	radius = (ab * bc * ac) / (4 * s);
		//	/*if ((x2 - x1) == 0)
		//	{
		//		continue;
		//	}
		//	ma_1 = ((y2 - y1) / (x2 - x1));
		//	if ((x3 - x2) == 0)
		//	{
		//		continue;
		//	}
		//	mb_1 = ((y3 - y2) / (x3 - x2));
		//	if ((mb_1 - ma_1) == 0)
		//	{
		//		continue;
		//	}
		//	x_z_1 = ((ma_1 * mb_1 * (y1 - y3)) + (mb_1 * (x1 + x2)) - (ma_1 * (x2 + x3))) / (2 * (mb_1 - ma_1));
		//	if ((ma_1) == 0)
		//	{
		//		continue;
		//	}
		//	y_z_1 = (-1 / ma_1) * (x_z_1 - ((x1 + x2) / 2)) + ((y1 + y2) / 2);
		//	if (pow((x1 - x_z_1), 2) + pow((y1 - y_z_1), 2) == 0)
		//	{
		//		continue;
		//	}
		//	double rad_1 = sqrt(pow((x1 - x_z_1), 2) + pow((y1 - y_z_1), 2));*/
		//	
		//	up.x = x2;
		//	up.rad = radius;
		//	radius_up.push_back(up);
		//	
		//}
		//for (int r = 0; r < vfrd.size(); r++)
		//{
		//	/*double ma_2 = (vpstr_down[i].y_b - vpstr_down[i].y_a) / (vpstr_down[i].x_b - vpstr_down[i].x_a);
		//	double mb_2 = (vpstr_down[i].y_c - vpstr_down[i].y_b) / (vpstr_down[i].x_c - vpstr_down[i].x_b);
		//	double x_z_2 = (ma_2 * mb_2 * (vpstr_down[i].y_a - vpstr_down[i].y_c) + mb_2 * (vpstr_down[i].x_a + vpstr_down[i].x_b) - ma_2 * (vpstr_down[i].x_b + vpstr_down[i].x_c)) / (2 * (mb_2 - ma_2));
		//	double y_z_2 = (-1 / ma_2) * (x_z_2 - ((vpstr_down[i].x_a + vpstr_down[i].x_b) / 2)) + ((vpstr_down[i].y_a + vpstr_down[i].y_b) / 2);
		//	double rad_2 = sqrt(pow((vpstr_down[i].x_a - x_z_2), 2) + pow((vpstr_down[i].y_a - y_z_2), 2));
		//	radius_down.push_back(rad_2);*/
		//	/*double ma_2 = 0;
		//	double mb_2 = 0;
		//	double x_z_2 = 0;
		//	double y_z_2 = 0;*/
		//	ab = 0;
		//	bc = 0;
		//	ac = 0;
		//	p = 0;
		//	s = 0;
		//	radius = 0;
		//	double y1 = vfrd[r].down_y1;
		//	double y2 = vfrd[r].down_y2;
		//	double y3 = vfrd[r].down_y3;
		//	double x1 = vfrd[r].down_x1;
		//	double x2 = vfrd[r].down_x2;
		//	double x3 = vfrd[r].down_x3;
		//	ab = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));
		//	bc = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
		//	ac = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
		//	p = (ab + bc + ac) / 2;
		//	s = sqrt(p*(p - ab)*(p - bc)*(p - ac));
		//	radius = (ab * bc * ac) / (4 * s);
		//	
		//	/*if ((x2 - x1) == 0) continue;
		//	ma_2 = (y2 - y1) / (x2 - x1);
		//	if ((x3 - x2) == 0) continue;
		//	mb_2 = (y3 - y2) / (x3 - x2);
		//	if ((mb_2 - ma_2) == 0) continue;
		//	x_z_2 = (ma_2 * mb_2 * (y1 - y3) + mb_2 * (x1 + x2) - ma_2 * (x2 + x3)) / (2 * (mb_2 - ma_2));
		//	if ((ma_2) == 0) continue;
		//	y_z_2 = (-1 / ma_2) * (x_z_2 - ((x1 + x2) / 2)) + ((y1 + y2) / 2);
		//	if (pow((x1 - x_z_2), 2) + pow((y1 - y_z_2), 2) == 0) continue;
		//	rad_2 = sqrt(pow((x1 - x_z_2), 2) + pow((y1 - y_z_2), 2));*/
		//	
		//	down.x = x2;
		//	down.rad = rad_2;
		//	radius_down.push_back(down);
		//	
		//}

		calc_radius_by_3_points(vfru, radius_up);
		calc_radius_by_3_points(vfrd, radius_down);
	}
	
	void Kerato_calculate::calc_distance(Mat image_source, vector<value_for_radius>& vfru, vector<value_for_radius>& vfrd, vector<vector_for_graph>& distance)
	{
		vector_for_graph dist;
		int ze = vfru.size();
		
		for (int r = 0; r < vfru.size(); r++)
		{
			vector<point_for_dist> line_for_dist;
			int dst_x = 0;
			int dst_y = 0;

			/*double ab = sqrt(pow((vfru[r].up_x2 - vfru[r].up_x1), 2) + pow((vfru[r].up_y2 - vfru[r].up_y1), 2));
			double bc = sqrt(pow((vfru[r].up_x3 - vfru[r].up_x2), 2) + pow((vfru[r].up_y3 - vfru[r].up_y2), 2));
			double ac = sqrt(pow((vfru[r].up_x3 - vfru[r].up_x1), 2) + pow((vfru[r].up_y3 - vfru[r].up_y1), 2));*/
			/*double p = (ab + bc + ac) / 2;
			double bd = 2 / ac * sqrt(p * (p - ab) * (p - bc) * (p - ac));
			double ad = sqrt(pow(ab, 2) - pow(bd, 2));
			double k = ad / ac;*/
			/*int xd = vfru[r].up_x1 + ((vfru[r].up_x3 - vfru[r].up_x1)*k);
			int yd = vfru[r].up_y1 + ((vfru[r].up_y3 - vfru[r].up_y1)*k);
			int xa = vfru[r].up_x2;
			int ya = vfru[r].up_y2;*/
			/*double A_bd = vfru[r].up_y2 - yd;
			double B_bd = xd - vfru[r].up_x2;
			double C_bd = (vfru[r].up_x2*yd) - (xd*vfru[r].up_y2);*/
			/*if ((A_bd == 0) || (B_bd == 0)) 
			{
				continue;
			}*/

			int up_y3 = vfru[r].y3;
			int up_y2 = vfru[r].y2;
			int up_y1 = vfru[r].y1;
			int up_x3 = vfru[r].x3;
			int up_x2 = vfru[r].x2;
			int up_x1 = vfru[r].x1;
			
			double kac_1 = vfru[r].y3 - vfru[r].y1;
			double kac_2 = vfru[r].x3 - vfru[r].x1;
			double kac = (kac_1 / kac_2);
			double kbd = ((-1) / kac);


			for (int i_y = vfru[r].y2 + 1; i_y < image_source.rows; i_y++)
			{
				point_for_dist point;
				point.pfd_y = i_y;
				point.pfd_x = ((i_y - vfru[r].y2) + (vfru[r].x2 * kbd)) / kbd;
				if (point.pfd_x >= image_source.cols) 
				{
					continue;
				}
				line_for_dist.push_back(point);
			}
			
			bool stop_for = 0; //Остановка следующего цикла

			for (int sp = 0; sp < line_for_dist.size(); sp++)
			{
				if (stop_for == 1)
				{
					break;
				}
				for (int i_vfrd = 0; i_vfrd < vfrd.size(); i_vfrd++)
				{
					if (line_for_dist[sp].pfd_y == vfrd[i_vfrd].y3)
					{
						if (((line_for_dist[sp].pfd_x - 2) == vfrd[i_vfrd].x3) || ((line_for_dist[sp].pfd_x - 1) == vfrd[i_vfrd].x3) || ((line_for_dist[sp].pfd_x + 2) == vfrd[i_vfrd].x3) || ((line_for_dist[sp].pfd_x + 1) == vfrd[i_vfrd].x3) || (line_for_dist[sp].pfd_x == vfrd[i_vfrd].x3))
						{
							dst_x = line_for_dist[sp].pfd_x;
							dst_y = line_for_dist[sp].pfd_y;
							stop_for = 1;
							break;
						}
					}
				}
			}
			if ((dst_x == 0) && (dst_y == 0))
			{
				continue;
			}
				/*
				bool x_sp = 0;
				bool y_sp = 0;
				bool stop_for = 0;

				for (int  i = 0; i < line_for_dist.size(); i++)
				{
					if (line_for_dist[i].pfd_x == vfrd[sp].down_x2) 
					{
						if ((line_for_dist[i].pfd_y == vfrd[sp].down_y2) || ((line_for_dist[i].pfd_y + 1) == vfrd[sp].down_y2) || ((line_for_dist[i].pfd_y - 1) == vfrd[sp].down_y2))
						{
							dst_x = line_for_dist[i].pfd_x;
							dst_y = line_for_dist[i].pfd_y;
							stop_for = 1;
							break;
						}
						else
						{
							continue;
						}
					}
				}*/
			int dist_1 = sqrt(pow((vfru[r].x2 - dst_x), 2) + pow((vfru[r].y2 - (dst_y - 1)), 2));
			
			dist.y = dist_1;
			dist.x = up_x2;

			distance.push_back(dist);

			//for (int h = 0; h < vfrd.size(); h++)
			//{
			//	if (((A_bd * vfrd[h].down_x2) + (B_bd * vfrd[h].down_y2)) == ((-1) * C_bd))
			//	{
			//		//x,y
			//		double dist = sqrt(pow((vfru[r].up_x2 - vfrd[r].down_x2), 2) + pow((vfru[r].up_y2 - vfrd[r].down_y2), 2));
			//		distance.push_back(dist);
			//		continue;
			//	}
			//	if (((A_bd * (vfrd[h].down_x2 - 1)) + (B_bd * (vfrd[h].down_y2 - 1))) == ((-1) * C_bd))
			//	{
			//		//1
			//		double dist = sqrt(pow((vfru[r].up_x2 - (vfrd[r].down_x2 - 1)), 2) + pow((vfru[r].up_y2 - (vfrd[r].down_y2 - 1)), 2));
			//		distance.push_back(dist);
			//		continue;
			//	}
			//	if (((A_bd * vfrd[h].down_x2) + (B_bd * (vfrd[h].down_y2 - 1))) == ((-1) * C_bd))
			//	{
			//		//2
			//		double dist = sqrt(pow((vfru[r].up_x2 - vfrd[r].down_x2), 2) + pow((vfru[r].up_y2 - (vfrd[r].down_y2 - 1)), 2));
			//		distance.push_back(dist);
			//		continue;
			//	}
			//	if (((A_bd * (vfrd[h].down_x2 + 1)) + (B_bd * (vfrd[h].down_y2 - 1))) == ((-1) * C_bd))
			//	{
			//		//3
			//		double dist = sqrt(pow((vfru[r].up_x2 - vfrd[r].down_x2), 2) + pow((vfru[r].up_y2 - vfrd[r].down_y2), 2));
			//		distance.push_back(dist);
			//		continue;
			//	}
			//	if (((A_bd * vfrd[h].down_x2) + (B_bd * vfrd[h].down_y2)) == ((-1) * C_bd))
			//	{
			//		//4
			//		double dist = sqrt(pow((vfru[r].up_x2 - vfrd[r].down_x2), 2) + pow((vfru[r].up_y2 - vfrd[r].down_y2), 2));
			//		distance.push_back(dist);
			//		continue;
			//	}
			//	if (((A_bd * vfrd[h].down_x2) + (B_bd * vfrd[h].down_y2)) == ((-1) * C_bd))
			//	{
			//		double dist = sqrt(pow((vfru[r].up_x2 - vfrd[r].down_x2), 2) + pow((vfru[r].up_y2 - vfrd[r].down_y2), 2));
			//		distance.push_back(dist);
			//	}
			//	if (((A_bd * vfrd[h].down_x2) + (B_bd * vfrd[h].down_y2)) == ((-1) * C_bd))
			//	{
			//		double dist = sqrt(pow((vfru[r].up_x2 - vfrd[r].down_x2), 2) + pow((vfru[r].up_y2 - vfrd[r].down_y2), 2));
			//		distance.push_back(dist);
			//	}	
		}
	}
	
	void Kerato_calculate::print_result(vector<vector_for_graph>& radius_up, vector<vector_for_graph>& radius_down, vector<vector_for_graph> distance)
	{
		cout << "Radius_up_line" << endl;
		for (int i = 0; i < radius_up.size(); i++)
		{
			cout << radius_up[i].y << " ";
		}
		cout << "" << endl;
		cout << "Radius_down_line" << endl;
		for (int i = 0; i < radius_down.size(); i++)
		{
			cout << radius_down[i].y << " ";
		}
		cout << "" << endl;
		cout << "Distance" << endl;
		for (int i = 0; i < distance.size(); i++)
		{
			cout << distance[i].y << " ";
		}
		system("pause");
	}
	
	void Kerato_calculate::calc_approxim(vector<vector_for_graph>& orig_vector, vector<vector_for_graph>& app_vector)
	{
		for (int i = 0; i < (orig_vector.size() - 10); i++) 
		{
			vector <data_for_approx> approx(10);
			for (int iv = 0; iv < 10; iv++)
			{
				approx[iv].x = orig_vector[i + iv].x;
				approx[iv].y = orig_vector[i + iv].y;
				approx[iv].xy = approx[iv].x * approx[iv].y;
				approx[iv].x2 = approx[iv].x * approx[iv].x;
				approx[iv].y2 = approx[iv].y * approx[iv].y;
			}
			
			struct MyStruct
			{
				double sum_x, sum_y, sum_xy, sum_x2, sum_y2, x_mean, y_mean, b, a;
			} data_other{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			

			for (int ib = 0; ib < 10; ib++)
			{
				data_other.sum_x = data_other.sum_x + approx[ib].x;
				data_other.sum_y = data_other.sum_y + approx[ib].y;
				data_other.sum_xy = data_other.sum_xy + approx[ib].xy;
				data_other.sum_x2 = data_other.sum_x2 + approx[ib].x2;
				data_other.sum_y2 = data_other.sum_y2 + approx[ib].y2;
			}

			data_other.x_mean = data_other.sum_x / 10;
			data_other.y_mean = data_other.sum_y / 10;
			
			data_other.b = ((10 * data_other.sum_xy) - (data_other.sum_x * data_other.sum_y)) / ((10 * data_other.sum_x2) - (data_other.sum_x * data_other.sum_x));
			data_other.a = data_other.y_mean - (data_other.b * data_other.x_mean);

			vector_for_graph vfg;
			vfg.x = orig_vector[i].x;
			vfg.y = data_other.a + (data_other.b * vfg.x);

			app_vector.push_back(vfg);
		}
	}

	void Kerato_calculate::calc_double_approxim(vector<vector_for_graph>& radius_up, vector<vector_for_graph>& radius_down, vector<vector_for_graph>& distance, vector<vector_for_graph>& double_app_radius_up, vector<vector_for_graph>& double_app_radius_down, vector<vector_for_graph>& double_app_distance)
	{
		//Для аппроксимированных линий
		vector<vector_for_graph> app_radius_up, app_radius_down, app_distance;

		//Первичная аппроксимация
		calc_approxim(radius_up, app_radius_up);
		calc_approxim(radius_down, app_radius_down);
		calc_approxim(distance, app_distance);
		//Вторичная аппроксимация
		calc_approxim(app_radius_up, double_app_radius_up);
		calc_approxim(app_radius_down, double_app_radius_down);
		//calc_approxim(app_distance, double_app_distance);
		double_app_distance = app_distance;
	}

	void Kerato_calculate::create_graph(Mat image_source, vector<vector_for_graph>& double_app_radius_up, vector<vector_for_graph>& double_app_radius_down, vector<vector_for_graph>& double_app_distance, char n[2], _bstr_t name_image, int center)
	{
		//int y = image_source.rows + 650;
		int y = 850;
		int	x = image_source.cols;
		
		Mat image_res_up (Size(x, y), CV_8UC1);
		Mat image_res_down (Size(x, y), CV_8UC1);
		Mat image_res_dist (Size(x, y), CV_8UC1);
		char name[16] = "image_res.jpg";
		strcat(n, name);



		//Заполняем изображения 
		for (int iy = 0; iy < y; iy++)
		{
			for (int ix = 0; ix < x; ix++)
			{
				image_res_up.at<unsigned char>(iy, ix) = 0;
				image_res_down.at<unsigned char>(iy, ix) = 0;
				image_res_dist.at<unsigned char>(iy, ix) = 0;
			} 
		}

		//рисуем центр
		for (int ipy = 10; ipy < 840; ipy++)
		{
			image_res_up.at<unsigned char>(ipy, center + 50) = 250;
			image_res_down.at<unsigned char>(ipy, center + 50) = 250;
			image_res_dist.at<unsigned char>(ipy, center + 50) = 250;
		}
		
		//Первое изображение

		//Оси и деления..................................................................................................
		for (int ixo1 = 50; ixo1 < (image_source.cols - 50); ixo1++) //Ось x для radius_up
		{
			image_res_up.at<unsigned char>(800, ixo1) = 250;
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int iyo1 = 50; iyo1 < 800; iyo1++) //Ось y для radius_up
		{
			image_res_up.at<unsigned char>(iyo1, 50) = 250;
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int ixd1 = 60; ixd1 < (image_source.cols - 50); ixd1 = ixd1 + 10) //Деления x для radius_up
		{
			for (int iydd1 = 797; iydd1 < 803; iydd1++)
			{
				image_res_up.at<unsigned char>(iydd1, ixd1) = 250;
			}
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int iyd1 = 60; iyd1 < 800; iyd1 = iyd1 + 10) //Деления y для radius_up
		{
			for (int ixdd1 = 47; ixdd1 < 53; ixdd1++)
			{
				image_res_up.at<unsigned char>(iyd1, ixdd1) = 250;
			}
		}
		//-------------------------------------------------------------------------------------------------------------
		
		//Рисуем первый график

		for (int iv1 = 0; iv1 < double_app_radius_up.size(); iv1++)
		{
			int xf = double_app_radius_up[iv1].x + 50;
			int yf = double_app_radius_up[iv1].y;
			int yz = 790;
			if (yf < 700)
			{
				image_res_up.at<unsigned char>((yz - yf), xf) = 250;
				image_res_up.at<unsigned char>((yz - yf - 1), xf - 1) = 250;
				image_res_up.at<unsigned char>((yz - yf - 1), xf) = 250;
				image_res_up.at<unsigned char>((yz - yf - 1), xf + 1) = 250;
				image_res_up.at<unsigned char>((yz - yf), xf - 1) = 250;
				image_res_up.at<unsigned char>((yz - yf), xf + 1) = 250;
				image_res_up.at<unsigned char>((yz - yf + 1), xf - 1) = 250;
				image_res_up.at<unsigned char>((yz - yf + 1), xf) = 250;
				image_res_up.at<unsigned char>((yz - yf + 1), xf + 1) = 250;
			}
			else
			{
				continue;
			}
		}
		//----------------------------------------------------------------------------------------------------------------

		//Второе изображение

		//Оси и деления..................................................................................................
		for (int ixo1 = 50; ixo1 < (image_source.cols - 50); ixo1++) //Ось x для radius_up
		{
			image_res_down.at<unsigned char>(800, ixo1) = 250;
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int iyo1 = 50; iyo1 < 800; iyo1++) //Ось y для radius_up
		{
			image_res_down.at<unsigned char>(iyo1, 50) = 250;
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int ixd1 = 60; ixd1 < (image_source.cols - 50); ixd1 = ixd1 + 10) //Деления x для radius_up
		{
			for (int iydd1 = 797; iydd1 < 803; iydd1++)
			{
				image_res_down.at<unsigned char>(iydd1, ixd1) = 250;
			}
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int iyd1 = 60; iyd1 < 800; iyd1 = iyd1 + 10) //Деления y для radius_up
		{
			for (int ixdd1 = 47; ixdd1 < 53; ixdd1++)
			{
				image_res_down.at<unsigned char>(iyd1, ixdd1) = 250;
			}
		}
		//-------------------------------------------------------------------------------------------------------------
		
		//Рисуем второй график (график радиуса нижней кривой)

		for (int iv2 = 0; iv2 < double_app_radius_down.size(); iv2++)
		{
			int xf = double_app_radius_down[iv2].x + 50;
			int yf = double_app_radius_down[iv2].y;
			int yz = 790;
			if (yf < 700)
			{
				image_res_down.at<unsigned char>((yz - yf), xf) = 250;
				image_res_down.at<unsigned char>((yz - yf - 1), xf - 1) = 250;
				image_res_down.at<unsigned char>((yz - yf - 1), xf) = 250;
				image_res_down.at<unsigned char>((yz - yf - 1), xf + 1) = 250;
				image_res_down.at<unsigned char>((yz - yf), xf - 1) = 250;
				image_res_down.at<unsigned char>((yz - yf), xf + 1) = 250;
				image_res_down.at<unsigned char>((yz - yf + 1), xf - 1) = 250;
				image_res_down.at<unsigned char>((yz - yf + 1), xf) = 250;
				image_res_down.at<unsigned char>((yz - yf + 1), xf + 1) = 250;
			}
			else
			{
				continue;
			}
		}
		//-------------------------------------------------------------------------------------------------------------

		//Третье изображение

		//Оси и деления..................................................................................................
		for (int ixo1 = 50; ixo1 < (image_source.cols - 50); ixo1++) //Ось x для radius_up
		{
			image_res_dist.at<unsigned char>(800, ixo1) = 250;
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int iyo1 = 50; iyo1 < 800; iyo1++) //Ось y для radius_up
		{
			image_res_dist.at<unsigned char>(iyo1, 50) = 250;
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int ixd1 = 60; ixd1 < (image_source.cols - 50); ixd1 = ixd1 + 10) //Деления x для radius_up
		{
			for (int iydd1 = 797; iydd1 < 803; iydd1++)
			{
				image_res_dist.at<unsigned char>(iydd1, ixd1) = 250;
			}
		}
		//-------------------------------------------------------------------------------------------------------------
		for (int iyd1 = 60; iyd1 < 800; iyd1 = iyd1 + 10) //Деления y для radius_up
		{
			for (int ixdd1 = 47; ixdd1 < 53; ixdd1++)
			{
				image_res_dist.at<unsigned char>(iyd1, ixdd1) = 250;
			}
		}
		//-------------------------------------------------------------------------------------------------------------

		//Рисуем третий график (график дистанции)

		for (int iv3 = 0; iv3 < double_app_distance.size(); iv3++)
		{
			int xf = double_app_distance[iv3].x + 50;
			int yf = double_app_distance[iv3].y;
			int yz = 790;
			if (yf < 700)
			{
				image_res_dist.at<unsigned char>((yz - yf), xf) = 250;
				image_res_dist.at<unsigned char>((yz - yf - 1), xf - 1) = 250;
				image_res_dist.at<unsigned char>((yz - yf - 1), xf) = 250;
				image_res_dist.at<unsigned char>((yz - yf - 1), xf + 1) = 250;
				image_res_dist.at<unsigned char>((yz - yf), xf - 1) = 250;
				image_res_dist.at<unsigned char>((yz - yf), xf + 1) = 250;
				image_res_dist.at<unsigned char>((yz - yf + 1), xf - 1) = 250;
				image_res_dist.at<unsigned char>((yz - yf + 1), xf) = 250;
				image_res_dist.at<unsigned char>((yz - yf + 1), xf + 1) = 250;
			}
			else
			{
				continue;
			}
		}
		//-------------------------------------------------------------------------------------------------------------

		//const char* image_out = name_image;
		wchar_t cir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, cir);
		wcscat(cir, L"\\pat_out\\");
		//wcscat(cir, L"\\");
		_bstr_t g_up_out = cir;
		_bstr_t g_down_out = cir;
		_bstr_t g_dist_out = cir;
		g_up_out = g_up_out + "gr_up_" + name_image;
		g_down_out = g_down_out + "gr_down_" + name_image;
		g_dist_out = g_dist_out + "gr_dist_" + name_image;
		const char* g_up = g_up_out;
		const char* g_down = g_down_out;
		const char* g_dist = g_dist_out;

		_bstr_t name_for_radius_up = cir;
		_bstr_t name_for_radius_down = cir;
		_bstr_t name_for_distance = cir;
		name_for_radius_up = name_for_radius_up + "r_up_" + name_image + ".txt";
		name_for_radius_down = name_for_radius_down + "r_down_" + name_image + ".txt";
		name_for_distance = name_for_distance + "dist_" + name_image + ".txt";

		FILE * file1;
		FILE * file2;
		FILE * file3;

		

		
		//file1 = fopen(name_for_radius_up, "w + t");
		//for (int izz = 0; izz < radius_up.size() - 1; izz++)
		//{
		//	fprintf(file1, "%d %d %s", radius_up[izz].x, radius_up[izz].y, "\n");

		//}
		//fclose(file1);

		//
		//file2 = fopen(name_for_radius_down, "w + t");
		//for (int izz = 0; izz < radius_down.size() - 1; izz++)
		//{
		//	fprintf(file2, "%d %d %s", radius_down[izz].x, radius_down[izz].y, "\n");

		//}
		//fclose(file2);

	
		//file3 = fopen(name_for_distance, "w + t");
		//for (int izz = 0; izz < distance.size() - 1; izz++)
		//{
		//	fprintf(file3, "%d %d %s", distance[izz].x, distance[izz].y, "\n");

		//}
		//fclose(file3);

		for (int zx = 0; zx < image_res_up.cols; zx++)
		{
			for (int zy = 0; zy < image_res_up.rows; zy++)
			{
				if (image_res_up.at<unsigned char>(zy, zx) > 20)
				{
					image_res_up.at<unsigned char>(zy, zx) = 0;
				}
				else if (image_res_up.at<unsigned char>(zy, zx) < 20)
				{
					image_res_up.at<unsigned char>(zy, zx) = 250;
				}
				//----
				if (image_res_down.at<unsigned char>(zy, zx) > 20)
				{
					image_res_down.at<unsigned char>(zy, zx) = 0;
				}
				else if (image_res_down.at<unsigned char>(zy, zx) < 20)
				{
					image_res_down.at<unsigned char>(zy, zx) = 250;
				}
				//----
				if (image_res_dist.at<unsigned char>(zy, zx) > 20)
				{
					image_res_dist.at<unsigned char>(zy, zx) = 0;
				}
				else if (image_res_dist.at<unsigned char>(zy, zx) < 20)
				{
					image_res_dist.at<unsigned char>(zy, zx) = 250;
				}
			}
		}
		
		imwrite(g_up, image_res_up);
		imwrite(g_down, image_res_down);
		imwrite(g_dist, image_res_dist);
		//imwrite("image.jpg", image_res_up);

		/*for (int i = 50; i < radius_up.size(); i++)
		{
			image_res.at<unsigned char>((900 - radius_up[i].rad), i) = 250;
		}
		for (int i = 50; i < radius_down.size(); i++)
		{
			image_res.at<unsigned char>((1000 - radius_down[i].rad), i) = 250;
		}
		for (int i = 50; i < distance.size(); i++)
		{
			image_res.at<unsigned char>((1800 - radius_down[i].rad), i) = 250;
		}*/
	}
		
	void Kerato_calculate::line_to_vector(Mat image_source, vector<lines_param>& line, int zx, int zy, short int trashold)
	{
		lines_param l;
		bool v_p = 0;
		short int prev_step = 0;

		while (v_p == 0)
		{
			//Записываем пиксель
			l.zx = zx;
			l.zy = zy;
			line.push_back(l);

			//Запуск поиска следующего хода
			short int result_step = step_juke(zx, zy, image_source, trashold, prev_step);
			switch (result_step)
			{
			case 1:
				prev_step = 1;
				zy = zy - 1;
				zx = zx + 1;
				break;
			case 2:
				prev_step = 2;
				zy = zy + 1;
				zx = zx + 1;
				break;
			case 3:
				prev_step = 3;
				zx = zx + 1;
				break;
			case 4:
				prev_step = 4;
				zy = zy - 1;
				break;
			case 5:
				prev_step = 5;
				zy = zy + 1;
				break;
			//case 6:
			//	prev_step = 6;
			//	zx = zx - 1;
			//	zy = zy - 1;
			//	break;
			//case 7:
			//	prev_step = 7;
			//	zy = zy + 1;
			//	zx = zx - 1;
			//	break;
			//case 8:
			//	prev_step = 8;
			//	zx = zx - 1;
			//	break;
			case 0:
				v_p = 1;
				break;
			default:
				v_p = 1;
				break;
			}

			if (v_p == 1)
			{
				v_p = 0;
				break;
			}
			continue;
		}
	}

	bool Kerato_calculate::test_line_for_vector(vector<lines_param>& line, int zx, int zy)
	{
		for (int i = 0; i < line.size(); i++)
		{
			if ((line[i].zx == zx) && (line[i].zy == zy))
			{
				return 1;
			}
		}
		return 0;
	}

	void Kerato_calculate::split_image(Mat image_source, vector<lines_param>& line_1, vector<lines_param>& line_2, short int trashold)
	{
		//для работы требуется два Mat вне функции, в которые складываются две кривые.
		//Все Mat должны быть в grayScale

		vector<lines_param> line_1_test;
		vector<lines_param> line_2_test;

		//bool complete_bag = 0;
		//bool end_for = 0;
		short int next_line = 0;
		bool stop_split = 0;

		for (int zy = (image_source.rows - 1); zy > 0; zy--)
		{
			if (stop_split == 1)
			{
				break;
			}
			for (int zx = 0; zx < (image_source.cols / 2); zx++)
			{
				if (next_line == 2) 
				{
					stop_split = 1;
				}
				if ((image_source.at<unsigned char>(zy, zx) > trashold) && (next_line == 0))
				{
					line_to_vector(image_source, line_1, zx, zy, trashold);
					next_line = 1;
					zx = zx + 2;
				}
				if ((image_source.at<unsigned char>(zy, zx) > trashold) && (next_line == 1) && (test_line_for_vector(line_1, zx, zy) == 0))
				{
					line_to_vector(image_source, line_2, zx, zy, trashold);
					next_line = 2;
				}
			}
		}

		//Line_2 должна быть down
		//Line_1 должна быть up
		if (line_1[line_1.size() / 2].zy > line_2[line_2.size() / 2].zy)
		{
			line_1_test = line_1;
			line_2_test = line_2;
			line_1 = line_2_test;
			line_2 = line_1_test;
		}
	
	}

	//void Kerato_calculate::start_func_Kerato_calculate(Mat image_source, size_mat size_mat_str, vector<point_str> vpstr_up, vector<point_str> vpstr_down, vector<out_str> vostr, short int trashold, char n[2], _bstr_t name_image, int center)
	//{
	//	vector<lines_param> line_1;
	//	vector<lines_param> line_2;
	//	vector<value_for_radius> vfru, vfrd;
	//	vector<vector_for_graph> radius_up, radius_down, distance, appr_radius_up, appr_radius_down, appr_distance, double_appr_radius_up, double_appr_radius_down, double_appr_distance;

	//	split_image(image_source, line_1, line_2, trashold);
	//	vector_to_vector_for_radius(line_1, line_2, vfru, vfrd);
	//	calc_radius(vfru, vfrd, radius_up, radius_down);
	//	calc_distance(image_source, vfru, vfrd, distance);
	//	//print_result(radius_up, radius_down, distance);
	//	create_graph(image_source, radius_up, radius_down, distance, n, name_image, center);
	//	//result_to_xls(radius_up, radius_down, distance);
	//	//calc_point_str(image_curves_up, image_curves_down, vpstr_up, vpstr_down, size_mat_str);
	//	//calc_out_str(image_source, image_curves_up, image_curves_down, vpstr_up, vpstr_down, vostr, size_mat_str);
	//}

	//double Kerato_calculate::radius(double x_a, double x_b, double x_c, double y_a, double y_b, double y_c) {
	//		double ma = (y_b - y_a) / (x_b - x_a);
	//		double mb = (y_c - y_b) / (x_c - x_b);
	//		double x_z = (ma * mb * (y_a - y_c) + mb * (x_a + x_b) - ma * (x_b + x_c)) / (2 * (mb - ma));
	//		double y_z = (-1 / ma) * (x_z - ((x_a + x_b) / 2)) + ((y_a + y_b) / 2);
	//		return sqrt(pow((x_a - x_z), 2) + pow((y_a - y_z), 2));
	//}

	//double Kerato_calculate::interval_curves(double x_a, double x_b, double x_c, double y_a, double y_b, double y_c, Mat image_curves_up, Mat image_curves_down) {
	//
	//		double ab = sqrt(pow((x_b - x_a), 2) + pow((y_b - y_a), 2));
	//		double bc = sqrt(pow((x_c - x_b), 2) + pow((y_c - y_b), 2));
	//		double ac = sqrt(pow((x_c - x_a), 2) + pow((y_c - y_a), 2));
	//		double p = (ab + bc + ac) / 2;
	//		double bd = 2 / ac * sqrt(p * (p - ab) * (p - bc) * (p - ac));
	//		double ad = sqrt(pow(ab, 2) - pow(bd, 2));
	//		int zx;
	//		int zy;
	//		bool complete_curves_search = 0;
	//		for (int zx = 0; zx < xmax; zx++) {
	//			if (complete_curves_search == 1) {
	//				break;
	//			}
	//			for (int zy = 0; zy < ymax; zy++) {
	//				if (complete_curves_search == 1) {
	//					break;
	//				}
	//				if (z > trashold) {
	//					if (zy - y_b == (-1 * (x_c - x_a) / (y_c - y_a) * (zx - x_b)))
	//						complete_curves_search = 1;
	//				}
	//			}
	//		}
	//	}
	//	
	//}

	//double Kerato_calculate::radius(double x_a, double x_b, double x_c, double y_a, double y_b, double y_c) {
	//		double ma = (y_b - y_a) / (x_b - x_a);
	//		double mb = (y_c - y_b) / (x_c - x_b);
	//		double x_z = (ma * mb * (y_a - y_c) + mb * (x_a + x_b) - ma * (x_b + x_c)) / (2 * (mb - ma));
	//		double y_z = (-1 / ma) * (x_z - ((x_a + x_b) / 2)) + ((y_a + y_b) / 2);
	//		return sqrt(pow((x_a - x_z), 2) + pow((y_a - y_z), 2));
	//	}
	// 

	/*void Kerato_calculate::calc_point_str(Mat image_curves_up, Mat image_curves_down, vector<point_str> vpstr_up, vector<point_str> vpstr_down, size_mat size_mat_str, short int trashold)
	{
	point_str a1;
	point_str a2;
	out_str b;

	for (int xb = 11; xb < (size_mat_str.ymax_up - 11); xb = xb + 10) {
	int xa = xb - 10;
	int xc = xb + 10;
	for (int yb = 0; yb < size_mat_str.xmax_up; yb++) {
	if (image_curves_up.at<unsigned char>(yb, xb) > trashold) {
	a1.x_b = xb;
	a1.y_b = yb;
	break;
	}
	}
	for (int ya = 0; ya < size_mat_str.xmax_up; ya++) {
	if (image_curves_up.at<unsigned char>(ya, xa) > trashold) {
	a1.x_a = xa;
	a1.y_a = ya;
	break;
	}
	}
	for (int yc = 0; yc < size_mat_str.xmax_up; yc++) {
	if (image_curves_up.at<unsigned char>(xc, yc) > trashold) {
	a1.x_c = xc;
	a1.y_c = yc;
	break;
	}
	}
	vpstr_up.emplace_back(a1);
	continue;
	}

	for (int xb = 11; xb < (size_mat_str.ymax_down - 11); xb = xb + 10) {
	int xa = xb - 10;
	int xc = xb + 10;
	for (int yb = 0; yb < size_mat_str.xmax_down; yb++) {
	if (image_curves_down.at<unsigned char>(xb, yb) > trashold) {
	a2.x_b = xb;
	a2.y_b = yb;
	break;
	}
	}
	for (int ya = 0; ya < size_mat_str.xmax_down; ya++) {
	if (image_curves_down.at<unsigned char>(xa, ya) > trashold) {
	a2.x_a = xa;
	a2.y_a = ya;
	break;
	}
	}
	for (int yc = 0; yc < size_mat_str.xmax_down; yc++) {
	if (image_curves_down.at<unsigned char>(xc, yc) > trashold) {
	a2.x_c = xc;
	a2.y_c = yc;
	break;
	}
	}
	vpstr_down.emplace_back(a2);
	continue;
	}
	}*/

	//void Kerato_calculate::calc_out_str(Mat image_source, vector<point_str> vpstr_up, vector<point_str> vpstr_down, vector<out_str> vostr, size_mat size_mat_str, short int trashold)
	//{
	//	for (int i = 0; i < vpstr_up.size(); i++)
	//	{
	//		out_str b;
	//		double ma_1 = (vpstr_up[i].y_b - vpstr_up[i].y_a) / (vpstr_up[i].x_b - vpstr_up[i].x_a);
	//		double mb_1 = (vpstr_up[i].y_c - vpstr_up[i].y_b) / (vpstr_up[i].x_c - vpstr_up[i].x_b);
	//		double x_z_1 = (ma_1 * mb_1 * (vpstr_up[i].y_a - vpstr_up[i].y_c) + mb_1 * (vpstr_up[i].x_a + vpstr_up[i].x_b) - ma_1 * (vpstr_up[i].x_b + vpstr_up[i].x_c)) / (2 * (mb_1 - ma_1));
	//		double y_z_1 = (-1 / ma_1) * (x_z_1 - ((vpstr_up[i].x_a + vpstr_up[i].x_b) / 2)) + ((vpstr_up[i].y_a + vpstr_up[i].y_b) / 2);
	//		double rad_1 = sqrt(pow((vpstr_up[i].x_a - x_z_1), 2) + pow((vpstr_up[i].y_a - y_z_1), 2));
	//		double ma_2 = (vpstr_down[i].y_b - vpstr_down[i].y_a) / (vpstr_down[i].x_b - vpstr_down[i].x_a);
	//		double mb_2 = (vpstr_down[i].y_c - vpstr_down[i].y_b) / (vpstr_down[i].x_c - vpstr_down[i].x_b);
	//		double x_z_2 = (ma_2 * mb_2 * (vpstr_down[i].y_a - vpstr_down[i].y_c) + mb_2 * (vpstr_down[i].x_a + vpstr_down[i].x_b) - ma_2 * (vpstr_down[i].x_b + vpstr_down[i].x_c)) / (2 * (mb_2 - ma_2));
	//		double y_z_2 = (-1 / ma_2) * (x_z_2 - ((vpstr_down[i].x_a + vpstr_down[i].x_b) / 2)) + ((vpstr_down[i].y_a + vpstr_down[i].y_b) / 2);
	//		double rad_2 = sqrt(pow((vpstr_down[i].x_a - x_z_2), 2) + pow((vpstr_down[i].y_a - y_z_2), 2));
	//		double ab = sqrt(pow((vpstr_down[i].x_b - vpstr_down[i].x_a), 2) + pow((vpstr_down[i].y_b - vpstr_down[i].y_a), 2));
	//		double bc = sqrt(pow((vpstr_down[i].x_c - vpstr_down[i].x_b), 2) + pow((vpstr_down[i].y_c - vpstr_down[i].y_b), 2));
	//		double ac = sqrt(pow((vpstr_down[i].x_c - vpstr_down[i].x_a), 2) + pow((vpstr_down[i].y_c - vpstr_down[i].y_a), 2));
	//		double p = (ab + bc + ac) / 2;
	//		double bd = 2 / ac * sqrt(p * (p - ab) * (p - bc) * (p - ac));
	//		double ad = sqrt(pow(ab, 2) - pow(bd, 2));
	//		
	//		int zx;
	//		int zy;
	//		double interval;
	//		bool complete_curves_search = 0;
	//		for (zx = 0; zx < size_mat_str.xmax_up; zx++) {
	//			if (complete_curves_search == 1) {
	//				break;
	//			}
	//			for (zy = 0; zy < size_mat_str.ymax_up; zy++) {
	//				if (complete_curves_search == 1) {
	//					break;
	//				}
	//				int z = image_source.at<unsigned char>(zx, zy);
	//				if (z > trashold) {
	//					if (zy - vpstr_down[i].y_b == (-1 * (vpstr_down[i].x_c - vpstr_down[i].x_a) / (vpstr_down[i].y_c - vpstr_down[i].y_a) * (zx - vpstr_down[i].x_b))) //Здесь спорный момент
	//						interval = sqrt(pow((zx - vpstr_down[i].x_b), 2) + pow((zy - vpstr_down[i].y_b), 2));
	//						complete_curves_search = 1;
	//				}
	//			}
	//		}
	//		b.interval = interval;
	//		b.radius_1 = rad_1;
	//		b.radius_2 = rad_2;
	//		vostr.emplace_back(b);
	//	}
	//}

	////if ((image.at<unsigned char>((zx + 1), zy) > trashold) && ((zx + 1) < image.cols))
	//if ((0 <= zy < image.rows) && (0 <= zx < image.cols) && (image.at<unsigned char>((zx + 1), zy) > trashold))
	//{
	//	return 2;
	//}
	////if ((image.at<unsigned char>(zx, (zy + 1)) > trashold) && ((zy + 1) < image.rows))
	//if ((0 <= zy < image.rows) && (0 <= zx < image.cols) && (image.at<unsigned char>(zx, (zy + 1)) > trashold))
	//{
	//	return 3;
	//}
	////if ((image.at<unsigned char>((zx - 1), zy) > trashold) && ((zx - 1) > 0))
	//if ((0 <= zy < image.rows) && (0 <= zx < image.cols) && (image.at<unsigned char>((zx - 1), zy) > trashold))
	//{
	//	return 4;
	//}
	////Ходы по горизонтали
	//if ((image.at<unsigned char>((zx - 1), (zy - 1)) > trashold) && ((zy - 1) > 0) && ((zx - 1) > 0))
	//{
	//	return 5;
	//}
	//if ((image.at<unsigned char>((zx + 1), (zy - 1)) > trashold) && ((zy - 1) > 0) && ((zx + 1) < image.rows))
	//{
	//	return 6;
	//}
	//if ((image.at<unsigned char>((zx + 1), (zy + 1)) > trashold) && ((zy + 1) < image.cols) && ((zx + 1) < image.rows))
	//{
	//	return 7;
	//}
	//if ((image.at<unsigned char>((zx - 1), (zy + 1)) > trashold) && ((zy + 1) < image.cols) && ((zx - 1) > 0))
	//{
	//	return 8;
	//}
	//return 0;

	//void Kerato_calculate::result_to_xls(vector<int> radius_up, vector<int> radius_down, vector<int> distance)
	//{
	//	BasicExcel xls;
	//	const char* path = "example.xls";
	//	// create sheet 1 and get the associated BasicExcelWorksheet pointer
	//	xls.New(1);
	//	BasicExcelWorksheet* sheet = xls.GetWorksheet(0);
	//	XLSFormatManager fmt_mgr(xls);
	//	// Create a table containing an header row in bold and four rows below.
	//	ExcelFont font_bold;
	//	font_bold._weight = FW_BOLD; // 700
	//	CellFormat fmt_bold(fmt_mgr);
	//	fmt_bold.set_font(font_bold);
	//	int col, row = 0;
	//	for (int i = 0; i < radius_up.size(); i++) 
	//	{
	//		BasicExcelCell* cell = sheet->Cell(row, col);
	//		cell->Set(radius_up[i]);
	//		cell->SetFormat(fmt_bold);
	//	}
	//	while (++row < 4) {
	//		for (int col = 0; col<10; ++col)
	//			sheet->Cell(row, col)->Set("text");
	//	}
	//	++row;
	//	ExcelFont font_red_bold;
	//	font_red_bold._weight = FW_BOLD;
	//	font_red_bold._color_index = EGA_RED;
	//	CellFormat fmt_red_bold(fmt_mgr, font_red_bold);
	//	fmt_red_bold.set_color1(COLOR1_PAT_SOLID);			// solid background
	//	fmt_red_bold.set_color2(MAKE_COLOR2(EGA_BLUE, 0));	// blue background
	//	CellFormat fmt_green(fmt_mgr, ExcelFont().set_color_index(EGA_GREEN));
	//	for (col = 0; col<10; ++col) {
	//		BasicExcelCell* cell = sheet->Cell(row, col);
	//		cell->Set("xxx");
	//		cell->SetFormat(fmt_red_bold);
	//		cell = sheet->Cell(row, ++col);
	//		cell->Set("yyy");
	//		cell->SetFormat(fmt_green);
	//	}
	//	xls.SaveAs(path);
	//}