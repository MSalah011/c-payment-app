#include <stdio.h>
#include "app.h"

ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction_t transData;


void appStart(void){
	char sel;
	while(1){
		do{
			printf("Please enter cardholder name as on card.\n");
			printf("Cardholder name:");
		}while(getCardHolderName(&cardData));

		do{
			printf("Please enter card expiry date on format MM/YY\n");
			printf("Date:");
		}while(getCardExpiryDate(&cardData));

		do{
			printf("Please enter PAN.\n");
			printf("PAN:");
		}while(getCardPAN(&cardData));

		do{
			printf("Please enter transaction date on format DD/MM/YYYY\n");
			printf("Date:");
		}while(getTransactionDate(&termData));

		if(isCardExpired(&cardData,&termData)==TERMINAL_OK){

			do{
				printf("Please enter transaction amount:");
			}while(getTransactionAmount(&termData));

			setMaxAmount(&termData, 20000);

			if(isBelowMaxAmount(&termData)==TERMINAL_OK){

				transData.cardHolderData = cardData;
				transData.terminalData = termData;

				switch(recieveTransactionData(&transData)){
				case 0:
					 listSavedTransactions();
					break;
				case 1:
					printf("Declined Insufficient Funds\n");
					break;
				case 2:
					printf("Declined Stolen Card\n");
					break;
				case 3:
					printf("Declined Invalid Account\n");
					break;
				case 4:
					printf("INTERNAL SERVER ERROR\n");
					break;
				}

			}else{
				printf("Declined Amount Exceeding Limit\n");
			}
		}else{
			printf("Declined Expired Card\n");
		}
		printf("Do you want to Quit ?\nPlease type (Y):");
		fflush(stdin);
		scanf("%c",&sel);
		if(sel=='Y'||sel=='y')break;
	}

}
