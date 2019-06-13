//Karagiannis Stefanos 3150057
//Morfiadakis Emmanouil 3150112
#include "stdafx.h"
#include<iostream>
#include<fstream>
#include"ppm.h"
#include<string>
using namespace imaging;
using namespace std;
float * imaging::ReadPPM(const char * filename, int * w, int * h) {
	ifstream ifs(filename,ifstream::binary);
	if (!ifs) {
		cerr << "failed to open file";
		return nullptr;
	}
	char fp2[3];
	
	ifs.read(fp2, 2);
	if (ifs.fail()) {
		cerr << "cannot read the file";
		return nullptr;
	}
	if (strncmp(fp2, "P6", 2)) {
		cout << "We only support P6";
		return nullptr;
	}
	ifs >> *w;
	if (ifs.fail()) {
		cerr << "cannot read the file";
		return nullptr;
	}
	ifs >> *h;
	if (ifs.fail()) {
		cerr << "cannot read the file";
		return nullptr;
	}
	int bite;
	ifs >> bite;
	if (ifs.fail()) {
		cerr << "cannot read the file";
		return nullptr;
	}
	if (bite != 255) {
		cout << "We support files with max 255bits";
		return nullptr;
	}
	int dor=0;
	ifs.get();// space or "\n"
	if (ifs.fail()) {
		cerr << "cannot read the file";
		return nullptr;
	}
	float * x = new float[3 * (*w)*(*h)];
	for (int yy = 0; yy < *h; yy++) {
		for (int xx = 0; xx < *w; xx++) {
			for (int i = 0; i < 3; i++) {
            	
				x[dor]=ifs.get();
				if (ifs.eof()) {
					cout << "The height or/and the widtht are wrong";
					return nullptr;
				}
				if (ifs.fail()) {
					cerr << "cannot read the file";
					return nullptr;
				}
				x[dor] =x[dor]/255.0f;
				if (x[dor] < 0 || x[dor]>1) {
					cout << "The limit is violated";
					return nullptr;
				}
				dor++;
			}
		}
	}
	
	ifs.get();
	if (!ifs.eof()) {
		cout<< "The height or/and the widtht are wrong";
		return nullptr;
	}
	ifs.close();
	cout << " Image dimensions are:" << (*w) << "X" << (*h);
	return x;

}
bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {
	ofstream ofs(filename,ofstream::binary);
	if (!ofs) {
		cerr << "failed to open file";
		return false;
	}
	ofs << "P6 " << " " << w << " " << h << " " << 255 << "\n";
	if (ofs.fail()) {
		cerr << "cannot read the file";
		return false;
	}
	int d = 3 * w*h;
	char nd;
	for (int i = 0; i <d; i ++) {
		 nd = (255 * data[i])+0;
		ofs.put(nd);
		if (ofs.fail()) {
			cerr << "cannot write the file";
			return false;
		}
	}
	ofs.close();
	return true;
}