/*Nhom 3:
  Tran Quoc Tuan-HE163901
  Nguyen Thanh Tung-HE161278
  Vu Duc Manh-HE163272
  Pham Quang Huy-HE161937 
  Nguyen Van Quyen-HE161892
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
//constant declaration: 
#define RATE_HEALTH 0.01
#define RATE_PENSION 0.05
#define DEPENDANT 1600
#define YOURSELF 4000.0
 
//prototype
int menu();
int Yes_No();
double Total(double p,double h,double d,double Gift );
double Tax(double TaxIncome );
void Output1(double Income,double p,double h,double d,double Gift);
void Output2(double total,double TaxIncome,double tax,double Net_Income);
void input();
double Check_realnumber(char str_income[]);
int Check_integer(double Num);

//main function
int main(){
	int Choose=menu();
	switch(Choose){
	case 1:input();
	break;
	case 0:exit(0);
	break;
 	}
   }

   
// menu function-Hien thi 2 chuc nang cua chuong trinh va tra ve lua chon cua nguoi nhap.
int menu(){
	char choose[2];
	do{
	printf(" Choose one of the following options:\n");
	printf(" 1.Tax calculator\n");//vao chuong trinh
	printf(" 0.Exit\n");          //Thoat
	printf(" You selection (0 -> 1):");
	scanf("%s",choose);
	fflush(stdin);
	 if(strcmp(choose,"0")!=0&&strcmp(choose,"1")!=0){
		printf("Invalid input, try again.\n");
	 }
	}while(strcmp(choose,"0")!=0&&strcmp(choose,"1")!=0);
	int temp=atoi(choose);
	return temp; 
	}
	
//input function -Cho phep nguoi dung nhap du lieu dau vao
void input(){
	char s1[2];
	char s2[2];
	char s3[2];
	double Num,Income,Gift;
	char str_Gift[50];
	char str_income[50];
	char str_Num[50];
	int number;
	double p=0,h=0,d=0;
	do{
	printf("Income tax Calculator\n======================\n");
    printf("Enter personal information <in thousand VND>\n");
    do{ 
	    fflush(stdin);
    	printf("Income for the current month: ");
    	fgets(str_income,sizeof(str_income),stdin);
     Income=Check_realnumber(str_income);//Check if the input is a real number
     if(Income<0){
     	printf("Invalid input, try again.\n");
	 }
	}while(Income<0);
	do{
 	   printf("Pension contributions<5%%> y/n?");
 	   	scanf("%s",s1);
 	   if(Yes_No(s1)==1){
 	   	p = Income * RATE_PENSION;
		}if(Yes_No(s1)==0){
			printf("You must press 'Y' or 'N' only, try again.\n");
		}
      }while(Yes_No(s1)==0);
      do{
      	printf("Health insurance<1%%> y/n?");
      	scanf("%s",s2);
      	if(Yes_No(s2)==1){
 	   	h = Income * RATE_HEALTH;
		}if(Yes_No(s1)==0){
			printf("You must press 'Y' or 'N' only, try again.\n");
		}
	  }while(Yes_No(s2)==0);
	  do{
	  fflush(stdin);
	  printf("Number of Dependants < 18 years old: ");
	  fgets(str_Num,sizeof(str_Num),stdin);
	  Num=Check_realnumber(str_Num);  
	  
	  /*After checking the input is a real
	   number continue to check if it is an integer*/
	
	  number=Check_integer(Num);
	  d=number*DEPENDANT;
	  if(number<0){
	  	printf("Invalid input, try again.\n");
	  }
      }while(number<0);
      do{
      fflush(stdin);
	  printf("Gift of charity: ");
	  fgets(str_Gift,sizeof(str_Gift),stdin);
	  Gift=Check_realnumber(str_Gift);//Check if the input is a real number
	  if(Gift<0||Gift>Income){
	  	printf("Invalid input, try again.\n");
	  }
      }while(Gift<0||Gift>Income);
      double total=Total(p,h,d,Gift);
      double TaxIncome=Income-total; // so tien phai chiu thue
      if(TaxIncome<0){
      	TaxIncome=0;
	  }
      double tax=Tax(TaxIncome);
      double Net_Income=Income-tax;
      Output1(Income,p,h,d,Gift);
      Output2(total,TaxIncome,tax,Net_Income);
      printf("\nAnother run <y/n>?");
      	scanf("%s",s3);
		if(Yes_No(s3)==0){
			printf("You must press 'Y' or 'N' only, try again.\n");
	  }if(Yes_No(s3)==2){
	  	getch();
	  }else system("cls");
      
	}while(Yes_No(s3)==1);
}


//Yes_No Fucntion-    So sanh du lieu nhap vao la y hay n, tra ve ket qua.
int Yes_No(char s[2]){
		int m,n;
		char a[2]="y";
	    char b[2]="n";
 	n=strcmp(s,a);
	m=strcmp(s,b);
 	if(n!=0&&m!=0)return 0;
	else if(n==0) return 1;
	else return 2;
}

// Total function - Cong tong so tien khau tru cua nguoi nhap 
double Total(double p,double h,double d,double Gift ){
	double Total1=p+h+d+Gift+YOURSELF;
	return Total1;
}
 
//  Tax function   -Tinh thue cua nguoi nhap
double Tax(double TaxIncome ){
	int i,j;
	double T=0;         
//-*TH1:thu nhap  5 tr tro xuong
//*TH2:Thu nhap tren 5tr den 80 tr
//*TH3:Thu nhap tren 80 tr.

	double x[6]={5000,10000,18000,32000,52000,80000};
	double y[6]={250,500,1200,2800,5000,8400};     //7000  tax=250+(7000-5000)*10%  
	double z[7]={0.05,0.1,0.15,0.2,0.25,0.3,0.35};//60000  tax=250+500+1200+2800+5000+(60000-52000)*0.3
	for(i=0;i<5;i++){
		if(x[i]<TaxIncome&&TaxIncome<=x[i+1]){
			for(j=0;j<=i;j++){
			  T+=y[j];
			}T=T+(TaxIncome-x[i])*z[i+1];
		}if(TaxIncome<=x[0]){
			T=TaxIncome*z[0];
			break;
		}if(TaxIncome>x[5]){
			T=(y[0]+y[1]+y[2]+y[3]+y[4]+y[5])+(TaxIncome-x[5])*z[6];
			break;
		}
		} return T;
}

//   OutPut1 function -Hien thi ra du lieu nhap vao .
void Output1(double Income,double p,double h,double d,double Gift){
	printf("Gross Income:\t\t%.1lf\n",Income);
	printf("Deduction\n");
	printf("  Personal allowance:\t%.1lf\n",YOURSELF);
	printf("  Pension contributions:%.1lf\n",p);
	printf("  Health insurance:\t%.1lf\n",h);
	printf("  Dependant:\t\t%.1lf\n",d);
	printf("  Charity:\t\t%.1lf\n",Gift);
	printf("----------------------------\n");
	}

//  Output 2 function -Hien thi ket qua tinh toan cua chuong trinh.
void Output2(double total,double TaxIncome,double tax,double Net_Income){
	printf("Total:\t\t\t%.1lf\n",total);
	printf("Taxable Income:\t\t%.1lf\n",TaxIncome);
	printf("Tax:\t\t\t%.1lf\n",tax);
	printf("Net Income:\t\t%.1lf\n",Net_Income);
} 

// Check_realnumber function  de check xem chuoi minh nhap vao co phai so thuc hay k?
double Check_realnumber(char str[])
{
   char *endPt;       
   double x;      
   str[strlen(str)-1] = '\0' ; //NULL.
   x = strtod(str, &endPt);
   if (*endPt != '\0' || strlen(str)==0 ) return -1;
   else return x; 
}

// Check_integer position function  xem so thuc do co phai so nguyen hay khong?
int Check_integer(double Num){
    if (ceil(Num) != floor(Num)){    //ceil:tra ve gia tri nguyen nho nhat lon hon hoac bang x(2.6->3)
    	return -1;                   //floor:tra ve gia tri nguyen lon nhat nho hon hoac bang x(2.6->2)
	}
    else return Num;
}

