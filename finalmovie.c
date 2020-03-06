#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
typedef struct Seat
{
	char person[20];
	char seat_name;
	int seat_num;
	float seat_cost;
	struct Seat*link;
	char status;
}Seat;

typedef struct List{
	Seat*head;
	int num_of_members;
}List;

List*init(void)
{
	List*temp = (List*)malloc(sizeof(List));
	temp->head = NULL;
	temp->num_of_members = 0;
	return temp;
}
List*families[90];
int index_curr = -1;

Seat matrix[9][10];// The following functions are used .
int checkAlreadyBookSeat(char*des);
void createMatrix(void);
void bookSeats(void);
void showSeats(void);
void display(List*sll);
void insert(List*sll,Seat*b);
void showFamilies(void);
float CalculateBill(List*sll);
void cinemaRevenue(void);
void cancelBooking(void);
void delete(List*sll,char*b);

int main()
{
	/*printf("\n\n\t\t\tWelcome to Book Our Show.\n");
	printf("\t\t\t\t1.Show Seats\n");
	printf("\t\t\t\t2.BookSeats\n");
	printf("\t\t\t\t3.ShowFamilies ,Bills and Vacancy\n");
	printf("\t\t\t\t4.Cinema Revenue (Only Admin !)\n");
	printf("\t\t\t\t5.Cancel Booking\n");
	printf("\t\t\t\t6.Exit\n");*/
	createMatrix();
	int try = 0;
	while(1)
	{	
		printf("\n\n\t\t\tWelcome to Book Our Show.\n");
		printf("\t\t\t\t1.Show Seats\n");
		printf("\t\t\t\t2.BookSeats\n");
		printf("\t\t\t\t3.ShowFamilies ,Bills and Vacancy\n");
		printf("\t\t\t\t4.Cinema Revenue (Only Admin !)\n");
		printf("\t\t\t\t5.Cancel Booking\n");
		printf("\t\t\t\t6.Exit\n");
		int choice;
		printf("\n\t\tEnter your option:?_");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:{
				showSeats();
				break;
			}
			case 2:{
				bookSeats();
				break;
			}
			case 3:{
				showFamilies();
				break;
			}
			case 4:{
				char b[15];
				char a[15]="kingkhan";
				printf("\n\tPlease Enter the admin PASSWORD :");
				scanf("%s",&b);
				printf("\nVerifying...");
			    //int try = 0;
				if(strcmp(a,b)==0)
				{
					sleep(5);
					printf("\t\t\t\t*****Access Granted******\n");
					cinemaRevenue();
				}
				else
				{
					sleep(1);
					printf("\t\t\t\t*****Access Denied*****\n");
					try++;
					if(try==3){
						printf("Risky user\n");
						sleep(2);
						printf("Closing the Program..");
						exit(1);
					}
				}
				break;
				}
			case 5:
			{
				cancelBooking();
				break;
			}
			case 6:
			{
				exit(1);
			}
			default:{
				printf("Invalid Input\n");
			}
		}
	}
}


float CalculateBill(List*sll)
{
	float bill = 0;
	if(sll->head==NULL)
		printf("\nThe bill is Zero\n");
	else
	{
		Seat*temp = sll->head;
		while(temp!=NULL)
		{
			bill+=temp->seat_cost;
			temp = temp->link;
		}
		printf("\nThe bill of Mr:%s =	Rs %.2f \n",sll->head->person,bill);
	}
	return bill;
}

void cinemaRevenue(void)
{
	float revenue = 0;
	for(int i=0;i<=index_curr;i++)
	{
		revenue+=CalculateBill(families[i]);
	}
	printf("The total revenue collected till now = %.2f\n",revenue);
}


void showFamilies(void)
{
	int totalOccupied =0;
	
	for(int i=0;i<=index_curr;i++)
	{
		totalOccupied += families[i]->num_of_members;
	}
	printf("\n\n\n\nAt the moment the  cinema hall has %d seats vacant\n\n",(90-totalOccupied));
	printf("The below is families with their member count:\n");
	for(int i=0;i<=index_curr;i++)
	{
		display(families[i]);
		printf("\n");
	}
}

void createMatrix(void){
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(i==0||i==1||i==2){
				matrix[i][j].seat_name = 'S';
				matrix[i][j].seat_num = j+10*i;
				matrix[i][j].seat_cost = 200;
				matrix[i][j].link = NULL;
				matrix[i][j].status = 'V';
			}
			else if(i==3||i==4||i==5){
				matrix[i][j].seat_name = 'G';
				matrix[i][j].seat_num = j+10*(i-3);
				matrix[i][j].seat_cost = 300;
				matrix[i][j].link = NULL;
				matrix[i][j].status = 'V';
			}
			else if(i==6||i==7||i==8){
				matrix[i][j].seat_name = 'P';
				matrix[i][j].seat_num = j+10*(i-6);
				matrix[i][j].seat_cost = 450;
				matrix[i][j].link = NULL;
				matrix[i][j].status = 'V';
			}
		}
	}
}

void showSeats(void){
	printf("\n\t\t\tCurrent Seat Configuration\n\n");
	printf("\t\t\t\tSCREEN\n\n\n");
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(matrix[i][j].seat_num/10==0){
			printf("|%c0%d,%c| ",matrix[i][j].seat_name,matrix[i][j].seat_num,matrix[i][j].status);
			}
			else{
			printf("|%c%d,%c| ",matrix[i][j].seat_name,matrix[i][j].seat_num,matrix[i][j].status);
			}
		}
		printf("\n");
		if(i==2||i==5||i==8){
			printf("\n");
			if(i==2)
				printf("\t\t\t\tSilver Cost Rs. 200 per ticket [G.S.T included]\n");
			else if(i==5)
				printf("\t\t\t\tGold Cost Rs. 300 per ticket [G.S.T included]\n");
			else if(i==8)
				printf("\t\t\t\tPlatinum Cost Rs. 450 per ticket [G.S.T included]\n");
			printf("\n\n");

		}

	}
}
int checkAlreadyBookSeat(char*des){
	if(des[0]=='S')
	{
		if(matrix[atoi(des+1)/10][atoi(des+1)%10].status=='V')
			return 0;
		else 
			return 1;
	}
	else if(des[0]=='G')
	{
		if(matrix[(atoi(des+1)/10)+3][atoi(des+1)%10].status=='V')
			return 0;
		else 
			return 1;
	}
	else if(des[0]=='P')
	{
		if(matrix[(atoi(des+1)/10)+6][atoi(des+1)%10].status=='V')
			return 0;
		else 
			return 1;
	}
}


void insert(List*sll,Seat*b)
{
	if(sll->head ==NULL){
		sll->head = b;
		b->link = NULL;
		sll->num_of_members++;
	}
	else
	{
		Seat*temp = sll->head;
		Seat*prev = NULL;
		while(temp!=NULL)
		{
			prev = temp;
			temp = temp->link;
		}
		prev->link = b;
		b->link = NULL;
		sll->num_of_members++;
	}
}
void display(List*sll)
{
	printf("members of family = %d\t",sll->num_of_members);
	if(sll->head==NULL)
		printf("The family has not bought any ticket!");
	else 
	{
		printf("%s\t",sll->head->person);
		Seat*temp = sll->head;
		while(temp!=NULL)
		{
			if(temp->seat_num/10==0){
			printf("|%c0%d,%c|->",temp->seat_name,temp->seat_num,temp->status);
			temp = temp->link;
			}
			else{
			printf("|%c%d,%c|->",temp->seat_name,temp->seat_num,temp->status);
			temp = temp->link;
			}

		}
		printf("NULL");
	}

}
void bookSeats()
{
			printf("\nWelcome to the seat booking \n");
			List*sll = init();

			int number;
			printf("\t\tEnter the number of members :?");
			scanf("%d",&number);
			printf("\n");
			showSeats();
			printf("Please choose the seats :-\n");
			while(number)
			{
				char des[5];
				scanf("%s",&des);
				int out = checkAlreadyBookSeat(des);
				if(out==1)
				{
					printf("Opps!!! That seat was already booked\n");
				}
				else
				{

					if(des[0]=='S')
					{
						matrix[(atoi(des+1)/10)][atoi(des+1)%10].status='B';
						printf("Enter the name of the Customer:");
						scanf("%s",matrix[(atoi(des+1)/10)][atoi(des+1)%10].person);
						insert(sll,&matrix[(atoi(des+1)/10)][atoi(des+1)%10]);
						number--;
					}
					else if(des[0]=='G')
					{
					    matrix[(atoi(des+1)/10)+3][atoi(des+1)%10].status='B';
					    printf("Enter the name of the Customer:");
					    scanf("%s",matrix[(atoi(des+1)/10)+3][atoi(des+1)%10].person);
					    insert(sll,&matrix[(atoi(des+1)/10)+3][atoi(des+1)%10]);
					    number--;
					}
					else if(des[0]=='P')
					{				
						matrix[(atoi(des+1)/10)+6][atoi(des+1)%10].status='B';
						printf("Enter the name of the Customer:");
						scanf("%s",matrix[(atoi(des+1)/10)+6][atoi(des+1)%10].person);
						insert(sll,&matrix[(atoi(des+1)/10)+6][atoi(des+1)%10]);
						number--;
					}
				}

			}
			
			showSeats();
			display(sll);
			float x = CalculateBill(sll);
			families[++index_curr] = sll;
}
void delete(List*sll,char*b)
{
	if(sll->head==NULL){
		printf("\nThe family does not exit ! Can\'t cancel\n");
	}	
	Seat*temp = sll->head;
	int flag = -1;
	while(temp!=NULL)
	{
		if(strcmp(temp->person,b)==0)
			flag++;
		temp = temp->link; 
	}
	if(flag==-1)
	{
		printf("No such ticket on this name.\n");
		return;
	}
	else if(strcmp(sll->head->person,b)==0) 
	{
		Seat*temp = sll->head;
		sll->head = sll->head->link;
		temp->status = 'V';
		free(temp);
		sll->num_of_members--;
	}
	else 
	{
		Seat*temp = sll->head;
		Seat*prev = NULL;
		Seat*cprev = NULL;
		while(strcmp(temp->person,b)!=0&&temp!=NULL)
		{
			cprev = prev;
			prev = temp;
			temp = temp->link;
		}
		if(temp==NULL)//last element match 
		{
			printf("ticket Cancelled\n");
			if(strcmp(prev->person,b)==0){
				prev->status = 'V';
				free(prev);
				cprev->link = NULL;
				sll->num_of_members--;
			}
			else 
				printf("no such member !\n");
		}
		else
		{	printf("Ticket Cancelled \n");
			if(strcmp(temp->person,b)==0){
			temp->status = 'V';
			prev->link = temp->link;
			free(temp);
			sll->num_of_members--;
			}
			else
				return;
		}
	}
}
void cancelBooking(void)
{
	char a[20];
	printf("\nEnter the name of client family:");
	scanf("%s",&a);
	for(int i=0;i<=index_curr;i++)
	{
		if(strcmp(families[i]->head->person,a)==0)
		{
			char b[20];
			printf("\nEnter whose ticket to delete:");
			scanf("%s",&b);
			delete(families[i],b);
			printf("Updated\n");
			int x = CalculateBill(families[i]);

		}
	}
}