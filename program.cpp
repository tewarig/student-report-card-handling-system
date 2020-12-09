#include<iostream>

#include<fstream>

#include<iomanip>

using namespace std;
//class used in the project
//only one class student is used in this project ,with few data members and get and set methods to change there value.
class student{
	//data members of student class
  int rollNo;
  char name[50];
  int pMarks ,cMarks,mMarks,eMarks,csMarks;
  double percentage;
  char grade;
  //private function of this class.
  void calculate()
  {

      percentage =(pMarks+cMarks+mMarks+eMarks+csMarks)/5.0;
	if(percentage>=80)
		grade='A';
	else if(percentage>=60)
		grade='B';
	else if(percentage>=45)
		grade='C';
    else if(percentage>=33)
        grade='D';
	else
		grade='F';

  };
  public:
  //get and set methords for setting values of data members.
      void setData()
      {
    cout<<"\nEnter The roll number of student ";
	cin>>rollNo;
	cout<<"\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in physics out of 100 : ";
	cin>>pMarks;
	cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>cMarks;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>mMarks;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>eMarks;
	cout<<"\nEnter The marks in computer science out of 100 : ";
	cin>>csMarks;
	calculate();
	//calculate function will calculate grade of the student.
    };
    void getData()
    {
    cout<<"\nRoll number of student : "<<rollNo;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Physics : "<<pMarks;
	cout<<"\nMarks in Chemistry : "<<cMarks;
	cout<<"\nMarks in Maths : "<<mMarks;
	cout<<"\nMarks in English : "<<eMarks;
	cout<<"\nMarks in Computer Science :"<<csMarks;
	cout<<"\nPercentage of student is  :"<<percentage;
	cout<<"\nGrade of student is :"<<grade;
    };
    void showTable()
    {
    cout<<rollNo<<setw(6)<<" "<<name<<setw(10)<<pMarks<<setw(4)<<cMarks<<setw(4)<<mMarks<<setw(4)
		<<eMarks<<setw(4)<<csMarks<<setw(8)<<percentage<<setw(6)<<grade<<endl;
    }
    int getRollNo()
    {

        return rollNo;
    }

} ;
//function to write in file
void writeData()
{
	student me;
	ofstream outFile;
	//we are using offile
	outFile.open("student.dat",ios::binary|ios::app);
	me.setData();
	outFile.write(reinterpret_cast<char *> (&me), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent report card has been added to database ";
	cin.ignore();
	cin.get();
}
//function to read data from the file
void displayData()
{    student me;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tAll records in file are!!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&me), sizeof(student)))
	{
		me.getData();
		cout<<"\n\n_______________________________________\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}
//function to read specific data or record from the file
void specific(int n)//n is roll number here
{
	student me;
	ifstream inFile;
	//if stream helps us in reading a file
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&me), sizeof(student)))
	{
		if(me.getRollNo()==n)
		{
	  		 me.getData();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}
//function to edit data of a student  from a file
void editData(int n)//here n is roll number of that student  whose data is to be edit
{
	bool found=false;
	student me;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&me), sizeof(student));
		if(me.getRollNo()==n)
		{
			me.getData();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			me.setData();
		    	int pos=(-1)*static_cast<int>(sizeof(me));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&me), sizeof(student));
		    	cout<<"\n\n\t Record of student Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found please check entered data onces again ";
	cin.ignore();
	cin.get();
}

//delete record from a file

void deleteData(int n)
{
	student me;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	//using of stream i can write in a file
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&me), sizeof(student)))
	{
		if(me.getRollNo()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&me), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}

//function to display result of all students
void allResult()
{
	student me;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tResult of all students\n\n";
	cout<<"__________________________________________________________\n";
	cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
	cout<<"___________________________________________________________\n";
	while(inFile.read(reinterpret_cast<char *> (&me), sizeof(student)))
	{
		me.showTable();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}
//function to display result menu


void showResult()
{
	char ch;
	int rollNo;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	allResult(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rollNo;
				specific(rollNo); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

void entryMenu()
{
	char ch;
	int rollNo;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.Create a report card for students";
	cout<<"\n\n\t2.Display all report card of students";
	cout<<"\n\n\t3.Search report card of students with roll no.";
	cout<<"\n\n\t4.Modify report card roll no required";
	cout<<"\n\n\t5.delete report card roll no required";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	writeData(); break;
	case '2':	showResult(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number of the student "; cin>>rollNo;
			specific(rollNo); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number of the student "; cin>>rollNo;
			editData(rollNo);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number  of the student"; cin>>rollNo;
			deleteData(rollNo);break;
	case '6':	break;
	default:	cout<<"\a"; entryMenu();
	}
}


//main function of program
int main()
{
    char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	do
	{
		system("cls");
		cout<<"\n\n\n\n\n\t\t\t\tStudent Report card Handling System\n";
       cout<<"\t\t\t     __________________________________________";
		cout<<"\n\n";
		cout<<"\t\t\t\t\t\t\t\tby Gaurav Tewari";
		cout<<"\n\n\n\n";
		cout<<"\n\n\n\tMain Menu";
		cout<<"\n\n\t1. See Result";
		cout<<"\n\n\t2.  Make Result";
		cout<<"\n\n\t3. Exit";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': showResult();
				break;
			case '2': entryMenu();
				break;
			case '3':
				break;
			default :cout<<"please enter a valid option\a";
		}
    }while(ch!='3');
	return 0;
}



