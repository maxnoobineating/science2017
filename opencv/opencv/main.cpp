#include <cstdio>
#include<iostream>
#include<vector>
#include <opencv2/opencv.hpp>
#define KIBI 16

using namespace cv;

using unit = long long;
using number = unit[KIBI];

int set = 0;
void plus(number, number);
void carry(number);

const unit mask = (unit)0b001 << (sizeof(unit) * 8 - 2);

int main() {
	number a = { 0 }
				 , b = { 0 };
	while (1) {
		std::cin >> a[0] >> b[0];
		set = 0;
	}
	
	Mat img = imread("C:\\cat.jpg");
	Mat img2 = img;
	img.create(img.cols, img.rows, img.type());
	namedWindow("Origin", WINDOW_NORMAL);
	imshow("Origin", img);
	img = img2;
	waitKey();
	imshow("Origin", img);
	waitKey();
	
	/*
	Mat img = imread("C:\\cat.jpg")
	       ,imgB
		   ,imgGB;
	double a = 0.0
				,b = 0.0;
	if (img.empty())
		return -1;
	namedWindow("Origin", WINDOW_NORMAL);
	namedWindow("Blur", WINDOW_NORMAL);
	namedWindow("GaussianBlur", WINDOW_NORMAL);
	blur(img, imgB, Size(3, 3));
	imshow("Origin", img);
	imshow("Blur", imgB);
	while (1) {
		GaussianBlur(img, imgGB, Size(3, 3), a, b);
		imshow("GaussianBlur", imgGB);
		switch (waitKey(0)) {
		case 119:
			b += 0.1;
			break;
		case 115:
			b -= 0.1;
			break;
		case 100:
			a += 0.1;
			break;
		case 97:
			a -= 0.1;
			break;
		case 27:
			return 0;
		}
		cout << a << " " << b << endl;
	}
	*/
	/*
	namedWindow("��J��", WINDOW_NORMAL);
	namedWindow("�W��", WINDOW_NORMAL);
	namedWindow("�f�V�D��J��", WINDOW_NORMAL);
	Mat padded;
	int m = getOptimalDFTSize(inputImg.rows);  //m���j�󵥩�inputImg.rows�̪��̤p�ȡA�B����2�B3�B5������ۭ�
	int n = getOptimalDFTSize(inputImg.cols);
	copyMakeBorder(inputImg, padded, 0, m - inputImg.rows, 0, n - inputImg.cols, BORDER_CONSTANT, Scalar::all(0)); //���F�Ĳv�A�ҥH��v����ɩݮi

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);
	dft(complexImg, complexImg);

	split(complexImg, planes);                  //�����q�D�Aplanes[0]����Ƴ����Aplanes[1]����Ƴ��� 
	magnitude(planes[0], planes[1], planes[0]); //planes[0] = sqrt((planes[0])^2 + (planes[1])^2
	Mat magI = planes[0];
	magI += Scalar::all(1);                     //magI = log(1+planes[0])
	log(magI, magI);

	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));  //�O���������

															  //�N�϶����ơA�����I�b�v��������
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));
	Mat q1(magI, Rect(cx, 0, cx, cy));
	Mat q2(magI, Rect(0, cy, cx, cy));
	Mat q3(magI, Rect(cx, cy, cx, cy));

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, CV_MINMAX);

	imshow("��J��", inputImg);
	imshow("�W��", magI);

	//�f�V�ť߸��ഫ
	Mat ifft;
	idft(complexImg, ifft, DFT_REAL_OUTPUT);
	normalize(ifft, ifft, 0, 1, CV_MINMAX);
	imshow("�f�V�D��J��", ifft);
	waitKey();
	*/
    /*
int j = (signed int)0b11111111111111111111111111111111 << 1;
int k = (signed int)0b11111111111111111111111111111110 >> 1;
std::cout << j << " " << k << std::endl;
*/
return 0;
}

/* ���Ѷ}�� 
  * �Ȱ��u����  
  * while(b)�~�٭n�]�@�h 
  *��16�Ӱ϶���unit
  */

void plus(number a = { 0 }, number b = { 0 }) {
	for (int i = 0; i < KIBI; i++) {
		unit temp = 0;
		while (b) {
			temp = a[set] ^ b[set];
			b[set] &= a[set];
			a[set] = temp;
			if (b[set] & mask) {
				b[set] <<= 1;
				set++;
				carry(a);
				set--;
			}
			else
				b[set] <<= 1;
		}
		set++;
	}
}
void carry(number a = { 0 } ) {
	unit b = 1;
	for (int i = 0; i < KIBI; i++) {
		unit temp = 0;
		while (b) {
			temp = a[set] ^ 1;
			b &= a[set];
			a[set] = temp;
			if (b & mask) {
				b <<= 1;
				set++;
				carry(a);
				set--;
			}
			else
				b <<= 1;
		}
		set++;
	}
}