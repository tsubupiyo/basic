//x軸方向に動かすだけ
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include "Vector3D.hpp"

constexpr double FORCE     = 10.0;	/*推進力*/ 
constexpr int    STEP      = 10;	/*ステップ数*/
constexpr double WEIGHT    = 10.0;	/*質量*/
constexpr double TIME_STEP = 1.0;	/*ステップごとのの時間*/
constexpr double OUT_FREQ  = 1.0;	/*出力頻度*/

void output_structure(const std::string& file_name, const int& step, const std::vector<Vector3D>& ps);

int main()
{
	str::vector<Vector3D> bacteria;	/*バクテリアの座標*/
	double length_step = FORCE*TIME_STEP*TIME_STEP/(2*WEIGHT);	/*ステップごとの移動距離*/

	const std::string file_name = "bacteria.dat";
	output_structure(file_name,0);
	for(int step = 0; step < STEP; ++step)
	{
		bacteria.x += length_step; 
	
		if((step%OUT_FREQ==0) && step!=0)
		{
			output_structure(file_name,step);
		}
	}
	output_structure(file_name,STEP);

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
