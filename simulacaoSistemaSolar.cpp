#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>

#define BODYNUMBER 20

using namespace cv;
using namespace std;

//compile with g++ -o simulacao simulacaoSistemaSolar.cpp `pkg-config opencv --cflags --libs`


double G = 1;
double gForce(double mass1, double mass2, double distance){
	return G*mass1*mass2/(distance*distance);
}

int main(){
	double position[BODYNUMBER][2];
	double velocity[BODYNUMBER][2];
	long mass[BODYNUMBER];
	double radius[BODYNUMBER];
	int color[BODYNUMBER][3];

	double timeDiff = 0.00001;

	long maxMass = 2147483647;
	long minMass = 100;
	for(int i = 0; i < BODYNUMBER; i += 1){
		color[i][0] = rand() % 255;
		color[i][1] = rand() % 255;
		color[i][2] = rand() % 255;
		mass[i] = rand() % maxMass + minMass;
		printf("%ld", mass[i]);
		radius[i] = 2*(mass[i]*14/2147483547 + 2147482147/2147483547);
		position[i][0] = rand() % 1000+ 100;
		position[i][1] = rand() % 500 + 100;
		velocity[i][0] = 0;
		velocity[i][1] = 0;
	}


	String windowName = "Window with Blank Image"; //Name of the window
	namedWindow(windowName); // Create a window

	int x = 1;
	while(x){

		for(int body1 = 0; body1<BODYNUMBER; body1+=1){

			double oldPosition[2];
			oldPosition[0] = position[body1][0];
			oldPosition[1] = position[body1][1];
			position[body1][0] += velocity[body1][0]*timeDiff;
			position[body1][1] += velocity[body1][1]*timeDiff;	

			for(int body2 = body1; body2<BODYNUMBER; body2+=1){
				if(body1!=body2){
					double deltaX = (oldPosition[0]-position[body2][0]);
					double deltaY = (oldPosition[1]-position[body2][1]);
					double distance = sqrt((deltaX*deltaX)+(deltaY*deltaY));
					double sinTheta = deltaY/distance;
					double cosTheta = deltaX/distance;

					if(distance < radius[body1] + radius[body2]){

					}
					else if(distance!=0){
						double force = gForce(mass[body1], mass[body2], distance);

						velocity[body1][0] -= (force/mass[body1])*cosTheta*timeDiff;
						velocity[body1][1] -= (force/mass[body1])*sinTheta*timeDiff;
						velocity[body2][0] += (force/mass[body2])*cosTheta*timeDiff;
						velocity[body2][1] += (force/mass[body2])*sinTheta*timeDiff;
					}
				}
			}
		}

    Mat image(700, 1200, CV_8UC3, Scalar(0, 0, 0));
	for(int i = 0; i<BODYNUMBER; i+=1	){
		circle(image, Point((int) position[i][0], (int) position[i][1]), radius[i], Scalar(color[i][0], color[i][1], color[i][2]),CV_FILLED, 8,0);
	}
	imshow(windowName, image); // Show our image inside the created window.
	waitKey(1);
	}
	int pause;
	scanf("%d", &pause);
	return 0;
}






