//职工类--父类
#pragma once
#include <iostream> 
#include <string>
using namespace std;

class Worker{
	public:
		//显示职工信息
		virtual void ShowInfo()=0; 
		
		//获得岗位名称
		virtual string getDeptName()=0;
		
	public:
		int m_Id;		 //职工编号 
		string m_Name;	 //职工姓名 
		int m_DeptId; 	 //部门编号 
};
