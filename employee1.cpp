#include "employee1.h"
//构造函数
Employee::Employee(int id,string name,int did) 
{
	this->m_Id=id;
	this->m_Name=name;
	this->m_DeptId=did;
}
		
//显示职工信息
void Employee::ShowInfo() 
{
	cout<<"职工编号："<<this->m_Id
		<<"\t职工姓名："<<this->m_Name
		<<"\t岗位名称："<<this->getDeptName()
		<<"岗位职责：完成经理布置的任务"<<endl; 
}
		
//获得岗位名称
string Employee::getDeptName()
{
	return string("员工"); 
}

