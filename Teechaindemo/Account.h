#pragma once
#include "Teechaindemo_t.h"

#include "sgx_trts.h"

#include <string>

using namespace std;

//teechain�е��˻�
class Account {
public:
	string public_key;
	string private_key;

	string blockchain_address;

	int deposit_amount;

	//string channle_list[];


};

//�����˻�
Account create_account(string public_key, string private_key, string blockchain_address, int deposit_amount) {
	Account account;

	account.public_key = public_key;
	account.private_key = private_key;
	account.blockchain_address = blockchain_address;
	account.deposit_amount = deposit_amount;

	return account;

}

//��Ӵ��
void add_deposite(Account& account, int deposite) {
	account.deposit_amount += deposite;
}

//�ͷŴ��ssss
void release_deposite(Account& account) {
	account.deposit_amount = 0;
}

//ȷ������Ƿ����
bool is_deposite_enough(Account& account, int need_deposite) {
	if (account.deposit_amount >= need_deposite) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//ocall��ӡ���
void print(const char* fmt, ...) {
	char buf[BUFSIZ] = { '\0' };
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	ocall_print_string(buf);
}


