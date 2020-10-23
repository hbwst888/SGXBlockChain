#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include "sgx_urts.h"
#include "Teechaindemo_u.h"
#include "Account.h"
using namespace std;

#define ENCLAVE_FILE _T("Teechaindemo.signed.dll")
#define MAX_BUF_LEN 100



void ocall_print_string(const char* str) {
	printf("%s", str);
}

void printAndChooseCommand() {
	cout << ("Command Help\n"
		"Setup Account:0\n"
		) << endl;
	int command;

	while (cin >> command)
	{
		switch (command)
		{
		case 0:
			SetupAccount();
		default:
			break;
		}
	}
}




//入口函
int main() {
	sgx_enclave_id_t eid;
	sgx_status_t ret = SGX_SUCCESS;
	sgx_launch_token_t token = { 0 };
	int updated = 0;
	char buffer[MAX_BUF_LEN] = "Hello World!";
	// Create the Enclave with above launch token.
	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
	if (ret != SGX_SUCCESS) {
		printf("App: error %#x, failed to create enclave.\n", ret);
		return -1;
	}
	Eid = eid;
	// An Enclave call (ECALL) will happen here.
	foo(eid, buffer, MAX_BUF_LEN);
	printf("%s", buffer);
	cout << endl;
	printAndChooseCommand();
	
	// Destroy the enclave when all Enclave calls finished.
	if (SGX_SUCCESS != sgx_destroy_enclave(eid))
		return -1;
	return 0;
}