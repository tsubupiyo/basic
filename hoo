//粒子N個の座標を動かす(周期境界条件)
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include "Vector3D.hpp"

constexpr double DELTA         = 10.0;			/*範囲*/
constexpr int    NUM_STEP      = 100;			/*ステップ数*/
constexpr int    OUT_FREQ      = 10;			/*出力頻度*/
constexpr int    SEED          = 140838812;		/*シード*/
constexpr int    NUM_PARTICLES = 10;			/*粒子数*/
constexpr double CELL_LENGTH   = 10;			/*セルの長さ*/	 
std::mt19937 mt(SEED);

void output_structure(const std::string& file_name, const int& step, const std::vector<Vector3D>& ps);

void pbc(Vector3D& point);

int main()
{
   std::vector<Vector3D> particles(NUM_PARTICLES); /*N個の粒子*/

   const std::string file_name = "hoo_INFO.dat";
/*
   const Vector3D wtf(5.0,5.0,5.0);
   for(int i = 1; i < NUM_PARTICLES; ++i)
   {
      particles.at(i)=i*wtf;
   }
*/
   std::uniform_real_distribution<double> dist_d(-0.5*DELTA,+0.5*DELTA);
   Vector3D d;
   output_structure(file_name,0,particles);
   for(int step = 0; step < NUM_STEP; ++step)
   {
      for(int ptcl = 0; ptcl < NUM_PARTICLES; ++ptcl)
      {
         do
         {
            d.x = dist_d(mt);
            d.y = dist_d(mt);
            d.z = dist_d(mt);
         } while (d.norm() >= 0.5*DELTA);
         particles.at(ptcl)+=d;
		 pbc(particles.at(ptcl));
      }
      if((step%OUT_FREQ==0) && step!=0)
      {
         output_structure(file_name,step,particles);
      }
   }
   output_structure(file_name,NUM_STEP,particles);

   return 0;
}

//出力
void output_structure(const std::string& file_name, const int& step, const std::vector<Vector3D>& ps)
{
   if(0==step)
   {
      std::ofstream dummy(file_name,std::ios::trunc);
      dummy.close();
   }
   std::ofstream ofs(file_name,std::ios::app);
   ofs<<"# Bead "<<step<<std::endl; 
   for(size_t ips=0,ips_size=ps.size();ips<ips_size;++ips)
   {
      ofs<<ips<<" "<<ps.at(ips)<<std::endl;
   }
   ofs<<std::endl;
   ofs.close();
   return ;   
}

//周期境界条件(移動)
void pbc(Vector3D& point)
{
	//各座標が CELL_LENGTH より大きい場合
	if(point.x > CELL_LENGTH){point.x -= CELL_LENGTH;}
	if(point.y > CELL_LENGTH){point.y -= CELL_LENGTH;}
	if(point.z > CELL_LENGTH){point.z -= CELL_LENGTH;}
	
	//各座標が 0 以下の場合
	if(point.x <= 0){point.x += CELL_LENGTH;}	
	if(point.y <= 0){point.y += CELL_LENGTH;}
	if(point.z <= 0){point.z += CELL_LENGTH;}	
}

//周期境界条件(呼び出し)
void pbc_call(const Vector3D& point)
{	
	Vector3D image;			/*イメージ粒子*/
	int i = 0;

	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			for(int z = -1; z <= 1; ++z)
			{
				image.at(i).x = point.x + CELL_LENGTH * x;
				image.at(i).y = point.y + CELL_LENGTH * y;
				image.at(i).z = point.z + CELL_LENGTH * z;
				i++;
			}
		}
	}
//この後??
}
