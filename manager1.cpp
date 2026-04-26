#include "manager1.h"
//构造函数
Manager::Manager(int id,string name,int did) 
{
	this->m_Id=id;
	this->m_Name=name;
	this->m_DeptId=did;
}
		
//显示职工信息
void Manager::ShowInfo() 
{
	cout<<"职工编号："<<this->m_Id
		<<"\t职工姓名："<<this->m_Name
		<<"\t岗位名称："<<this->getDeptName()
		<<"岗位职责：完成老板布置的任务，并且给员工派发任务"<<endl; 
}
		
//获得岗位名称
string Manager::getDeptName()
{
	return string("经理"); 
}

