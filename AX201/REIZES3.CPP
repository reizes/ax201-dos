// 1996. 3. 25    9522014081  Nam gi hoon
// Programing  Reoprt
#include <stdio.h>
#include <iostream.h>

int error_flag=0;
char calc_symbol;

int check_range(long ,long,long);

int (*calc[4])(int ,int );

int select()
 {
  int s;
  do{
  printf("\nEnter the number you want");
  printf("\n1.Addition");
  printf("\n2.Subtraction");
  printf("\n3.Multiplication");
  printf("\n4.Division");
  printf("\n5.QUIT");
  printf("\n\n ->");
  cin>>s;
  if (check_range(s,1,5)) break;
  printf("\nInvalid number...please input again..");
  } while(1);
  return s;
 }
int check_range(long data,long low,long high)
 {
  return (((data<low)||(data>high)) ? 0: 1);
 }
int add(int a,int b)
 {
  long ch;
  ch=a+b;
  calc_symbol='+';
  if (check_range(ch,-32768,32767)) return (int)ch;
  printf("\nOverflow error... please input again..");
  error_flag=1;
  return 0;
  }
int sub(int a,int b)
 {
  long ch;
  ch=a-b;
  calc_symbol='-';
  if (check_range(ch,-32768,32767)) return (int)ch;
  printf("\nOverflow error... please input again..");
  error_flag=1;
  return 0;

 }
void input_number(char *s,long *a) { do {
										printf(s); cin>>(*a);
										if (check_range(*a,-32768,32767)) break;
										printf("\nOverflow error...Input again...");
									   }while(1);
								  }
int mul(int a,int b)
 {
  long ch;
  ch=a*b;
  calc_symbol='*';
  if (check_range(ch,-32768,32767)) return (int)ch;
  printf("\nOverflow error... please input again..");
  error_flag=1;
  return 0;
 }
int div(int a,int b)
 {
  long ch;
  ch=a/b;
  calc_symbol='/';
  if (check_range(ch,-32768,32767)) return (int)ch;
  printf("\nOverflow error... please input again..");
  error_flag=1;
  return 0;
 }
void process(int s)
 {
  long a,b;
  int result;
  char ch;
  do{
   do {
	error_flag=0;
	input_number("\nEnter the number A :",&a);
	input_number("\nEnter the number B :",&b);
	result=(*calc[s-1])((int)a,(int)b);
	if (!error_flag) printf("\nThe result of %d %c %d = %d..",(int)a,calc_symbol,(int)b,result);
	}while(error_flag);
	do {
		printf("\n Do you again ? (Y/N)");
		cin>>ch;
	   }while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'));
   }while((ch=='Y')||(ch=='y'));
  }

void init()
 {
  error_flag=0;
  calc[0]=add;
  calc[1]=sub;
  calc[2]=mul;
  calc[3]=div;
 }
void main()
 {
  int s;
  init();
  do {
	  s=select();
	  if (s!=5) process(s);
	 }while(s!=5);
  printf("\n Good bye... ");
 }

