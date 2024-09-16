#include <iostream>  //头文件
#include <vector>    //容器，用来装数组u的
#include <cmath>
#include <fstream>
#include <math.h> 

//case1: {1 0}; case2: {-1 1}; case3: {0 1 0}; case4: {sinx};
#define testcase "4"

using namespace std;

constexpr int nx = 100;
constexpr int Nstep = 81;
constexpr double L = 2.0;

//cells:     0    1     2    3    4   nx-1    (u) 
int init(vector<double> &u, double dx)
{
	for (int i = 0; i < nx; i++)
	{
		double xi = i * dx;//格心
		if (testcase == "1") {
			if (xi <= 1.0){
				u[i] = 1.0;
			} else {
				u[i] = 0.0;
			}
		} else if (testcase == "2") {
			if (xi <= 1.0){
				u[i] = -1.0;
			} else {
				u[i] = 0.0;
			}
		} else if (testcase == "3") {
			if (xi >= 2.0/3.0 && xi <= 4.0/3.0){
				u[i] = 1.0;
			} else {
				u[i] = 0.0;
			}
		} else if (testcase == "4") {
			if (xi >= 2.0/3.0 && xi <= 4.0/3.0){
				u[i] = sin(3.0*M_PI*(xi-2.0/3.0));
			} else {
				u[i] = 0.0;
			}
		}
	}
	return 0;
}

//fluxs: nx-1  0    1     2    3    4   nx-1    (un) 
int update(vector<double> &u, vector<double> &un, double dt, double dx)
{
	vector<double> F(nx-1);

	for (int i=0; i<nx-1; i++) {
		// shock and rarefraction condition
		if (0.5*(u[i]+u[i+1])>0) {
			F[i] = 0.5*u[i]*u[i];
		} else {
			F[i] = 0.5*u[i+1]*u[i+1];
		}
		// transonic rarefraction fix
		if (u[i] <0 && u[i+1] > 0) 
			F[i] = 0.0;
	}
	
	// 一阶迎风
	for (int i=1; i<nx-1; i++) 
	{
		un[i] = u[i] + dt/dx * (F[i-1] - F[i]);
	}

	// boundary
	if (testcase == "1") {
		un[0] = 1.0;
		un[nx-1] = 0.0;
	} else if (testcase == "2") {
		un[0] = -1.0;
		un[nx-1] = 0.0;
	} else {
		un[0] = 0.0;
		un[nx-1] = 0.0;
	}
	return 0;
}

int output(vector<double> &u, int step)
{
	string fname = to_string(step) + ".dat";  //给文件命名
	ofstream file;  //生成文件
	file.open(fname);  //打开文件
    //编写
	for (int i=0; i<nx; i++)
	{
		file << u[i] << endl;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	double dx = L / (nx - 1);
	double dt = 0.01;

	vector<double> u(nx, 0.0);
	vector<double> un(nx, 0.0); // n+1 时刻

	init(u, dx);//初始化

	output(u, 0); // 0 时刻

	for (int i=0; i<Nstep; i++)
	{
		update(u, un, dt, dx);

		swap(u, un);

		if (i%10 == 0) {
			output(u, i);
		}
	}
	return 0;
}