/*
 * This program is developed by Aurimas Paukshte. The main goal of this program
 * is to read/write from/to .txt file & modify the data.
 *
 * All tasks are hardcoded in the function and therefore user will not be able to
 * inpact anything directly. Question at the end is an exception.
 *
 * Developed for the Vilniaus Kolegija, University of Applied Sciences.
 * This product includes software developed by the VIKO Project
 * (https://www.viko.lt).
 * See the COPYRIGHT file at the top-level directory of this distribution
 * for details of code ownership.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define MAX_ENTRIES 256        // here is defined the maximum amount of profiles, that can be created
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// This is the main nested structure for the profiles

struct birthCertificate {

	size_t year;
	size_t month;
	size_t day;

};

typedef struct {

	char name[256];
	char surname[256];
	int stateId;
	struct birthCertificate;

}id;

char* menu();                 // function opening the main menu
int compare(char*);           // a simple function to compare 2 strings
int load(id*);                // function, taht loads all profiles from the .txt file
void printEntries(id*, int);  // function to print all entries
void modMenu(id*, int);       // function responsible for opening modification menu
void modifier(int, id*, int); // function responsible for modification of profiles
void creatorMenu(id*, int);   // function, that creates new profiles
void cleanup(id*, int);       // function, that writes all modified entries to the file, from where they were read

int main() {

	id list[MAX_ENTRIES]; // creating the array of structures to store all profile information

	int loaded = load(list); // loading all the profiles into @param id* list & returning the amount of loaded profiles.

	char* answ = "NULL"; // in this variable is stored input from user

	while (strcmp(&answ, "exit") != 0) {

		enum e { elist = 0, modify = 1, add = 2, exit = 3 } an; // this enum is used to replace numberic cases with according words for an easier orientation

		answ = menu(); // menu gets called and answer from user is returned

		switch (compare(answ)) { // now we take that answer and check if it is valid and opening an according menu
		case elist:
			printEntries(list, loaded);
			break;
		case modify:
			modMenu(list, loaded);
			break;
		case add:
			creatorMenu(list, loaded);
			loaded++;
			break;
		case exit:
			cleanup(list, loaded);
			break;
		default: printf("Error! Issued task is invalid.");
		}

	}
	return 0;
}

/*
 * Comparing swicth cases.
 * 
 * @note Swicth only accepts numberic system of comparison, therefore we cannot use char *answ
 *       to check what user selected. So we convert user selected function into an according number
 *       using this comparing algorythm.
 *
 * @param char* answer is user inputted string, which represents user selected option from the menu.
 *
 * @return this function returns an integer, that coresponds accordingly with functions listed in menu()
 *         and is used in swicth().
 * 
 */

	int	compare(char* answer) {

		int rez = 3;
		const char* commands[4] = { "list","modify","add" };
	
		for (int i = 0; i < 3; i++) {
		
			if (strcmp(&answer, commands[i]) == 0) {
			
				rez = i;
				break;

			}
		
		}
		return rez;
	
	}

/*
 * Printing list of entries.
 *
 * @param id* entries is the array of structers where profile information is stored.
 *
 * @param int volume is the amount of loaded profiles.
 *
 */

void printEntries(id* entries, int volume) {
	
	for (int i = 0; i < volume; i++) {
		
		printf("\n-----------------------------\n");
		printf("Name: %s\n", entries[i].name);
		printf("Surname: %s\n", entries[i].surname);
		printf("State ID: %d\n", entries[i].stateId);
		printf("DOB: %d/%d/%d\n", entries[i].year, entries[i].month, entries[i].day);
		printf("\n-----------------------------\n");
	
	}
	system("PAUSE");
	system("CLS");
}

/*
 * Opening modification menu.
 *
 * @param id* entries is the array of structers where profile information is stored.
 *
 * @param int volume is the amount of loaded profiles.
 *
 */

	void modMenu(id* entries, int volume) {
	
		char* modify;
		int change;
		int target = -1;
		printf("Enter the name of an entry you want to modify\n");
		scanf(" %s", &modify);
		system("CLS");

		for (int i = 0; i < volume; i++) {
		
			if (strcmp(&modify, entries[i].name) == 0) {
			
				target = i;
				break;
			}
		
		}
		
		if (target > -1) {
		
			printf("What you want changed?\n");
			printf("Name           [1]\n");
			printf("Surname        [2]\n");
			printf("State ID       [3]\n");
			printf("Year of birth  [4]\n");
			printf("Month of birth [5]\n");
			printf("Day of birth   [6]\n");
			scanf(" %d", &change);
			system("cls");
			modifier(change, entries, target);
		
		}
		else {
		
			printf("Name you entered does not exist.\n");
			system("PAUSE");
			system("CLS");
		
		}
	}

/*
 * Modifying entries.
 *
 * @param int change represents the parameter in the structure, that user prefers to modify.
 *
 * @param id* target is the array of structers where profile information is stored.
 *
 * @param int target our targeted profile's number in our array of structures
 *
 */

	void modifier(int change, id* entries, int target) {
	
		char* update1;
		size_t update2;



		switch (change) {
		
		case 1:
			printf("Enter new name\n");
			scanf(" %s", &update1);
			system("CLS");
			strcpy(entries[target].name, &update1);
			break;
		case 2:
			printf("Enter new surname\n");
			scanf(" %s", &update1);
			system("CLS");
			strcpy(entries[target].surname, &update1);
			break;
		case 3:
			printf("Enter new state ID\n");
			scanf(" %d", &update2);
			system("CLS");
			entries[target].stateId = update2;
			break;
		case 4:
			printf("Enter new year of birth\n");
			scanf(" %d", &update2);
			system("CLS");
			entries[target].year = update2;
			break;
		case 5:
			printf("Enter new month of birth\n");
			scanf(" %d", &update2);
			system("CLS");
			entries[target].month = update2;
			break;
		case 6:
			printf("Enter new day of birth\n");
			scanf(" %d", &update2);
			system("CLS");
			entries[target].day = update2;
			break;
		default:
			printf("Invalid argument\n");
			system("pause");
			system("cls");
		
		}

		printf("Profile updated successfuly!\n");
		system("pause");
		system("cls");
	
	}
/*
 * Opening new profile creation menu.
 *
 * @param id* entries is the array of structers where profile information is stored.
 *
 * @param int place position, where the new array element will be stored.
 *
 */

	void creatorMenu(id* entries, int place) {
	
		char* name, *sname;
		int state, year, month, day;

		printf("\nEnter NAME for the new entry\n");
		scanf(" %s", &name);
		system("CLS");

		printf("\nEnter SURNAME for the new entry\n");
		scanf(" %s", &sname);
		system("CLS");

		printf("\nEnter STATE ID for the new entry\n");
		scanf(" %d", &state);
		system("CLS");

		printf("\nEnter YEAR OF BIRTH for the new entry\n");
		scanf(" %d", &year);
		system("CLS");

		printf("\nEnter MONTH OF BIRTH for the new entry\n");
		scanf(" %d", &month);
		system("CLS");

		printf("\nEnter DAY OF BIRTH for the new entry\n");
		scanf(" %d", &day);
		system("CLS");
		
		id newEntry;

		strcpy(newEntry.name, &name);
		strcpy(newEntry.surname, &sname);
		newEntry.stateId = state;
		newEntry.year = year;
		newEntry.month = month;
		newEntry.day = day;

		entries[place] = newEntry;

		printf("New entry created successfuly!\n");
		system("Pause");
		system("CLS");
	
	}

/*
 * Saving all data to .txt file.
 *
 * @param id* entries is the array of structers where profile information is stored.
 *
 * @param int loaded is the amount of loaded profiles.
 *
 */

	void cleanup(id* entries, int loaded) {

		printf("Saving files...\n");

		FILE* fp = fopen("profiles.txt", "w+");

		for (int i = 0; i < loaded; i++) {

			fprintf(fp, "%s;%s;%d;%d;%d;%d\n", entries[i].name, entries[i].surname, entries[i].stateId, entries[i].year, entries[i].month, entries[i].day);
		
		}
		fclose(fp);

		printf("Done!\n");
	
	}

/*
 * Loading all profiles from the .txt file.
 *
 * @param id* list is the array of structers where profile information will be stored.
 *
 * @return loaded is the amount of profiles loaded.
 *
 */

	int load(id* list) {

		char temp[256];
		char* temp2[7];
		FILE* fp;
		const char s[2] = ";";
		char* token;
		int n = 0, o = 0, loaded = 0;
	
		printf("Loading profiles from .txt file.\n");

		fp = fopen("profiles.txt", "r");

		if (fp == NULL) {

			printf("Error opening file. Are you sure this file exists?\n");
			exit(-1);

		}

		while (fgets(temp, 256, (FILE*)fp) != NULL) {

			token = strtok(temp, s);

			while (token != NULL) {

				temp2[n] = token;

				token = strtok(NULL, s);
				n++;
			}

			strcpy(list[o].name, temp2[0]);
			strcpy(list[o].surname, temp2[1]);
			list[o].stateId = atoi(temp2[2]);
			list[o].year = atoi(temp2[3]);
			list[o].month = atoi(temp2[4]);
			list[o].day = atoi(temp2[5]);

			o++;
			n = 0;
			loaded++;

		}

		fclose(fp);

		printf("Done. Loaded %d profiles.\n", loaded);

		system("PAUSE");
		system("CLS");

		return loaded;
	
	}

/*
 * Opening main menu.
 *
 * @return answ is variable that holds the input from user.
 *
 */

	char* menu() {
		
		char* answ;

		printf("To view the list of all the entries type [list]\n");
		printf("To modify an entry type [modify]\n");
		printf("To add an entry type [add]\n");
		printf("To save and exit type [exit]\n");
		scanf(" %s", &answ);
		system("CLS");
	
		return answ;
	}