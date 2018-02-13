#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<cstdio>
#include<stdlib.h>
#include<sstream>
#include <unistd.h> //TO CAUSE A DELAY 
//#include<pwd.h>
#include<conio.h>
//#include<window.h>
using namespace std;
class mobiles
{
	protected:
	int product_no;
	int quantity;
	char product_name[60];
	char description[50];
	float price;
	float discount;
	float tax;
	int stock;
	int flag;
	public:
	mobiles()
	{
		flag=0;
	}	
	void create_product()
	{
		char choice;
		cout<<"\n ENTER THE PRODUCT NUMBER : ";
		cin>>product_no;
		cout<<"\n ENTER THE PRODUCT NAME : ";
		cin.ignore();
		cin.getline(product_name,60);
		cout<<"\n ENTER THE PRICE OF THE PRODUCT : ";
		cin>>price;
		cout<<"\n ENTER TAX(%) FOR THE PRODUCT : ";
		cin>>tax; 
		cout<<"\n ENTER THE DISCOUNT(%) FOR THE PRODUCT : ";
		cin>>discount;
		//cin>>expirymonth;
		//cin>>expiryyear;
		cout<<"\n ENTER STOCK OF PRODUCT : ";
		cin>>stock;
		cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
			cin.ignore();
			cin.getline(description,50);
		}
		else
		{
			flag=1;
		}
		
	}
	void show_product()
	{
		cout<<"\n  PRODUCT NUMBER  :               "<<product_no;
		cout<<"\n  PRODUCT NAME  :                 "<<product_name;
		cout<<"\n  PRICE OF THE PRODUCT  :         "<<price<<" Rs";
		cout<<"\n  TAX(GST) FOR PRODUCT  :         "<<tax<<" %";
		cout<<"\n  DISCOUNT FOR THE PRODUCT (%) :  "<<discount<<" %";
		cout<<"\n  AVAILABLE STOCK OF PRODUCT      "<<stock;
		if(flag==1)
		{
			cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE";
		}
		else
		{
			cout<<"\n\n  DESCRIPTION : " ;
			cout<<description;
		}
	}
	/*int returnday()
	{
		day[0]=expiry[0];
		day[1]=expiry[1];
		int x= atoi(day); 
		return x;
	}
	int returnmonth()
	{
		month[0]=expiry[3];
		month[1]=expiry[4];
		int x= atoi(month);
		return x;
	}
	int returnyear()
	{
		year[0]=expiry[6];
		year[1]=expiry[7];
		year[2]=expiry[8];
		year[3]=expiry[9];
		int x= atoi (year);
		return x;
	}*/
	float returntax()
	{
		return tax;
	}
	int returnproduct_no()
	{
		return product_no;
	}
	float returnprice()
	{
		return price;
	}
	
	char* returnproduct_name()
	{
		return product_name;
	}
	/*char* returnexpiry()
	{
		return expiry;
	}*/
	float returndiscount()
	{
		return discount;
	}
	int returnstock()
	{
		return stock;
	}
	void write_product();
	void display_all();
	void modify_product();
	void display_specific_record(int n);
	void delete_product();
		  
};
mobiles mobile;
void introduction()    //introduction function
{
	int i;
  	cout<<"\n\n\n";
 	cout<<"\t\t\t\t\t\t"<<setfill('=')<<setw(60)<<"=";
 	cout<<"\n\t\t\t\t\t\t---------------SUPER MARKET BILLING PROJECT----------------\n";
  	cout<<"\t\t\t\t\t\t"<<setfill('=')<<setw(60)<<"=";
  	cout<<"\n\n";
  	cout<<"\t\t\t\t\t\tMADE BY:\n\n\t\t\t\t\t\tMAYUR DESHMUKH \n\t\t\t\t\t\tANDREW KAMBLE \n\t\t\t\t\t\tHUSAIN ABIALI \n\t\t\t\t\t\tATHARVA THORAT \n\t\t\t\t\t\tRAJAT DEORE";
  	cout<<"\n\n\n\t\t\t\t\t\tCOLLEGE:KK WAGH INSTITUTE OF ENGINEERING EDUCATION & RESEARCH\n";
  
}
	
void mobiles::write_product()
{
	fstream file1;
	file1.open("mobiledatabase.dat",ios::out|ios::app);
	create_product();
	file1.write((char*)&mobile,sizeof(mobiles));
	file1.close();
	cout<<"\n PRODUCT HAS BEEN SUCCESSFULLY CREATED !!!! ";
}
void mobiles::display_all()
{
	 fstream file1;
 	 cout<<"\nPRODUCTS AVAILABLE IN MOBILES AND ACCESSORIES :  \n";
 	 file1.open("mobiledatabase.dat",ios::in);
  	while(file1.read((char*)&mobile,sizeof(mobiles)))        
  	{
   		 show_product();
    		 cout<<"\n======================================================\n";
  	}
     	file1.close();
}
void mobiles::modify_product()
{
	fstream file1;
	int no,f;
	f=0;
	cout<<"\n\n UPDATE A PRODUCT :   ";
	cout<<"\n\nPLEASE ENTER PRODUCT NUMBER OF PRODUCT TO BE UPDATED : ";
	cin>>no;
	file1.open("mobiledatabase.dat",ios::in|ios::out);
	while(file1.read((char*)&mobile,sizeof(mobiles)) && f==0)
	{
		if(returnproduct_no()==no)
		{
			show_product();
			//int pos=-1*sizeof(product);
			file1.seekp(-1*sizeof(mobiles),ios::cur);
			create_product();
			file1.write((char*)&mobile,sizeof(mobiles));
			cout<<"\n\n PRODUCT SUCCESSFULLY UPDATED !!!!";
			f=1;
		}
	}
	file1.close();
	if(f==0)
	{
		cout<<"\n\n Record Not Found ";
	}
}
void mobiles::display_specific_record(int n)
{
	int f;
	f=0;
	fstream file;
	file.open("mobiledatabase.dat",ios::in);                  //to open database file
	while(file.read((char*)&mobile,sizeof(mobiles)))  //to read every element in database file
	{
		if(returnproduct_no()==n)
		{ 						     																												
			show_product();
			f=1;
		}
		file.close();		//to close database file
		if(f==0)
		{
			cout<<"\n\nRECORD DOES NOT EXIST !!!";
		}
	}  //end of while
}
void mobiles::delete_product()		//delete function
{
 	fstream file1,fil2;
  	int product_no;
  //	cout<<"\n\n\nDELETE RECORD";
  	cout<<"\n\n PLEASE ENTER THE PRODUCT NO OF THE PRODUCT YOU WANT TO DELETE : ";
 	cin>>product_no;
  	file1.open("mobiledatabase.dat",ios::in|ios::out);    //opening original file
  	fil2.open("Temp.dat",ios::out);         //opening temporary file
  	file1.seekg(0,ios::beg);                  //bringing file pointer at beginning
  	while(file1.read((char*)&mobile,sizeof(mobiles)))
  	{
    		 if(returnproduct_no()!=product_no)
     		 {
	 		 fil2.write((char*)&mobile,sizeof(mobiles));
     		 }
  	}   //end of while
 
  	fil2.close();       //closing temporary file
  	file1.close();        //closing original file
  	remove("mobiledatabase.dat");     // deleting original file 
  	rename("Temp.dat","mobiledatabase.dat");   //renaming temporary file as original file
	usleep(3000000);
	cout<<"\n\nDELETING PRODUCT....";
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!";
  
} // end of class mobiles


class computers
{
	protected:
	int product_no;
	int quantity;
	char product_name[60];
	char description[50];
	float price;
	float discount;
	float tax;
	int stock;
	int flag;
	public:
	computers()
	{
		flag=0;
	}	
	void create_product()
	{
		char choice;
		cout<<"\n ENTER THE PRODUCT NUMBER : ";
		cin>>product_no;
		cout<<"\n ENTER THE PRODUCT NAME : ";
		cin.ignore();
		cin.getline(product_name,60);
		cout<<"\n ENTER THE PRICE OF THE PRODUCT : ";
		cin>>price;
		cout<<"\n ENTER TAX(%) FOR THE PRODUCT : ";
		cin>>tax; 
		cout<<"\n ENTER THE DISCOUNT(%) FOR THE PRODUCT : ";
		cin>>discount;
		cout<<"\n ENTER STOCK OF PRODUCT : ";
		cin>>stock;
		cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
			cin.ignore();
			cin.getline(description,50);
		}
		else
		{
			flag=1;
		}
		
	}
	void show_product()
	{
		cout<<"\n  PRODUCT NUMBER  :               "<<product_no;
		cout<<"\n  PRODUCT NAME  :                 "<<product_name;
		cout<<"\n  PRICE OF THE PRODUCT  :         "<<price<<" Rs";
		cout<<"\n  TAX(GST) FOR PRODUCT  :         "<<tax<<" %";
		cout<<"\n  DISCOUNT FOR THE PRODUCT  (%) : "<<discount<<" %";
		cout<<"\n  AVAILABLE STOCK OF PRODUCT :    "<<stock;
		if(flag==1)
		{
			cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE";
		}
		else
		{
			cout<<"\n\n  DESCRIPTON : " ;
			cout<<description;
		}
	}
	float returntax()
	{
		return tax;
	}
	int returnproduct_no()
	{
		return product_no;
	}
	float returnprice()
	{
		return price;
	}
	
	char* returnproduct_name()
	{
		return product_name;
	}
	/*char* returnexpiry()
	{
		return expiry;
	}*/
	float returndiscount()
	{
		return discount;
	}
	int returnstock()
	{
		return stock;
	}
	void write_product();
	void display_all();
	void modify_product();
	void display_specific_record(int n);
	void delete_product();
}; //end of class computers
		  
computers computer;
void computers::write_product()
{
	fstream file2;
	file2.open("computerdatabase.dat",ios::out|ios::app);
	create_product();
	file2.write((char*)&computer,sizeof(computers));
	file2.close();
	cout<<"\n PRODUCT HAS BEEN SUCCESSFULLY CREATED !!!! ";
	}
void computers::display_all()
{
	 fstream file2;
 	 cout<<"\nPRODUCTS IN COMPUTERS AND LAPTOPS SECTION :  \n";
 	 file2.open("computerdatabase.dat",ios::in);
  	while(file2.read((char*)&computer,sizeof(computers)))        
  	{
   		 show_product();
    		 cout<<"\n===========================================================\n";
  	}
     	file2.close();
	}
void computers::modify_product()
{
	fstream file2;
	int no,f;
	f=0;
	cout<<"\n\nUPDATE A PRODUCT ";
	cout<<"\n\n\nPLEASE ENTER PRODUCT NUMBER OF PRODUCT TO BE UPDATED : ";
	cin>>no;
	file2.open("computerdatabase.dat",ios::in|ios::out);
	while(file2.read((char*)&computer,sizeof(computers)) && f==0)
	{
		if(returnproduct_no()==no)
		{
			show_product();
			//int pos=-1*sizeof(product);
			file2.seekp(-1*sizeof(computers),ios::cur);
			create_product();
			file2.write((char*)&computer,sizeof(computers));
			cout<<"\n\n PRODUCT SUCCESSFULLY UPDATED !!!!";
			f=1;
		}
	}
	file2.close();
	if(f==0)
	{
		cout<<"\n\n PRODUCT NOT FOUND ";
	}
}
void computers::display_specific_record(int n)
{
	int f;
	f=0;
	fstream file;
	file.open("computerdatabase.dat",ios::in);                  //to open database file
	while(file.read((char*)&computer,sizeof(computers)))  //to read every element in database file
	{
		if(returnproduct_no()==n)
		{	  						     																												
			show_product();
			f=1;
		}
	}
	file.close();		//to close database file
	if(f==0)
	{
		cout<<"\n\nPRODUCT DOES NOT EXIST !!!";
	}
	
}
void computers::delete_product()		//delete function
{
 	fstream file2,fil3;
  	int product_no;
  //	cout<<"\n\n\nDELETE RECORD";
  	cout<<"\n\n PLEASE ENTER THE PRODUCT NO OF THE PRODUCT YOU WANT TO DELETE : ";
 	cin>>product_no;
  	file2.open("computerdatabase.dat",ios::in|ios::out);    //opening original file
  	fil3.open("Temp.dat",ios::out);         //opening temporary file
  	file2.seekg(0,ios::beg);                  //bringing file pointer at beginning
  	while(file2.read((char*)&computer,sizeof(computers)))
  	{
    		 if(returnproduct_no()!=product_no)
     		 {
	  	 fil3.write((char*)&computer,sizeof(computers));
     		 }
  	}   //end of while
 
  	fil3.close();       //closing temporary file
  	file2.close();        //closing original file
  	remove("computerdatabase.dat");     // deleting original file 
  	rename("Temp.dat","computerdatabase.dat");   //renaming temporary file as original file
	cout<<"\n\nDELETING PRODUCT....";
	//usleep(3000000);
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!";
} // end of class computers


class cookings
{
	protected:
	int product_no;
	int quantity;                         //Quantity in Kg or Litre as per product
	char product_name[60];
	char description[50];
	float price;                          //price per kg or litre
	float discount;
	float tax;
	int stock;
	int flag;		             //Stock in Kg or Litre as per product
	char expiry[10];
	char day[2];
	char month[2];
	char year[4];
	public:
	cookings()
	{
	 flag=0;
    }
	

void create_product()
	{
		char choice;
		cout<<"\n ENTER THE PRODUCT NUMBER : ";
		cin>>product_no;
		cout<<"\n ENTER THE PRODUCT NAME : ";
		cin.ignore();
		cin.getline(product_name,60);
		cout<<"\n ENTER THE PRICE OF THE PRODUCT(per Kg or per Litre) : ";
		cin>>price;
		cout<<"\n ENTER TAX(%) FOR THE PRODUCT : ";
		cin>>tax; 
		cout<<"\n ENTER THE DISCOUNT(%) FOR THE PRODUCT : ";
		cin>>discount;
		cout<<"\n ENTER EXPIRY DATE OF PRODUCT(DAY/MONTH/YEAR) : ";
		cin>>expiry;
		cout<<"\n ENTER STOCK OF PRODUCT(In Kg or in litres) : ";
		cin>>stock;
		cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
			cin.ignore();
			cin.getline(description,50);
		}
		else
		{
			flag=1;
		}
		
	}
	void show_product()
	{
		cout<<"\n  PRODUCT NUMBER  :                            "<<product_no;
		cout<<"\n  PRODUCT NAME  :                              "<<product_name;
		cout<<"\n  PRICE OF THE PRODUCT(PER KG OR PER LITRE)  : "<<price<<" Rs";
		cout<<"\n  TAX(GST) FOR PRODUCT  :                      "<<tax<<" %";
		cout<<"\n  DISCOUNT FOR THE PRODUCT (%) :               "<<discount<<" %";
		cout<<"\n  DATE OF EXPIRY :                             "<<expiry;
		cout<<"\n  AVAILABLE STOCK OF PRODUCT :                 "<<stock;
		if(flag==1)
		{
			cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE";
		}
		else
		{
			cout<<"\n\n  DESCRIPTION : " ;
			cout<<description;
		}
	}

	int returnday()
	{
		day[0]=expiry[0];
		day[1]=expiry[1];
		int x= atoi(day); 
		return x;
	}
	int returnmonth()
	{
		month[0]=expiry[3];
		month[1]=expiry[4];
		int x= atoi(month);
		return x;
	}
	int returnyear()
	{
		year[0]=expiry[6];
		year[1]=expiry[7];
		year[2]=expiry[8];
		year[3]=expiry[9];
		int x= atoi (year);
		return x;
	}
	float returntax()
	{
		return tax;
	}
	int returnproduct_no()
	{
		return product_no;
	}
	float returnprice()
	{
		return price;
	}
	
	char* returnproduct_name()
	{
		return product_name;
	}
	char* returnexpiry()
	{
		return expiry;
	}
	float returndiscount()
	{
		return discount;
	}
	int returnstock()
	{
		return stock;
	}
	void write_product();
	void display_all();
	void modify_product();
	void display_specific_record(int n);
	void delete_product();

};


cookings cooking;

void cookings::write_product()
{
	fstream file3;
	file3.open("cookingdatabase.dat",ios::out|ios::app);
	create_product();
	file3.write((char*)&cooking,sizeof(cookings));
	file3.close();
	cout<<"\n PRODUCT HAS BEEN SUCCESSFULLY CREATED !!!! ";
}

void cookings::display_all()
{
	 fstream file3;
 	 cout<<"\nPRODUCTS AVAILABLE IN COOKING SUPPLIES SECTION :  \n";
 	 file3.open("cookingdatabase.dat",ios::in);
  	while(file3.read((char*)&cooking,sizeof(cookings)))        
  	{
   		 show_product();
    		 cout<<"\n===========================================================\n";
  	}
     	file3.close();
}
void cookings::modify_product()
{
	fstream file3;
	int no,f;
	f=0;
	cout<<"\n\n UPDATE A PRODUCT :   ";
	cout<<"\n\nPLEASE ENTER PRODUCT NUMBER OF PRODUCT TO BE UPDATED : ";
	cin>>no;
	file3.open("cookingdatabase.dat",ios::in|ios::out);
	while(file3.read((char*)&cooking,sizeof(cookings)) && f==0)
	{
		if(returnproduct_no()==no)
		{
			show_product();
			//int pos=-1*sizeof(product);
			file3.seekp(-1*sizeof(cookings),ios::cur);
			create_product();
			file3.write((char*)&cooking,sizeof(cookings));
			cout<<"\n\n PRODUCT SUCCESSFULLY UPDATED !!!!";
			f=1;
		}
	}
	file3.close();
	if(f==0)
	{
		cout<<"\n\n Record Not Found ";
	}
}
void cookings::display_specific_record(int n)
{
	int f;
	f=0;
	fstream file;
	file.open("cookingdatabase.dat",ios::in);                  //to open database file
	while(file.read((char*)&cooking,sizeof(cookings)))  //to read every element in database file
	{
		if(returnproduct_no()==n)
		{ 						     																												
			show_product();
			f=1;
		}
		file.close();		//to close database file
		if(f==0)
		{
			cout<<"\n\nRECORD DOES NOT EXIST !!!";
		}
	}  //end of while
}
void cookings::delete_product()		//delete function
{
 	fstream file3,fil4;
  	int product_no;
  //	cout<<"\n\n\nDELETE RECORD";
  	cout<<"\n\n PLEASE ENTER THE PRODUCT NO OF THE PRODUCT YOU WANT TO DELETE : ";
 	cin>>product_no;
  	file3.open("cookingdatabase.dat",ios::in|ios::out);    //opening original file
  	fil4.open("Temp.dat",ios::out);         //opening temporary file
  	file3.seekg(0,ios::beg);                  //bringing file pointer at beginning
  	while(file3.read((char*)&cooking,sizeof(cookings)))
  	{
    		 if(returnproduct_no()!=product_no)
     		 {
	 		 fil4.write((char*)&cooking,sizeof(cookings));
     		 }
  	}   //end of while
 
  	fil4.close();       //closing temporary file
  	file3.close();        //closing original file
  	remove("cookingdatabase.dat");     // deleting original file 
  	rename("Temp.dat","cookingdatabase.dat");   //renaming temporary file as original file
	usleep(3000000);
	cout<<"\n\nDELETING PRODUCT....";
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!";
  
} // end of class cookings

class cosmetics
{
	protected:
	int product_no;
	int quantity;                         
	char product_name[60];
	char description[50];
	float price;                         
	float discount;
	float tax;
	int stock;		             
	char expiry[10];
	int flag;
	char day[2];
	char month[2];
	char year[4];
	public:
	cosmetics()
	{
		flag=0;
	}

void create_product()
	{
		char choice;
		cout<<"\n ENTER THE PRODUCT NUMBER : ";
		cin>>product_no;
		cout<<"\n ENTER THE PRODUCT NAME : ";
		cin.ignore();
		cin.getline(product_name,60);
		cout<<"\n ENTER THE PRICE OF THE PRODUCT : ";
		cin>>price;
      	        cout<<"\n ENTER TAX(%) FOR THE PRODUCT : ";
		cin>>tax; 
		cout<<"\n ENTER THE DISCOUNT(%) FOR THE PRODUCT : ";
		cin>>discount;
		cout<<"\n ENTER EXPIRY DATE OF PRODUCT(DAY/MONTH/YEAR) : ";
		cin>>expiry;
		cout<<"\n ENTER STOCK OF PRODUCT : ";
		cin>>stock;
		cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
			cin.ignore();
			cin.getline(description,50);
		}
		else
		{
			flag=1;
		}
		
	}
	void show_product()
	{
		cout<<"\n  PRODUCT NUMBER  :              "<<product_no;
		cout<<"\n  PRODUCT NAME IS :              "<<product_name;
		cout<<"\n  PRICE OF THE PRODUCT  :        "<<price<<" Rs";
		cout<<"\n  TAX(GST) FOR PRODUCT  :        "<<tax<<" %";
		cout<<"\n  DISCOUNT FOR THE PRODUCT (%) : "<<discount<<" %";
		cout<<"\n  DATE OF EXPIRY :               "<<expiry;
		cout<<"\n  AVAILABLE STOCK OF PRODUCT :   "<<stock;
		if(flag==1)
		{
			cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE";
		}
                else
		{
			cout<<"\n\n  DESCRIPTION : " ;
			cout<<description;
		}
	}


	int returnday()
	{
		day[0]=expiry[0];
		day[1]=expiry[1];
		int x= atoi(day); 
		return x;
	}
	int returnmonth()
	{
		month[0]=expiry[3];
		month[1]=expiry[4];
		int x= atoi(month);
		return x;
	}
	int returnyear()
	{
		year[0]=expiry[6];
		year[1]=expiry[7];
		year[2]=expiry[8];
		year[3]=expiry[9];
		int x= atoi (year);
		return x;
	}
	float returntax()
	{
		return tax;
	}
	int returnproduct_no()
	{
		return product_no;
	}
	float returnprice()
	{
		return price;
	}
	
	char* returnproduct_name()
	{
		return product_name;
	}
	char* returnexpiry()
	{
		return expiry;
	}
	float returndiscount()
	{
		return discount;
	}
        int returnstock()
	{
		return stock;
	}
	void write_product();
	void display_all();
	void modify_product();
	void display_specific_record(int n);
	void delete_product();
}; //end of class cosmetics
		  
cosmetics cosmetic;
void cosmetics::write_product()
{
	fstream file4;
	file4.open("cosmeticsdatabase.dat",ios::out|ios::app);
	create_product();
	file4.write((char*)&cosmetic,sizeof(cosmetics));
	file4.close();
	cout<<"\n PRODUCT HAS BEEN SUCCESSFULLY ADDED !!!! ";
}

void cosmetics::display_all()
{
	 fstream file4;
 	 cout<<"\nPRODUCT AVAILABLE IN COSMETICS SECTION : \n";
 	 file4.open("cosmeticsdatabase.dat",ios::in);
  	 while(file4.read((char*)&cosmetic,sizeof(cosmetics)))        
  	 {
   		 show_product();
    		 cout<<"\n===========================================================\n";
  	 }
     	file4.close();
	
}

void cosmetics::modify_product()
{
	fstream file4;
	int no,f;
	f=0;
	cout<<"\n\nUPDATE A PRODUCT ";
	cout<<"\n\n\nPLEASE ENTER PRODUCT NUMBER OF PRODUCT TO BE UPDATED : ";
	cin>>no;
        file4.open("cosmeticsdatabase.dat",ios::in|ios::out);
	while(file4.read((char*)&cosmetic,sizeof(cosmetics)) && f==0)
	{
		if(returnproduct_no()==no)
		{
			cosmetic.show_product();
			cout<<"\n ENTER NEW DETAILS OF PRODUCT";
			cosmetic.create_product();
			//int pos=-1*sizeof(cosmetics);
			file4.seekp(-1*sizeof(cosmetics),ios::cur);
			//file.seekp(pos,ios::cur);
			file4.write((char*)&cosmetic,sizeof(cosmetics));
			cout<<"\n\n PRODUCT SUCCESSFULLY UPDATED !!!!";
			f=1;
		}
	}
	file4.close();
	if(f==0)
	{
		cout<<"\n\n Record Not Found ";
	}
}
void cosmetics::display_specific_record(int n)
{
	int f;
	f=0;
	fstream file;
	file.open("cosmeticsdatabase.dat",ios::in);                  //to open database file
	while(file.read((char*)&cosmetic,sizeof(cosmetics)))  //to read every element in database file
	{
		if(returnproduct_no()==n)
		{ 						     																												
			show_product();
			f=1;
		}
		file.close();		//to close database file
                if(f==0)
		{
			cout<<"\n\nRECORD DOES NOT EXIST !!!";
		}
	}  //end of while
}
void cosmetics::delete_product()		//delete function
{
 	fstream file4,fil5;
  	int product_no;
  //	cout<<"\n\n\nDELETE RECORD";
  	cout<<"\n\n PLEASE ENTER THE PRODUCT NO OF THE PRODUCT YOU WANT TO DELETE : ";
 	cin>>product_no;
  	file4.open("cosmeticsdatabase.dat",ios::in|ios::out);    //opening original file
  	fil5.open("Temp.dat",ios::out);         //opening temporary file
  	file4.seekg(0,ios::beg);                  //bringing file pointer at beginning
  	while(file4.read((char*)&cosmetic,sizeof(cosmetics)))
  	{
    		 if(returnproduct_no()!=product_no)
     		 {
	 		 fil5.write((char*)&cosmetic,sizeof(cosmetics));
     		 }
  	}   //end of while
 
  	fil5.close();       //closing temporary file
  	file4.close();        //closing original file
  	remove("cosmeticsdatabase.dat");     // deleting original file 
  	rename("Temp.dat","cookingdatabase.dat");   //renaming temporary file as original file
	usleep(3000000);
	cout<<"\n\nDELETING PRODUCT....";
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!!";
  
} // end of class cosmetics


class Snacks
{
	protected:
		int product_no;
		int quantity;
		char product_name[60];
		float price;
		float discount;
		float tax;
		int flag;
		//int stock;
		char expiry[10];
		int stock;
		char description[50];
		char day[2];
		char month[2];
		char year[4];
		
	public:
		Snacks()
		{
			flag=0;
		}
		void create_product()
		{
			//flag=0;
			char choice;
			cout<<"\n ENTER THE PRODUCT NUMBER : ";
			cin>>product_no;
			cout<<"\n ENTER THE PRODUCT NAME : ";
			cin.ignore();
			cin.getline(product_name,60);
			cout<<"\n ENTER THE PRICE OF THE PRODUCT : ";
			cin>>price;
			cout<<"\n ENTER THE TAX(%) ON THE PRODUCT : ";
			cin>>tax;
			cout<<"\n ENTER THE DISCOUNT(%) ON THE PRODUCT : ";
			cin>>discount;
			cout<<"\n ENTER THE EXPIRY DATE OF THE PRODUCT(DATE/MONTH/YEAR) : ";
			cin>>expiry;
			cout<<"\n ENTER STOCK OF PRODUCT : ";
			cin>>stock;
			cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
			cin>>choice;
			if(choice=='Y' || choice=='y')
			{
				cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
				cin.ignore();
				cin.getline(description,50);
			}
			else
			{
				flag=1;
			}
		}

		void show_product()
		{
			cout<<"\n  PRODUCT NUMBER :               "<<product_no;
			cout<<"\n  PRODUCT NAME  :                "<<product_name;
			cout<<"\n  PRICE OF THE PRODUCT  :        "<<price;
			cout<<"\n  TAX(GST) ON THE PRODUCT :      "<<tax;
			cout<<"\n  DATE OF EXPIRY  :              "<<expiry;
			cout<<"\n  DISCOUNT ON THE PRODUCT :      "<<discount;
			
			cout<<"\n  AVAILABLE STOCK OF PRODUCT :   "<<stock;
			
			if(flag==1)
			{
				cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE";
			}
            else
			{
				cout<<"\n\n  DESCRIPTION : " ;
				cout<<description;
			}		
		}

		
		int returnday()
		{
			day[0]=expiry[0];
			day[1]=expiry[1];
			int x= atoi(day); 
			return x;
		}
		int returnmonth()
		{
			month[0]=expiry[3];
			month[1]=expiry[4];
			int x= atoi(month);
			return x;
		}
		int returnyear()
		{
			year[0]=expiry[6];
			year[1]=expiry[7];
			year[2]=expiry[8];
			year[3]=expiry[9];
			int x= atoi (year);
			return x;
		}
		float returntax()
		{
			return tax;
		}			
		int returnproduct_no()
		{
			return product_no;
		}		
		float returnprice()
		{
			return price;
		}	
		float returndiscount()
		{
			return discount;
		}
		char* returnproduct_name()
		{
			return product_name;
		}	
		char* returnexpiry()
		{
			return expiry;
		}

		void write_product();
		void display_all();
		void modify_product();
		void delete_product();
		void display_specific_record(int);
};

Snacks snack;


void Snacks::write_product()
{
	fstream fu;             
	fu.open("snacksdatabase.dat",ios::out|ios::app);
	create_product();
	fu.write((char*)&snack,sizeof(Snacks));
	fu.close();
	cout<<"\n  PRODUCT HAS BEEN SUCCESSFULLY CREATED !!!!";
}

void Snacks::display_all()
{
	fstream fu;
	cout<<"\n ALL PRODUCTS PRESENT IN SNACKS SECTIONS : \n";
	fu.open("snacksdatabase.dat",ios::in);
	while(fu.read((char*)&snack,sizeof(Snacks)))
	{
		show_product();
		cout<<"\n===========================================================\n";	
	}
	fu.close();
}

void Snacks::modify_product()
{
	fstream fu;
	int number,flag;
	flag=0;
	cout<<"\n\n	UPDATE A PRODUCT :   ";
	cout<<"\n\nPLEASE ENTER THE PRODUCT NUMBER OF THE PRODUCT TO BE UPDATED : ";
	cin>>number;
	fu.open("snacksdatabase.dat",ios::out|ios::in);
	while(fu.read((char*)&snack,sizeof(Snacks)) && flag==0)
	{
		if(returnproduct_no()==number)
		{
			show_product();
			fu.seekp(-1*sizeof(Snacks),ios::cur);
			snack.create_product();
			fu.write((char*)&snack,sizeof(Snacks));
			cout<<"\n\n  PRODUCT SUCCESSFULLY UPDATED !!!! ";
			flag=1;
		}
	}
	fu.close();
	if(flag==0)
	{
		cout<<"\n\nPRODUCT NOT FOUND !!!!";
	}
}

void Snacks::display_specific_record(int x)
{
	int flag;
	fstream fu;
	fu.open("snacksdatabase.dat",ios::in);
	while(fu.read((char*)&snack,sizeof(Snacks)))
	{
		if(returnproduct_no()==x)
		{
			show_product();
			flag=1;
		}
		fu.close();
		if(flag==0)
		{
			cout<<"\n\n PRODUCT DOES NOT EXIST !!!!";
		}
	}
}

void Snacks::delete_product()
{
	fstream fu1,fu2;
	int product_number;
	//cout<<"\n\n\nDELETE RECORD ";
	cout<<"\n\n PLEASE ENTER THE PRODUCT NUMBER OF THE PRODUCT TO BE DELETED : ";
	cin>>product_number;
	fu1.open("snacksdatabase.dat",ios::in|ios::out);
	fu2.open("temp.dat",ios::out);
	fu1.seekg(0,ios::beg);
	while(fu1.read((char*)&snack,sizeof(Snacks)))
	{
		if(returnproduct_no()!=product_number)
		{
			fu2.write((char*)&snack,sizeof(Snacks));
		}
	}
	fu2.close();
	fu1.close();
	remove("snacksdatabase.dat");
	rename("temp.dat","snacksdatabase.dat");
	usleep(3000000);
	cout<<"\n\nDELETING PRODUCT....";
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!";
}


class beverages
{
	protected:
	int product_no;
	int quantity;
	char product_name[60];
	char description[50];
	float price;
	float discount;
	float tax;
	int stock;
	float volume;
	int flag;
	char expiry[10];
	char day[2];
	char month[2];
	char year[4];
	public:
	beverages()
	{
		flag=0;
	}	
	void create_product()
	{
		char choice;
		cout<<"\n ENTER THE PRODUCT NUMBER : ";
		cin>>product_no;
		cout<<"\n ENTER THE PRODUCT NAME : ";
		cin.ignore();
		cin.getline(product_name,60);
		cout<<"\n ENTER THE NET VOLUME OF THE PRODUCT : ";
		cin>>volume;
		cout<<"\n ENTER THE PRICE OF THE PRODUCT : ";
		cin>>price;
		cout<<"\n ENTER TAX(%) FOR THE PRODUCT : ";
		cin>>tax;
		cout<<"\n ENTER THE DISCOUNT(%) FOR THE PRODUCT : ";
		cin>>discount;
		cout<<"\n ENTER EXPIRY DATE OF PRODUCT(DAY/MONTH/YEAR) : ";
		cin>>expiry;
		cout<<"\n ENTER STOCK OF PRODUCT : ";
		cin>>stock;
		cout<<"\n ADD SHORT DESCRIPTION (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			cout<<"\n ENTER THE DESCRIPTION ABOUT PRODUCT : ";
			cin.ignore();
			cin.getline(description,50);
		}
		else
		{
			flag=1;
		}
		
	}
	void show_product()
	{
		cout<<"\n  PRODUCT NUMBER :               "<<product_no;
		cout<<"\n  PRODUCT NAME  :                "<<product_name;
		cout<<"\n  PRODUCT NET VOLUME  :          "<<volume<<" ml/ltr";
		cout<<"\n  PRICE OF THE PRODUCT  :        "<<price<<" Rs";
		cout<<"\n  TAX(GST) FOR PRODUCT  :        "<<tax<<" %";
		cout<<"\n  DISCOUNT FOR THE PRODUCT (%) : "<<discount<<" %";
		cout<<"\n  DATE OF EXPIRY :               "<<expiry;
		cout<<"\n  AVAILABLE STOCK OF PRODUCT :   "<<stock;
		if(flag==1)
		{
			cout<<"\n\n  DESCRIPTION : NO DESCRIPTION AVAILABLE ";
		}
		else
		{
			cout<<"\n\n  DESCRIPTION : " ;
			cout<<description;
		}
	}

	int returnday()
	{
		day[0]=expiry[0];
		day[1]=expiry[1];
		int x= atoi(day); 
		return x;
	}
	int returnmonth()
	{
		month[0]=expiry[3];
		month[1]=expiry[4];
		int x= atoi(month);
		return x;
	}
	int returnyear()
	{
		year[0]=expiry[6];
		year[1]=expiry[7];
		year[2]=expiry[8];
		year[3]=expiry[9];
		int x= atoi (year);
		return x;
	}
	float returntax()
	{
		return tax;
	}
	int returnproduct_no()
	{
		return product_no;
	}
	float returnprice()
	{
		return price;
	}
	
	char* returnproduct_name()
	{
		return product_name;
	}
	char* returnexpiry()
	{
		return expiry;
	}
	float returndiscount()
	{
		return discount;
	}
	int returnstock()
	{
		return stock;
	}
	void write_product();
	void display_all();
	void modify_product();
	void display_specific_record(int n);
	void delete_product();
		  
};
beverages beverage;
	
void beverages::write_product()
{
	fstream file;
	file.open("beveragedatabase.dat",ios::out|ios::app);
	create_product();
	file.write((char*)&beverage,sizeof(beverages));
	file.close();
	cout<<"\n PRODUCT HAS BEEN SUCESSFULLY CREATED !!!! ";
}
void beverages::display_all()
{
	 fstream file;
 	 cout<<"\nPRODUCTS AVAILABLE IN BEVERAGES SECTION :  \n";
 	 file.open("beveragedatabase.dat",ios::in);
  	while(file.read((char*)&beverage,sizeof(beverages)))        
  	{
   		 show_product();
    		 cout<<"\n===========================================================\n";
  	}
     	file.close();
}
void beverages::modify_product()
{
	fstream file5;
	int no,f;
	f=0;
//	cout<<"\n\nTo Modify";
	cout<<"\n\nPLEASE ENTER PRODUCT NUMBER OF PRODUCT TO BE UPDATED : ";
	cin>>no;
	file5.open("beveragedatabase.dat",ios::in|ios::out);
	while(file5.read((char*)&beverage,sizeof(beverages)) && f==0)
	{
		if(returnproduct_no()==no)
		{
			show_product();
			//int pos=-1*sizeof(product);
			file5.seekp(-1*sizeof(beverages),ios::cur);
			create_product();
			file5.write((char*)&beverage,sizeof(beverages));
			cout<<"\n\n  PRODUCT SUCCESSFULLY UPDATED !!!!";
			f=1;
		}
	}
	file5.close();
	if(f==0)
	{
		cout<<"\n\n PRODUCT NOT FOUND !!!";
	}
}
void beverages::display_specific_record(int n)
{
	int f;
	f=0;
	fstream file;
	file.open("beveragedatabase.dat",ios::in);                  //to open database file
	while(file.read((char*)&beverage,sizeof(beverages)))  //to read every element in database file
	{
		if(returnproduct_no()==n)
		{ 						     																												
			show_product();
			f=1;
		}
		file.close();		//to close database file
		if(f==0)
		{
			cout<<"\n\nPRODUCT DOES NOT EXIST !!!";
		}
	}  //end of while
}
void beverages::delete_product()		//delete function
{
 	fstream file,file2;
  	int product_no;
  //	cout<<"\n\n\nDELETE RECORD";
  	cout<<"\n\n PLEASE ENTER THE PRODUCT NO OF THE PRODUCT YOU WANT TO DELETE : ";
 	cin>>product_no;
  	file.open("beveragedatabase.dat",ios::in|ios::out);    //opening original file
  	file2.open("Temp.dat",ios::out);         //opening temporary file
  	file.seekg(0,ios::beg);                  //bringing file pointer at beginning
  	while(file.read((char*)&beverage,sizeof(beverages)))
  	{
    		 if(returnproduct_no()!=product_no)
     		 {
	 		 file2.write((char*)&beverage,sizeof(beverages));
     		 }
  	}   //end of while
 
  	file2.close();       //closing temporary file
  	file.close();        //closing original file
  	remove("beveragedatabase.dat");     // deleting original file 
  	rename("Temp.dat","beveragedatabase.dat");   //renaming temporary file as original file
	usleep(3000000);
	cout<<"\n\nDELETING PRODUCT....";
  	cout<<"\n\n\tPRODUCT SUCCESSFULLY DELETED !!!";
  
} // end of class beverages




class placeorder:public mobiles,public computers,public cookings
{

	int prod_number5[100],quantity5[100], prod_number[100],quantity[100],prod_number1[100],quantity1[100],quantity4[100],prod_number4[100],prod_number2[100],quantity2[100],prod_number3[100],quantity3[100];
	int c,m,n,p,v,q,choice,choice1;
	double amount1,amount2,amount3,amount4,amount5,amount6,amount_after_dis1,amount_after_dis2,amount_after_dis5,amount_after_dis3,amount_after_dis4,amount_after_dis6;
	double total1,total2,total3,total4,total5,total6,total,saving1,saving2,saving3,saving4,saving5,saving6,saving;
	char ch,ch1,ch2,ch3,ch4,ch5;
	char date1[12];
	char date2[10];
	char date3[10];
	
	//menu();
	public:
	placeorder()
	{
		c=0;
		m=0;
		n=0;
		p=0;
		v=0;
		q=0;
		total=0;
		saving1=0,saving2=0,saving3=0,saving4=0,saving5=0,saving6=0;
		saving=0;
		ch='Y';
	}
	void  place_order();

};
void placeorder:: place_order()
	{
		fstream file,file1,file2;
		char str[3]="am";
		char str1[3]="pm";
		char str3[4];
		int count1;
		char customer_name[20];
		time_t currentTime;
  		struct tm *localTime;

 		time( &currentTime );                   // Get the current time
  		localTime = localtime( &currentTime );  // Convert the current time to the local time
		 int Day    = localTime->tm_mday;
 		 int Month  = localTime->tm_mon+1;
 		 int Year   = localTime->tm_year+1900;
  		 int Hour   =localTime->tm_hour;
  		 int Min    = localTime->tm_min;
		if(Hour>=12)
		{
			strcpy(str3,str1);
		}
		else
		{
			strcpy(str3,str);
		}
		if(Hour>12)
		{
			Hour =localTime->tm_hour-12;
		}
		else
		{
			Hour =localTime->tm_hour;
		}
		/*string result;  ///* to convert int date to char date */
		/*ostringstream convert;
		convert<<Day;
		convert<<Month;
		convert<<Year;
		result=convert.str();
		for(int i=0;i<2;i++)
		{
			date1[i]=result[i];
		}
		date1[2]='/';
		//date1[3]=0;
		date1[3]=result[2];
		date1[4]='/';
		for(int i=3;i<8;i++)
		{
			date1[i+2]=result[i];
		}
		//cout<<"\n"<<date1;*/
		cout<<"\n\t\tPLACE YOUR ORDER\t\t\n";
		cout<<"\n ENTER NAME OF CUSTOMER : ";
		cin.ignore();
		cin.getline(customer_name,20);
		labelorder://if(count1==1)
		    ///  {
			    system("cls");
		    //  }*/
		cout<<"\n\n\n\t\t\t\t\t\t\t\tADD A PRODUCT TO CART FROM THE FOLLOWING\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.GROCERY SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.PROCEED FOR INVOICE";
		cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
		cin>>choice;
		try
		{
			if(choice>4 ||choice==0)
			{
				throw(choice);
			}
		}
		catch(int x)
		{
			cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
			cout<<"\n\nENTER YOUR CHOICE : ";
			cin>>choice;
		}	
		switch(choice)
		{
		case 1:{
				labelorderelectronics: system("cls");
				cout<<"\n\n\n\t\t\t\t\t\t\t\tADD A PRODUCT TO CART FROM THE FOLLOWING\n\n\n\t\t\t\t\t\t\t\t1.MOBILE STORE\n\n\n\t\t\t\t\t\t\t\t2.COMPUTER AND LAPTOP STORE\n\n\n\t\t\t\t\t\t\t\t3.GO BACK";
				cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
				cin>>choice1;
				try
				{
					if(choice1>3 ||choice1==0)
					{
						throw(choice1);
					}
				}
				catch(int x)
				{
					cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-3)";
					cout<<"\n\nENTER YOUR CHOICE : ";
					cin>>choice1;
				}
				switch(choice1)
				{
					case 1:	{
						do
						{
							system("cls");
							mobile.display_all();
							cout<<"\n\n\n ENTER THE PRODUCT NUMBER : ";
							cin>>prod_number[c];
							cout<<" ENTER THE QUANTITY IN NUMBER : ";
							cin>>quantity[c];
							c++;
							cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
							cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
							cin>>ch;
			
						}while(ch=='y' || ch=='Y');
						count1=1;
						goto labelorderelectronics;
						break;
						}
					case 2:{
						do
						{	
							system("cls");
							computer.display_all();
							cout<<"\n\n\n ENTER THE PRODUCT NUMBER : ";
							cin>>prod_number1[m];
							cout<<" ENTER THE QUANTITY IN NUMBER : ";
							cin>>quantity1[m];
							m++;
							cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
							cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
							cin>>ch1;
			
						}while(ch1=='y' || ch1=='Y');
						count1=1;
						goto labelorderelectronics;
						break;
						}
					case 3:count1=1;
						goto labelorder;
				}		
			}
		case 2:{
				labelordergrocery: system("cls");
				cout<<"\n\n\n\t\t\t\t\t\t\t\tADD A PRODUCT TO CART FROM THE FOLLOWING SECTIONS : \n\n\n\t\t\t\t\t\t\t\t1.COOKING SUPPLLIES STORE\n\n\n\t\t\t\t\t\t\t\t2.SNACKS SECTION\n\n\n\t\t\t\t\t\t\t\t3.BEVERAGES SECTIONS\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
				cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
				cin>>choice1;
				try
				{
					if(choice1>4 ||choice1==0)
					{
						throw(choice1);
					}
				}
				catch(int x)
				{
					cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
					cout<<"\n\nENTER YOUR CHOICE : ";
					cin>>choice1;
				}
				switch(choice1)
				{
					case 1:{
		
						do
						{
							system("cls");
							cooking.display_all();
							cout<<"\n\n\n ENTER THE PRODUCT NUMBER : ";
							cin>>prod_number2[n];
							cout<<" ENTER THE QUANTITY IN NUMBER : ";
							cin>>quantity2[n];
							n++;
							cout<<n;
							cout<<"\n"<<prod_number2[n];
							cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
							cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
							cin>>ch2;
			
						}while(ch2=='y' || ch2=='Y');
						count1=1;
						goto labelordergrocery;
					       }
					case 2:{
					  	do
						{
							system("cls");
							snack.display_all();
							cout<<"\n\n\n ENTER THE PRODUCT NUMBER : ";
							cin>>prod_number5[q];
							cout<<" ENTER THE QUANTITY IN NUMBER : ";
							cin>>quantity5[q];
							q++;
							cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
							cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
							cin>>ch5;
			
						}while(ch5=='y' || ch5=='Y');
						count1=1;
						goto labelordergrocery;
					       }
					case 3:{
						do
						{
							system("cls");
							beverage.display_all();
							cout<<"\n\n\n ENTER THE PRODUCT NUMBER : ";
							cin>>prod_number4[v]; 
							cout<<" ENTER THE QUANTITY IN NUMBER : ";
							cin>>quantity4[v];
							v++;
							cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
							cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
							cin>>ch4;
						}while(ch4=='y' || ch4=='Y');
						count1=0;
						goto labelordergrocery;
						}
					case 4: count1=1;
						goto labelorder;
						
				}
				
						
			}		
		case 3:{
			do
			{
				system("cls");
				cosmetic.display_all();
				cout<<"\n\n\n Enter the product number:";
				cin>>prod_number3[p];
				cout<<" Enter the quantity in number : ";
				cin>>quantity3[p];
				p++;
				cout<<"\n\nPRODUCT HAS BEEN ADDED TO THE CART !!!";
				cout<<"\n\nDO YOU WANT TO ORDER ANOTHER PRODUCT IN CART(Y/N) : ";
				cin>>ch3;
			
			}while(ch3=='y' || ch3=='Y');
			goto labelorder;
			}	
		case 4:goto invoice;
	
		}
		
	
		
		invoice: system("cls");
		cout<<"\n\n"<<setfill('*')<<setw(80)<<"*"<<"INVOICE"<<setfill('*')<<setw(80)<<"*"<<"\n\n";
		cout<<"CUSTOMER NAME : "<<customer_name<<endl;
		cout<<setfill(' ')<<setw(150)<<"DATE = "<<Day<<"/"<<Month<<"/"<<Year<<" "<<endl;
		cout<<setfill(' ')<<setw(150)<<"TIME = "<<Hour<<":"<<Min<<str3<<" ";
	//	cout<<"\n"<<setfill('-')<<setw(140)<<"-";
		cout<<"\n"<<setfill('=')<<setw(170)<<"=";
		cout<<setfill(' ')<<setw(25)<<"\nPRODUCT NUMBER"<<setw(28)<<"PRODUCT NAME"<<setw(20)<<"QUANTITY"<<setw(19)<<"PRICE"<<setw(16)<<"AMOUNT"<<setw(13)<<"TAX"<<setw(14)<<"DISCOUNT"<<setw(45)<<"AMOUNT AFTER DISCOUNT AND TAXES\n\n";
		cout<<setfill('=')<<setw(170)<<"=";
		//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
		for(int i=0;i<c;i++)
		{
			file.open("mobiledatabase.dat",ios::in);
			file.read((char*)&mobile,sizeof(mobiles));
			while(!file.eof())
			{
			/*if(Day>=mobile.returnday() && Month>=mobile.returnmonth() && Year>=mobile.returnyear() )
			{
				cout<<"\n PRODUCT HAS EXPIRED !!!";
				//count=1;
				cout<<"\n"<<setfill('-')<<setw(140)<<"-";
			}
			else
			{ */
			if(mobile.returnproduct_no()==prod_number[i])
			{
				amount1=mobile.returnprice()*quantity[i];
				amount_after_dis1=amount1-(amount1*mobile.returndiscount()/100)+(amount1*mobile.returntax()/100);
				
				cout<<setfill(' ')<<"\n"<<setw(5)<<prod_number[i]<<setw(40)<<mobile.returnproduct_name()<<setw(15)<<quantity[i]<<setw(20)<<mobile.returnprice()<<" Rs"<<setw(12)<<amount1<<" Rs"<<setw(10)<<mobile.returntax()<<" %"<<setw(10)<<mobile.returndiscount()<<" %"<<setw(20)<<amount_after_dis1<<" Rs";
				total1+=amount_after_dis1;
				saving1=saving1+(amount1-amount_after_dis1);
			}
			
			file.read((char*)&mobile,sizeof(mobiles));
			}
		file.close();
		}
		//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
		for(int j=0;j<m;j++)
		{
			file1.open("computerdatabase.dat",ios::in);
			file1.read((char*)&computer,sizeof(computers));
			while(!file1.eof())
			{
			/*if(strcmp(date1,computer.returnexpiry())==0)
			{
				cout<<"\n PRODUCT HAS EXPIRED !!!";
				//count=1;
				cout<<"\n"<<setfill('-')<<setw(140)<<"-";
			}
			else
			{ */
			if(computer.returnproduct_no()==prod_number1[j])
			{
				amount2=computer.returnprice()*quantity1[j];
				amount_after_dis2=amount2-(amount2*computer.returndiscount()/100)+(amount2*computer.returntax()/100);
				
				cout<<"\n"<<setfill(' ')<<setw(5)<<prod_number1[j]<<setw(40)<<computer.returnproduct_name()<<setw(15)<<quantity1[j]<<setw(20)<<computer.returnprice()<<" Rs"<<setw(12)<<amount2<<" Rs"<<setw(10)<<computer.returntax()<<" %"<<setw(10)<<computer.returndiscount()<<" %"<<setw(20)<<amount_after_dis2<<" Rs";
				total2+=amount_after_dis2;
				saving2=saving2+(amount2-amount_after_dis2);
			}
			file1.read((char*)&computer,sizeof(computers));
			}
		file1.close();
		}
	//	cout<<"\n"<<setfill('-')<<setw(140)<<"-";
		for(int k=0;k<n;k++)
		{
			file2.open("cookingdatabase.dat",ios::in);
			file2.read((char*)&cooking,sizeof(cookings));
			while(!file2.eof())
			{
			if( (Day>=cooking.returnday() || Month>=cooking.returnmonth() ) && Year>=cooking.returnyear() )
			{
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
				cout<<"\n    PRODUCT NO."<<prod_number2[k]<<" IN BEVERAGE SECTION HAS EXPIRED !!!  PLEASE REMOVE THIS PRODUCT !!!";
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
			}
			else
			{ 
			if(cooking.returnproduct_no()==prod_number2[k])
			{
				amount3=cooking.returnprice()*quantity2[k];
				amount_after_dis3=amount3-(amount3*cooking.returndiscount()/100)+(amount3*cooking.returntax()/100);
				
				cout<<"\n"<<setfill(' ')<<setw(5)<<prod_number2[k]<<setw(40)<<cooking.returnproduct_name()<<setw(15)<<quantity2[k]<<setw(20)<<cooking.returnprice()<<" Rs"<<setw(12)<<amount3<<" Rs"<<setw(10)<<cooking.returntax()<<" %"<<setw(10)<<cooking.returndiscount()<<" %"<<setw(20)<<amount_after_dis3<<" Rs";
				total3+=amount_after_dis3;
				saving3=saving3+(amount3-amount_after_dis3);
			}
			}
			file2.read((char*)&cooking,sizeof(cookings));
			}
		file2.close();
		}
		//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
		for(int r=0;r<q;r++)
		{
			ifstream file7;
			file7.open("snacksdatabase.dat",ios::in);
			file7.read((char*)&snack,sizeof(Snacks));
			while(!file7.eof())
			{
			if( (Day>=snack.returnday() || Month>=snack.returnmonth() ) && Year>=snack.returnyear() )
			{
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
				cout<<"\n    PRODUCT NO."<<prod_number5[r]<<" IN SNACKS SECTION HAS EXPIRED !!!  PLEASE REMOVE THIS PRODUCT !!!";
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
			}
			else
			{ 
			if(snack.returnproduct_no()==prod_number5[r])
			{
				amount6=snack.returnprice()*quantity5[r];
				amount_after_dis6=amount6-(amount6*snack.returndiscount()/100)+(amount6*snack.returntax()/100);
				
				cout<<"\n"<<setfill(' ')<<setw(5)<<prod_number5[r]<<setw(40)<<snack.returnproduct_name()<<setw(15)<<quantity5[r]<<setw(20)<<snack.returnprice()<<" Rs"<<setw(12)<<amount6<<" Rs"<<setw(10)<<snack.returntax()<<" %"<<setw(10)<<snack.returndiscount()<<" %"<<setw(20)<<amount_after_dis6<<" Rs";
				total6+=amount_after_dis6;
				saving6=saving6+(amount6-amount_after_dis6);
			}
			}
			file7.read((char*)&snack,sizeof(Snacks));
			}
		file7.close();
		}
		//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
		for(int t=0;t<v;t++)
		{
			ifstream file6;
			file6.open("beveragedatabase.dat",ios::in);
			file6.read((char*)&beverage,sizeof(beverages));
			while(!file6.eof())
			{
			if( (Day>=beverage.returnday() || Month>=beverage.returnmonth() ) && Year>=beverage.returnyear() )
			{
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
				cout<<"\n    PRODUCT NO."<<prod_number4[t]<<" IN BEVERAGE SECTION HAS EXPIRED !!!  PLEASE REMOVE THIS PRODUCT !!!";
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
			}
			else
			{ 
			if(beverage.returnproduct_no()==prod_number4[t])
			{
				amount5=beverage.returnprice()*quantity4[t];
				amount_after_dis5=amount5-(amount5*beverage.returndiscount()/100)+(amount5*beverage.returntax()/100);
				
				cout<<"\n"<<setfill(' ')<<setw(5)<<prod_number4[t]<<setw(40)<<beverage.returnproduct_name()<<setw(15)<<quantity4[t]<<setw(20)<<beverage.returnprice()<<" Rs"<<setw(12)<<amount5<<" Rs"<<setw(10)<<beverage.returntax()<<" %"<<setw(10)<<beverage.returndiscount()<<" %"<<setw(20)<<amount_after_dis5<<" Rs";
				total5+=amount_after_dis5;
				saving5=saving5+(amount5-amount_after_dis5);
			}
			}
			file6.read((char*)&beverage,sizeof(beverages));
			}
		file6.close();
		}
		
		for(int i=0;i<p;i++)
		{
			ifstream file3;
			file3.open("cosmeticsdatabase.dat",ios::in);
			file3.read((char*)&cosmetic,sizeof(cosmetics));
			while(!file3.eof())
			{
			if((Day>=cosmetic.returnday() || Month>=cosmetic.returnmonth()) && Year>=cosmetic.returnyear() )
			{
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
				cout<<"\nPRODUCT NO."<<prod_number3[i]<<" \tPRODUCT HAS EXPIRED !!!  PLEASE REMOVE THIS PRODUCT !!!";
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
			}
			else
			{ 
			if(cosmetic.returnproduct_no()==prod_number3[i])
			{
				amount4=cosmetic.returnprice()*quantity3[i];
				amount_after_dis4=amount4-(amount4*cosmetic.returndiscount()/100)+(amount4*cosmetic.returntax()/100);
				
				cout<<"\n"<<setfill(' ')<<setw(5)<<prod_number3[i]<<setw(40)<<cosmetic.returnproduct_name()<<setw(15)<<quantity3[i]<<setw(20)<<cosmetic.returnprice()<<" Rs"<<setw(12)<<amount4<<" Rs"<<setw(10)<<cosmetic.returntax()<<" %"<<setw(10)<<cosmetic.returndiscount()<<" %"<<setw(20)<<amount_after_dis4<<" Rs";
				total4+=amount_after_dis4;
				saving4=saving4+(amount4-amount_after_dis4);
			}
			}
			file3.read((char*)&cosmetic,sizeof(cosmetics));
			}
		file3.close();
		}
		//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
		/*for(int u=0;u<p;u++)
		{
			ifstream file10;
			file10.open("cosmeticsdatabase.dat",ios::in);
			file10.read((char*)&cosmetic,sizeof(cosmetics));
			while(!file10.eof())
			{
			if( Day>=cosmetic.returnday() || Month>=cosmetic.returnmonth() )
			{	
				if(Year>=cosmetic.returnyear() )
			    {
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
			//	cout<<"\n    PRODUCT NO."<<prod_number3[u]<<" IN COSMETIC SECTION HAS EXPIRED !!!  PLEASE REMOVE THIS PRODUCT !!!";
				//cout<<"\n"<<setfill('-')<<setw(140)<<"-";
			    
				}
			}
			else
			{ 
			if(cosmetic.returnproduct_no()==prod_number3[u])
			{
				amount4=cosmetic.returnprice()*quantity3[u];
				amount_after_dis4=amount4-(amount4*cosmetic.returndiscount()/100)+(amount4*cosmetic.returntax()/100);
				
				cout<<"\n"<<setfill(' ')<<setw(5)<<prod_number3[u]<<setw(40)<<cosmetic.returnproduct_name()<<setw(15)<<quantity3[u]<<setw(20)<<cosmetic.returnprice()<<" Rs"<<setw(12)<<amount4<<" Rs"<<setw(20)<<amount_after_dis4<<" Rs";
				total4+=amount_after_dis4;
				saving4=saving4+(amount4-amount_after_dis4);
			}
			}
			file10.read((char*)&cosmetic,sizeof(cosmetics));
			}
		file10.close();
		}*/
		//cout<<"\n"<<setfill('=')<<setw(140)<<"=";
		c=0;
		m=0;
		n=0;
		p=0;
		v=0;
		q=0;
		cout<<"\n"<<setfill('-')<<setw(170)<<"-";
		total=total1+total2+total3+total4+total5+total6;
		saving=saving1+saving2+saving3+saving4+saving5+saving6;
		cout<<"\n\n\n\t\tYOUR TOTAL SAVINGS : "<<saving<<" Rs"<<" !!!";
		cout<<"\n\n\n\t\t\tTOTAL= "<<total<<" Rs"<<"\n";
		cout<<"\n\n\t\tTHANK YOU FOR PLACING YOUR ORDER !!!!";
	}
class adminmenu
{
	public:

	void admin_menu();
	
};

void adminmenu::admin_menu()
{
		char ch='y';
		char str[100];
		//char acct[100];
		string str1;
		//string pass="";
		for(;;)
		{
			string pass="";
			char ch;
			cout<<"\nENTER PASSWORD : ";
			ch = _getch();
			while(ch != 13){//character 13 is enter
			pass.push_back(ch);
			cout << '*';
			ch = _getch();
			}
			
   			//cin>>str;
 		
			ifstream fin("password.dat");
			fin>>str1;
			if(str1==pass)
			{
				 label0:system("cls");
				 int choice,choice1,choice2;
				 cout<<"\t\t\t\t\t\t\t"<<setfill('=')<<setw(80)<<"=";
				 cout<<setw(20)<<"\n\n\t\t\t\t\t\t\t\t\t\tADMINISTRATION MENU\n";
			  	 cout<<"\t\t\t\t\t\t\t"<<setfill('=')<<setw(80)<<"=";
				 cout<<"\n\n\n\t\t\t\t\t\t\t\t1.ADD A NEW PRODUCT\n\n\n\t\t\t\t\t\t\t\t2.DISPLAY A PRODUCT\n\n\n\t\t\t\t\t\t\t\t3.UPDATE A PRODUCT\n\n\n\t\t\t\t\t\t\t\t4.DELETE A PRODUCT\n\n\n\t\t\t\t\t\t\t\t5.BACK TO MAIN MENU\n\n\t";
					cout<<"\n\n\t\t\t\t\t\t\tPLEASE ENTER YOUR CHOICE (1-5) : ";
					cin>>choice;
					try
					{
						if(choice>5 ||choice==0)
						{
							throw(choice);
						}
					}
					catch(int x)
					{
						cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-5)";
						cout<<"\n\nENTER YOUR CHOICE : ";
						cin>>choice;
					}
					switch(choice)
					{
						case 1:{ 
								labeladd: system("cls");
								cout<<"\n\t\t\t\t\t\t\t\tADD A NEW PRODUCT IN PARTICULAR SECTION GIVEN BELOW : ";
								cout<<"\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.GROCERY SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
								cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
								cin>>choice1;
								try
								{
									if(choice1>4 ||choice1==0)
									{
										throw(choice1);
									}
								}
								catch(int x)
								{
									cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
									cout<<"\n\nENTER YOUR CHOICE : ";
									cin>>choice1;
								}
								switch(choice1)
								{
								 	case 1: //FOR ELECTRONICS SECTION
								  	{
								  		system("cls");
								   		labeladdelectronics:cout<<"\n\n\t\t\t\t\t\t\t\tADD NEW PRODUCT IN FOLLOWING SECTION : ";
								  		cout<<"\n\n\n\t\t\t\t\t\t\t\t1.MOBILES AND ACCESSORIES\n\n\n\t\t\t\t\t\t\t\t2.LAPTOPS AND COMPUTER\n\n\n\t\t\t\t\t\t\t\t3.GO BACK";
								 		 cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
								 		 cin>>choice2;
										try
										{
											if(choice2>3 ||choice2==0)
											{
												throw(choice2);
											}
										}
										catch(int x)
										{
											cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-3)";
											cout<<"\n\nENTER YOUR CHOICE : ";
											cin>>choice2;
										}
								  		switch(choice2)
								 		{
											case 1:{	//FOR MOBILE 
												    
												do
												{
													system("cls");
									      			 cout<<"\n\t\t\t\t\t\t\t\tADD PRODUCT IN MOBILE SECTION : \n\n\n";
													mobile.write_product();
													cout<<"\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
													cin>>ch;
												}while(ch=='y' || ch=='Y');
												 system("cls");
												 goto labeladdelectronics;
												}
											case 2:		//FOR COMPUTER AND LAPTOPS
												{
												
												do
												{
													system("cls");
									   			cout<<"\n\t\t\t\t\t\t\t\tADD PRODUCT IN COMPUTER AND LAPTOP SECTION : \n\n\n";
													computer.write_product();
													cout<<"\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
													cin>>ch;
												}while(ch=='y' || ch=='Y');
												system("cls");
												goto labeladdelectronics;
											case 3: goto labeladd;
										}
									}
									case 2://FOR GLOCERY SECTION
									{
										system("cls");
										labeladdglocery:cout<<"\n\t\t\t\t\t\t\t\tADD NEW PRODUCT IN FOLLOWING SECTION : ";
										cout<<"\n\n\n\t\t\t\t\t\t\t\t1.COOKING SUPPLIES SECTION\n\n\n\t\t\t\t\t\t\t\t2.SNACKS SECTION\n\n\n\t\t\t\t\t\t\t\t3.BEVERAGES SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
										cout<<"\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
										cin>>choice1;
										try
										{
											if(choice1>4 ||choice1==0)
											{
												throw(choice1);
											}
										}
										catch(int x)
										{
											cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
											cout<<"\n\nENTER YOUR CHOICE : ";
											cin>>choice1;
										}
										switch(choice1)
										{
											case 1:{      //FOR COOKING SUPPLIES
											// 	system("cls");
									   
												do
												{
													system("cls");
													cout<<"\n\t\t\t\t\t\t\t\tADD PRODUCT IN COOKING SUPPLIES SECTION : \n\n\n";
													cooking.write_product();
													cout<<"\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
													cin>>ch;
												}while(ch=='y' || ch=='Y');
												system("cls");
												goto labeladdglocery;
												}
											case 2:{	//FOR BEVERAGES
												// system("cls");
									     		//	cout<<"\n\nADD PRODUCT IN SNACKS SECTION : \n\n\n";
												do
												{
													system("cls");
													cout<<"\n\t\t\t\t\t\t\t\tADD PRODUCT IN SNACKS SECTION : \n\n\n";
													snack.write_product();
													cout<<"\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
													cin>>ch;
												}while(ch=='y' || ch=='Y');
												system("cls");
												goto labeladdglocery;
												}
											case 3:{	//FOR BEVERAGES
												// system("cls");
									     		//	cout<<"\nADD PRODUCT IN BEVERAGES SECTION : \n\n\n";
												do
												{
													system("cls");
													cout<<"\n\t\t\t\t\t\t\t\tADD PRODUCT IN BEVERAGES SECTION : \n\n\n";
													beverage.write_product();
													cout<<"\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
													cin>>ch;
												}while(ch=='y' || ch=='Y');
												system("cls");
												goto labeladdglocery;
												}
									
											case 4:	  system("cls");
												 goto labeladd;
				
										}
									}
									case 3:		//FOR COSMETICS SECTION
									{
										// system("cls");
										
										do
										{
											system("cls");
											cout<<"\n\t\t\t\t\t\t\t\tADD PRODUCT IN COSMETICS SECTION : \n\n\n";
											cosmetic.write_product();
											cout<<"\n\nDO WANT TO ADD MORE PRODUCT (Y/N) : ";
											cin>>ch;
											}while(ch=='y' || ch=='Y');
										goto labeladd;
										}
									}
									case 4: goto label0;
								}
							}   //END OF ADD PRODUCT SWITCH CASE 	
						case 2: {
								 system("cls");
								labeldisplay:cout<<"\n\t\t\t\t\t\t\t\tDISPLAY PRODUCTS IN FOLLOWING SECTION : ";
								cout<<"\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.GROCERY SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
								cout<<"\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
								cin>>choice1;
								try
								{
									if(choice1>4 ||choice1==0)
									{
										throw(choice1);
									}
								}
								catch(int x)
								{
									cout<<"\n\nPLEASE ENTER CHOICE BETWEEN (1-4)";
									cout<<"\n\nENTER YOUR CHOICE : ";
									cin>>choice1;
								}
								switch(choice1)
								{
									case 1:{
											 system("cls");
											labeldisplayelectronics:cout<<"\n\t\t\t\t\t\t\t\tDISPLAY PRODUCT IN FOLLOWING SECTION : ";
											cout<<"\n\n\t1.MOBILES AND ACCESSORIES\n\n\n\t2.LAPTOPS AND COMPUTER\n\n\n\t3.GO BACK";
											cout<<"\n\n\n\tENTER YOUR CHOICE : ";
											cin>>choice2;
											try
											{
												if(choice2>3 ||choice1==0)
												{
													throw(choice2);
												}
											}
											catch(int x)
											{
												cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-3)";
												cout<<"\n\nENTER YOUR CHOICE : ";
												cin>>choice2;
											}
											switch(choice2)
									  		{
									 			 case 1: {
													 system("cls");
										 			 cout<<"\n\n\t\t\t\t\t\t\t\tPRODUCT IN MOBILE SECTION : \n\n\n";
													
													 mobile.display_all();
													
									
													 goto labeldisplayelectronics;
													 }
									 			 case 2: {
													   system("cls");
													  cout<<"\n\n\n\t\t\t\t\t\t\t\tPRODUCTS IN COMPUTERS AND LAPTOPS : ";
						
													  computer.display_all();
													  goto labeldisplayelectronics;
													 }
												  case 3: system("cls");
													goto labeldisplay;
											}
									       }    
									case 2:
										{
											system("cls");
											labeldisplaygrocery:cout<<"\n\n\t\t\t\t\t\t\t\tDISPLAY PRODUCT IN FOLLOWING SECTION : \n\n";
											cout<<"\n\n\t1.COOKING SUPPLIES SECTION\n\n\n\t2.SNACKS SECTION\n\n\n\t3.BEVERAGES SECTION\n\n\n\t4.GO BACK";
											cout<<"\n\n\n\tENTER YOUR CHOICE : ";
											cin>>choice2;
											switch(choice2)
											{
												case 1:
													{
													 system("cls");
													 cout<<"\n\t\t\t\t\t\t\t\tPRODUCT IN COOKING SUPPLIES SECTION : \n\n\n";
													 cooking.display_all();
													 goto labeldisplaygrocery;
													}
												case 2:
													{
													 system("cls");
													 cout<<"\n\t\t\t\t\t\t\t\tPRODUCT IN SNACKS SECTION : \n\n\n";
													 snack.display_all();
									 				 goto labeldisplaygrocery;
													}
								  				case 3:
													{
													 system("cls");
													 cout<<"\n\t\t\t\t\t\t\t\tPRODUCT IN BEVERAGES SECTION : \n\n\n";
													 beverage.display_all();
									 				 goto labeldisplaygrocery;
													}
								  				case 4:system("cls");
													goto labeldisplay;
											}
										}
									case 3: 
										{
											 system("cls");
											cout<<"\n\t\t\t\t\t\t\t\tPRODUCT IN COSMETICS SECTION : \n\n\n";
											cosmetic.display_all();
											goto labeldisplay;
										}	
									case 4: 
										goto label0;
						
								}
							}
						/*case 3: {
								int n;
								cout<<"\nMENU";
								cout<<"\n\n1.MOBILE SECTION\n\n2.COMPUTER SECTION\n\n3.COOKING SUPPLIES SECTION";
								cin>>choice1;
								try
								{
									if(choice1>3 ||choice1==0)
									{
										throw(choice1);
									}
								}
								catch(int x)
								{
									cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-3)";
									cout<<"\n\nENTER YOUR CHOICE : ";
									cin>>choice1;
								}
								switch(choice1)
								{
								case 1:{
									cout<<"\n\n\tPlease Enter the product no";
									cin>>n;
									mobile.display_specific_record(n);
									break;
									}
								case 2:{
									cout<<"\n\n\tPlease Enter the product no";
									cin>>n;
									computer.display_specific_record(n);
									break;
									}
								case 3:{
									cout<<"\n\n\tPlease Enter the product no";
									cin>>n;
									cooking.display_specific_record(n);
									break;
									}
								case 4:{
									cout<<"\n\n\tPlease Enter the product no";
									cin>>n;
									computer.display_specific_record(n);
									break;
									}
								}
						
							 }*/
						case 3: {
								labelmodify:system("cls");
								cout<<"\n\t\t\t\t\t\t\t\tSELECT THE SECTION OF PRODUCT TO BE UPDATE";
								cout<<"\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.GROCERY SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
								cout<<"\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
								cin>>choice1;
								try
								{
									if(choice1>4 ||choice1==0)
									{
										throw(choice1);
									}
								}
								catch(int x)
								{
									cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
									cout<<"\n\nENTER YOUR CHOICE : ";
									cin>>choice1;
								}
								switch(choice1)
								{
									case 1:{
											labelmodifyelectronics:system("cls");
											cout<<"\n\n\t\t\t\t\t\t\t\tSELECT THE SECTION OF PRODUCT TO BE UPDATE";
											cout<<"\n\n\t\t\t\t\t\t\t\t1.MOBILE AND ACCESSORIES\n\n\t\t\t\t\t\t\t\t2.COMPUTERS AND LAPTOPS\n\n\t\t\t\t\t\t\t\t3.GO BACK";
											cout<<"\n\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
											cin>>choice2;
											switch(choice2)
											{
												case 1:
													system("cls");
													mobile.display_all();
													mobile.modify_product();
													goto labelmodifyelectronics;
												case 2:
													 system("cls");
													 computer.display_all();
													computer.modify_product();
													goto labelmodifyelectronics;
												case 3: 
													goto labelmodify;
											}
										}
									case 2:{
										 	system("cls");
											labelmodifygrocery:cout<<"\n\n\t\t\t\t\t\t\t\tSELECT THE SECTION OF PRODUCT TO BE UPDATE : \n";
											cout<<"\n\n\t\t\t\t\t\t\t\t1.COOKING SUPPLIES\n\n\n\t\t\t\t\t\t\t\t2.SNACKS\n\n\n\t\t\t\t\t\t\t\t3.BEVERAGES\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
											cout<<"\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
											cin>>choice2;
											switch(choice2)
											{
												case 1:
													 system("cls");
													 cooking.display_all();
													cooking.modify_product();
													goto labelmodifygrocery;
												case 2:
													 system("cls");
													snack.display_all();
													snack.modify_product();
													goto labelmodifygrocery;
												case 3:
													 system("cls");
													 beverage.display_all();
													beverage.modify_product();
													goto labelmodifygrocery;
												case 4: 
													 system("cls");
													goto labelmodify;
											}
										}
									
							
									case 3:{
											system("cls");
											cosmetic.display_all();
											cosmetic.modify_product();
											goto labelmodify;
										}
									case 4:
										goto label0;
								}
						
							}
						case 4:{
								labeldelete: system("cls");
								cout<<"\n\n\t\t\t\t\t\t\t\tSELECT THE SECTION OF PRODUCT TO BE DELETED : \n";
								cout<<"\n\n\n\t\t\t\t\t\t\t\t1.ELECTRONICS SECTION\n\n\n\t\t\t\t\t\t\t\t2.GROCERY SECTION\n\n\n\t\t\t\t\t\t\t\t3.COSMETICS SECTION\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
								cout<<"\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
								cin>>choice1;
								try
								{
									if(choice1>4 ||choice1==0)
									{
										throw(choice1);
									}
								}
								catch(int x)
								{
									cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
									cout<<"\n\nENTER YOUR CHOICE : ";
									cin>>choice1;
								}
								switch(choice1)
								{
									case 1:{
											 system("cls");
											labeldeleteelectronics:cout<<"\n\n\t\t\t\t\t\t\t\tSELECT THE SECTION OF PRODUCT TO DELETED : \n";
											cout<<"\n\n\t\t\t\t\t\t\t\t1.MOBILE AND ACCESSORIES\n\n\n\t\t\t\t\t\t\t\t2.COMPUTERS AND LAPTOPS\n\n\n\t\t\t\t\t\t\t\t3.GO BACK";
											cout<<"\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
											cin>>choice2;
											try
											{
												if(choice2>3 || choice2==0)
												{
													throw(choice2);
												}
											}
											catch(int x)
											{
												cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-3)";
												cout<<"\n\nENTER YOUR CHOICE : ";
												cin>>choice2;
											}
											switch(choice2)
											{
												case 1:
													 system("cls");
													mobile.display_all();
													mobile.delete_product();
													goto labeldeleteelectronics;
												case 2:
													 system("cls");
													computer.display_all();
													computer.delete_product();
													goto labeldeleteelectronics;
												case 3: 
													 system("cls");
													goto labeldelete;
											}
										}
									case 2:{
											 system("cls");
											labeldeletegrocery:cout<<"\n\n\t\t\t\t\t\t\t\tSELECT THE SECTION OF PRODUCT TO BE DELETED : \n";
											cout<<"\n\n\t\t\t\t\t\t\t\t1.COOKING SUPPLIES\n\n\n\t\t\t\t\t\t\t\t2.SNACKS\n\n\n\t\t\t\t\t\t\t\t3.BEVERAGES\n\n\n\t\t\t\t\t\t\t\t4.GO BACK";
											cout<<"\n\n\n\t\t\t\t\t\t\t\tENTER YOUR CHOICE : ";
											cin>>choice2;
											try
											{
												if(choice2>4 || choice2==0)
												{
													throw(choice2);
												}
											}
											catch(int x)
											{
												cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
												cout<<"\n\nENTER YOUR CHOICE : ";
												cin>>choice2;
											}
											switch(choice2)
											{
												case 1:
													 system("cls");
													cooking.display_all();
													cooking.delete_product();
													goto labeldeletegrocery;
												case 2:
													system("cls");
													snack.display_all();
													snack.delete_product();
													goto labeldeletegrocery;
												case 3:
													system("cls");
													beverage.display_all();
													beverage.delete_product();
													goto labeldeletegrocery;
												case 4: 
													 system("cls");
													goto labeldelete;
											}
										}
									
							
									case 3:{
											 system("cls");
											cosmetic.display_all();
											cosmetic.delete_product();
											goto labeldelete;
										}
									case 4:{
										goto label0;
										}
								}		
					
							}
						case 5: system("cls");
							break;
						default:
							cout<<"\a";
							admin_menu();
					}
					break;
			}
			else
			{
				cout<<"\n\nINCORRECT PASSWORD !!! PLEASE TRY AGAIN !!!";
			}
		}		
}	
int main()
{
	introduction();
	int choice1,choice,choice2,m;
	placeorder p;
	fstream file;
	adminmenu a;
	system("color 1A");
	char str[20];
	char reset_password[20];
	int s=0,count=0;
	for(;;)
	{
		if(count==1)
		{
		main_menu:
		 system("cls");
		}
		cout<<"\n\n\n\n\t\t\t\t\t\t"<<setfill('=')<<setw(59)<<"=";
		cout<<setw(20)<<"\n\n\t\t\t\t\t\t\t\tMAIN MENU";
		cout<<"\n\n\t\t\t\t\t\t"<<setfill('=')<<setw(60)<<"=";
		cout<<"\n\n\n\t\t\t\t\t\t\t\t1.ADD PRODUCTS TO CART\n\n\n\t\t\t\t\t\t\t\t2.ADMINISTRATOR\n\n\n\t\t\t\t\t\t\t\t3.RESET ADMINISTRATOR PASSWORD\n\n\n\t\t\t\t\t\t\t\t4.EXIT";
		cout<<"\n\n\n\t\t\t\t\t\t\t\tPLEASE ENTER YOUR CHOICE : ";
		cin>>choice1;
		try
		{
			if( choice1>4 || choice1==0)
			{
				throw(choice1);
			}
		}
		catch(int x)
		{
			cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-4)";
			cout<<"\n\nENTER YOUR CHOICE : ";
			cin>>choice1;
		}
		switch(choice1)
		{
			case 1:		

					
					system("cls");
					count=1;
					p.place_order();
					cout<<"\n\n\n\n\t1.GO TO MAIN MENU\n\n\t2.EXIT";
					cout<<"\n\n\tENTER YOUR CHOICE : ";
					cin>>choice2;
					try
					{
						if(choice2>2 || choice2==0)
						{
							throw(choice2);
						}
					}
					catch(int x)
					{
						cout<<"\nPLEASE ENTER CHOICE BETWEEN (1-2)";
						cout<<"\n\nENTER YOUR CHOICE : ";
						cin>>choice2;
					}
					switch(choice2)
					{
						case 1:goto main_menu;
							break;
						case 2:
							   exit(0);
					}
					break;

			case 2:
					system("cls");
					a.admin_menu();
					break;

			case 3:	 	system("cls");
					{
					string pass="";
					char ch,ch2;
					cout<<"\nENTER PREVIOUS PASSWORD : ";
					ch = _getch();
					while(ch != 13){//character 13 is enter
					pass.push_back(ch);
					cout << '*';
					ch = _getch();
					}
					ifstream fin("password.dat");
					fin>>reset_password;
					if(reset_password==pass)
					{

						ofstream fout("password.dat");
						cout<<"\nENTER NEW PASSWORD : ";
						cin>>reset_password;
						fout<<reset_password;
						fout.close();
						cout<<"\n PASSWORD SUCESSFULLY CHANGED  !!!!";
					}
					else
					{
						cout<<"\n INCORRECT PASSWORD !!! PLEASE ENTER CORRECT PASSWORD";
					}
					}
					break;
			case 4: 
			
					exit(0);
					
					
			//default: cout<<"\a";
		}
	}
	return(0);
}

