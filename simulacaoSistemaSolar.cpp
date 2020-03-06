#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <vector>

#define BODYNUMBER 1000

using namespace cv;
using namespace std;

//compile with g++ -o simulacao simulacaoSistemaSolar.cpp `pkg-config opencv --cflags --libs`


double G = 1e-2;
double timeDiff = 0.00008;

double gForce(double mass1, double mass2, double distance){
	return G*mass1*mass2/(distance*distance);
}

struct body{
	double position[2];
	double velocity[2];
	double radius;
	long mass;
	int color[3];
};

int deleteList[BODYNUMBER];
int main(){
	vector<struct body> universe;


	long maxMass = 2147483647e+5;
	long minMass = 100;
	long density = maxMass*1e-2/(3.1415*225);
	
	int maxVelocity = 10000;
	int minVelocity = -maxVelocity/2;

	for(int i = 0; i < BODYNUMBER; i += 1){
		struct body a;
		a.color[0] = rand() % 255;
		a.color[1] = rand() % 255;
		a.color[2] = rand() % 255;
		a.mass = rand() % maxMass + minMass;
		a.radius = sqrt(a.mass/(density*3.1415));
		if(a.radius<1) a.radius = 1;
		a.position[0] = rand() % 1200;
		a.position[1] = rand() % 700;
		a.velocity[0] = rand() % maxVelocity + minVelocity;
		a.velocity[1] = rand() % maxVelocity + minVelocity;
		universe.push_back(a);
	}

	String windowName = "Window with Blank Image"; //Name of the window
	namedWindow(windowName); // Create a window

	int x = 1;
	while(x){
		Mat image(700, 1200, CV_8UC3, Scalar(0, 0, 0));
		for(int body1 = 0; body1<BODYNUMBER; body1+=1){

			double oldPosition[2];
			oldPosition[0] = universe[body1].position[0];
			oldPosition[1] = universe[body1].position[1];
			universe[body1].position[0] += universe[body1].velocity[0]*timeDiff;
			universe[body1].position[1] += universe[body1].velocity[1]*timeDiff;	
			for(int body2 = body1; body2<universe.size(); body2+=1){
				if(body1!=body2){
					double deltaX = (oldPosition[0]-universe[body2].position[0]);
					double deltaY = (oldPosition[1]-universe[body2].position[1]);
					double distance = sqrt((deltaX*deltaX)+(deltaY*deltaY));
					double sinTheta = deltaY/distance;
					double cosTheta = deltaX/distance;

					if(distance < universe[body1].radius + universe[body2].radius){
						struct body newBody;
						newBody.position[0] = (universe[body1].position[0]*universe[body1].mass + universe[body2].position[0]*universe[body2].mass)/(universe[body1].mass+universe[body2].mass);
						newBody.position[1] = (universe[body1].position[1]*universe[body1].mass + universe[body2].position[1]*universe[body2].mass)/(universe[body1].mass+universe[body2].mass);

						newBody.velocity[0] = (universe[body1].mass*universe[body1].velocity[0] 
													  +universe[body2].mass*universe[body2].velocity[0])
													   /(universe[body1].mass+universe[body2].mass);
						newBody.velocity[1] = (universe[body1].mass*universe[body1].velocity[1] 
													  +universe[body2].mass*universe[body2].velocity[1])
													   /(universe[body1].mass+universe[body2].mass);						universe[body1].mass = universe[body1].mass + universe[body1].mass;
						
						newBody.mass = universe[body1].mass + universe[body2].mass;
						if(newBody.mass>maxMass) newBody.mass = maxMass;
						newBody.radius = sqrt(newBody.mass/(density*3.1415));
						// if(newBody.radius>15) newBody.radius = 15;	
						if(newBody.radius<1) newBody.radius = 1;	

						newBody.color[0] = rand() % 255;
						newBody.color[1] = rand() % 255;
						newBody.color[2] = rand() % 255;						 

						universe.erase(universe.begin()+body2);
						universe.erase(universe.begin()+body1);
						universe.insert(universe.begin()+body1, newBody);

					}
					else if(distance!=0){
						double force = gForce(universe[body1].mass, universe[body2].mass, distance);

						universe[body1].velocity[0] -= (force/universe[body1].mass)*cosTheta*timeDiff;
						universe[body1].velocity[1] -= (force/universe[body1].mass)*sinTheta*timeDiff;
						universe[body2].velocity[0] += (force/universe[body2].mass)*cosTheta*timeDiff;
						universe[body2].velocity[1] += (force/universe[body2].mass)*sinTheta*timeDiff;
					}
				}
			}
		}

	for(int body = 0; body<universe.size(); body+=1){
		circle(image, Point((int) universe[body].position[0], (int) universe[body].position[1]), universe[body].radius, Scalar(universe[body].color[0], universe[body].color[1], universe[body].color[2]),CV_FILLED, 8,0);
	}

	imshow(windowName, image); // Show our image inside the created window.
	waitKey(1);
	}
	int pause;
	scanf("%d", &pause);
	return 0;
}






