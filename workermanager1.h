#pragma once		//防止头文件重复 
#include <iostream>
#include "worker1.h"
#include "employee1.h"
#include "manager1.h"
#include "boss1.h"
#include <fstream>
#define FILENAME "empFile.txt"

using namespace std;

//管理类 
class WorkerManager{
	public:
		//构造函数 
		WorkerManager();
		
		//展示菜单
		void Show_Menu(); 
		
		//退出功能
		void ExitSystem(); 
		
		//添加功能
		void Add_Emp(); 
		
		//保存文件
		void save(); 
		
		//初始化员工 
		void init_Emp(); 
		
		//统计人数
		int get_EmpNum();
		
		//显示职工
		void Show_Emp();
		
		//删除职工
		void Del_Emp();
		
		//查找员工是否存在
		int IsExist(int id);
		
		//修改职工
		void Mod_Emp();
		
		//查找职工
		void Find_Emp(); 
		
		//排序职工
		void Sort_Emp(); 
		
		//清空文件
		void Clean_File(); 
		
		//析构函数 
		~WorkerManager();
		
		//记录职工人数
		int m_EmpNum;
		
		//职工数组指针
		Worker **m_EmpArray;
		
		//文件是否为空标志
		bool m_FileIsEmpty; 
};
