#ifndef _MONEY_H_
#define _MONEY_H_

#define USER_MONEY_MAX 1000000000 // 1 billion

extern int BBS_user_money;

extern int money_balance();
extern int money_deposit(int money);
extern int money_withdraw(int money);
extern int money_refresh(void);

#endif
