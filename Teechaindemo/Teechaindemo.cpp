#include "Teechaindemo_t.h"

#include "sgx_trts.h"

#include <string>


using namespace std;

class Account {
public:
	string public_key;
	string private_key;

	string blockchain_address;

	int balance;

	//string channle_list[];


};

Account create_account(string public_key, string private_key, string blockchain_address, int balance) {
	Account account;

	account.public_key = public_key;
	account.private_key = private_key;
	account.blockchain_address = blockchain_address;
	account.balance = balance;

	return account;
	
}

void print(const char* fmt, ...) {
	char buf[BUFSIZ] = { '\0' };
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	ocall_print_string(buf);
}


void foo(char *buf, size_t len) {
	Account a1 = create_account("123456", "78789", "741741", 100);
	const char* p = a1.blockchain_address.c_str();
	print(p);


	const char* secret = "Hello Enclave!";
	if (len > strlen(secret))
	{
		memcpy(buf, secret, strlen(secret) + 1);
		print("successful");
	}

}

