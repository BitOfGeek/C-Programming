#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Library_catalog.h"


int main(){
	ccList *head=NULL;
	int choice;
	char number[20], Title[80], Author[50];

	while (1) {
		printf("\nList menu\n");
		printf("1. Add new data into the Library Catalog\n");
		printf("2. Acualise the Catalog\n");
		printf("3. Searh by book title\n");
		printf("4. Serch by Author\n");
		printf("0. Exit\n");
		printf("Your choice: ");
		scanf("%d", &choice);
		
		switch (choice) {
		case 1:
			if (head == NULL){
				head = readFile();
			}
			head= addNew(head);
			printf("\nDone");
			break;

		case 2:
			printf("Enter catalog number: ");
			scanf("%s", number);
			if (head == NULL){
				head = readFile();
			}
			update(number, head);
			printf("\nDone\n");
			break;

		case 3:
			printf("\nEnter title you want to search with: ");
			fflush(stdin);
			fgets(Title,80,stdin);
			if (head == NULL){
				head = readFile();
			}
			search_title(head, Title);
			break;
		case 4:
			printf("\nEnter author you want to search with: ");
			fflush(stdin);
			fgets(Author,50,stdin);
			if (head == NULL){
				head = readFile();
			}
			search_author(head, Author);
			break;
		case 0:
			exit(0);
		default:
			printf("Selfdestruct\n");
		}
		fflush(stdin);
	}
	return 0;
}

ccList* addNew(ccList *head){
	ccList  *cList;
	catalog temp;
	cList = (ccList*)malloc(sizeof(ccList));
	if (cList == NULL){
		printf("error");
		exit(1);
	}
	printf("\nCatalog number: ");
	scanf("%s", &temp.cat_number);
	printf("\nTitle: ");
	fflush(stdin);
	fgets(&temp.title, 80, stdin);
	printf("\nAuthor: ");
	fflush(stdin);
	fgets(&temp.author, 50, stdin);
	printf("\nPrice: ");
	scanf("%lf", &temp.price);
	printf("\nYear: ");
	scanf("%d", &temp.year);
	printf("\nPublisher: ");
	fflush(stdin);
	fgets(&temp.publisher, 80, stdin);;
	strcpy(cList->cat_number, temp.cat_number);
	strcpy(cList->title, temp.title);
	strcpy(cList->author, temp.author);
	cList->price = temp.price;
	cList->year = temp.year;
	strcpy(cList->publisher, temp.publisher);
	cList->next = head;
	head = cList;

	fflush(stdin);
	saveFile(head);
	return head;
}

ccList* readFile(){
	FILE *fp;
	catalog temp;
	ccList *head = NULL, *cList;

	if ((fp = fopen("catalog.dat", "rb")) == NULL){
		printf("file is currently empty");
		return(head);
	}
	while ((fread(&temp.cat_number, 20 * sizeof(char), 1, fp)) == 1){

		if ((fread(&temp.title, 80 * sizeof(char), 1, fp)) != 1){
			printf("error occured while reading");
			exit(1);
		}
		if ((fread(&temp.author, 50 * sizeof(char), 1, fp)) != 1){
			printf("error occured while reading");
			exit(1);
		}
		if ((fread(&temp.price, sizeof(double), 1, fp)) != 1){
			printf("error occured while reading");
			exit(1);
		}
		if ((fread(&temp.year, sizeof(int), 1, fp)) != 1){
			printf("error occured while reading");
			exit(1);
		}
		if ((fread(&temp.publisher, 80 * sizeof(char), 1, fp)) != 1){
			printf("error occured while reading");
			exit(1);
		}
		cList = (ccList*)malloc(sizeof(ccList));
		if (cList == NULL){
			printf("error");
			exit(1);
		}
		strcpy(cList->cat_number, temp.cat_number);
		strcpy(cList->title, temp.title);
		strcpy(cList->author, temp.author);
		cList->price = temp.price;
		cList->year = temp.year;
		strcpy(cList->publisher, temp.publisher);

		cList->next = head;
		head = cList;
	}
	fclose(fp);
	return head;
}
void saveFile(ccList *head){
	FILE *fp;
	ccList *cList = head;

	if ((fp = fopen("catalog.dat", "wb")) == NULL){
		printf("error");
		exit(1);
	}
	for (cList; cList != NULL; cList = cList->next){
		if ((fwrite(cList->cat_number, 20 * sizeof(char), 1, fp)) != 1){
			printf("error");
			fclose(fp);
			exit(1);
		}
		if ((fwrite(cList->title, 80 * sizeof(char), 1, fp)) != 1){
			printf("error");
			fclose(fp);
			exit(1);
		}
		if ((fwrite(cList->author, 50 * sizeof(char), 1, fp)) != 1){
			printf("error");
			fclose(fp);
			exit(1);
		}
		if ((fwrite(&(cList->price), sizeof(double), 1, fp)) != 1){
			printf("error");
			fclose(fp);
			exit(1);
		}
		if ((fwrite(&(cList->year), sizeof(int), 1, fp)) != 1){
			printf("error");
			fclose(fp);
			exit(1);
		}
		if ((fwrite(cList->publisher, 80 * sizeof(char), 1, fp)) != 1){
			printf("error");
			fclose(fp);
			exit(1);
		}
	}
	fclose(fp);
}

ccList* update(char *num, ccList*head){
	char newNum[20], newTitle[80], newAuthor[50], newPublisher[80];
	double newPrice;
	int newYear;
	for (head; head != NULL; head = head->next){
		if ((strcmp(head->cat_number, num)) == 0){
			printf("\nEnter new catalog number: ");
			scanf("%s", newNum);
			printf("\nEnter new title: ");
			fflush(stdin);
			fgets(newTitle, 80, stdin);
			printf("\nEnter new author: ");
			fflush(stdin);
			fgets(newAuthor, 50, stdin);;
			printf("\nEnter new price: ");
			scanf("%lf", &newPrice);
			printf("\nEnter new year: ");
			scanf("%d", &newYear);
			printf("\nEnter new publisher: ");
			fflush(stdin);
			fgets(newPublisher, 80, stdin);
			strcpy(head->cat_number, newNum);
			strcpy(head->title, newTitle);
			strcpy(head->author, newAuthor);
			head->price = newPrice;
			head->year = newYear;
			strcpy(head->publisher, newPublisher);
		}
	}
	saveFile(head);
	return head;
}
void search_title(ccList*head, char *title){
	for (head; head != NULL; head = head->next){
		if ((strcmp(head->title, title)) == 0){
			printf("\n%s", head->cat_number);
			printf("\n%s", head->title);
			printf("\n%s", head->author);
			printf("\n%f", head->price);
			printf("\n%d", head->year);
			printf("\n%s", head->publisher);
		}
	}
}

void search_author(ccList*head, char *author){
	for (head; head != NULL; head = head->next){
		if ((strcmp(head->author, author)) == 0){
			printf("\n%s", head->cat_number);
			printf("\n%s", head->title);
			printf("\n%s", head->author);
			printf("\n%f", head->price);
			printf("\n%d", head->year);
			printf("\n%s", head->publisher);
		}
	}
}
