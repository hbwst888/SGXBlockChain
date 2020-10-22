#include "Teechaindemo_t.h"

#include "sgx_trts.h"

#include <string>
#include "Account.h"
using namespace std;



//²âÊÔÎÄ¼þ
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

