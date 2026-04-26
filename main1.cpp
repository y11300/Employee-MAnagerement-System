#include <iostream>
#include "workermanager1.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	WorkerManager wm;	//创建一个管理类对象 
	int ret=0;
	while(true){
		wm.Show_Menu();
		cout<<"请输入你的选择："<<endl;
		cin>>ret;
		switch(ret){
			case 0:		//退出系统 
				wm.ExitSystem();
				break;
			case 1:		//增加职工
				wm.Add_Emp(); 
				break;
			case 2:		//显示职工
				wm.Show_Emp(); 
				break;
			case 3:		//删除职工 
				wm.Del_Emp();
				break;	
			case 4:		//修改职工
				wm.Mod_Emp();
				break;
			case 5:		//查找职工
				wm.Find_Emp(); 
				break;
			case 6:		//排序职工 
				wm.Sort_Emp();
				break;
			case 7:		//清空职工
				wm.Clean_File(); 
				break;
			default:
				system("cls");	//清屏操作	
				break;						
		}
	}
	
	system("pause");
	
	return 0;
}
