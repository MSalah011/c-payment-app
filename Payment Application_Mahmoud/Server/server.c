#include <stdio.h>
#include <string.h>
#include "server.h"
#include "../Application/app.h"

ST_accountsDB_t accountsDB[255]={
	{3000.0, RUNNING, "8989374615436851"},
	{100000.0, BLOCKED, "5807007076043875"},
	{3000.0, RUNNING, "3379513561108795"},
	{20000.0, RUNNING, "2769148304059987"},
	{10000.0, BLOCKED, "4847352989263094"},
	{3000.0, BLOCKED, "4003600000000014"}
};

ST_transaction_t transactionsDB[255]={0};

uint8_t sequence_number=0,accountRef;

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
	uint8_t i;
	
	for(i=0;i<255;i++){
		if(strcmp((*cardData).primaryAccountNumber, accountRefrence[i].primaryAccountNumber)==0){
			accountRef=i;
			return SERVER_OK;
		}
	}
	accountRef=0;
	return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void){

	ST_cardData_t cardData;

	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: isValidAccount\n");

	printf("\nTest Case 1: Non-valid account\n");
	strcpy(cardData.primaryAccountNumber,"1234567890123456");
	printf("Input Data: 1234567890123456\n");
	printf("Expected Result: %d \n",ACCOUNT_NOT_FOUND);
	printf("Actual Result: %d \n", isValidAccount(&cardData, accountsDB));

	printf("\nTest Case 2: valid account\n");
	strcpy(cardData.primaryAccountNumber,"4003600000000014");
	printf("Input Data: 4003600000000014\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", isValidAccount(&cardData, accountsDB));
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){

	if((*accountRefrence).state==RUNNING)
		return SERVER_OK;
	else
		return BLOCKED_ACCOUNT;
}

void isBlockedAccountTest(void){

	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: isBlockedAccount\n");

	printf("\nTest Case 1: Non-valid account\n");
	printf("Input Data: 1\n");
	printf("Expected Result: %d \n",BLOCKED_ACCOUNT);
	printf("Actual Result: %d \n", isBlockedAccount(&accountsDB[1]));

	printf("\nTest Case 2: valid account\n");
	printf("Input Data: 0\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", isBlockedAccount(&accountsDB[0]));
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){

	if((*termData).transAmount<=(*accountRefrence).balance)
		return SERVER_OK;
	else
		return LOW_BALANCE;
}

void isAmountAvailableTest(void){

	ST_terminalData_t termData;
	termData.transAmount=5000;
	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: isAmountAvailable\n");

	printf("\nTest Case 1: low balance\n");
	printf("Input Data: 2000\n");
	printf("Expected Result: %d \n",LOW_BALANCE);
	printf("Actual Result: %d \n", isAmountAvailable(&termData, &accountsDB[0]));

	printf("\nTest Case 2: sufficient balance\n");
	printf("Input Data: 100000\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", isAmountAvailable(&termData, &accountsDB[1]));
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){

	if(sequence_number>=255) return SAVING_FAILED;
	(*transData).transactionSequenceNumber=++sequence_number;
	transactionsDB[(*transData).transactionSequenceNumber-1].cardHolderData=(*transData).cardHolderData;
	transactionsDB[(*transData).transactionSequenceNumber-1].terminalData=(*transData).terminalData;
	transactionsDB[(*transData).transactionSequenceNumber-1].transState=(*transData).transState;
	transactionsDB[(*transData).transactionSequenceNumber-1].transactionSequenceNumber=(*transData).transactionSequenceNumber;

	return SERVER_OK;
}

void saveTransactionTest(void){
	
	ST_transaction_t transData;

	printf("Tester Name: Mahmoud Salah\n");
	printf("Function Name: saveTransaction\n");

	transData.cardHolderData=(ST_cardData_t){.cardHolderName="MAHMOUD SALAH ABDULLAH", 
												.primaryAccountNumber="1234567890123456", 
												.cardExpirationDate="05/20"};
	transData.terminalData=(ST_terminalData_t){.transAmount=2000, 
												.maxTransAmount=20000, 
												.transactionDate="31/12/2022"};
	transData.transState=FRAUD_CARD;
	printf("\nTest Case 1: low balance\n");
	printf("Input Data:{\"MAHMOUD SALAH ABDULLAH\",\"1234567890123456\",\"05/20\"},{2000,20000,\"31/12\"},FRAUD_CARD,1\n");
	printf("Expected Result: %d \n",SERVER_OK);
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("SequenceNumber: %d \n",transData.transactionSequenceNumber);

	transData.cardHolderData=(ST_cardData_t){.cardHolderName="MOHAMED SALAH ABDULLAH", 
												.primaryAccountNumber="5807007076043875", 
												.cardExpirationDate="12/24"};
	transData.terminalData=(ST_terminalData_t){.transAmount=5000, 
												.maxTransAmount=20000, 
												.transactionDate="31/12/2022"};
	transData.transState=DECLINED_STOLEN_CARD;
	printf("\nTest Case 2: sufficient balance\n");
	printf("Input Data: 100000\n");
	printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("SequenceNumber: %d \n",transData.transactionSequenceNumber);

}

void listSavedTransactions(void){

	int i;
	for(i=0;i<sequence_number;i++){
		printf("\n#########################\n");
		printf("Transaction Sequence Number: %d\n",i+1);
		printf("Transaction Date: %s\n",transactionsDB[i].terminalData.transactionDate);
		printf("Transaction Amount: %.2f\n",transactionsDB[i].terminalData.transAmount);
		printf("Transaction State: %d\n",transactionsDB[i].transState);
		printf("Terminal Max Amount: %.2f\n",transactionsDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n",transactionsDB[i].cardHolderData.cardHolderName);
		printf("PAN: %s\n",transactionsDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n",transactionsDB[i].cardHolderData.cardExpirationDate);
		printf("#########################\n");
	}
}

void listSavedTransactionsTest(void){

	saveTransactionTest();
	listSavedTransactions();
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
	if(isValidAccount(&(*transData).cardHolderData, accountsDB)==ACCOUNT_NOT_FOUND){
		(*transData).transState=FRAUD_CARD;
		return FRAUD_CARD;
	}else if(isBlockedAccount(&accountsDB[accountRef])==BLOCKED_ACCOUNT){
		(*transData).transState=DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}else if(isAmountAvailable(&(*transData).terminalData, &accountsDB[accountRef])==LOW_BALANCE){
		(*transData).transState=DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}else if(saveTransaction(transData)==SAVING_FAILED){
		(*transData).transState=INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	accountsDB[accountRef].balance-=(*transData).terminalData.transAmount;
	printf("\nYour new balance now is: %.2f\n", accountsDB[accountRef].balance);

	return APPROVED;
}

void recieveTransactionDataTest(void){

	ST_transaction_t transData;
	printf("Tester Name: Mahmoud Salah \n");
	printf("Function Name: recieveTransactionData\n");
	
	printf("\nTest Case 1: Fraud card\n");
	transData.cardHolderData=(ST_cardData_t){.cardHolderName="MAHMOUD SALAH ABDULLAH",
											 .primaryAccountNumber="1234567890123456",
											  .cardExpirationDate="05/23"};
	transData.terminalData=(ST_terminalData_t){.transAmount=2000, 
												.maxTransAmount=20000, 
												.transactionDate="31/12/2022"};
	printf("Input Data:{\"MAHMOUD SALAH ABDULLAH\",\"1234567890123456\",\"05/20\"},{2000,20000,\"31/12\"}\n");
	printf("Expected Result: %d\n",FRAUD_CARD);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));

	printf("\nTest Case 2: BLOCKED ACCOUNT\n");
	transData.cardHolderData=(ST_cardData_t){.cardHolderName="MOHAMED SALAH ABDULLAH", 
												.primaryAccountNumber="5807007076043875", 
												.cardExpirationDate="12/24"};
	transData.terminalData=(ST_terminalData_t){.transAmount=5000, 
												.maxTransAmount=20000, 
												.transactionDate="31/12/2022"};
	printf("Input Data:{\"MOHAMED SALAH ABDULLAH\",\"5807007076043875\",\"12/24\"},{5000,20000,\"31/12\"}\n");
	printf("Expected Result: %d\n", DECLINED_STOLEN_CARD);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));

	printf("\nTest Case 3: INSUFFECIENT FUND \n");
	transData.cardHolderData=(ST_cardData_t){.cardHolderName="SALEH ABDULLAH ABDELAATY", 
												.primaryAccountNumber="3379513561108795", 
												.cardExpirationDate="11/25"};
	transData.terminalData=(ST_terminalData_t){.transAmount=5000, 
												.maxTransAmount=20000, 
												.transactionDate="31/12/2022"};
	printf("Input Data:{\" SALEH ABDULLAH ABDELAATY\",\"3379513561108795\",\"11/25\"},{5000,20000,\"31/12\"}\n");
	printf("Expected Result: %d\n", DECLINED_INSUFFECIENT_FUND);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));

	printf("\nTest Case 4: Approved \n");
	transData.cardHolderData=(ST_cardData_t){.cardHolderName="SALAH ABDULLAH ABDELAATY", 
												.primaryAccountNumber="8989374615436851", 
												.cardExpirationDate="12/25"};
	transData.terminalData=(ST_terminalData_t){.transAmount=1000, 
												.maxTransAmount=20000, 
												.transactionDate="31/12/2022"};
	printf("Input Data:{\" SALAH ABDULLAH ABDELAATY\",\"8989374615436851\",\"12/25\"},{1000,20000,\"31/12\"}\n");
	printf("Expected Result: %d\n", APPROVED);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));

}