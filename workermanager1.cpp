#include "workermanager1.h"

//构造函数 
WorkerManager::WorkerManager()
{
	//1.文件不存在
	//2.文件存在但数据为空
	//文件存在并且有数据
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	if(!ifs.is_open()){//is_open()判断ifs是不是一个空文件 ,是的话返回true 
		//初始化人数 
		this->m_EmpNum=0;
		//初始化数组指针 
		this->m_EmpArray=NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty=true;
		ifs.close();
		return;		
	}
	char ch;
	if(!ifs>>ch){
		if(ifs.eof()){//判断是否已经达到文件末尾eof=end or flie 
			//初始化人数 
			this->m_EmpNum=0;
			//初始化数组指针 
			this->m_EmpArray=NULL;
			//初始化文件是否为空
			m_FileIsEmpty=true;
			ifs.close();
			return;
		}
	}
	int num=this->get_EmpNum();
	this->m_EmpNum=num;
	this->m_EmpArray=new Worker*[this->m_EmpNum];
	//初始化员工 
	this->init_Emp();
	
}

//展示菜单
void WorkerManager::Show_Menu()
{
	cout<<"***********************************"<<endl;
    cout<<"********欢迎使用职工管理系统*******"<<endl;
    cout<<"*********0.退出管理系统************"<<endl;
    cout<<"*********1.增加职工信息************"<<endl;
    cout<<"*********2.显示职工信息************"<<endl;
    cout<<"*********3.删除职工信息************"<<endl;
    cout<<"*********4.修改职工信息************"<<endl;
    cout<<"*********5.查找职工信息************"<<endl;
    cout<<"*********6.按照编号排序************"<<endl;
    cout<<"*********7.清空所有文档************"<<endl;
    cout<<"***********************************"<<endl;
    cout<<endl;
}

//退出功能
void WorkerManager::ExitSystem()
{
	cout<<"欢迎下次使用！"<<endl;
	system("pause");
	exit(0);	//退出系统，没有返回类型的函数时，exit直接终止程序 
}

//添加功能
void WorkerManager::Add_Emp()
{
	cout<<"请输入要添加的职工人数："<<endl;
	int addNum;
	cin>>addNum;
	
	if(addNum>0){
		int newSize=this->m_EmpNum+addNum;
		Worker **newSpace=new Worker*[newSize];
		
		if(this->m_EmpArray!=NULL){
			for(int i=0;i<this->m_EmpNum;i++){
				newSpace[i]=this->m_EmpArray[i]; 
			}
		}
		for(int i=0;i<addNum;i++){
			int id;
			string name;
			int dSelect;
			
			bool qqq;
			do{
				qqq=false;
				cout<<"请输入第"<<i+1<<"个员工的职工编号"<<endl;
				cin>>id;
				for(int j=0;j<this->m_EmpNum;j++){
					if(this->m_EmpArray[j]->m_Id==id){
						cout<<"该职工编号已经存在！"<<endl;
						qqq=true;
						break;
					}
				}
			}while(qqq); 
			
			
			cout<<"请输入第"<<i+1<<"个员工的姓名"<<endl;
			cin>>name;
			
			cout<<"请选择该职工的岗位"<<endl;
			cout<<"1.员工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;
			cin>>dSelect;
			Worker *worker=NULL;
			switch(dSelect){
				case 1:
					worker=new Employee(id,name,1);
					break;
				case 2:
					worker=new Manager(id,name,2);
					break;
				case 3:
					worker=new Boss(id,name,3);
					break;
				default:
					cout<<"输入有误！"<<endl;
					break;
			}
			newSpace[this->m_EmpNum+i]=worker;
		}
		delete[] m_EmpArray;
		m_EmpArray=newSpace;
		this->m_EmpNum=newSize;
		//成功添加后保存到文件
		this->save();
		this->m_FileIsEmpty=false;
		
		cout<<"成功添加"<<addNum<<"名职工！"<<endl; 
	}else{
		cout<<"输入有误！"<<endl;
	}
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME,ios::out);
	
	for(int i=0;i<this->m_EmpNum;i++){
		ofs<<this->m_EmpArray[i]->m_Id<<" "
		   <<this->m_EmpArray[i]->m_Name<<" "
		   <<this->m_EmpArray[i]->m_DeptId<<endl;
	}
	ofs.close();
} 

//初始化员工 
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	int id;
	string name;
	int did;
	int index=0;
	while(ifs>>id && ifs>>name && ifs>>did){
		Worker *worker=NULL;
		if(did==1){
			worker=new Employee(id,name,did);
		}else if(did==2){
			worker=new Manager(id,name,did);
		}else if(did=3){
			worker=new Boss(id,name,did);
		}
		this->m_EmpArray[index]=worker;
		index++;
	}
	ifs.close();
} 

//统计人数
int WorkerManager::get_EmpNum()
{
	int num=0;
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	int id;
	string name;
	int did;
	while(ifs>>id && ifs>>name && ifs>>did){
		num++;
	}
	ifs.close();
	return num;
} 

//显示职工
void WorkerManager::Show_Emp()
{
	if(this->m_FileIsEmpty){
		cout<<"文件不存在或者数据为空！"<<endl;
	}else{
		for(int i=0;i<this->m_EmpNum;i++){
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp()
{
	if(this->m_FileIsEmpty){
		cout<<"该文件不存在或者数据为空！"<<endl;
	}else{
		cout<<"请输入你要删除的职工编号："<<endl;
		int id=0;
		cin>>id;
		
		int ret=this->IsExist(id);
		
		if(ret==-1){
			cout<<"删除失败，该职工并不存在！"<<endl;
		}
		else{
			for(int i=ret;i<this->m_EmpNum-1;i++){
				this->m_EmpArray[ret]=this->m_EmpArray[ret+1];
			}
			cout<<"删除成功！"<<endl;
			this->m_EmpNum--;
			this->save();
		} 
	}
	if(this->m_EmpNum==0){
		this->m_FileIsEmpty=true;
	}
	system("pause");
	system("cls");
}
		
//查找员工是否存在
int WorkerManager::IsExist(int id)
{
	int index=-1;
	for(int i=0;i<this->m_EmpNum;i++){
		if(this->m_EmpArray[i]->m_Id==id){
			index=i;
			break;//返回id的下角标 
		}
	}
	return index;
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if(this->m_FileIsEmpty){
		cout<<"该文件不存在或者数据为空！"<<endl;
	}
	else{
		cout<<"请输入你要修改的职工编号："<<endl;
		int id=0;
		cin>>id;
		
		int ret=this->IsExist(id);
		if(ret==-1){
			cout<<"该职工并不存在！"<<endl;
		}else{
			int newid=0;
			string newname=" ";
			int newdid=0;
			cout<<"查找到"<<id<<"号员工：请输入修改后的职工编号："<<endl; 
			cin>>newid;
			cout<<"请输入修改后的职工姓名："<<endl;
			cin>>newname;
			cout<<"请选择职工类型"<<endl;
			cout<<"1.员工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;
			cin>>newdid;
			delete this->m_EmpArray[ret];
			Worker *worker=NULL;
			switch(newdid){
				case 1:
					worker=new Employee(newid,newname,1);
					break;
				case 2:
					worker=new Manager(newid,newname,2);
					break;
				case 3:
					worker=new Boss(newid,newname,3);
					break;
				default:
					cout<<"输入有误！"<<endl;
					break;
			}
			this->m_EmpArray[ret]=worker;
			this->save();
			cout<<"修改成功！"<<endl;
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if(this->m_FileIsEmpty){
		cout<<"该文件不存在或者数据为空！"<<endl;
	}
	else{
		int index=0;
		cout<<"请选择查询方式："<<endl;
		cout<<"1.按照职工编号查找"<<endl;
		cout<<"2.按照职工姓名查找"<<endl;
		cin>>index;
		
		if(index==1){
			cout<<"请输入你要查找的职工编号："<<endl;
			int id=0;
			cin>>id;
		
			int ret=this->IsExist(id);
			if(ret==-1){
				cout<<"查找失败，该职工并不存在！"<<endl;
			}
			else{
				cout<<"查找成功！职工信息如下："<<endl;
				this->m_EmpArray[ret]->ShowInfo();
			}
		}
		else if(index==2){
			cout<<"请输入你要查找的职工姓名："<<endl;
			string name=" ";
			cin>>name;
			bool qqq=false;
			for(int i=0;i<this->m_EmpNum;i++){
				if(this->m_EmpArray[i]->m_Name==name){
					cout<<"查找成功！职工信息如下："<<endl;
					this->m_EmpArray[i]->ShowInfo();
					qqq=true;
				}
			}
			if(!qqq){
				cout<<"查找失败，该职工并不存在！"<<endl;
			}
		}else{
			cout<<"输入选项有误！"<<endl;
		}
	}
	system("pause");
	system("cls");
}

//排序职工
void WorkerManager::Sort_Emp()
{
	if(this->m_FileIsEmpty){
		cout<<"该文件不存在或者数据为空！"<<endl;
		system("pause");
		system("cls");
	}
	else{
		int index=0;
		cout<<"请选择排序方式"<<endl;
		cout<<"1.按升序排序"<<endl;
		cout<<"2.按降序排序"<<endl;
		cin>>index;
		
		for(int i=0;i<this->m_EmpNum;i++){
			int maxormin=i;
			for(int j=i+1;j<this->m_EmpNum;j++){
				
				if(index==1){
					if(this->m_EmpArray[j]->m_Id<this->m_EmpArray[maxormin]->m_Id){
						maxormin=j;
					}
				}
				
				if(index==2){
					if(this->m_EmpArray[j]->m_Id>this->m_EmpArray[maxormin]->m_Id){
						maxormin=j;
					}
				}
			}
			if(i!=maxormin){
				Worker *temp=this->m_EmpArray[i];
				this->m_EmpArray[i]=this->m_EmpArray[maxormin];
				this->m_EmpArray[maxormin]=temp;
			}
		}
		cout<<"排序成功！"<<endl;
		this->save();
		this->Show_Emp();
	}
}

//清空文件
void WorkerManager::Clean_File()
{
	cout<<"确认清空？"<<endl;
	cout<<"1.确认"<<endl;
	cout<<"2.取消"<<endl;
	int index=0;
	cin>>index;
	if(index==1){
		
		ofstream ofs;
		ofs.open(FILENAME,ios::trunc);
		ofs.close();
		
		if(this->m_EmpArray!=NULL){
			for(int i=0;i<this->m_EmpNum;i++){
				delete this->m_EmpArray[i];
				this->m_EmpArray[i]=NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray=NULL;
			this->m_EmpNum=0;
			this->m_FileIsEmpty=true;
			cout<<"文件已清空！"<<endl;
		}
	}
	system("pause");
	system("cls");
}

//析构函数 
WorkerManager::~WorkerManager()
{
	if(this->m_EmpArray!=NULL){
		for(int i=0;i<this->m_EmpNum;i++){
			delete this->m_EmpArray[i];
			this->m_EmpArray[i]=NULL;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray=NULL;
	}
}
