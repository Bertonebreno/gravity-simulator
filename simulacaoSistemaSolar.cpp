#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

double G = 1;
double gForce(double mass1, double mass2, double distance){
	return G*mass1*mass2/(distance*distance);
}

int main(){
	double position[5][2];
	double velocity[5][2];
	double mass[5];

	std::vector<double> body1AllX, body1AllY, body2AllX, body2AllY, body3AllX, body3AllY, body4AllX, body4AllY, body5AllX, body5AllY;
	plt::figure_size(640, 640);

	double timeDiff = 0.0001;


	mass[0] = 10;
	position[0][0] = -10;
	position[0][1] = 0;
	velocity[0][0] = 0;
	velocity[0][1] = 100;


	mass[1] = 10;
	position[1][0] = 100;
	position[1][1] = 0;
	velocity[1][0] = 0;
	velocity[1][1] = 31.622776601684f;


	mass[2] = 10;	
	position[2][0] = -50;
	position[2][1] = 0;
	velocity[2][0] = 0;
	velocity[2][1] = 44.72135954f;

	
	mass[3] = 10;
	position[3][0] = 0;
	position[3][1] = 20;
	velocity[3][0] = 70.7106781f;
	velocity[3][1] = 0;

	
	mass[4] = 100000;
	position[4][0] = 0;
	position[4][1] = 0;
	velocity[4][0] = 0;
	velocity[4][1] = 0;


	int x = 1;
	while(x<10000000000){

		for(int i = 0; i<5; i+=1){
			double oldPosition[2];
			oldPosition[0] = position[i][0];
			oldPosition[1] = position[i][1];
			position[i][0] += velocity[i][0]*timeDiff;
			position[i][1] += velocity[i][1]*timeDiff;				
			for(int j = i; j<5; j+=1){
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
    body1AllX.push_back(position[0][0]); body1AllY.push_back(position[0][1]);
    body2AllX.push_back(position[1][0]); body2AllY.push_back(position[1][1]);
    body3AllX.push_back(position[2][0]); body3AllY.push_back(position[2][1]);
    body4AllX.push_back(position[3][0]); body4AllY.push_back(position[3][1]);
    body5AllX.push_back(position[4][0]); body5AllY.push_back(position[4][1]);
    
    printf("%lf\n", (((double)(x%1000))/1000));
	if(x%1000==0){	
		plt::clf();
		plt::xlim(-110, 110);
		plt::ylim(-110, 110);
		plt::plot(body1AllX, body1AllY);
		plt::plot(body2AllX, body2AllY);
		plt::plot(body3AllX, body3AllY);
		plt::plot(body4AllX, body4AllY);
		plt::plot(body5AllX, body5AllY);
		plt::pause(0.0000000000001);
	}
	x++;
	}
	int pause;

	scanf("%d", &pause);
	// x = 0;
	return 0;
}






