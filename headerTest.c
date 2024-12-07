#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char encoded_flag[] = {70, 68, 122, 95, 126, 117, 27, 14, 117, 67, 103, 90, 26, 88, 1, 75, 68, 94, 0};

void print_flag() {
	for (int i = 0; encoded_flag[i] != 0; i++) {
		encoded_flag[i] ^= 42;
	}
	printf("Congratulations! Here is your flag: lspuCTF{%s}\n", encoded_flag);


	for (int i = 0; encoded_flag[i] != 0; i++) {
		encoded_flag[i] ^= 42;
	}
}

int scanner(const char *input) {
	for (int i = 0; input[i] != '\0'; i++) {
		if (isdigit(input[i])) {
			return 1;
		}
	}
	return 0;
}

int is_void_input(const char *input) {
	return strlen(input) == 0;
}

void challenge() {
	char input_1[10], input_2[20];
	int number;

	// First Challenge
	printf("1st Input: ");
	fgets(input_1, sizeof(input_1), stdin);
	input_1[strcspn(input_1, "\n")] = 0; // Remove newline

	// Check for void input (empty input)
	if (is_void_input(input_1)) {
		printf("Invalid input.\n");
		return;
	}

	number = atoi(input_1);
	
	printf("%d",number);

	if (number == 0 && strcmp(input_1, "0") != 0) {
		printf("Correct Input!\n");
	} 
	
	else {
		printf("First challenge failed. Try again!\n");
		return;
	}

	// Second input challenge
	printf("2nd Input: ");
	fgets(input_2, sizeof(input_2), stdin);
	input_2[strcspn(input_2, "\n")] = 0; // Remove newline

	// Check for void input (empty input)
	if (is_void_input(input_2)) {
		printf("Invalid input.\n");
		return;
	}

	if (scanner(input_2)) {
		print_flag();
	} 
	
	else {
		printf("Second challenge failed. Try again!\n");
	}
}

int main() {
	char choice[10];

	while (1) {
		// Menu
		printf("\n--- Menu ---\n");
		printf("1. Start the challenge\n");
		printf("2. Exit\n");
		printf("Enter your choice: ");
		fgets(choice, sizeof(choice), stdin);
		choice[strcspn(choice, "\n")] = 0; // Remove newline

		// Check for void input (empty string)
		if (strlen(choice) == 0) {
			printf("Invalid choice. Please try again.\n");
			continue;
		}

		int choice_int = atoi(choice);

		switch (choice_int) {
		case 1:
			challenge();
			break;
		case 2:
			printf("Goodbye!\n");
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	}

	return 0;
}