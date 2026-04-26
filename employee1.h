#pragma once
#include <iostream>
#include <string>
#include "worker1.h"
using namespace std;

class Employee :public Worker{
	public:
		//构造函数
		Employee(int id,string name,int did); 
		
		//显示职工信息
		void ShowInfo(); 
		
		//获得岗位名称
		string getDeptName();
};
