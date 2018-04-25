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

std::vector<Vector3D> cell_all()

std::vector<Vector3D> cellb = cell_all()

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

std::vector<Vector3D> cell_all()
{
	Vector3D diff;
	std::vector<Vector3D> result(27);
	result.reserve(27);
	for(int x = -1; x <= 1; ++x)
	{
		diff.x = CELL_LENGTH * x;
		for(int y = -1; y <= 1; ++y)
		{
			diff.y = CELL_LENGTH * y;
			for(int z = -1; z <= 1; ++z)
			{
				diff.z = CELL_LENGTH * z;
				result.push_back(diff);
			}
		}
	}
	return result;						
}

//周期境界条件(呼び出し)
Vector3D pbc_call(const Vector3D& pi, const Vector3D& pj)
{
	//粒子iに最近接な粒子jの位置(基本セルもしくはイメージセル)を返す関数	
	//つまりVector3Dを返す関数で、引数は２つのVector3Dである。
	double min = DBL_MAX;
	Vector3D result;

	for(size_t i = 0, size = cellb.size(); i < size; ++i)
	{ 	
		const Vector3D hoo = pj + cellb.at(i);
		const double dis = (hoo-pi).norm();
		if(min>dis)	
		{
			min = dis;
			result = hoo;
		}
	}
	return result;
}
