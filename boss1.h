#pragma once
#include <iostream>
#include <string>
#include "worker1.h"
using namespace std;

class Boss :public Worker{
	public:
		//构造函数
		Boss(int id,string name,int did); 
		
		//显示职工信息
		void ShowInfo(); 
		
		//获得岗位名称
		string getDeptName();
};
