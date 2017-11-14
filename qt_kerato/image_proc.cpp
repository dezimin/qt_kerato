#include "Header.h"

Kerato_image_proc::Kerato_image_proc()
{

}

int Kerato_image_proc::auto_k_for_frame(Mat image_source, int dy, int dx, bool select)
{
	//1 - слева направо
	//0 - справа налево 
	int sum;
	if (select == 0)
	{
		sum = (image_source.at<unsigned char>(dy, dx - 1)) + (image_source.at<unsigned char>(dy - 1, dx)) + (image_source.at<unsigned char>(dy - 1, dx - 1)) + (image_source.at<unsigned char>(dy - 2, dx)) + (image_source.at<unsigned char>(dy - 2, dx - 1)) + (image_source.at<unsigned char>(dy + 1, dx)) + (image_source.at<unsigned char>(dy + 1, dx - 1)) + (image_source.at<unsigned char>(dy + 2, dx)) + (image_source.at<unsigned char>(dy + 2, dx - 1));
		return sum;
	}
	else if (select == 1)
	{
		sum = (image_source.at<unsigned char>(dy, dx - 1)) + (image_source.at<unsigned char>(dy - 1, dx)) + (image_source.at<unsigned char>(dy - 1, dx - 1)) + (image_source.at<unsigned char>(dy - 2, dx)) + (image_source.at<unsigned char>(dy - 2, dx - 1)) + (image_source.at<unsigned char>(dy + 1, dx)) + (image_source.at<unsigned char>(dy + 1, dx - 1)) + (image_source.at<unsigned char>(dy + 2, dx)) + (image_source.at<unsigned char>(dy + 2, dx - 1));
		return sum;
	}
}

void Kerato_image_proc::delete_auto_frame(Mat image_source, int center)
{
	short int fx1 = 0;
	short int fx2 = 0;
	short int zx1, zx2;
	short int zy1, zy2;
	bool v_p1 = 0;
	bool v_p2 = 0;
	short int count1 = 0;
	short int count2 = 0;
	short int prev_step_0 = 0;
	short int prev_step_1 = 0;


	for (int iy = 0; iy < image_source.rows / 2; iy++)
	{
		if (image_source.at<unsigned char>(iy, 320) > 35)
		{
			while (v_p1 == 0)
			{
				short int result_step_0 = 0;
				count1++;
				if (count1 == 1)
				{
					zx1 = 320;
					zy1 = iy;
					prev_step_0 = 0;
				}

				result_step_0 = juke_step(image_source, prev_step_0, 35, zx1, zy1, 0);
				switch (result_step_0)
				{
				case 1:
					prev_step_0 = 1;
					zy1 = zy1 - 1;
					zx1 = zx1 + 1;
					break;
				case 2:
					prev_step_0 = 2;
					zy1 = zy1 + 1;
					zx1 = zx1 + 1;
					break;
				case 3:
					prev_step_0 = 3;
					zx1 = zx1 + 1;
					break;
				case 4:
					prev_step_0 = 4;
					zy1 = zy1 - 1;
					break;
				case 5:
					prev_step_0 = 5;
					zy1 = zy1 + 1;
					break;
				case 6:
					prev_step_0 = 6;
					zx1 = zx1 - 1;
					zy1 = zy1 - 1;
					break;
				case 7:
					prev_step_0 = 7;
					zy1 = zy1 + 1;
					zx1 = zx1 - 1;
					break;
				case 8:
					prev_step_0 = 8;
					zx1 = zx1 - 1;
					break;
				case 0:
					v_p1 = 1;
					break;
				default:
					v_p1 = 1;
					break;
				}
			}

			while (v_p2 == 0)
			{
				short int result_step_1 = 0;
				count2++;


				if (count2 == 1)
				{
					zx2 = 320;
					zy2 = iy;
					prev_step_1 = 0;
				}

				result_step_1 = juke_step(image_source, prev_step_1, 35, zx2, zy2, 1);
				switch (result_step_1)
				{
				case 1:
					prev_step_1 = 1;
					zy2 = zy2 - 1;
					zx2 = zx2 + 1;
					break;
				case 2:
					prev_step_1 = 2;
					zy2 = zy2 + 1;
					zx2 = zx2 + 1;
					break;
				case 3:
					prev_step_1 = 3;
					zx2 = zx2 + 1;
					break;
				case 4:
					prev_step_1 = 4;
					zy2 = zy2 - 1;
					break;
				case 5:
					prev_step_1 = 5;
					zy2 = zy2 + 1;
					break;
				case 6:
					prev_step_1 = 6;
					zx2 = zx2 - 1;
					zy2 = zy2 - 1;
					break;
				case 7:
					prev_step_1 = 7;
					zy2 = zy2 + 1;
					zx2 = zx2 - 1;
					break;
				case 8:
					prev_step_1 = 8;
					zx2 = zx2 - 1;
					break;
				case 0:
					v_p2 = 1;
					break;
				default:
					v_p2 = 1;
					break;
				}
			}

			//Проверяем область по длинне
			
			//Корректировка на случай наплыва снизу
			/*if (((fx2 - fx1) > 361) && ((fx2 - fx1) <= 450))
			{
				fx1 = zx1 + 30;
				fx2 = zx2 - 30;
			}*/
			/*if ((fx2 - fx1) > 450)
			{
				fx1 = fx1 + 35;
				fx2 = fx2 - 35;
			}*/
			if ((zx2 - zx1) > 250)
			{
				zx1 = zx1 + 30;
				zx2 = zx2 - 30;
				delete_frame(image_source, zx1, zx2);
				break;
			}
			else
			{
				MessageBox(0, L"Это изображение не подходит", L"Решение", MB_OK);
				exit(0);
			}
			/*if (((center - zx1) > 200) && ((zx2 - center) > 200))
			{
				zx1 = center - 200;
				zx2 = center + 200;
				delete_frame(image_source, zx1, zx2);
				break;
			}*/
			/*else
			{
				cout << "bad image" << endl;
				system("pause");
				exit(0);
			}*/
		}
	}
}

int Kerato_image_proc::calc_center(Mat image_source)
{
	int cx1, cy1;
	int cx2, cy2;
	bool stop_1 = 0;
	bool stop_2 = 0;
	//Вычисляем cx1, cy1 точку границы области слева
	for (int  ix = 200; ix < image_source.cols/2; ix++)
	{
		if (stop_1 == 0)
		{
			for (int iy = image_source.rows - 1; iy > 100; iy--)
			{
				if (image_source.at<unsigned char>(iy, ix) > 60)
				{
					cx1 = ix;
					cy1 = iy;
					break;
				}
				else if (iy == (100 + 1))
				{
					stop_1 = 1;
				}
				continue;
			}
		}
	}
	//Вычисляем cx2, cy2 точку границы области справа
	for (int ix = 480; ix > image_source.cols / 2; ix--)
	{
		if (stop_2 == 0)
		{
			for (int iy = image_source.rows - 1; iy > 100; iy--)
			{
				if (image_source.at<unsigned char>(iy, ix) > 60)
				{
					cx2 = ix;
					cy2 = iy;
					break;
				}
				else if (iy == (100 + 1))
				{
					stop_2 = 1;
				}
			}
		}
	}
	//Вычисляем точку центра
	return (((cx2 - cx1) / 2) + cx1);
}

void Kerato_image_proc::delete_frame(Mat image_source, short int fx1, short int fx2)
{
	//слева
	for (int ix = 0; ix < fx1; ix++)
	{
		for (int iy = 0; iy < image_source.rows; iy++)
		{
			image_source.at<unsigned char>(iy, ix) = 0;
		}
	}
	//справа
	for (int ix = fx2; ix < image_source.cols; ix++)
	{
		for (int iy = 0; iy < image_source.rows; iy++)
		{
			image_source.at<unsigned char>(iy, ix) = 0;
		}
	}
	//сверху
	for (int ix = 0; ix < image_source.cols; ix++)
	{
		for (int iy = 0; iy < 35; iy++)
		{
			image_source.at<unsigned char>(iy, ix) = 0;
		}
	}
	//снизу
	for (int ix = 0; ix < image_source.cols; ix++)
	{
		for (int iy = image_source.rows - 200; iy < image_source.rows; iy++)
		{
			image_source.at<unsigned char>(iy, ix) = 0;
		}
	}

	imwrite("frame.jpg", image_source);
}

void Kerato_image_proc::brightness_delete(Mat image_source)
{
	for (int ix = 0; ix < image_source.cols; ix++)
	{
		for (int iy = 0; iy < image_source.rows; iy++)
		{
			if (image_source.at<unsigned char>(iy, ix) > 110)
			{
				image_source.at<unsigned char>(iy, ix) = 0;
			}
			else
			{
				continue;
			}
		}
	}
	imwrite("brightness.jpg", image_source);
}

void Kerato_image_proc::delete_noise(Mat image_source)
{
	for (int ix = 0; ix < image_source.cols; ix++)
	{
		for (int iy = 0; iy < image_source.rows; iy++)
		{
			if (image_source.at<unsigned char>(iy, ix) > 1)
			{
				if ((iy > 1) && (iy < (image_source.rows - 1)) && (ix > 1) && (ix < (image_source.cols - 1)))
				{
					int n1, n2, n3, n4, n5, n6, n7, n8;
					n1 = image_source.at<unsigned char>(iy - 1, ix - 1);
					n2 = image_source.at<unsigned char>(iy - 1, ix);
					n3 = image_source.at<unsigned char>(iy - 1, ix + 1);
					n4 = image_source.at<unsigned char>(iy, ix - 1);
					n5 = image_source.at<unsigned char>(iy, ix + 1);
					n6 = image_source.at<unsigned char>(iy + 1, ix - 1);
					n7 = image_source.at<unsigned char>(iy + 1, ix);
					n8 = image_source.at<unsigned char>(iy + 1, ix + 1);

					if ((n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8) < 256)
					{
						image_source.at<unsigned char>(iy, ix) = 0;
					}
				}
			}
			else
			{
				continue;
			}
		}
	}

	imwrite("noise_mini.jpg", image_source);
}

void Kerato_image_proc::main_binar(Mat image_source)
{
	for (int mbx = 0; mbx < (image_source.cols); mbx++)
	{
		for (int mby = 0; mby < (image_source.rows); mby++)
		{
			if ((image_source.at<unsigned char>(mby, mbx) > 150))
			{
				image_source.at<unsigned char>(mby, mbx) = 60;
			}
			if ((image_source.at<unsigned char>(mby, mbx) < 14))
			{
				image_source.at<unsigned char>(mby, mbx) = 0;
			}
			if ((image_source.at<unsigned char>(mby, mbx) > 14) && (image_source.at<unsigned char>(mby, mbx) < 22))
			{
				image_source.at<unsigned char>(mby, mbx) = 22;
			}
		}
	}
}

void Kerato_image_proc::binar(Mat image_source)
{
	Mat image_source_bin;
	threshold(image_source, image_source_bin, 0, 255, CV_THRESH_OTSU);
	for (int by = 10; by < image_source_bin.rows - 10; by++)
	{
		for (int bx = 10; bx < image_source_bin.cols - 10; bx++)
		{
			if ((image_source_bin.at<unsigned char>(by, bx) < 10) && (image_source_bin.at<unsigned char>(by, bx + 1) > 10) && (image_source_bin.at<unsigned char>(by, bx - 1) > 10) && (image_source_bin.at<unsigned char>(by, bx - 2) > 10))
			{
				image_source_bin.at<unsigned char>(by, bx) = 255;
			}
			else if ((image_source_bin.at<unsigned char>(by, bx) < 10) && (image_source_bin.at<unsigned char>(by, bx + 1) > 10) && (image_source_bin.at<unsigned char>(by, bx - 1) < 10) && (image_source_bin.at<unsigned char>(by, bx - 2) > 10))
			{
				image_source_bin.at<unsigned char>(by, bx) = 255;
				image_source_bin.at<unsigned char>(by, bx - 1) = 255;
			}
			else if ((image_source_bin.at<unsigned char>(by, bx) < 10) && (image_source_bin.at<unsigned char>(by, bx + 1) > 10) && (image_source_bin.at<unsigned char>(by, bx - 1) < 10) && (image_source_bin.at<unsigned char>(by, bx - 2) < 10) && (image_source_bin.at<unsigned char>(by, bx - 3) > 10))
			{
				image_source_bin.at<unsigned char>(by, bx) = 255;
				image_source_bin.at<unsigned char>(by, bx - 1) = 255;
				image_source_bin.at<unsigned char>(by, bx - 2) = 255;
			}
		}
	}

	image_source_bin.copyTo(image_source);
	imwrite("binar.jpg", image_source);
}

void Kerato_image_proc::delete_noise_mini(Mat image_source)
{
	for (int ix = 0; ix < image_source.cols; ix++)
	{
		for (int iy = 0; iy < image_source.rows; iy++)
		{
			if (image_source.at<unsigned char>(iy, ix) > 1)
			{
				if ((iy > 1) && (iy < (image_source.rows - 1)) && (ix > 1) && (ix < (image_source.cols - 1)))
				{
					int n1, n2, n3, n4, n5, n6, n7, n8;
					n1 = image_source.at<unsigned char>(iy - 1, ix - 1);
					n2 = image_source.at<unsigned char>(iy - 1, ix);
					n3 = image_source.at<unsigned char>(iy - 1, ix + 1);
					n4 = image_source.at<unsigned char>(iy, ix - 1);
					n5 = image_source.at<unsigned char>(iy, ix + 1);
					n6 = image_source.at<unsigned char>(iy + 1, ix - 1);
					n7 = image_source.at<unsigned char>(iy + 1, ix);
					n8 = image_source.at<unsigned char>(iy + 1, ix + 1);

					if ((n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8) < 514)
					{
						image_source.at<unsigned char>(iy, ix) = 0;
					}
				}
			}
		}
	}
}

void Kerato_image_proc::two_line(Mat image_source)
{
	for (int ix = 0; ix < (image_source.cols); ix++)
	{
		for (int iy = 0; iy < (image_source.rows); iy++)
		{
			if (image_source.at<unsigned char>(iy, ix) > 100)
			{
				for (int iyd = iy + 1; iyd < (image_source.rows); iyd++)
				{
					if (iyd == (image_source.rows - 4))
					{
						break;
					}
					//Заполняем нулями внутри роговицы
					if ((image_source.at<unsigned char>(iyd, ix) > 100) && (image_source.at<unsigned char>((iyd + 1), ix) > 100))
					{
						image_source.at<unsigned char>(iyd, ix) = 0;
					}
					//Если есть шум
					if ((image_source.at<unsigned char>(iyd, ix) > 100) && (image_source.at<unsigned char>((iyd + 1), ix) == 0) && ((image_source.at<unsigned char>((iyd + 2), ix) == 0) || (image_source.at<unsigned char>((iyd + 2), ix) > 100)) && ((image_source.at<unsigned char>((iyd + 3), ix) > 100)))
					{
						image_source.at<unsigned char>(iyd, ix) = 0;
						continue;
					}
					//Находим границу роговицы и удаляем всё что ниже.
					if ((image_source.at<unsigned char>(iyd, ix) > 100) && (image_source.at<unsigned char>((iyd + 1), ix) == 0) && (image_source.at<unsigned char>((iyd + 2), ix) == 0) && (image_source.at<unsigned char>((iyd + 3), ix) == 0))
					{
						image_source.at<unsigned char>(iyd, ix) = 255;
						for (int iyd0 = iyd + 1; iyd0 < (image_source.rows-1); iyd0++)
						{
							image_source.at<unsigned char>(iyd0, ix) = 0;
						}
					}
				}
			}
		}
	}
	for (int fx = 50; fx < image_source.cols - 50; fx++)
	{
		for (int fy = 40; fy < image_source.rows - 200; fy++)
		{
			if (image_source.at<unsigned char>(fy, fx) == 0)
			{
				if ((image_source.at<unsigned char>(fy - 1, fx - 2) > 10) &&(image_source.at<unsigned char>(fy-1, fx-1) > 10) && (image_source.at<unsigned char>(fy+1, fx) > 10) && (image_source.at<unsigned char>(fy + 1, fx + 1) > 10) && (image_source.at<unsigned char>(fy, fx - 1) < 10))
				{
					image_source.at<unsigned char>(fy + 1, fx) = 0;
					image_source.at<unsigned char>(fy, fx) = 255;
				}
				else if ((image_source.at<unsigned char>(fy - 1, fx + 2) > 10) && (image_source.at<unsigned char>(fy - 1, fx + 1) > 10) && (image_source.at<unsigned char>(fy + 1, fx) > 10) && (image_source.at<unsigned char>(fy + 1, fx - 1) > 10) && (image_source.at<unsigned char>(fy, fx + 1) < 10))
				{
					image_source.at<unsigned char>(fy + 1, fx) = 0;
					image_source.at<unsigned char>(fy, fx) = 255;
				}
				else if ((image_source.at<unsigned char>(fy, fx - 1) > 10) && (image_source.at<unsigned char>(fy - 1, fx) > 10) && (image_source.at<unsigned char>(fy, fx + 1) > 10))
				{
					image_source.at<unsigned char>(fy - 1, fx) = 0;
					image_source.at<unsigned char>(fy, fx) = 255;
				}
				else if ((image_source.at<unsigned char>(fy, fx - 1) > 10) && (image_source.at<unsigned char>(fy + 1, fx) > 10) && (image_source.at<unsigned char>(fy, fx + 1) > 10))
				{
					image_source.at<unsigned char>(fy + 1, fx) = 0;
					image_source.at<unsigned char>(fy, fx) = 255;
				}
			}
		}
	}

	imwrite("two_line.jpg", image_source);
}

void Kerato_image_proc::finishing(Mat image_source)
{
	for (int fx = 0; fx < image_source.cols; fx++)
	{
		for (int fy = 0; fy < image_source.rows; fy++)
		{
			if (image_source.at<unsigned char>(fy, fx) > 10)
			{
				if ((fy >  1) && (fy <  (image_source.rows - 1)) && (fx >  1) && (fx <  (image_source.cols - 1)))
				{
					int n1, n2, n3, n4, n5, n6, n7, n8;
					n1 = image_source.at<unsigned char>(fy - 1, fx - 1);
					n2 = image_source.at<unsigned char>(fy - 1, fx);
					n3 = image_source.at<unsigned char>(fy - 1, fx + 1);
					n4 = image_source.at<unsigned char>(fy, fx - 1);
					n5 = image_source.at<unsigned char>(fy, fx + 1);
					n6 = image_source.at<unsigned char>(fy + 1, fx - 1);
					n7 = image_source.at<unsigned char>(fy + 1, fx);
					n8 = image_source.at<unsigned char>(fy + 1, fx + 1);

					if ((n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8) < 513)
					{
						image_source.at<unsigned char>(fy, fx) = 0;
					}
				}
			}
			else
			{
				continue;
			}
		}
	}
	imwrite("two_line_finishing.jpg", image_source);
}

void Kerato_image_proc::lines_to_mat(Mat image_source, Mat Kerato_image_proc, int zx, int zy)
{
	
	short int trashold = 100;
	lines_param l;
	bool v_p = 0;
	short int prev_step = 0;

	while (v_p == 0)
	{
		//Записываем Пиксель в изображение. 
		Kerato_image_proc.at<unsigned char>(zy, zx) = 255;

		//Запуск поиска следующего хода
		short int result_step = juke_step(image_source, prev_step, 20, zx, zy, 1);
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
		case 6:
			prev_step = 6;
			zx = zx - 1;
			zy = zy - 1;
			break;
		case 7:
			prev_step = 7;
			zy = zy + 1;
			zx = zx - 1;
			break;
		case 8:
			prev_step = 8;
			zx = zx - 1;
			break;
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

bool Kerato_image_proc::stop_auto_frame_light(Mat image_source, int zx, int zy, bool select)
{
	//bool select: 1 "вперед" - ход слева направо, 0 "назад" - ход справа налево.
	//Ходы по горизонтали и вертикали
	if (select == 1)
	{
		int fnx = zx + 3;
		int fny = zy + 30;
		for (int qx = zx; qx < fnx; qx++)
		{
			for (int qy = zy - 1; qy < fny; qy++)
			{
				if (image_source.at<unsigned char>(qy, qx) > 150)
				{
					return 1;
				}
			}
		}
		return 0;
	}
	if (select == 0)
	{
		int fnx = zx - 3;
		int fny = zy + 30;
		for (int qx = zx; qx > fnx; qx--)
		{
			for (int qy = zy - 1; qy < fny; qy++)
			{
				if (image_source.at<unsigned char>(qy, qx) > 150)
				{
					return 1;
				}
			}
		}
		return 0;
	}
}

short int Kerato_image_proc::juke_step(Mat image_source, short int prev_step, short int trashold, int zx, int zy, bool select)
{
	//bool select: 1 "вперед" - ход слева направо, 0 "назад" - ход справа налево.
	//Ходы по горизонтали и вертикали

	if (select == 1)
	{
		if (0 <= zy < image_source.rows)
		{
			if (0 <= zx < image_source.cols)
			{
				if ((prev_step == 3) && (zy == (image_source.rows - 1)))
				{
					return 0;
				}
				if (stop_auto_frame_light(image_source, zx, zy, 1) == 1)
				{
					return 0;
				}
				//Ход вправо
				if ((image_source.at<unsigned char>(zy, (zx + 1)) > trashold ) && (image_source.at<unsigned char>(zy, (zx + 1)) < 100))
				{
					return 3;
				}
				////Ход вверх
				//if ((image_source.at<unsigned char>((zy - 1), zx) > trashold) && (image_source.at<unsigned char>((zy - 1), zx) < (trashold + trashold / 2)) && (prev_step != 5))
				//{
				//	return 4;
				//}
				//Ход вниз
				if ((image_source.at<unsigned char>((zy + 1), zx) > trashold) && (image_source.at<unsigned char>((zy + 1), zx) < 100) && (prev_step != 4))
				{
					return 5;
				}
				////Ход вправо-вверх
				//if ((image_source.at<unsigned char>((zy - 1), (zx + 1)) > trashold) && (image_source.at<unsigned char>((zy - 1), (zx + 1)) < (trashold + trashold / 2)))
				//{
				//	return 1;
				//}
				//Ход вправо-вниз
				if ((image_source.at<unsigned char>((zy + 1), (zx + 1)) > trashold) && (image_source.at<unsigned char>((zy + 1), (zx + 1)) < 100))
				{
					return 2;
				}	
				return 0;
			}
		}
	}
	else if (select == 0)
	{
		if (0 <= zy < image_source.rows)
		{
			if (0 <= zx < image_source.cols)
			{
				if ((prev_step == 3) && (zy == (image_source.rows - 1)))
				{
					return 0;
				}
				if (stop_auto_frame_light(image_source, zx, zy, 0) == 1)
				{
					return 0;
				}
				//Ход влево
				if ((image_source.at<unsigned char>(zy, (zx - 1)) > trashold) && (image_source.at<unsigned char>(zy, (zx - 1)) < 100))
				{
					return 8;
				}
				////Ход вверх
				//if ((image_source.at<unsigned char>((zy - 1), zx) > trashold) && (image_source.at<unsigned char>((zy - 1), zx) < (trashold + trashold / 2)) && (prev_step != 5))
				//{
				//	return 4;
				//}
				//Ход вниз
				if ((image_source.at<unsigned char>((zy + 1), zx) > trashold) && (image_source.at<unsigned char>((zy + 1), zx) < 100) && (prev_step != 4))
				{
					return 5;
				}
				////Ход влево-вверх
				//if ((image_source.at<unsigned char>((zy - 1), (zx - 1)) > trashold) && (image_source.at<unsigned char>((zy - 1), (zx - 1)) < (trashold + trashold / 2)))
				//{
				//	return 6;
				//}
				//Ход влево-вниз
				if ((image_source.at<unsigned char>((zy + 1), (zx - 1)) > trashold) && (image_source.at<unsigned char>((zy + 1), (zx - 1)) < 100))
				{
					return 7;
				}
				return 0;
			}
		}
	}

	
	return 0;
}

//short int Kerato_image_proc::juke_step_two_line(Mat image, short int prev_step, short int trashold, int zx, int zy, bool select)
//{
//	//bool select: 1 "вперед" - ход слева направо, 0 "назад" - ход справа налево.
//	//Ходы по горизонтали и вертикали
//
//	if (select == 1)
//	{
//		if (0 <= zy < image.rows)
//		{
//			if (0 <= zx < image.cols)
//			{
//				if ((prev_step == 3) && (zy == (image.rows - 1)) && )
//				{
//					return 0;
//				}
//				//Ход вправо
//				if ((image.at<unsigned char>(zy, (zx + 1)) > trashold) && (image.at<unsigned char>(zy, (zx + 1)) < 100))
//				{
//					return 3;
//				}
//				////Ход вверх
//				//if ((image.at<unsigned char>((zy - 1), zx) > trashold) && (image.at<unsigned char>((zy - 1), zx) < (trashold + trashold / 2)) && (prev_step != 5))
//				//{
//				//	return 4;
//				//}
//				//Ход вниз
//				if ((image.at<unsigned char>((zy + 1), zx) > trashold) && (image.at<unsigned char>((zy + 1), zx) < 100) && (prev_step != 4))
//				{
//					return 5;
//				}
//				////Ход вправо-вверх
//				//if ((image.at<unsigned char>((zy - 1), (zx + 1)) > trashold) && (image.at<unsigned char>((zy - 1), (zx + 1)) < (trashold + trashold / 2)))
//				//{
//				//	return 1;
//				//}
//				//Ход вправо-вниз
//				if ((image.at<unsigned char>((zy + 1), (zx + 1)) > trashold) && (image.at<unsigned char>((zy + 1), (zx + 1)) < 100))
//				{
//					return 2;
//				}
//				return 0;
//			}
//		}
//	}
//	else if (select == 0)
//	{
//		if (0 <= zy < image.rows)
//		{
//			if (0 <= zx < image.cols)
//			{
//				if ((prev_step == 3) && (zy == (image.rows - 1)))
//				{
//					return 0;
//				}
//				//Ход влево
//				if ((image.at<unsigned char>(zy, (zx - 1)) > trashold) && (image.at<unsigned char>(zy, (zx - 1)) < 100))
//				{
//					return 8;
//				}
//				////Ход вверх
//				//if ((image.at<unsigned char>((zy - 1), zx) > trashold) && (image.at<unsigned char>((zy - 1), zx) < (trashold + trashold / 2)) && (prev_step != 5))
//				//{
//				//	return 4;
//				//}
//				//Ход вниз
//				if ((image.at<unsigned char>((zy + 1), zx) > trashold) && (image.at<unsigned char>((zy + 1), zx) < 100) && (prev_step != 4))
//				{
//					return 5;
//				}
//				////Ход влево-вверх
//				//if ((image.at<unsigned char>((zy - 1), (zx - 1)) > trashold) && (image.at<unsigned char>((zy - 1), (zx - 1)) < (trashold + trashold / 2)))
//				//{
//				//	return 6;
//				//}
//				//Ход влево-вниз
//				if ((image.at<unsigned char>((zy + 1), (zx - 1)) > trashold) && (image.at<unsigned char>((zy + 1), (zx - 1)) < 100))
//				{
//					return 7;
//				}
//				return 0;
//			}
//		}
//	}
//
//
//	return 0;
//}

void Kerato_image_proc::end_filter(Mat image_source)
{
	Mat Kerato_image_proc;
	for (int ix = 149; ix < image_source.cols; ix++)
	{
		
		for (int iy = 49; iy < image_source.rows; iy++)
		{
			if (image_source.at<unsigned char>(iy, ix) > 100)
			{
				lines_to_mat(image_source, Kerato_image_proc, ix, iy);
				

			}
		}
	}
}

//short int Kerato_image_proc::step_juke_right(int zx, int zy, Mat image, short int trashold, short int prev_step)
//{
//	//Ходы по горизонтали и вертикали
//	//if ((0 < zy < image.rows) && (0 < zx < image.cols) && (image.at<unsigned char>(zx, (zy - 1)) > trashold) && ((zy - 1) > 0))
//	if (0 <= zy < image.rows)
//	{
//		if (0 <= zx < image.cols)
//		{
//			if ((prev_step == 3) && (zy == (image.rows - 1)))
//			{
//				return 0;
//			}
//
//			if ((image.at<unsigned char>(zy, (zx + 1)) > trashold) && (prev_step != 8))
//			{
//				return 3;
//			}
//			if ((image.at<unsigned char>((zy - 1), zx) > trashold) && (prev_step != 5))
//			{
//				return 4;
//			}
//			if ((image.at<unsigned char>((zy + 1), zx) > trashold) && (prev_step != 4))
//			{
//				return 5;
//			}
//			if ((image.at<unsigned char>((zy - 1), (zx + 1)) > trashold) && (prev_step != 7))
//			{
//				return 1;
//			}
//			if ((image.at<unsigned char>((zy + 1), (zx + 1)) > trashold) && (prev_step != 6))
//			{
//				return 2;
//			}
//			/*if ((image.at<unsigned char>((zy - 1), (zx - 1)) > trashold) && (prev_step != 2))
//			{
//			return 6;
//			}
//			if ((image.at<unsigned char>((zy + 1), (zx - 1)) > trashold) && (prev_step != 1))
//			{
//			return 7;
//			}
//			if ((image.at<unsigned char>(zy, (zx - 1)) > trashold) && (prev_step != 3))
//			{
//			return 8;
//			}*/
//		}
//	}
//	return 0;
//}

//short int Kerato_image_proc::step_juke_left(int zx, int zy, Mat image, short int trashold, short int prev_step)
//{
//	//Ходы по горизонтали и вертикали
//	//if ((0 < zy < image.rows) && (0 < zx < image.cols) && (image.at<unsigned char>(zx, (zy - 1)) > trashold) && ((zy - 1) > 0))
//	if (0 <= zy < image.rows)
//	{
//		if (0 <= zx < image.cols)
//		{
//			if ((prev_step == 3) && (zy == (image.rows - 1)))
//			{
//				return 0;
//			}
//
//			if ((image.at<unsigned char>(zy, (zx + 1)) > trashold) && (prev_step != 8))
//			{
//				return 3;
//			}
//			if ((image.at<unsigned char>((zy - 1), zx) > trashold) && (prev_step != 5))
//			{
//				return 4;
//			}
//			if ((image.at<unsigned char>((zy + 1), zx) > trashold) && (prev_step != 4))
//			{
//				return 5;
//			}
//			if ((image.at<unsigned char>((zy - 1), (zx + 1)) > trashold) && (prev_step != 7))
//			{
//				return 1;
//			}
//			if ((image.at<unsigned char>((zy + 1), (zx + 1)) > trashold) && (prev_step != 6))
//			{
//				return 2;
//			}
//			/*if ((image.at<unsigned char>((zy - 1), (zx - 1)) > trashold) && (prev_step != 2))
//			{
//			return 6;
//			}
//			if ((image.at<unsigned char>((zy + 1), (zx - 1)) > trashold) && (prev_step != 1))
//			{
//			return 7;
//			}
//			if ((image.at<unsigned char>(zy, (zx - 1)) > trashold) && (prev_step != 3))
//			{
//			return 8;
//			}*/
//		}
//	}
//	return 0;
//}

//void Kerato_image_proc::line_allocation(Mat image_source)
//{
//	Mat line_image;
//	int st_x = 0;
//	int st_y = 0;
//	for (int iy = 0; iy < (image_source.rows / 2); iy++)
//	{
//		if (image_source.at<unsigned char>(iy, (image_source.cols / 2)) > 10)
//		{
//			st_x = image_source.cols / 2;
//			st_y = iy;
//		}
//	}
//	for (int ixl = (image_source.cols / 2); ixl > 100; ixl--)
//	{
//		for (int iyl = st_y - 5; iyl < image_source.rows; iyl++)
//		{
//			if ((iyl > st_y) && (image_source.at<unsigned char>(iyl, ixl) < 10))
//			{
//				break;
//			}
//		}
//	}
//
//	imwrite("line.jpg", image_source);
//	system("pause");
//}

//void Kerato_image_proc::sobel(Mat image_source)
//{
//	Mat sobelx;
//	//Sobel(image_source, sobelx, CV_32F, 1, 0);
//	Sobel(image_source, sobelx, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
//	sobelx.copyTo(image_source);
//	imwrite("sobel.jpg", image_source);
//}