#pragma once
#include "Teechaindemo_t.h"

#include "sgx_trts.h"

#include <string>

using namespace std;

//ocall��ӡ���
void print(const char* fmt, ...) {
	char buf[BUFSIZ] = { '\0' };
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	ocall_print_string(buf);
}

//teechain�е��˻�
class Account {
public:
	char* public_key;
	char* private_key;

	//string blockchain_address;

	unsigned long long deposit_amount;

	//string channle_list[];


};
Account local_Account;


//���� �����˻�
void Ecall_SetupAccount(char* Public_Key ,char* Private_Key, unsigned long long Deposit_Amount) {
	//����Ӧ��ͨ��ִ�����ܺ�Լ�����û����������ϵĵĽ��ת��ϵͳ�˻�
	//��ģ��
	
	local_Account.public_key = Public_Key;
	local_Account.private_key = Private_Key;
	local_Account.deposit_amount = Deposit_Amount;
	print("kkkk");
}


//�����˻�
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
////��Ӵ��
//void add_deposite(Account& account, int deposite) {
//	account.deposit_amount += deposite;
//}
//
////�ͷŴ��ssss
//void release_deposite(Account& account) {
//	account.deposit_amount = 0;
//}
//
////ȷ������Ƿ����
//bool is_deposite_enough(Account& account, int need_deposite) {
//	if (account.deposit_amount >= need_deposite) {
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}




