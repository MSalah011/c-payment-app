#include <stdio.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){

	uint8_t name[28];
	fflush(stdin);
	fgets(name, sizeof name, stdin);
	name[strcspn(name, "\n")] = 0;
	if(strlen(name)<=24 && strlen(name)>=20){
		strcpy((*cardData).cardHolderName,name);
		return CARD_OK;
	}else{
		printf("WRONG NAME\n");
		return WRONG_NAME;
	}

}

void getCardHolderNameTest(void){
	
	ST_cardData_t cardData;

	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: getCardHolderName\n");

	printf("\nTest Case 1: less than 20 characters \n");
	printf("Input Data: MAHMOUD\n");
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("Data stored: %s \n",cardData.cardHolderName);

	printf("\nTest Case 2: more than 24 characters \n");
	printf("Input Data: MAHMOUD SALAH ABDULLAH ABDELAATY \n");
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("Data stored: %s \n",cardData.cardHolderName);

	printf("\nTest Case 3: NULL \n");
	printf("Input Data: \n");
	printf("Expected Result: 1 \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("Data stored: %s \n",cardData.cardHolderName);

	printf("\nTest Case 4: happy-case \n");
	printf("Input Data: MAHMOUD SALAH ABDULLAH\n");
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n", getCardHolderName(&cardData));
	printf("Data stored: %s \n",cardData.cardHolderName);
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){

	uint8_t date[9];
	fflush(stdin);
	fgets(date,sizeof date,stdin);
	date[strcspn(date, "\n")] = 0;
	if(strlen(date)==5 && date[2]=='/'){
		strcpy((*cardData).cardExpirationDate,date);
		return CARD_OK;
	}else{
		printf("WRONG EXP DATE\n");
		return WRONG_EXP_DATE;
	}

}

void getCardExpiryDateTest(void){

	ST_cardData_t cardData;
	
	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: getCardExpiryDate\n");

	printf("\nTest Case 1: NULL \n");
	printf("Input Data: \n");
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n",cardData.cardExpirationDate);

	printf("\nTest Case 2: more than 5 characters \n");
	printf("Input Data: 12/2022 \n");
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n",cardData.cardExpirationDate);

	printf("\nTest Case 3: less than 5 characters \n");
	printf("Input Data: 9/22\n");
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n",cardData.cardExpirationDate);

	printf("\nTest Case 4: wrong format \n");
	printf("Input Data: 09-22\n");
	printf("Expected Result: 2 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n",cardData.cardExpirationDate);

	printf("\nTest Case 5: happy-case \n");
	printf("Input Data: 05/25\n");
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n", getCardExpiryDate(&cardData));
	printf("Data stored: %s \n",cardData.cardExpirationDate);
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){

	uint8_t pan[23];
	fflush(stdin);
	fgets(pan, sizeof pan, stdin);
	pan[strcspn(pan, "\n")] = 0;
	if(strlen(pan)<=19 && strlen(pan)>=16){
		strcpy((*cardData).primaryAccountNumber,pan);
		return CARD_OK;
	}else{
		printf("WRONG PAN\n");
		return WRONG_PAN;
	}

}

void getCardPANTest(void){

	ST_cardData_t cardData;

	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: getCardPAN\n");

	printf("\nTest Case 1: less than 16 characters \n");
	printf("Input Data: 543212345678986\n");
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("Data stored: %s \n",cardData.primaryAccountNumber);

	printf("\nTest Case 2: more than 19 characters \n");
	printf("Input Data: 42313456786432134569\n");
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("Data stored: %s \n",cardData.primaryAccountNumber);

	printf("\nTest Case 3: NULL \n");
	printf("Input Data: \n");
	printf("Expected Result: 3 \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("Data stored: %s \n",cardData.primaryAccountNumber);

	printf("\nTest Case 4: happy-case \n");
	printf("Input Data: 8989374615436851\n");
	printf("Expected Result: 0 \n");
	printf("Actual Result: %d \n", getCardPAN(&cardData));
	printf("Data stored: %s \n",cardData.primaryAccountNumber);
}
