#include "boss1.h"
//构造函数
Boss::Boss(int id,string name,int did) 
{
	this->m_Id=id;
	this->m_Name=name;
	this->m_DeptId=did;
}
		
//显示职工信息
void Boss::ShowInfo() 
{
	cout<<"职工编号："<<this->m_Id
		<<"\t职工姓名："<<this->m_Name
		<<"\t岗位名称："<<this->getDeptName()
		<<"岗位职责：管理整个公司"<<endl; 
}
		
//获得岗位名称
string Boss::getDeptName()
{
	return string("老板"); 
}

