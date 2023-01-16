#include <stdio.h>
#include <string.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	
	uint8_t date[14];
	fflush(stdin);
	fgets(date, sizeof date,stdin);							   /////////////////////////
	date[strcspn(date, "\n")] = 0;						      // 01  2  34  5  6789  //
	if(strlen(date)==10 && date[2]=='/' && date[5]=='/'){    //	 DD  /  MM  /  YYYY //
		strcpy((*termData).transactionDate,date);			/////////////////////////
		return TERMINAL_OK;
	}else{
		printf("Wrong Date");
		return WRONG_DATE;
	}
}

void getTransactionDateTest(void){

	ST_terminalData_t termData;
	
	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: getTransactionDate\n");
	printf("\nTest Case 1: NULL \n");
	printf("Input Data: \n");
	printf("Expected Result: %d \n",WRONG_DATE);
	printf("Actual Result: %d \n", getTransactionDate(&termData));
	printf("Data stored: %s \n",termData.transactionDate);

	printf("\nTest Case 2: more than 10 characters \n");
	printf("Input Data: 12/12/20222 \n");
	printf("Expected Result: %d \n",WRONG_DATE);
	printf("Actual Result: %d \n", getTransactionDate(&termData));
	printf("Data stored: %s \n",termData.transactionDate);

	printf("\nTest Case 3: less than 10 characters \n");
	printf("Input Data: 9/9/2022\n");
	printf("Expected Result: %d \n",WRONG_DATE);
	printf("Actual Result: %d \n", getTransactionDate(&termData));
	printf("Data stored: %s \n",termData.transactionDate);

	printf("\nTest Case 4: wrong format \n");
	printf("Input Data: 05-10-2022\n");
	printf("Expected Result: %d \n",WRONG_DATE);
	printf("Actual Result: %d \n", getTransactionDate(&termData));
	printf("Data stored: %s \n",termData.transactionDate);

	printf("\nTest Case 5: happy-case \n");
	printf("Input Data: 05/10/2022\n");
	printf("Expected Result: %d \n",TERMINAL_OK);
	printf("Actual Result: %d \n", getTransactionDate(&termData));
	printf("Data stored: %s \n",termData.transactionDate);
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){	

	uint8_t int_trans_year, int_trans_month, int_exp_year, int_exp_month;
	uint8_t s_trans_year[3], s_trans_month[3], s_exp_year[3],  s_exp_month[3];

	s_trans_year[0] = (*termData).transactionDate[8]; //DD/MM/YYYY  01/34/6789
	s_trans_year[1] = (*termData).transactionDate[9];s_trans_year[2] = '\0';

	s_trans_month[0] = (*termData).transactionDate[3];
	s_trans_month[1] = (*termData).transactionDate[4];s_trans_month[2] = '\0';

	s_exp_year[0] = (*cardData).cardExpirationDate[3];  //MM/YY  01/34
	s_exp_year[1] = (*cardData).cardExpirationDate[4];s_exp_year[2] = '\0';

	s_exp_month[0] = (*cardData).cardExpirationDate[0];
	s_exp_month[1] = (*cardData).cardExpirationDate[1];s_exp_month[2] = '\0';

	int_trans_year = atoi(s_trans_year);int_trans_month = atoi(s_trans_month);
	int_exp_year = atoi(s_exp_year);int_exp_month = atoi(s_exp_month);

	if(int_exp_year>int_trans_year)
		return TERMINAL_OK;
	else if(int_exp_year==int_trans_year){
		if(int_exp_month>=int_trans_month)
			return TERMINAL_OK;
		else
			return EXPIRED_CARD;
	}else
		return EXPIRED_CARD;
}

void isCardExpiredTest(void){

	ST_terminalData_t termData;
	ST_cardData_t card1 = { "","", "10/21"};
	ST_cardData_t card2 = { "","", "11/22"};
	ST_cardData_t card3 = { "","", "12/22"};
	ST_cardData_t card4 = { "","", "09/23"};
	
	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: isCardExpired\n");

	printf("Enter transaction date\n");
	getTransactionDate(&termData);
	
	printf("\nTest Case 1: expired card exp_year < trans_year \n");
	printf("Input Data: 10/21 \n");
	printf("Expected Result: %d \n",EXPIRED_CARD);
	printf("Actual Result: %d \n", isCardExpired(&card1,&termData));
	
	printf("\nTest Case 2: expired card exp_year == trans_year  && exp_month < trans_month\n");
	printf("Input Data: 11/22 \n");
	printf("Expected Result: %d \n",EXPIRED_CARD);
	printf("Actual Result: %d \n", isCardExpired(&card2,&termData));
	
	printf("\nTest Case 3: non-expired card exp_year == trans_year  && exp_month == trans_month\n");
	printf("Input Data: 12/22 \n");
	printf("Expected Result: %d \n",TERMINAL_OK);
	printf("Actual Result: %d \n", isCardExpired(&card3,&termData));
	
	printf("\nTest Case 4: non-expired card exp_year > trans_year \n");
	printf("Input Data: 09/23 \n");
	printf("Expected Result: %d \n",TERMINAL_OK);
	printf("Actual Result: %d \n", isCardExpired(&card4,&termData));
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){

	float amount;
	fflush(stdin);
	scanf("%f",&amount);
	if(amount>0.0){
		(*termData).transAmount=amount;
		return TERMINAL_OK;
	}else{
		printf("INVALID AMOUNT");
		return INVALID_AMOUNT;
	}
}

void getTransactionAmountTest(void){

	ST_terminalData_t termData;

	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: getTransactionAmount\n");

	printf("\nTest Case 1: Zero amount \n");
	printf("Input Data: 0 \n");
	printf("Expected Result: %d \n",INVALID_AMOUNT);
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
	printf("Data stored: %.2f \n",termData.transAmount);

	printf("\nTest Case 2: negative amount \n");
	printf("Input Data: -100 \n");
	printf("Expected Result: %d \n",INVALID_AMOUNT);
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
	printf("Data stored: %.2f \n",termData.transAmount);

	printf("\nTest Case 3: valid amount\n");
	printf("Input Data: 555.55 \n");
	printf("Expected Result: %d \n",TERMINAL_OK);
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
	printf("Data stored: %.2f \n",termData.transAmount);
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){

	if(maxAmount>0){
		(*termData).maxTransAmount=maxAmount;
		return TERMINAL_OK;
	}else{
		printf("INVALID AMOUNT");
		return INVALID_MAX_AMOUNT;
	}
}

void setMaxAmountTest(void){

	ST_terminalData_t termData;

	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: setMaxAmount\n");

	printf("\nTest Case 1: Zero amount \n");
	printf("Input Data: 0 \n");
	printf("Expected Result: %d \n",INVALID_MAX_AMOUNT);
	printf("Actual Result: %d \n", setMaxAmount(&termData, 0));
	printf("Data stored: %.2f \n",termData.maxTransAmount);

	printf("\nTest Case 1: negative amount \n");
	printf("Input Data: -100 \n");
	printf("Expected Result: %d \n",INVALID_MAX_AMOUNT);
	printf("Actual Result: %d \n", setMaxAmount(&termData, -100));
	printf("Data stored: %.2f \n",termData.maxTransAmount);

	printf("\nTest Case 2: valid amount\n");
	printf("Input Data: 20000 \n");
	printf("Expected Result: %d \n", TERMINAL_OK);
	printf("Actual Result: %d \n", setMaxAmount(&termData, 20000));
	printf("Data stored: %.2f \n",termData.maxTransAmount);

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	if((*termData).transAmount<=(*termData).maxTransAmount)
		return TERMINAL_OK;
	else
		return EXCEED_MAX_AMOUNT;
}

void isBelowMaxAmountTest(void){

	ST_terminalData_t termData;

	setMaxAmount(&termData, 20000);
	
	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: isBelowMaxAmount\n");

	printf("\nTest Case 1: Larger than max \n");
	termData.transAmount=21000;
	printf("Input Data: 21000 \n");
	printf("Expected Result: %d \n", EXCEED_MAX_AMOUNT);
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));

	printf("\nTest Case 1: Equal max amount \n");
	termData.transAmount=20000;
	printf("Input Data: 20000 \n");
	printf("Expected Result: %d \n",TERMINAL_OK);
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));

	printf("\nTest Case 2: Below Max Amount\n");
	termData.transAmount=5000;
	printf("Input Data: 5000 \n");
	printf("Expected Result: %d \n", TERMINAL_OK);
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));
}
