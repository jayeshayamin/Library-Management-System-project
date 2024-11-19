#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define username "admin"
#define password "fast123"

struct book{
int registration;
char title[50];
char author[20];
int status; //0 for borrowed and 1 for available
};

int login();
void addbook();
void deletebook();
void borrow();
void returnbook();
void search();
void view();

int login()
{
	char un[20],pw[10];
	printf("Enter username: ");
	scanf("%s",&un);
	printf("Enter password: ");
	scanf("%s",pw);
	
	if((strcmp(username,un)==0) && (strcmp(password,pw)==0))
	{
		printf("Welcome, Admin.\n");
		return 1;
	}
	else{
		printf("Incorrect username or password.\n");
		return 0;
	}

}

void addbook()
{
	struct book book;
	FILE *file=fopen("books.txt","a");
	if (file==NULL)
	{
		printf("Error while opening file.\n");
		return;
	}
	
	printf("Enter registration number: ");
	scanf("%d", &book.registration);
	getchar();
	
	printf("Enter book title: ");
	fgets(book.title,sizeof(book.title),stdin);
	book.title[strcspn(book.title, "\n")] = '\0';
	
	printf("Enter book author: ");
	fgets(book.author,sizeof(book.author),stdin);
	book.author[strcspn(book.author, "\n")] = '\0';
	
	book.status=1;
	
	fprintf(file,"%d|%s|%s|%d\n",book.registration,book.title,book.author,book.status);
	fclose(file);
	printf("Book added sucessfully!\n");
}

void deletebook()
{
	int reg,found=0;
	struct book book;
	FILE *file=fopen("books.txt","r");
	if (file==NULL)
	{
		printf("Error while opening file.\n");
		return;
	}
	FILE *tempfile=fopen("temp.txt","w");
	if (tempfile==NULL)
	{
		printf("Error while opening file.\n");
		return;
	}
	
	printf("Enter registration number of the book to be deleted: ");
	scanf("%d",&reg);
	getchar();
	
	while(fscanf(file, "%d|%49[^|]|%19[^|]|%d\n", &book.registration,book.title,book.author,&book.status)!=EOF)
	{
		if(book.registration==reg)
		{
			found=1;
		}
		else{
			fprintf(tempfile,"%d|%s|%s|%d\n",book.registration,book.title,book.author,book.status);
		}
	}
	
	fclose(tempfile);
	fclose(file);
	
	if (found==1)
	{
	remove("books.txt");
	rename("temp.txt","books.txt");
	printf("Book removed sucessfully!\n");}
	else
	{
		remove("temp.txt");
		printf("0 results matching provided registration number.\n");
	}
}

void borrow()
{
	FILE *file=fopen("books.txt","r");
	FILE *tempfile=fopen("temp.txt","w");
	struct book book;
	int reg,found=0;
	if(file==NULL || tempfile==NULL)
	{
		printf("Error opening file.");
		return;
	}
	printf("Enter registration number: ");
	scanf("%d", &reg);
	getchar();
	
	while(fscanf(file,"%d|%49[^|]|%19[^|]|%d\n",&book.registration,book.title,book.author,&book.status)!=EOF)
	{
		if(book.registration==reg)
		{
			found=1;
			if(book.status==1)
			{
				book.status=0;
				printf("Book borrowed successfully!\nEnjoy!\n");
			
			}
			else
			{
			
			found=1;
			printf("Book is not available for borrowing.\n");
		}}
		fprintf(tempfile,"%d|%s|%s|%d\n",book.registration,book.title,book.author,book.status);
		
	}
	fclose(file);
	fclose(tempfile);
	if (!found)
	{
	printf("0 results matching registration number.\n");
	}
	if (found)
	{
	remove("books.txt");
	rename("temp.txt","books.txt");}
	else
	{
		remove("temp.txt");
	}
	
}

void returnbook()
{
	FILE *file=fopen("books.txt","r");
	FILE *tempfile=fopen("temp.txt","w");
	struct book book;
	int reg,found=0;
	if(file==NULL || tempfile==NULL)
	{
		printf("Error opening file.");
		return;
	}
	printf("Enter registration number: ");
	scanf("%d", &reg);
	getchar();
	
	while(fscanf(file,"%d|%49[^|]|%19[^|]|%d\n",&book.registration,book.title,book.author,&book.status)!=EOF)
	{
		if(book.registration==reg)
		{
			found=1;
			if(!book.status)
			{
				book.status=1;
				printf("Book returned successfully!\n");
			}
			else
			printf("Book has already been returned.\n");
		}
		fprintf(tempfile,"%d|%s|%s|%d\n",book.registration,book.title,book.author,book.status);
	}
	if (!found)
	{
		printf("0 results matching registration number.\n");
	}
	fclose(file);
	fclose(tempfile);
	if (found)
	{
	remove("books.txt");
	rename("temp.txt","books.txt");}
	else
	{
		remove("temp.txt");
	}

}

void search()
{
	int found=0;
	FILE *file=fopen("books.txt","r");
	struct book book;
	if(file==NULL)
	{
		printf("Error opening file.\n");
		return;
	}
	int search,reg,av;
	char t[50],auth[20];
	printf("Search for book by:\n1. Registration number\n2. Title\n3. Author\n4. Availibility\n:");
	scanf("%d", &search);
	getchar();
	if (search>=1 && search<=4)
	{
	
	switch(search)
	{
		case 1:
			printf("Enter Book Registration Number: ");
			scanf("%d",&reg);
			getchar();
			fseek(file, 0, SEEK_SET);
			found=0;
			while(fscanf(file, "%d|%49[^|]|%19[^|]|%d\n", &book.registration,book.title,book.author,&book.status)!=EOF)
			{
				if(book.registration==reg)
				{
				found=1;
				printf("%-10d|%-49s|%-19s|%d\n",book.registration,book.title,book.author,book.status);
				}
			}
			break;
		case 2:
			printf("Enter Book Title: ");
			fgets(t,sizeof(t),stdin);
			t[strcspn(t,"\n")]='\0';
			fseek(file, 0, SEEK_SET);
			found=0;
			while(fscanf(file, "%d|%49[^|]|%19[^|]|%d\n", &book.registration,book.title,book.author,&book.status)!=EOF)
			{
				if(strcmp(book.title,t)==0)
				{
				found=1;
				printf("%-10d|%-49s|%-19s|%d\n",book.registration,book.title,book.author,book.status);
				}}
			break;
		case 3:
			printf("Enter Author name: ");
			fgets(auth,sizeof(auth),stdin);
			auth[strcspn(auth,"\n")]='\0';
			fseek(file, 0, SEEK_SET);
			found=0;
			while(fscanf(file, "%d|%49[^|]|%19[^|]|%d\n", &book.registration,book.title,book.author,&book.status)!=EOF)
			{
				if(strcmp(book.author,auth)==0)
				{
				found=1;
				printf("%-10d|%-49s|%-19s|%d\n",book.registration,book.title,book.author,book.status);
				}
			}
			break;
		case 4:
			printf("0. Not Available\n1. Available: ");
			scanf("%d",&av);
			getchar();
			fseek(file, 0, SEEK_SET);
			found=0;
			if(av==0 || av==1)
			{
			
			while(fscanf(file, "%d|%49[^|]|%19[^|]|%d\n", &book.registration,book.title,book.author,&book.status)!=EOF)
			{
				if(book.status==av)
				{
				found=1;
				printf("%-10d|%-49s|%-19s|%d\n",book.registration,book.title,book.author,book.status);
				}
			}
			}
			else
			printf("Incorrect choice.\n");
			break;		
	}
	if(!found)
	{
	printf("0 results matching.\n");
	}
	}
	else
	printf("Invalid selection.\n");
	fclose(file);
	return;
}

void view()
{
	FILE *file = fopen("books.txt", "r");
	struct book book;

	if (file == NULL)
	{
		printf("Error opening file.\n");
		return;
	}

	printf("\n%-10s | %-49s | %-19s | %-10s\n", "Reg No", "Title", "Author", "Status");
	printf("--------------------------------------------------------------------------------------------------\n");

	while (fscanf(file, "%d|%49[^|]|%19[^|]|%d\n",&book.registration,book.title,book.author,&book.status)!=EOF)
	{
		printf("%-10d | %-49s | %-19s | %-10d\n",book.registration,book.title,book.author,book.status);
	}

	fclose(file);
}


int main()
{
    int choice;
    printf("Welcome to Library Management System!\nPlease choose operation:\n1. Add Book\n2. Delete Book\n3. Borrow Book\n4. Return Book\n5. Search for Book\n6. View Book List\n7. Exit\n");
    while (1)
    {
    printf("Enter operation: ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    	if (login())
    	{
    		if (choice==1)
    		{
    			addbook();
			}
			else if (choice==2)
			{
				deletebook();
			}
			else if (choice==3)
			{
				borrow();
			}
			else if (choice==4)
			{
				returnbook();
			}
		}
		else{
			printf("You donot have admin access.");
		}
    break;
    case 5:
    search();
    break;
    case 6:
    view();
    break;
    case 7:
    printf("Thankyou for using The Library Management System.\nGoodbye!\nExiting..");
    return 0;
    default:
    printf("Invalid Operation.\n");
    break;
    }}
    return 0;
}
