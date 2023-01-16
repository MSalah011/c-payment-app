#ifndef APP_H
#define APP_H
#include <stdint.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

void appStart(void);

extern ST_accountsDB_t accountsDB[];

#endif