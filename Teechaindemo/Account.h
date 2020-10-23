#pragma once
#include "Teechaindemo_t.h"

#include "sgx_trts.h"

#include <string>

using namespace std;

//ocall打印输出
void print(const char* fmt, ...) {
	char buf[BUFSIZ] = { '\0' };
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	ocall_print_string(buf);
}

//teechain中的账户
class Account {
public:
	char* public_key;
	char* private_key;

	//string blockchain_address;

	unsigned long long deposit_amount;

	//string channle_list[];


};
Account local_Account;


//测试 创建账户
void Ecall_SetupAccount(char* Public_Key ,char* Private_Key, unsigned long long Deposit_Amount) {
	//这里应该通过执行智能合约来将用户在区块链上的的金额转入系统账户
	//先模拟
	
	local_Account.public_key = Public_Key;
	local_Account.private_key = Private_Key;
	local_Account.deposit_amount = Deposit_Amount;
	print("kkkk");
}


//创建账户
//Account create_account(string public_key, string private_key, string blockchain_address, int deposit_amount) {
//	Account account;
//
//	account.public_key = public_key;
//	account.private_key = private_key;
//	account.blockchain_address = blockchain_address;
//	account.deposit_amount = deposit_amount;
//
//	return account;
//
//}
//
////添加存款
//void add_deposite(Account& account, int deposite) {
//	account.deposit_amount += deposite;
//}
//
////释放存款ssss
//void release_deposite(Account& account) {
//	account.deposit_amount = 0;
//}
//
////确定存款是否充足
//bool is_deposite_enough(Account& account, int need_deposite) {
//	if (account.deposit_amount >= need_deposite) {
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}




