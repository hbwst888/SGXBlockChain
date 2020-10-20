#include "Teechaindemo_t.h"

#include "sgx_trts.h"

#include <string>


using namespace std;

class Account {
public:
	string public_key;
	string private_key;

	string blockchain_address;

	int deposit_amount;

	//string channle_list[];


};

//创建函数
Account create_account(string public_key, string private_key, string blockchain_address, int deposit_amount) {
	Account account;

	account.public_key = public_key;
	account.private_key = private_key;
	account.blockchain_address = blockchain_address;
	account.deposit_amount = deposit_amount;

	return account;
	
}

//添加存款
void add_deposite(Account& account, int deposite) {
	account.deposit_amount += deposite;
}

//释放存款
void release_deposite(Account& account) {
	account.deposit_amount = 0;
}

//确定存款是否充足
bool is_deposite_enough(Account& account, int need_deposite) {
	if (account.deposit_amount >= need_deposite) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//ocall打印输出
void print(const char* fmt, ...) {
	char buf[BUFSIZ] = { '\0' };
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	ocall_print_string(buf);
}



//测试文件
void foo(char *buf, size_t len) {
	Account a1 = create_account("123456", "78789", "741741", 100);
	add_deposite(a1, 20);

	bool k = is_deposite_enough(a1, 130);
	bool l = is_deposite_enough(a1, 100);
	const char* p = a1.blockchain_address.c_str();
	print(p);
	if (k == 1) {
		print("true");
	}
	else
	{
		print("false");
	}
	if (l == 1) {
		print("true");
	}
	else
	{
		print("false");
	}
	release_deposite(a1);
	if (a1.deposit_amount == 0) {
		print("true");
	}
	else
	{
		print("false");
	}

	const char* secret = "Hello Enclave!";
	if (len > strlen(secret))
	{
		memcpy(buf, secret, strlen(secret) + 1);
		print("successful");
	}
	
	

}

