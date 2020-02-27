#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>

//compile with g++ -o simulacao simulacaoSistemaSolar.cpp `pkg-config opencv --cflags --libs`

using namespace cv;
using namespace std;

double G = 1;
double gForce(double mass1, double mass2, double distance){
	return G*mass1*mass2/(distance*distance);
}

int main(){
	double position[5][2];
	double velocity[5][2];
	long mass[5];


	double timeDiff = 0.00001;

	mass[0] = 42875000e+4;
	position[0][0] = 400;
	position[0][1] = 400;
	velocity[0][0] = 0;
	velocity[0][1] = 0;


	mass[1] = 1e+5;
	position[1][0] = 50;
	position[1][1] = 400;
	velocity[1][0] = 0;
	velocity[1][1] = 35000;


	mass[2] = 1;
	position[2][0] = 50;
	position[2][1] = 410;
	velocity[2][0] = 100;
	velocity[2][1] = 35000;


	String windowName = "Window with Blank Image"; //Name of the window
	namedWindow(windowName); // Create a window

	int x = 1;
	while(x){

		for(int i = 0; i<3; i+=1){
			double oldPosition[2];
			oldPosition[0] = position[i][0];
			oldPosition[1] = position[i][1];
			position[i][0] += velocity[i][0]*timeDiff;
			position[i][1] += velocity[i][1]*timeDiff;				
			for(int j = i; j<3; j+=1){
				if(i!=j){
					double deltaX = (oldPosition[0]-position[j][0]);
					double deltaY = (oldPosition[1]-position[j][1]);
					double distance = sqrt((deltaX*deltaX)+(deltaY*deltaY));
					// printf("OldP: %lf %lf\n", oldPosition[0], oldPosition[1]);
					// printf("dX:%lf dY:%lf S:%lf\n", deltaX, deltaY, distance);

					if(distance!=0){
						double sinTheta = deltaY/distance;
						double cosTheta = deltaX/distance;
						// printf("s:%lf c:%lf\n", sinTheta, cosTheta);

						double force = gForce(mass[i], mass[j], distance);
						// printf("f:%lf\n", force);

						velocity[i][0] -= (force/mass[i])*cosTheta*timeDiff;
						velocity[i][1] -= (force/mass[i])*sinTheta*timeDiff;
						velocity[j][0] += (force/mass[j])*cosTheta*timeDiff;
						velocity[j][1] += (force/mass[j])*sinTheta*timeDiff;
					}
				}
			}
		}

    Mat image(800, 800, CV_8UC3, Scalar(0, 0, 0));
	circle(image, Point(position[0][0], position[0][1]), 15, Scalar(255, 255, 255),CV_FILLED, 8,0);
	circle(image, Point(position[1][0], position[1][1]), 7, Scalar(255, 255, 255),CV_FILLED, 8,0);
	circle(image, Point(position[2][0], position[2][1]), 2, Scalar(255, 255, 255),CV_FILLED, 8,0);
	imshow(windowName, image); // Show our image inside the created window.
	waitKey(1);
	}
	int pause;
	scanf("%d", &pause);
	return 0;
}






