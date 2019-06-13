// neg.cpp : Defines the entry point for the console application.
//

// neg.cpp : Defines the entry point for the console application.
//
//Karagiannis Stefanos 3150057
//Morfiadakis Emmanouil 3150112
#include "stdafx.h"
#include<iostream>
#include<fstream>
#include"Image.h"
using namespace imaging;
using namespace std;

int main(int argc, char**argv)
{
	Image im;
	string fi2;
	int gf;
	if (argc != 2) {
		cout << "File name of the image to load:  ";
		string fi;
		cin >> fi;
		fi2 = fi;
	}
	else {
		string fi(argv[1]);
		fi2 = fi;
	}
	int g = fi2.find(".") + 1;
	if (im.load(fi2.substr(0, g), fi2.substr(g))) 
	im.save(fi2.substr(0, g - 1), fi2.substr(g));


	return 0;
}



