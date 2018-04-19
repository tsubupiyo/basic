//粒子N個の座標を動かす
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include "Vector3D.hpp"

constexpr double DELTA         = 10.0;       /*範囲*/
constexpr int    STEP          = 100;        /*ステップ数*/
constexpr int    SEED          = 140838812;     /*シード*/
constexpr int    NUM_PARTICLES = 10;   /*粒子数*/

std::mt19937 mt(SEED);

int main()
{
   std::vector<Vector3D> particles(NUM_PARTICLES); /*N個の粒子*/
   std::ofstream ofs("hoo.dat",std::ios::trunc);

   const Vector3D wtf(5.0,5.0,5.0);
   for(int i = 1; i < NUM_PARTICLES; ++i)
   {
      particles.at(i)=i*wtf;
   }

   std::uniform_real_distribution<double> dist_d(-0.5*DELTA,+0.5*DELTA);
   Vector3D d;
   for(int i = 0; i < STEP; ++i)
   {
      for(int j = 0; j < NUM_PARTICLES; ++j)
      {
         do
         {
            d.x = dist_d(mt);
            d.y = dist_d(mt);
            d.z = dist_d(mt);
         } while (d.norm() >= 0.5*DELTA);
         particles.at(j)+=d;
         ofs<<particles.at(j)<<" ";
         //x1 y1 z1 x2 y2 z2 ... xn yn zn
      }
      ofs<<std::endl;
   }

   return 0;
}
