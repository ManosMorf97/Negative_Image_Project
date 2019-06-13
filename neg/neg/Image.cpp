//Karagiannis Stefanos 3150057
//Morfiadakis Emmanouil 3150112
#include "stdafx.h"
#include<iostream>
#ifndef _ASIGMENT 
#define _ASIGMENT
#include"Image.h"
#include"ppm.h"
using namespace imaging;
using namespace std;
Color* Image::getRawDataPtr() {
	return buffer;
}
Color Image::getPixel(unsigned int x, unsigned int y)const {
	if (x<width&&y<height)
		return buffer[x + width*y];
	else {
		Color c;
		return c;
	}
}
void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
	if (x<width&&y<height)
		buffer[x + width*y] = value;
}
void Image::setData(const Color * & data_ptr) {
	if (width == 0 || height == 0 || !buffer)
		return;
	for (int i = 0; i<width*height; i++)
		buffer[i] = data_ptr[i];
}
Image::Image() {
	width = 0;
	height = 0;
	buffer = nullptr;
}
Image::Image(unsigned int width, unsigned int height) {
	this->height = height;
	this->width = width;
	buffer = new Color[height*width];

}
Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) {
	this->height = height;
	this->width = width;
	buffer = new Color[height*width];
	setData(data_ptr);
}
Image::Image(const Image &src) {
	height = src.getHeight();
	width = src.getWidth();
	buffer = new Color[height*width];
	for (int i = 0; i < width; i++)
		for (int j = 0; j <= height; j++)
			setPixel(i, j, src.getPixel(i, j));
}
Image::~Image() {
	if (buffer != nullptr) {
		delete[] buffer;
		buffer = nullptr;
	}
}
Image& Image::operator = (const Image & right) {
	this->height = right.getHeight();
	this->width = right.getWidth();
	if (buffer != nullptr)
		delete[] buffer;
	buffer = new Color[height*width];
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			setPixel(i, j, right.getPixel(i, j));
	return *this;
}
bool Image::load(const std::string & filename, const std::string & format) {
	if (strcmp(format.c_str(), "ppm")) {
		return false;
	}
	std::string last = filename + format;
	float *ar = ReadPPM(last.c_str(), (int*)&width, (int*)&height);//width height unsigned int
	if (ar == nullptr) return false;
	int q;
	buffer = new Color[height*width];
	int u;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			u = 3 * (j + width*i);
			setPixel(j, i, Color(ar[u], ar[u + 1], ar[u + 2]));

		}
	}
	return true;

}
bool Image::save(const std::string & filename, const std::string & format) {
	if (strcmp(format.c_str(), "ppm")) {
		return false;
	}
	float*data = new float[3 * width*height];
	int d = 0;
	for (int y = 0; y<height; y++) {
		for (int i = 0; i < width; i++) {
			setPixel(i, y, Color(1.0f, 1.0f, 1.0f) - getPixel(i, y));
			for (int j = 0; j < 3; j++) {
				data[d] = buffer[i + y*width][j];
				d++;
			}
		}
	}
	std::string a = "_neg";
	std::string a2 = ".";
	std::string last = filename + a + a2 + format;
	return WritePPM(data, width, height, last.c_str());
}
#endif