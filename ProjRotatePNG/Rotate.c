#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char** argv)
{
	int height, width, channels_in_file;
	unsigned char* image = stbi_load("image.png", &width, &height, &channels_in_file, 0);
	printf("width: %i, height: %i, channels: %i\n Write value of angle: ", width, height, channels_in_file);
	float ang = 0.0;
	scanf("%f", &ang);
	// ¬ычисл€ю значени€ индексов центра старого фото, и количества пикселей в старом фото
	int newwidth = 0, newheight = 0, newsquare = 0, x_cent = width / 2, y_cent = height / 2, x_cent_new, y_cent_new, oldsq = height * width;
	newwidth = ceil(sqrt(height * height + width * width));	// ¬ычисл€ю значение ширины и высоты дл€ нового фото как диагональ старого фото
	newheight = newwidth;
	x_cent_new = newwidth / 2;	// Ќовые индексы дл€ центра фото
	y_cent_new = newheight / 2;
	newsquare = newheight * newwidth;
	unsigned char* newim = calloc(newsquare * channels_in_file, sizeof(char));
	struct timespec t, t1, t2;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
	for (int i = 0; i < oldsq; i++)
	{
		int x = i % width - x_cent, y = (i / width) - y_cent;					// ѕеренос в новую систему координат
		int new_x = x * cos(ang) - y * sin(ang), new_y = x * sin(ang) + y * cos(ang);	// ѕоворот
		new_x = new_x + x_cent_new; new_y = new_y + y_cent_new;			// —нова перенос
		for (int j = 0; j < channels_in_file; j++)
			newim[channels_in_file * (new_x + new_y * newwidth) + j] = image[channels_in_file * i + j];	// копирую цвета пиксел€
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
	t.tv_sec = t2.tv_sec - t1.tv_sec;
	if ((t.tv_nsec = t2.tv_nsec - t1.tv_nsec) < 0) {
		t.tv_sec--;
		t.tv_nsec += 1000000000;
	}
	printf("ActC: %ld.%09ld\n", t.tv_sec, t.tv_nsec);
	int stride_in_bytes = newwidth * channels_in_file;
	stbi_write_png("result.png", newwidth, newheight, channels_in_file, newim, stride_in_bytes); // сохран€ю новое фото
	stbi_image_free(image);
	free(newim);
	return 0;
}