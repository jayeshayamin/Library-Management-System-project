#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>
#define username "admin"
// Stock of books (int)
struct book{
    int registration;
    char title[50];
    char author[20];
    bool status; // 0 for unavailable, 1 for available
    int quantity; // Track the quantity of each book
    int maxquantity;// inorder to make sure stock does not increase its own value
};
struct book book;
//	19 Function Declarations
int login();
void update();
void addbook();
void deletebook();
void borrow();
void returnbook();
void search();
void view();
int getnewregistrationn();
int getvalidoption();
void mainmenu();
void adminmenu();
void usermenu();
void logout();
int readPasswordFromFile();
void savePasswordToFile();
void SetColor();
void ResetColor();
void printColoredText();
void displaySeparator();
// Function to read the password from a file
int readPasswordFromFile(char *password) {
    FILE *file = fopen("password.txt", "r");
    if (file == NULL) {
        printf("Password file not found. Please set a new password.\n");
        return 0; // Indicates password not found
    }
    fgets(password, 20, file);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character
    fclose(file);
    return 1; // Password found successfully
}

// Function to save the password to the file
void savePasswordToFile(const char *password) {
    FILE *file = fopen("password.txt", "w");
    if (file == NULL) {
        printf("Error saving password to file.\n");
        return;
    }
    fprintf(file, "%s\n", password); // Save password with a newline
    fclose(file);
}

int getnewregistrationn(int *reg) {
    FILE *regfile = fopen("reg.txt", "r");
    if(regfile==NULL)
    {
    	*reg=0;//file doesnt exists so starting form 0
	}
	else
	{
		fscanf(regfile, "%d", reg); // Read the last registration number
        fclose(regfile);
	}
	
	(*reg)++;
    regfile = fopen("reg.txt", "w");
    if(regfile==NULL)
    {
    	printf("ERROR: reg.txt cannot be opened.");
    	return 0;
	}
        fprintf(regfile, "%d", *reg);
        fclose(regfile);

    return *reg;
}

// Function to change console text color
void SetColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((bgColor << 4) | textColor));
}

// Function to reset console color to default
void ResetColor() {
    SetColor(7, 0);  // Reset to white text on blaack bg
}

// Function to print colored text
void printColoredText(const char *text, int textColor) {
    SetColor(textColor, 0);  // 0 is for black background
    printf("%s", text);
    ResetColor();
}

// Function to display a separator line
void displaySeparator() {
    printColoredText("------------------------------------------------------------------------------------------------------------------------------\n", 8);  // Gray color
}

// Function to ensure a valid integer input within a range
int getvalidoption(int min, int max) {
    int option;
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear the input buffer
        } else if (option < min || option > max) {
            printf("Choice out of range. Please select between %d and %d.\n", min, max);
        } else {
            return option;
        }
    }
}

// Admin menu function
void adminmenu() {
    while (1) {
        printColoredText("\nAdmin Menu\n", 5);
        printColoredText("1. Add Book\n", 8);
        printColoredText("2. Delete Book\n", 8);
        printColoredText("3. Borrow Book\n", 8);
        printColoredText("4. Return Book\n", 8);
        printColoredText("5. Update Book\n", 8);
        printColoredText("6. View All Books\n", 8);
        printColoredText("7. Search Books\n", 8);
        printColoredText("8. Change Admin Password\n", 8);
        printColoredText("9. Back to Main Menu\n", 8);

        int choice = getvalidoption(1, 9);

        switch (choice) {
            case 1: 
			addbook(); 
			break;
            case 2: 
			deletebook(); 
			break;
            case 3: 
			borrow();
			break;
            case 4: 
			returnbook();
			break;
            case 5: 
			update(); 
			break;
            case 6:
			view(); 
			break;
            case 7: 
			search(); 
			break;
			case 8:
			{
				char newPassword[20];
                printf("Enter new password: ");
                scanf("%s", newPassword);
                savePasswordToFile(newPassword);  // Save the new password to the file
                printColoredText("Password changed successfully!\n", 2);
                return;
                break;
		}
            case 9: 
			return;  // Return to main menu
            default: 
			printColoredText("Invalid choice. Please try again.\n", 4);
        }
    }
}

// User menu function
void usermenu() {
    while (1) {
        printColoredText("\nUser Menu\n", 5);
        printColoredText("1. Borrow Book\n", 8);
        printColoredText("2. Return Book\n", 8);
        printColoredText("3. View All Books\n", 8);
        printColoredText("4. Search Books\n", 8);
        printColoredText("5. Back to Main Menu\n", 8);

        int choice = getvalidoption(1, 5);

        switch (choice) {
            case 1: 
			borrow(); 
			break;
            case 2: 
			returnbook();
			break;
            case 3:
			view();
			break;
            case 4: 
			search();
			break;
            case 5:
			return;  // Return to main menu
            default: 
			printColoredText("Invalid choice. Please try again.\n", 4);
        }
    }
}

int login() {
    char enteredPassword[20];
    char storedPassword[20];
    int correctPassword = 0;
    int count = 0;

   // Read the password from the file
    if (!readPasswordFromFile(storedPassword)) {
        // If no password file, prompt the user to set a new password
        printf("New password for the admin: ");
        scanf("%s", &storedPassword);
        savePasswordToFile(storedPassword);  // Save the new password to file
        printf("New password saved.\n");
    }

    // Loop to attempt password entry
    while (count < 3) {
            printf("Enter password: ");
            scanf("%s", &enteredPassword);
            if (strcmp(enteredPassword, storedPassword) == 0) {
                printf("Login successful!\n");
                return 1; // Admin access granted
            } else {
                count++;
                printf("Incorrect password.Remaining Attempts %d\n", 3 - count);
            }
    }
    printf("\nToo many incorrect attempts. Returning to Main Menu.\n");
    return 0;
}

// Main menu function
void mainmenu() {
	printColoredText(" Welcome to the Library Management System!\n", 9);
    while (1) {
        printColoredText("\n1. Admin Login\n", 8);
        printColoredText("2. User Access\n", 8);
        printColoredText("3. Logout\n", 8);

        int choice = getvalidoption(1, 3);

        switch (choice) {
            case 1:
                if (login()) {
                    adminmenu();
                }
                break;
            case 2:
                usermenu();
                break;
            case 3:
                printColoredText("Thankyou for using The Library Management System!\nLogging out... Goodbye!\n", 2);
                return;  // Exit program
            default:
                printColoredText("Invalid choice. Please try again.\n", 4);
        }
    }
}

void update()
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("Error opening books.txt.\n");
        return;
    }

    FILE *tempfile = fopen("temp.txt", "w");
    if (tempfile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(file);  // **Close the original file if error occurs**
        return;
    }

    int r, found = 0;
    char quantityInput[50];

    printf("Enter registration number of the book to be updated: \n");
    scanf("%d", &r);
    getchar();  // **Clear the newline character from the buffer**

    while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity, &book.maxquantity) != EOF)
    {
        if (book.registration == r)
        {
            found = 1;
            char safetitle[50],safeauthor[20];
            strcpy(safetitle, book.title); // Copy the book title to safetitle
			strcpy(safeauthor, book.author); // Copy the book author to safeauthor
            printf("Enter updated book title: ");
            fgets(book.title, sizeof(book.title), stdin);
            book.title[strcspn(book.title, "\n")] = '\0'; // Remove trailing newline
			if(book.title[0]=='\0')
			{
				strcpy(book.title,safetitle);
			 } 

            printf("Enter updated book author: ");
            fgets(book.author, sizeof(book.author), stdin);
            book.author[strcspn(book.author, "\n")] = '\0';  // Remove trailing newline
            if(book.author[0]=='\0')
			{
				strcpy(book.author,safeauthor);
			 } 

            while (1) 
            {
            	int safequantity=book.quantity;
                printf("Enter updated book quantity: ");
                fgets(quantityInput, sizeof(quantityInput), stdin);  // Read the input as a string

                // Check if the input is a valid integer
                if (sscanf(quantityInput, "%d", &book.quantity) != 1) 
                {
                    printf("Invalid input. Please enter an integer.\n");
                    continue;  // Repeat the loop until valid input is given
                }

                // Validate the range of the quantity
                if (book.quantity < 0 || book.quantity > 999)
                {
                    printf("Invalid quantity. Please enter a number between 0 and 999.\n");
                    continue;  // Repeat the loop until valid input is given
                }

                book.maxquantity = book.quantity;
                book.status = (book.quantity > 0) ? true : false;
                break;  // Exit the loop once valid input is given
            }

            // Write updated book information to the temporary file
            fprintf(tempfile, "%d|%s|%s|%d|%d|%d\n", book.registration, book.title, book.author, book.status, book.quantity, book.maxquantity);
        }
        else
        {
            // If the book is not found, copy it as-is to the temporary file
            fprintf(tempfile, "%d|%s|%s|%d|%d|%d\n", book.registration, book.title, book.author, book.status, book.quantity, book.maxquantity);
        }
    }

    fclose(file);
    fclose(tempfile);

    if (found)
    {
        remove("books.txt");
        rename("temp.txt", "books.txt");
        printf("Book updated successfully!\n");
    }
    else
    {
        remove("temp.txt");
        printf("No results matching provided registration number.\n");
    }
}

void addbook() 
{
    struct book book;
    FILE *file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error while opening books.txt.\n");
        return;
    }

    int reg;
	char quantityInput[50];
    book.registration = getnewregistrationn(&reg);
    getchar(); // Consume newline

    printf("Enter book title: ");
    fgets(book.title, sizeof(book.title), stdin);
    book.title[strcspn(book.title, "\n")] = '\0';  // Remove trailing newline

    printf("Enter book author: ");
    fgets(book.author, sizeof(book.author), stdin);//author[50]
    book.author[strcspn(book.author, "\n")] = '\0';  // Remove trailing newline
    
    while (1) 
            {
                printf("Enter quantity of books: ");
                fgets(quantityInput, sizeof(quantityInput), stdin);  // Read the input as a string

                // Check if the input is a valid integer
                if (sscanf(quantityInput, "%d", &book.quantity) != 1) 
                {
                    printf("Invalid input. Please enter an integer.\n");
                    continue;  // Repeat the loop until valid input is given
                }

                // Validate the range of the quantity
                if (book.quantity < 0 || book.quantity > 999)
                {
                    printf("Invalid quantity. Please enter a number between 0 and 999.\n");
                    continue;  // Repeat the loop until valid input is given
                }

                book.maxquantity = book.quantity;
                book.status = (book.quantity > 0) ? true : false;
                break;  // Exit the loop once valid input is given
            }
    fprintf(file, "%d|%s|%s|%d|%d|%d\n", book.registration, book.title, book.author, book.status, book.quantity, book.maxquantity);
    fclose(file);
    printf("Book added successfully!\n");
}

void deletebook() {
    int reg, found = 0;
    struct book book;
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error while opening file books.txt.\n");
        return;
    }

    FILE *tempfile = fopen("temp.txt", "w");
    if (tempfile == NULL) {
        printf("Error while opening temporary file.\n");
        fclose(file);
        return;
    }

    printf("Enter registration number of the book to be deleted: ");
    scanf("%d", &reg);
    getchar(); // Consume the newline character

    while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity,&book.maxquantity)!= EOF) {
        if (book.registration == reg) {
            found = 1;  // Found the book to delete
        } else {
            // Write all non-matching books to the temporary file
            if(found!=1)
            fprintf(tempfile, "%d|%s|%s|%d|%d|%d\n", book.registration, book.title, book.author, book.status, book.quantity,book.maxquantity);
            else if(found==1)
            {
           	   fprintf(tempfile, "%d|%s|%s|%d|%d|%d\n", book.registration-1, book.title, book.author, book.status, book.quantity,book.maxquantity);

			}
        }
    }

    fclose(tempfile);
    fclose(file);

    if (found) {
        // Remove the og file and rename the tempo file to replace it
        remove("books.txt");
        rename("temp.txt", "books.txt");
        printf("Book removed successfully!\n");
    } else {
        // If book not found, remove the temporary file
        remove("temp.txt");
        printf("No book found with the provided registration number.\n");
    }
}

// Borrow Book function
void borrow() {
    FILE *file = fopen("books.txt", "r");
    FILE *tempfile = fopen("temp.txt", "w");
    struct book book;
    int reg, found = 0;

    if (file == NULL ) {
        printf("Error opening file books.txt.");
        return;
    }
    if (tempfile == NULL ) {
        printf("Error opening file temp.txt.");
        return;
    }

    printf("Enter registration number: ");
    scanf("%d", &reg);
    getchar(); // Consume newline

    while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity,&book.maxquantity) != EOF) {
        if (book.registration == reg) {
            found = 1;
            if (book.quantity > 0) {
                book.quantity--; // Decrease quantity
                if (book.quantity == 0) {
                    book.status = false; // Mark as unavailable when quantity is 0
                }
                printf("Book borrowed successfully!\nEnjoy!\n");
            } else {
                printf("No copies available for borrowing.\n");
            }
        }
        fprintf(tempfile, "%d|%s|%s|%d|%d|%d\n", book.registration, book.title, book.author, book.status, book.quantity,book.maxquantity);
    }

    fclose(file);
    fclose(tempfile);

    if (found) {
        remove("books.txt");
        rename("temp.txt", "books.txt");
    } else {
        remove("temp.txt");
        printf("No results matching registration number.\n");
    }
}

// Return Book function
void returnbook() {
    FILE *file = fopen("books.txt", "r");
    FILE *tempfile = fopen("temp.txt", "w");
    struct book book;
    int reg, found = 0;

    if (file == NULL || tempfile == NULL) {
        printf("Error opening file.");
        return;
    }

    printf("Enter registration number: ");
    scanf("%d", &reg);
    getchar(); // Consume newline

    while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity,&book.maxquantity) != EOF) {
        if (book.registration == reg) {
            found = 1;
            if (book.quantity<book.maxquantity ) {
                book.status = true; // Mark as returned
                book.quantity++; // Increase quantity
                printf("Book returned successfully!\n");
            } else {
                printf("All copies already returned.\n");
            }
        }
        fprintf(tempfile, "%d|%s|%s|%d|%d|%d\n", book.registration, book.title, book.author, book.status, book.quantity,book.maxquantity);
    }

    fclose(file);
    fclose(tempfile);

    if (found) {
        remove("books.txt");
        rename("temp.txt", "books.txt");
    } else {
        remove("temp.txt");
        printf("No results matching registration number.\n");
    }
}

// Search function
void search() {
    int found = 0;
    FILE *file = fopen("books.txt", "r");
    struct book book;
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int search, reg, av;
    char t[50], auth[20];
    printf("Search for book by:\n1. Registration number\n2. Title\n3. Author\n4. Availability\n");
    printf("Enter Your Choice: ");
    scanf("%d", &search);
    getchar(); // Consume newline
        switch (search) {
        case 1:
            printf("Enter Book Registration Number: ");
            scanf("%d", &reg);
            getchar();
            fseek(file, 0, SEEK_SET);
            found = 0;
            printf("\n%-10s | %-49s | %-19s | %-12s | %-8s | %-12s\n", "Reg No", "Title", "Author", "Status", "Quantity","MAX Quantity");
            printf("------------------------------------------------------------------------------------------------------------------------------\n");
            while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity,&book.maxquantity) != EOF) {
                if (book.registration == reg) {
                    found = 1;
                    printf("%-10d | %-49s | %-19s | %-12s | %-8d | %-12d\n", book.registration, book.title, book.author, book.status?"Available":"Unavailable", book.quantity,book.maxquantity);
                }
            }
            break;
        case 2:
            printf("Enter Book Title: ");
            fgets(t, sizeof(t), stdin);
            t[strcspn(t, "\n")] = '\0';
            fseek(file, 0, SEEK_SET);
            found = 0;
            printf("\n%-10s | %-49s | %-19s | %-12s | %-8s | %-12s\n", "Reg No", "Title", "Author", "Status", "Quantity","MAX Quantity");
            printf("------------------------------------------------------------------------------------------------------------------------------\n");
            while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity,&book.maxquantity) != EOF) {
                if (strcmp(book.title, t) == 0) {
                    found = 1;
                    printf("%-10d | %-49s | %-19s | %-12s | %-8d | %-12d\n", book.registration, book.title, book.author, book.status?"Available":"Unavailable", book.quantity,book.maxquantity);
                }
            }
            break;
        case 3:
            printf("Enter Book Author: ");
            fgets(auth, sizeof(auth), stdin);
            auth[strcspn(auth, "\n")] = '\0';
            fseek(file, 0, SEEK_SET);
            found = 0;
            printf("\n%-10s | %-49s | %-19s | %-12s | %-8s | %-12s\n", "Reg No", "Title", "Author", "Status", "Quantity","MAX Quantity");
            printf("------------------------------------------------------------------------------------------------------------------------------\n");
            while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity,&book.maxquantity) != EOF) {
                if (strcmp(book.author, auth) == 0) {
                    found = 1;
					printf("%-10d | %-49s | %-19s | %-12s | %-8d | %-12d\n", book.registration, book.title, book.author,book.status? "Available" :"Unavailable", book.quantity,book.maxquantity);                }
            }
            break;
        case 4:
            printf("Enter Availability (1 for Available, 0 for Unavailable): ");
            scanf("%d", &av);
            fseek(file, 0, SEEK_SET);
            found = 0;
            printf("\n%-10s | %-49s | %-19s | %-12s | %-8s | %-12s\n", "Reg No", "Title", "Author", "Status", "Quantity","MAX Quantity");
            printf("------------------------------------------------------------------------------------------------------------------------------\n");
            while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity,&book.maxquantity) != EOF) {
                if (book.status == av) {
                    found = 1;
					printf("%-10d | %-49s | %-19s | %-12s | %-8d | %-12d\n", book.registration, book.title, book.author,book.status?"Available":"Unavailable", book.quantity,book.maxquantity);}
            break;
        default:
            printf("Invalid search option.\n");
            break;
        }
    }

    if (!found) {
        printf("No books found matching the criteria.\n");
    }

    fclose(file);
}

// View all books
void view() {
    FILE *file = fopen("books.txt", "r");
    struct book book;
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n%-10s | %-49s | %-19s | %-12s | %-8s | %-12s\n", "Reg No", "Title", "Author", "Status", "Quantity","MAX Quantity");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d|%49[^|]|%19[^|]|%d|%d|%d\n", &book.registration, book.title, book.author, &book.status, &book.quantity,&book.maxquantity) != EOF) {
        printf("%-10d | %-49s | %-19s | %-12s | %-8d | %-12d\n", book.registration, book.title, book.author,book.status?"Available":"Unavailable", book.quantity,book.maxquantity);
    }

    fclose(file);
}
int main(){
	mainmenu();
	return 0;
}
       
