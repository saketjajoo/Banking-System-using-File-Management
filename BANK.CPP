#include <iostream.h>
#include <fstream.h>
#include <process.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iomanip.h>
#include <graphics.h>


void openingscreen()
{
	clrscr();
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\bgi");
	cleardevice();
	int p=getmaxx();
	int t=478;
	int x=0;
	for(int m=p;m>0;m--)
	{
		setcolor(m);
		line(x,0,x,t);  x+=5;
	}
	delay(3);
	for(int i=p;i>0;i-=2)
	{
		bar(i-2,0,i,t);
		setbkcolor(BLACK);
		delay(20);
	}
	closegraph();
}



typedef char option[15];
const int ROW = 10,COL = 10;

int scan;
int ascii;

option a[]= {"NewAccount","ListofAccounts","IndAccount","DailyTrans","MonthlyReport","EditAccount","Exit"};
option b[] = {"Modify Account","Closeaccount","Quit"};

class main_menu
{
	int i,done;
	public:
		void normalvideo(int x,int y,char *str);
		void reversevideo(int x,int y,char *str);
		void box(int x1,int y1,int x2,int y2);
		char menu();
		void control_menu();
		char e_menu();
		void edit_menu();
		void help();
};

class shape
{
	public:
		void line_hor(int, int, int, char);
		void line_ver(int, int, int, char);
		void box(int, int, int, int, char);
};

class initial
{
	void modify_account(int, char t_name[30], char t_address[30]);	// Function to modify the customer account
	int accno;
	char name[30], address[30];
	float balance;
	public:
	void add_to_file(int, char t_name[30], char t_address[30], float);
	void display_list();
	void delete_account(int);
	void update_balance(int, char t_name[30], char t_address[30], float);
	void modify();
	int last_accno();
	int found_account(int);
	char *return_name(int);
	char *return_address(int);
	float give_balance(int);
	int recordno(int);
	void display(int);
};

class account
{
	void add_to_file(int, int, int, int, char, char t_type[10], float, float, float);
	void delete_account(int);
	int no_of_days(int, int, int, int, int, int);
	float calculate_interest(int, float);
	void display(int);
	void box_for_display(int);
	int accno;
	char type[10];
	int dd, mm, yy;
	char tran;
	float interest, amount, balance;
	public:
	void new_account();
	void close_account();
	void display_account();
	void transaction();
	void clear(int, int);
	void month_report();
};

void main_menu::normalvideo(int x,int y,char *str)
{
   gotoxy(x,y);
   cprintf("%s",str);
}

void main_menu::reversevideo(int x,int y,char *str)
{
	textcolor(5+143);
	textbackground(WHITE);
	gotoxy(x,y);
	cprintf("%s",str);
	textcolor(GREEN);
	textbackground(BLACK);
}

void main_menu::box(int x1,int y1,int x2,int y2)
{
	 for(int col=x1;col<x2;col++)
	 {
		   gotoxy(col,y1);
		   cprintf("%c",196);
		   gotoxy(col,y2);
		   cprintf("%c",196);
	 }

	 for(int row=y1;row<y2;row++)
	 {
		   gotoxy(x1,row);
		   cprintf("%c",179);
		   gotoxy(x2,row);
		   cprintf("%c",179);
	 }
	 gotoxy(x1,y1);
	 cprintf("%c",218);
	 gotoxy(x1,y2);
	 cprintf("%c",192);
	 gotoxy(x2,y1);
	 cprintf("%c",191);
	 gotoxy(x2,y2);
	 cprintf("%c",217);
}

void end()
{
   int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\bgi");
	cleardevice();
       settextstyle(0,HORIZ_DIR,2);
       setcolor(LIGHTRED);
       outtextxy(20,108,"P R E S E N T E D   B Y : ");
       settextstyle(0,HORIZ_DIR,2);
       setcolor(WHITE);
       outtextxy(20,208,"N a m e       : Saket Jajoo");
       delay(3000);
	cleardevice();
	int x=getmaxx();
	int y=getmaxy();
	rectangle(0,0,x,y);
	int t=476;
	for(int j=5;j<640;j+=4)
	{
			setcolor(j);
			line(j,0,j,t);
			delay(30);
	}
	setcolor(WHITE);
	settextstyle(0,HORIZ_DIR,3);
	outtextxy(20,230,"   T H A N K   Y O U  ");
	delay(2000);
       closegraph();
       exit(0);
}

char main_menu::menu()
{
	clrscr();

	textcolor(22);
	box(20, 6, 65, 20);
	box(18, 4, 67, 22);
	textcolor(5+143);
	gotoxy(36, 5);
	textbackground(BLUE);
	cprintf("B A N K I N G");
	textbackground(BLACK);
	textcolor(22);
	for(i = 1; i < 7; i++)
	normalvideo(32, i+10, a[i]);
	reversevideo(32, 10, a[0]);
	i = done = 0;
	_setcursortype(_NOCURSOR);
	do
	{
		int key = getch();
		switch (key)
		{
			case 00:
				key = getch();
				switch (key)
				{
					case 72:
						normalvideo(32, i+10, a[i]);
						i--;
						if (i == -1)
							i = 6;
						reversevideo(32,i+10,a[i]);
						break;
					case 80:
						normalvideo(32, i+10, a[i]);
						i++;
						if (i == 7)
							i = 0;
						reversevideo(32, i+10, a[i]);
						break;
				}
				break;
			case 13:
				done = 1;
		}
	}
	while (!done);
	_setcursortype(_NOCURSOR);
	return(i+49);
}

void main_menu::control_menu()
{

	char choice;
	account a;

	do
	{
		choice = menu();
		clrscr();
		switch (choice)
		{
			case '1':
				_setcursortype(_NORMALCURSOR);
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);

				a.new_account();
				break;
			case '2':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);
				initial ini;
				ini.display_list();
				break;
			case '3':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);

				 _setcursortype(_NORMALCURSOR);
				a.display_account();
				break;
			case '4':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);

				account a;
				_setcursortype(_NORMALCURSOR);
				a.transaction();
				 break;
			case '5':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);

				_setcursortype(_NORMALCURSOR);
				a.month_report();
				break;
			case '6':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);
				gotoxy(10,10);
				edit_menu();
				break;
			case '7' :end();
		   }
	  } while (choice != 6);
}

char main_menu::e_menu()
{
	clrscr();

	textcolor(22);
	box(25,6,60,15);
	box(23,4,62,17);
	textcolor(5+143);

	gotoxy(34,5);
	textbackground(GREEN);
	cprintf("E D I T  -  M E N U");
	textcolor(22);
	textbackground(BLACK);
	for (i = 1;i < 3; i++)
		normalvideo(32, i+10, b[i]);

	reversevideo(32, 10, b[0]);
	i = done = 0;

	_setcursortype(_NOCURSOR);
	do
	{
		int key = getch();
		switch (key)
		{
			case 00:
				key = getch();
				switch (key)
				{
					case 72:
						normalvideo(32, i+10, b[i]);
						i--;
						if (i == -1)
							i = 2;
						reversevideo(32, i+10, b[i]);
						break;
					case 80:
						normalvideo(32, i+10, b[i]);
						i++;
						if (i == 3)
							i=0;
						reversevideo(32, i+10, b[i]);
						break;
				}
				break;
			case 13:
				done = 1;
		}
	}
	while (!done);
	_setcursortype(_NOCURSOR);
	return(i+49);
}

void main_menu::edit_menu()
{
	char choice;
	account a;
	do
	{
		choice = e_menu();
		clrscr();
		switch (choice)
		{
			case '1':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);
				initial ini;
				_setcursortype(_NORMALCURSOR);
				ini.modify();
				break;

			case '2':
				box(3, 1, 75, 24);
				box(5, 2, 73, 23);
				account a;
				_setcursortype(_NORMALCURSOR);
				a.close_account();
				break;
			case '3':
				return;
		}
	} while (choice != 6);
}

void shape::line_hor(int column1, int column2, int row, char c)
{
	for (column1; column1 <= column2; column1++)
	{
		gotoxy(column1, row);
		cout << c;
	}
}

void shape::line_ver(int row1, int row2, int column, char c)
{
	for (row1; row1 <= row2; row1++)
	{
		gotoxy(column, row1);
		cout << c;
	}
}

void shape::box(int column1, int row1, int column2, int row2, char c)
{
	char ch = 218;
	char c1, c2, c3, c4;
	char l1 = 196, l2 = 179;
	if (c == ch)
	{
		c1 = 218;
		c2 = 191;
		c3 = 217;
		c4 = 217;
		l1 = 196;
		l2 = 179;
	}
	else
	{
		c1 = c;
		c2 = c;
		c3 = c;
		c4 = c;
		l1 = c;
		c2 = c;
	}
	gotoxy(column1, row1);
	cout << c1;
	gotoxy(column2, row1);
	cout << c2;
	gotoxy(column1, row2);
	cout << c3;
	gotoxy(column2, row2);
	cout << c4;
	column1++;
	column2--;
	line_hor(column1, column2, row1, l1);
	line_hor(column1, column2, row2, l1);
	column1--;
	column2++;
	row1++;
	row2--;
	line_ver(row1, row2, column1, l2);
	line_ver(row1, row2, column2, l2);
}

void initial::modify()
{
	clrscr();
	int j;
	char t_acc[10];
	int t, t_accno;
	gotoxy(17, 1);
	cout << "<0>=Exit";
	gotoxy(5,5);
	cout << "Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	if (!found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found";
		getch();
		return;
	}
	gotoxy(71, 1);
	cout << "<0>=Exit";
	textbackground(WHITE);
	gotoxy(3, 3);
	for (j = 1; j<= 76; j++)
		cprintf(" ");
	textbackground(BLACK);
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(30, 3);
	cprintf("Modify Account Screen");
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(4, 2);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	char ch;
	display(t_accno);
	account a;
	do
	{
		a.clear(5, 13);
		gotoxy(5, 13);
		cout << "Modify this account <y/n>: ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	int modified = 0, valid;
	char t_name[30], t_address[30];
	gotoxy(5, 15);
	cout << "Name : ";
	gotoxy(5, 16);
	cout << "Address : ";

	do
	{
		a.clear(15, 15);
		a.clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Name or Press Enter for No Change";
		valid = 1;
		gotoxy(15, 15);
		gets(t_name);
		strupr(t_name);
		if (t_name[0] == '0')
			return;
		if (strlen(t_name) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Name should not greater than 25");
			getch();
		}
	} while (!valid);

	do
	{
		a.clear(15, 16);
		a.clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Address or press enter for no Change";
		valid = 1;
		gotoxy(15, 16);
		gets(t_address);
		strupr(t_address);
		if (t_address[0] == '0')
			return;
		if (strlen(t_address) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Address should not greater than 25");
			getch();
		}
	}while (!valid);

	if (strlen(t_address) > 0)
		modified = 1;
	if (!modified)
		return;
	a.clear(5,23);

	do
	{
		a.clear(5, 23);
		gotoxy(5, 18);
		cout << "Do you want to save Changes <Y/N>: ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');

	if (ch == 'N')
		return;
	modify_account(t_accno, t_name, t_address);
	gotoxy(5, 21);
	cout << "\7Record modified";
	gotoxy(5, 23);
	cout << "Press any key to continue...";
	getch();
}

void initial::display(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	while (file.read((char *)this, sizeof(initial)))
	{
		if (t_accno == accno)
		{
			gotoxy(8, 5);
			cout << "Account no. " << accno;
			gotoxy(10, 8);
			cout << "Name : ";
			puts(name);
			gotoxy(10, 9);
			cout << "Address : ";
			puts(address);
			gotoxy(10, 10);
			cout << "Balance : " << setw(15)
						<< setprecision(2)
						<< setiosflags(ios::left)
						<< setiosflags(ios::showpoint)
						<< setiosflags(ios::fixed)
						<< balance;
			break;
		}
	}
	file.close();
}

void initial::modify_account(int t_accno, char t_name[30], char t_address[30])
{
	int recno;
	recno = recordno(t_accno);
	fstream file;
	file.open("INITIAL.dat", ios::out|ios::ate);
	strcpy(name, t_name);
	strcpy(address, t_address);
	int location;
	location = (recno-1) * sizeof(initial);
	file.seekp(location);
	file.write((char *)this, sizeof(initial));
	file.close();
	return;
}

int initial::last_accno()
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	int count = 0;
	while (file.read((char *)this, sizeof(initial)))
		count = accno;
	file.close();
	return count;
}

void initial::add_to_file(int t_accno, char t_name[30], char t_address[30], float t_balance)
{
	accno = t_accno;
	strcpy(name, t_name);
	strcpy(address, t_address);
	balance = t_balance;
	fstream file;
	file.open("INITIAL.dat", ios::out|ios::app);
	file.write((char *)this, sizeof(initial));
	file.close();
}

void initial::delete_account(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	fstream temp;
	temp.open("TEMP.dat", ios::out);
	file.seekg(0,ios::beg);
	while (!file.eof())
	{
		file.read((char *)this, sizeof(initial));
		if (file.eof())
			break;
		if (accno != t_accno)
			temp.write((char *)this, sizeof(initial));
	}
	file.close();
	temp.close();
	file.open("INITIAL.dat", ios::out);
	temp.open("TEMP.dat", ios::in);
	temp.seekg(0, ios::beg);
	while (!temp.eof())
	{
		temp.read((char *)this, sizeof(initial));
		if (temp.eof())
			break;
		if (accno != t_accno)
			file.write((char *)this, sizeof(initial));
	}
	file.close();
	temp.close();
}

void account::add_to_file(int t_accno, int d1, int m1, int y1, char t_tran, char t_type[10], float t_interest, float t_amount, float t_balance)
{
	fstream file;
	file.open("BANKING.dat", ios::app);
	accno = t_accno;
	getch();
	dd = d1;
	mm = m1;
	yy = y1;
	tran = t_tran;
	strcpy(type, t_type);
	interest = t_interest;
	amount = t_amount;
	balance = t_balance;
	file.write((char *)this, sizeof(account));
	file.close();
}

void account::delete_account(int t_accno)
{
	fstream file;
	file.open("BANKING.dat", ios::in);
	fstream temp;
	temp.open("TEMP.dat", ios::out);
	file.seekg(0, ios::beg);
	while (!file.eof())
	{
		file.read((char *)this, sizeof(account));
		if (file.eof())
			break;
		if (accno != t_accno)
			temp.write((char *)this, sizeof(account));
	}
	file.close();
	temp.close();
	file.open("BANKING.dat", ios::out);
	temp.open("TEMP.dat", ios::in);
	temp.seekg(0, ios::beg);
	while (!temp.eof())
	{
		temp.read((char *)this, sizeof(account));
		if (temp.eof())
			break;
		if (accno != t_accno)
			file.write((char *)this, sizeof(account));
	}
	file.close();
	temp.close();
}

void initial::display_list()
{
	clrscr();
	int flag;
	float t_bal = 0.0;
	fstream file;
	gotoxy(25,2);

	cout << "Accounts List in Bank";
	gotoxy(25, 3);
	cout << "=====================";
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(62, 3);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	gotoxy(1, 4);
	for (int j = 1; j <= 79; j++)
		cout << "=";

	gotoxy(1, 5);
	cout << "Accno#";
	gotoxy(10,5);
	cout << "Name";
	gotoxy(30,5);
	cout << "Address";
	gotoxy(65,5);
	cout << "Balance";
	gotoxy(1, 6);
	for (j = 1; j <= 79; j++)
		cout << "=";
	file.open("INITIAL.dat", ios::in);
	file.seekg(0,ios::beg);
	int row = 7;
	while (file.read((char *)this, sizeof(initial)))
	{
		flag = 0;
		delay(2);
		gotoxy(3, row);
		cout << accno;
		gotoxy(10, row);
		puts(name);
		gotoxy(30, row);
		puts(address);
		gotoxy(65, row);

		cout <<  setw(15)
			<< setprecision(2)
			<< setiosflags(ios::left)
			<< setiosflags(ios::showpoint)
			<< setiosflags(ios::fixed)
			<< balance;
		t_bal = t_bal + balance;
		row++;
		if (row > 23)
		{
			flag = 1;
			row = 6;
			gotoxy(4, 24);
			cout << "Press any key to continue.... ";
			getch();
			clrscr();
		}
	}
	gotoxy(1, row);
	for (j = 1; j <= 79; j++)
		cout << "=";
	row++;
	gotoxy(3, row);
	cout << "Total Balance in Bank is : ";
	gotoxy(65, row);

	cout << setw(15)
		<< setprecision(2)
		<< setiosflags(ios::left)
		<< setiosflags(ios::showpoint)
		<< setiosflags(ios::fixed)
		<< t_bal;
	file.close();
	if (!flag)
	{
		gotoxy(4, 24);
		cout << "Press any key to continue...";
		getch();
	}
}

void account::clear(int col, int row)
{
	for (int j = col; j <= 79; j++)
	{
		gotoxy(j, row);
		cout << " ";
	}
}

int initial::found_account(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	int found = 0;
	while (file.read((char *)this, sizeof(initial)))
	{
		if (accno == t_accno)
		{
			found = 1;
			break;
		}
	}
	file.close();
	return found;
}

char *initial::return_name(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	char t_name[30];
	while (file.read((char *)this, sizeof(initial)))
	{
		if (accno == t_accno)
		{
			strcpy(t_name, name);
			break;
		}
	}
	file.close();
	return t_name;
}

char *initial::return_address(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	char t_address[30];
	while (file.read((char *)this, sizeof(initial)))
	{
		if (accno == t_accno)
		{
			strcpy(t_address, address);
			break;
		}
	}
	file.close();
	return t_address;
}

void account::box_for_display(int t_accno)
{
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(63, 2);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	gotoxy(4, 2);
	cout << "Account No. " << t_accno;
	initial ini;
	char t_name[30];
	strcpy(t_name, ini.return_name(t_accno));
	char t_address[30];
	strcpy(t_address, ini.return_address(t_accno));
	gotoxy(25, 2);
	cout << t_name;
	gotoxy(25, 3);
	cout << t_address;
	gotoxy(4, 5);
	cout << "Global Report of Account";
	textbackground(WHITE);
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(1, 6);
	for (int i = 1; i <=79; i++)
		cout << "=";
	gotoxy(4, 7);
	cprintf("Date       Particular   Deposit      Withdraw                Balance");
	gotoxy(1, 8);
	for (i = 1; i <=79; i++)
		cout << "=";
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
}

void account::display_account()
{
	clrscr();
	char t_acc[10];
	int j;
	int tamt = 0, damt = 0, wamt = 0;
	int t, t_accno;
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(5, 5);
	cout << "Enter account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found";
		getch();
		return;
	}
	box_for_display(t_accno);
	int row = 9, flag;
	fstream file;
	file.open("BANKING.dat", ios::in);
	while (file.read((char *)this, sizeof(account)))
	{
		if (accno == t_accno)
		{
			flag = 0;
			delay(2);
			gotoxy(4, row);
			cout << dd << "-" << mm << "-" << yy;
			gotoxy(16, row);
			puts(type);
			if (tran == 'D')
			{
				damt = damt + amount;
				tamt = tamt + amount;
				gotoxy(30, row);
			}
			else
			{
				wamt = wamt + amount;
				tamt = tamt - amount;
				gotoxy(42, row);
			}

			cout <<  setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< amount;

			gotoxy(66, row);
			cout << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< balance;

			row++;
			if (row > 23)
			{
				flag = 1;
				row = 7;
				gotoxy(4, 24);
				cout << "Press any key to continue";
				getch();
				clrscr();
				box_for_display(t_accno);
			}
		}
	}
	file.close();
	gotoxy(1, row);
	for (j = 1; j <= 79; j++)
		cout << "=";
	row++;
	gotoxy(4, row);
	cout << "Total-->:";
	gotoxy(30, row);
	cout << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< damt;
	gotoxy(42, row);
	cout << setw(15)
			<< setprecision(2)
			<< setiosflags(ios::left)
			<< setiosflags(ios::showpoint)
			<< setiosflags(ios::fixed)
			<< wamt;
	gotoxy(66, row);
	cout << setw(15)
			<< setprecision(2)
			<< setiosflags(ios::left)
			<< setiosflags(ios::showpoint)
			<< setiosflags(ios::fixed)
			<< tamt;
	if (!flag)
	{
		gotoxy(4, 24);
		cout << "Press any key to continue...";
		getch();
	}
}

void account::month_report()
{
	int dd1, mm1, yy1;
	clrscr();
	gotoxy(10, 5);
	cout << "Enter any date of a month ";
	gotoxy(38, 5);
	cin >> dd1;
	gotoxy(40, 5);
	cout << "-";
	gotoxy(41, 5);
	cin >> mm1;
	gotoxy(43, 5);
	cout << "-";
	gotoxy(44, 5);
	cin >> yy1;
	clrscr();
	char t_acc[10];
	int j;
	int tamt = 0, damt = 0, wamt = 0;
	int t, t_accno;
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(5, 5);
	cout << "Enter account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found";
		getch();
		return;
	}
	box_for_display(t_accno);
	gotoxy(4, 5);
	cout << "Statement Month: " << dd1 << "/" << mm1 << "/" << yy1;
	getch();

	int row = 9, flag;
	fstream file;
	file.open("BANKING.dat", ios::in);
	float pre_balance = 0.0;
	while (file.read((char *)this, sizeof(account)))
	{
		if ((accno == t_accno) && ((mm < mm1 && yy <= yy1) || (mm1 < mm && yy < yy1)))
		{
			pre_balance = balance;
		}
	}

	file.close();
	file.open("BANKING.dat", ios::in);
	gotoxy(54, row);

	cout << "B/F ....    " << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< pre_balance;
	row++;
	while (file.read((char *)this, sizeof(account)))
	{
		if ((accno == t_accno) && (mm1 == mm && yy1 <= yy))
		{
			flag = 0;
			delay(2);
			gotoxy(4, row);
			cout << dd << "-" << mm << "-" << yy;
			gotoxy(16, row);
			puts(type);
			if (tran == 'D')
			{
				damt = damt + amount;
				tamt = tamt + amount;
				gotoxy(30, row);
			}
			else
			{
				wamt = wamt + amount;
				tamt = tamt - amount;
				gotoxy(42, row);
			}

			cout <<  setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< amount;

			gotoxy(66, row);
			cout << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< balance;
			row++;
			if (row > 23)
			{
				flag = 1;
				row = 7;
				gotoxy(4, 24);
				cout << "Press any key to continue";
				getch();
				clrscr();
				box_for_display(t_accno);
			}
		}
	}
	file.close();
	gotoxy(1, row);
	for (j = 1; j <= 79; j++)
		cout << "=";
	row++;
	gotoxy(4, row);
	cout << "Total-->:";
	gotoxy(30, row);
	cout << setw(15)
		<< setprecision(2)
		<< setiosflags(ios::left)
		<< setiosflags(ios::showpoint)
		<< setiosflags(ios::fixed)
		<< damt;
	gotoxy(42, row);
	cout << setw(15)
		<< setprecision(2)
		<< setiosflags(ios::left)
		<< setiosflags(ios::showpoint)
		<< setiosflags(ios::fixed)
		<< wamt;
	gotoxy(66, row);
	tamt = tamt + pre_balance;
	cout << setw(15)
		<< setprecision(2)
		<< setiosflags(ios::left)
		<< setiosflags(ios::showpoint)
		<< setiosflags(ios::fixed)
		<< tamt;
	if (!flag)
	{
		gotoxy(4, 24);
		cout << "Press any key to continue...";
		getch();
	}

}

void account::new_account()
{
	char ch;
	int i, valid;
	clrscr();
	initial ini;
	shape s;
	s.box(2, 1, 79, 25, 218);
	s.box(25, 2, 54, 4, 219);
	gotoxy(65, 2);
	cout << "<0>=Exit";
	gotoxy(3,3);
	for (i = 1; i<= 76; i++)
		cprintf(" ");
	textbackground(BLACK);
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(30, 3);
	cprintf("Open New Account");
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	int t_accno;
	t_accno = ini.last_accno();
	t_accno++;
	if (t_accno == 1)
	{
		ini.add_to_file(t_accno, "abc", "xyz", 1.1);
		ini.delete_account(t_accno);
		add_to_file(t_accno, 1, 1, 1997, 'D', "INITIAL", 1.1, 1.1, 1.1);
		delete_account(t_accno);
	}
	char t_name[30], t[10], t_address[30];
	float t_bal = 0.0, t_balance = 0.0;
	gotoxy(5, 6);
	cout << "Date: " << d1 << '/' << m1 << '/' << y1;
	gotoxy(5, 8);
	cout << "Account No # " << t_accno;
	gotoxy(5, 10);
	cout << "Name : ";
	gotoxy(5, 11);
	cout << "Address : ";
	gotoxy(5, 12);
	cout << "Name of verifying Person : ";
	gotoxy(5, 14);
	cout << "Initial Deposit : ";

	do
	{
		clear(15, 10);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Name of the Person";
		valid = 1;
		gotoxy(15, 10);
		gets(t_name);
		strupr(t_name);
		if (t_name[0] == '0')
			return;
		if (strlen(t_name) == 0 || strlen(t_name) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Name should not greater than 25");
			getch();
		}
	}while (!valid);
	do
	{
		clear(25, 15);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Address of the Person ";
		valid = 1;
		gotoxy(15, 11);
		gets(t_address);
		strupr(t_address);
		if (t_address[0] == '0')
			return;
		if (strlen(t_address) == 0 || strlen(t_address) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Address should not greater than 25");
			getch();
		}
	}while (!valid);
	do
	{
		char vari[30];
		clear(13, 12);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter name of the verifying Person ";
		valid = 1;
		gotoxy(31, 12);
		gets(vari);
		strupr(vari);
		if (vari[0] == '0')
			return;
		if (strlen(vari) == 0 || strlen(vari) > 25)
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("Should not blank or greater than 25");
			getch();
		}
	}while (!valid);
	do
	{
		clear(13, 12);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter initial amount to be deposit ";
		valid = 1;
		gotoxy(23, 14);
		gets(t);
		t_bal = atof(t);
		t_balance = t_bal;
		if (t[0] == '0')
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Should not less than 500");
			getch();
		}
	}while (!valid);
	clear(5, 23);
	do
	{
		clear(5, 17);
		valid = 1;
		gotoxy(5, 17);
		cout << "Do you want to save the record <Y/N>: ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	float t_amount, t_interest;
	t_amount = t_balance;
	t_interest = 0.0;
	char t_tran, t_type[10];
	t_tran = 'D';
	strcpy(t_type, "INITIAL");
	ini.add_to_file(t_accno, t_name, t_address, t_balance);
	add_to_file(t_accno, d1, m1, y1, t_tran, t_type, t_interest, t_amount, t_balance);
}

float initial::give_balance(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	float t_balance;
	while (file.read((char *)this, sizeof(initial)))
	{
		if (accno == t_accno)
		{
			t_balance = balance;
			break;
		}
	}
	file.close();
	return t_balance;
}

int initial::recordno(int t_accno)
{
	fstream file;
	file.open("INITIAL.dat", ios::in);
	file.seekg(0, ios::beg);
	int count = 0;
	while (file.read((char *)this, sizeof(initial)))
	{
		count++;
		if (t_accno == accno)
			break;
	}
	file.close();
	return count;
}

void initial::update_balance(int t_accno, char t_name[30], char t_address[30], float t_balance)
{
	int recno;
	recno = recordno(t_accno);
	fstream file;
	file.open("INITIAL.dat", ios::out|ios::ate);
	strcpy(name, t_name);
	strcpy(address, t_address);
	balance = t_balance;
	int location;
	location = (recno-1) * sizeof(initial);
	file.seekp(location);
	file.write((char *)this, sizeof(initial));
	file.close();
}

int account::no_of_days(int d1, int m1, int y1, int d2, int m2, int y2)
{
	static int month[] = {31, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
	int days = 0;
	while (d1 != d2 || m1 != m2 || y1 != y2)
	{
		days++;
		d1++;
		if (d1 > month[m1-1])
		{
			d1 = 1;
			m1++;
		}
		if (m1 > m2)
		{
			m1 = 1;
			y1++;
		}
	}
	return days;
}

float account::calculate_interest(int t_accno, float t_balance)
{
	fstream file;
	file.open("BANKING.dat", ios::in);
	file.seekg(0, ios::beg);
	int d1, m1, y1, days;
	while (file.read((char *)this, sizeof(account)))
	{
		if (accno == t_accno)
		{
			d1 = dd;
			m1 = mm;
			y1 = yy;
			break;
		}
	}
	int d2, m2, y2;
	struct date d;
	getdate(&d);
	d2 = d.da_day;
	m2 = d.da_mon;
	y2 = d.da_year;
	float t_interest = 0.0;
	if ((y2 < y1) || (y2 == y1 && m2 < m1) || (y2 == y1 && m2 == m1) && (d2 < d1))
		return t_interest;
	days = no_of_days(d1, m1, y1, d2, m2, y2);
	int months = 0;
	if (days > 30)
	{
		months = days / 30;
		t_interest = ((t_balance*2)/100 * months);
	}
	file.close();
	return t_interest;
}

void account::transaction()
{
	clrscr();
	char t_acc[10];
	int t, t_accno, valid;
	gotoxy(71,1);
	cout << "<0>=Exit";
	gotoxy(5, 5);
	cout << "Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found";
		getch();
		return;
	}
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(3, 3);
	for (int i = 1; i <= 76; i++)
		cprintf(" ");
	textbackground(BLACK);
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(29, 3);
	cprintf ("Transaction in Account");
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(5, 6);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	gotoxy(5, 8);
	cout << "Account no. " << t_accno;
	char t_name[30];
	char t_address[30];
	float t_balance;
	strcpy(t_name, ini.return_name(t_accno));
	strcpy(t_address, ini.return_address(t_accno));
	t_balance = ini.give_balance(t_accno);
	gotoxy(27, 11);
	cout << "Name : " << t_name;
	gotoxy(27, 12);
	cout << "Address : " << t_address;

	gotoxy(5, 15);
	cout << "Last balance Rs. " << setw(15)
				<< setprecision(2)
				<< setiosflags(ios::left)
				<< setiosflags(ios::showpoint)
				<< setiosflags(ios::fixed)
				<< t_balance;

	char t_tran, t_type[10], tm[10];
	float t_amount, t_amt;

	do
	{
		clear(5, 10);
		valid = 1;
		gotoxy(5, 10);
		cout << "Deposit or Withdraw (D/W) : ";
		t_tran = getch();
		if (t_tran == '0')
			return;
		t_tran = toupper(t_tran);
	}while (t_tran != 'D' && t_tran != 'W');

	do
	{
		clear(5, 19);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Transaction by Cash or Cheque ";
		valid = 1;
		gotoxy(5, 19);
		cout << "Cash/Cheque : ";
		gets(t_type);
		strupr(t_type);
		if (t_type[0] == '0')
			return;
		if (strcmp(t_type, "CASH") && strcmp(t_type, "CHEQUE"))
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Enter correctly");
			getch();
		}
	}while (!valid);

	do
	{
		clear(5, 21);
		clear(5, 23);
		gotoxy(5, 23);
		cout << "Enter Amount for Transaction ";
		valid = 1;
		gotoxy(5, 21);
		cout << "Amount Rs. ";
		gets(tm);
		t_amt = atof(tm);
		t_amount = t_amt;
		if (tm[0] == '0')
			return;
		if ((t_tran == 'W' && t_amount > t_balance) || (t_amount < 1))
		{
			valid = 0;
			gotoxy(5, 23);
			cprintf("\7Invalid Data entered");
			getch();
		}
	}while (!valid);

	char ch;
	clear(5, 23);
	do
	{
		clear(20, 23);
		valid = 1;
		gotoxy(40, 20);
		cout << "Save Transaction <Y/N> : ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	float t_interest;

	t_interest = calculate_interest(t_accno, t_balance);

	if (t_tran == 'D')
		t_balance = t_balance + t_amount + t_interest;
	else
		t_balance = (t_balance - t_amount) + t_interest;
	ini.update_balance(t_accno, t_name, t_address, t_balance);
	add_to_file(t_accno, d1, m1, y1, t_tran, t_type, t_interest, t_amount, t_balance);
}

void account::close_account()
{
	clrscr();
	char t_acc[10];
	int t, t_accno;
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(5, 5);
	cout << "Enter the account no. ";
	gets(t_acc);
	t = atoi(t_acc);
	t_accno = t;
	if (t_accno == 0)
		return;
	clrscr();
	initial ini;
	if (!ini.found_account(t_accno))
	{
		gotoxy(5, 5);
		cout << "\7Account not found ";
		getch();
		return;
	}
	gotoxy(71, 1);
	cout << "<0>=Exit";
	gotoxy(3, 3);
	textbackground(WHITE);
	for (int i = 1; i <= 76; i++)
		cprintf(" ");
	textbackground(BLACK);
	textcolor(BLACK+BLINK);
	textbackground(WHITE);
	gotoxy(30, 3);
	cprintf("Close account screen");
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	int d1, m1, y1;
	struct date d;
	getdate(&d);
	d1 = d.da_day;
	m1 = d.da_mon;
	y1 = d.da_year;
	gotoxy(5, 6);
	cout << "Date: " << d1 << "/" << m1 << "/" << y1;
	char ch;
	ini. display(t_accno);
	do
	{
		clear(5, 15);
		gotoxy(5, 15);
		cout << "Close this account <y/n?? ";
		ch = getche();
		if (ch == '0')
			return;
		ch = toupper(ch);
	}while (ch != 'N' && ch != 'Y');
	if (ch == 'N')
		return;
	ini.delete_account(t_accno);
	delete_account(t_accno);
	gotoxy(5, 20);
	cout << "\7Account Deleted";
	gotoxy(5, 23);
	cout << "Press any key to continue...";
	getch();
}

void welcome1()
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver,&gmode, "\\bgi");
	cleardevice();
	setbkcolor(2);
	settextstyle(0,HORIZ_DIR,2);
	rectangle(25,55,150,80);
	outtextxy(30,60,"W");delay(70);gotoxy(7,5);cout<<" E";delay(70);cout<<" L";delay(70);cout<<" C";delay(70);cout<<" O";delay(70);cout<<" M";delay(70);cout<<" E";delay(70);
	rectangle(115,120,149,146);
	outtextxy(120,125,"T");delay(70);gotoxy(17,9);cout<<" O";
	rectangle(220,185,340,212);
	outtextxy(210,190," B");delay(70);gotoxy(31,13);cout<<" A";delay(70);cout<<" N";delay(70);cout<<" K";delay(70);cout<<" I";delay(70);cout<<" N";delay(70);cout<<" G";
	rectangle(310,250,423,275);
	outtextxy(300,255," S");delay(80);gotoxy(43,17);cout<<" Y";delay(80);cout<<" S";delay(80);cout<<" T";delay(80);cout<<" E";delay(80);cout<<" M";
	ellipse(260,360,0,360,160,20);
	gotoxy(16,23);cout<<"  Press any key to continue.....  ";
	getch();
	closegraph();
}

void loading()
{
	clrscr();
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\bgi");
	setbkcolor(CYAN);
	char lb=177;
	gotoxy(20,13);cout<<lb;delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<" ";delay(70);cout<<" ";delay(70);
	cout<<" L";delay(70);cout<<" O";delay(70);cout<<" A";delay(70);cout<<" D";delay(70);cout<<" I";delay(70);cout<<" N";delay(70);cout<<" G ";
	gotoxy(49,13);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<".";delay(70);cout<<lb;delay(1000);
}



void main()
{
	openingscreen();
	welcome1();
	loading();
	main_menu  m_menu;
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	closegraph();
	m_menu.control_menu();
}