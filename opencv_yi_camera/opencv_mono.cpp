// opencvyicamera.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;




#define SHIFT 16
#define SIZE 16
#define N 32
char sprite[N][SIZE][SIZE][3];
int old_p = 0, new_p = 0;
bool mxy_done = false;
int sx[N], sy[N];






void f1(uchar *p) {

}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		if (new_p< (N-1))
		new_p++;
		//cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		//cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		//cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		if (new_p!=old_p) {
			sx[old_p] = x;
			sy[old_p] = y;
			mxy_done = true;
		}
		//cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

	}
}
int compareSprite(const int n,int mx, int my, char p[]) {
	int res = 0;
	for (int y = 0; y<SIZE; y++)
		for (int x = 0; x < SIZE; x++) {
			int m = ((my + y - SIZE / 2) * 640 + mx + x - SIZE / 2) * 3;
			res+=2*abs((int)sprite[n][y][x][0] - (int)p[m]);
			res+=4*abs((int)sprite[n][y][x][1] - (int)p[m + 1]);   
			res+=abs((int)sprite[n][y][x][2] - (int)p[m + 2]);
		}
	return res;
}

int readSprite(const int n, int mx, int my, char p[]) {
	for (int y = 0; y<SIZE; y++)
		for (int x = 0; x < SIZE; x++) {
			int m = ((my + y - SIZE / 2) * 640 + mx + x - SIZE / 2) * 3;
			sprite[n][y][x][0] = p[m];
			sprite[n][y][x][1] = p[m + 1];
			sprite[n][y][x][2] = p[m + 2];

		}

	return 0;
}

int writeSprite(char p[], int n, int mx, int my) {

	for (int y = 0; y<SIZE; y++)
		for (int x = 0; x < SIZE; x++) {
			int m = ((my + y - SIZE / 2) * 640 + mx + x - SIZE / 2) * 3; 
			p[m] =     sprite[n][y][x][0];
			p[m + 1] = sprite[n][y][x][1];
			p[m + 2] = sprite[n][y][x][2];

		}
	return 0;
}

int writeGreen(char p[], int n, int mx, int my) {

	for (int y = 0; y<SIZE; y++)
		for (int x = 0; x < SIZE; x++) {
			int m = ((my + y - SIZE / 2) * 640 + mx + x - SIZE / 2) * 3;
			p[m] = 0;
			p[m + 1] = sprite[n][y][x][1];
			p[m + 2] = 0;

		}
	return 0;
}
int writeBlue(char p[], int n, int mx, int my) {

	for (int y = 0; y<SIZE; y++)
		for (int x = 0; x < SIZE; x++) {
			int m = ((my + y - SIZE / 2) * 640 + mx + x - SIZE / 2) * 3;
			p[m] = sprite[n][y][x][0];
			p[m + 1] = 0;// sprite[n][y][x][1];
			p[m + 2] = 0;

		}
	return 0;
}
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

void f(Mat des, Mat sr) {
	uchar *dp = (uchar*)&des.at<Vec3b>(Point(0, 0));
	uchar *sp = (uchar*)&sr.at<Vec3b>(Point(0, 0));

	for (int y = 1; y < 479; y++) {
		for (int x = 1; x < 639; x++) {
			int p = (y * 640 + x) * 3;

			int r = sp[p + 0];
			int g = sp[p + 1];
			int b = sp[p + 2];


			int dc[3] = { 0,0,0 };

		/*	if (x > 0) {
				cnt++;
				int p1 = (y * 640 + x-1) * 3;
				dc[0] += abs(r - sp[p1]);
				dc[1] += abs(g - sp[p1 + 1]);
				dc[2] += abs(b - sp[p1 + 2]);
			}
			if (x < 639) {
				cnt++;
				int p1 = (y * 640 + x +1 ) * 3;
				dc[0] += abs(r - sp[p1]);
				dc[1] += abs(g - sp[p1 + 1]);
				dc[2] += abs(b - sp[p1 + 2]);
			}
			if (y > 0) {
				cnt++;
				int p1 = ((y-1) * 640 + x) * 3;
				dc[0] += abs(r - sp[p1]);
				dc[1] += abs(g - sp[p1 + 1]);
				dc[2] += abs(b - sp[p1 + 2]);
			}
			if (y < 479) {
				cnt++;
				int p1 = ((y+1) * 640 + x) * 3;
				dc[0] += abs(r - sp[p1]);
				dc[1] += abs(g - sp[p1 + 1]);
				dc[2] += abs(b - sp[p1 + 2]);
			}
			*/

				int p1 = ((y - 1) * 640 + x-1) * 3;
				dc[0] += abs(r - sp[p1]);
				dc[1] += abs(g - sp[p1 + 1]);
				dc[2] += abs(b - sp[p1 + 2]);
			

				p1 = ((y + 1) * 640 + x+1) * 3;
				dc[0] += abs(r - sp[p1]);
				dc[1] += abs(g - sp[p1 + 1]);
				dc[2] += abs(b - sp[p1 + 2]);

				p1 = ((y - 1) * 640 + x + 1) * 3;
				dc[0] += abs(r - sp[p1]);
				dc[1] += abs(g - sp[p1 + 1]);
				dc[2] += abs(b - sp[p1 + 2]);

				p1 = ((y + 1) * 640 + x - 1) * 3;
				dc[0] += abs(r - sp[p1]);
				dc[1] += abs(g - sp[p1 + 1]);
				dc[2] += abs(b - sp[p1 + 2]);

#define MAXX 70

			dp[p] =  constrain(dc[0], 0, 255);
			
			dp[p + 1] = constrain(dc[1],0,255);
			dp[p + 2] =  constrain(dc[2], 0, 255);

			int c = dp[p + 1] + dp[p + 1];
			c /= 10;
			dp[p] = dp[p + 1] = dp[p + 2] =  (c*c > MAXX) ? 255 : 0;

		}
	}



}

int main(int argc, char** argv)
{

	namedWindow("My Window", 1);
	namedWindow("My Window1", 1);
	setMouseCallback("My Window", CallBackFunc, NULL);


	float fG0 = 0,fG1=0, fB = 0, fR = 0;
enum {B,G,R};
	
VideoCapture cap("d:/2.avi");
	//VideoCapture cap;
	//if (!cap.open(0))
//		return 0;

	

	for (;;)
	{
		Mat frame;
		cap >> frame;
		Mat mat=frame.clone();


		
		f(mat, frame);



		if (frame.empty()) break; // end of video stream


		char *p=(char*)&frame.at<Vec3b>(Point(0,0));
		//char *pd = (char*)&mat.at<Vec3b>(Point(0, 0));
		if ( mxy_done && new_p!=old_p) 
		{
			
			mxy_done = false;	
			readSprite(old_p,sx[old_p], sy[old_p], p);
			old_p = new_p;
		}


		
		int sx1, sy1;
		

#define MINRES (SIZE*SIZE*50*7)

		for (int n=0; n<old_p; n++){
			int res = 2000000000;
			int tx = sx[n];
			int y1 = max(sy[n] - SHIFT,SIZE/2);
			int y2 = min(sy[n] + SHIFT,480-SIZE/2);
			int x2 = min (sx[n] + SHIFT,640-SIZE/2);
			for (; y1 < y2; y1++) {
				for(int x1=max(tx- SHIFT,SIZE/2); x1 < x2; x1++) {
					int nres = compareSprite(n,x1, y1, p);

					if (nres < MINRES && nres < res) {
						res = nres;
						sx[n] = x1;
						sy[n] = y1;
					}
				}
			}
			//printf("%i\n", res);
			if (res<MINRES)
				readSprite(n,sx[n], sy[n], p);
			//writeSprite(p, n,sx[n], sy[n]);
			writeBlue(p, n, sx[n], sy[n]);
		}

		//-------
		
		imshow("My Window", frame);
		imshow("My Window1", mat);
		int key=waitKey(1);
		if (key == 0) {
			old_p = new_p = 0;
		}
		if (key == 27) break; // stop capturing by pressing ESC 
	}
	// the camera will be closed automatically upon exit
	// cap.close();
	if (true)return 0;


	Mat image;
	image = imread(argv[1], IMREAD_COLOR); // Read the file

	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	
	return 0;
}
