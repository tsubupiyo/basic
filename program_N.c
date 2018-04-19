//粒子N個の座標を動かす
#include <stdio.h>
#include <math.h>
#include "MT.h"

#define DELTA 10			/*範囲*/
#define STEP  100			/*ステップ数*/
#define SEED  140838812		/*シード*/
#define NUM_PARTICLES 10	/*粒子数*/
//構造体
typedef struct {
	double x;
	double y;
	double z;
} vector;

//点の距離を求める
double distance(double x, double y, double z)
{
	int dis;
	dis = sqrt(x*x + y*y + z*z);

	return dis;
}

int main(void)
{
	FILE *fp;
	int i, j;
	vector hoo[NUM_PARTICLES] = {{0.0, 0.0, 0.0}};	/*N個の粒子*/
	vector d;			/*ベクトルd*/
	double del = DELTA / 2;

	init_genrand(SEED);		/*乱数の初期化*/

	for(i = 1; i < NUM_PARTICLES; i++)
	{
		hoo[i].x = hoo[i-1].x + 5;
		hoo[i].y = hoo[i-1].y + 5;
		hoo[i].z = hoo[i-1].z + 5;
	}

	fp = fopen("hoo.dat","w");
	for(i = 0; i < STEP; i++)
	{
		for(j = 0; j < NUM_PARTICLES; j++)
		{
			do {
				d.x = genrand_real1() * 2 * del - del;
				d.y = genrand_real1() * 2 * del - del;
				d.z = genrand_real1() * 2 * del - del;
			} while (distance(d.x, d.y, d.z) >= del);
			hoo[j].x += d.x;
			hoo[j].y += d.y;
			hoo[j].z += d.z;
			fprintf(fp, "%f %f %f ", hoo[j].x, hoo[j].y, hoo[j].z);
			//x1 y1 z1 x2 y2 z2 ... xn yn zn
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	return 0;
}
