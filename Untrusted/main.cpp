#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include "sgx_urts.h"
#include "Teechaindemo_u.h"
#include "Account.h"
#include "ethcontract.h"
#include "Client.h"
#include "Server.h"
using namespace std;

#define ENCLAVE_FILE _T("Teechaindemo.signed.dll")
#define MAX_BUF_LEN 100


void ocall_eth_transaction(char* account,int amount) {

	
	char transaction_account[] = "0x55161ff956E763759ffbbC35F110C71214a6F2f7";
	char transaction_private_key[] = "43477f8ad781b0536c7db95d3d17f9a2890057c91652380547a76014388ab9e9";
	char* result = eth_transaction(transaction_account, account, transaction_private_key, amount);
	cout << result << endl;
}


void ocall_print_string(const char* str) {
	printf("%s", str);
}

void printAndChooseCommand() {
	cout << ("Command Help\n"
		"Setup Account:0\n"
		"Show Account:1\n"
		"Setup Server:2\n"
		"Setup Client:3\n"
		"Release Deposite:4"
		) << endl;
	int command;
	while (cin >> command)
	{
		switch (command)
		{
		case 0:
			SetupAccount();
			break;
		case 1:
			Ecall_ShowAccount(Eid);
			break;
		case 2:
			setupServer();
			break;
		case 3:
			setupClient();
			break;
		case 4:
			Release();
		default:
			break;
		}
	}
}




//入口函数

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
	cout << Eid << endl;
	// An Enclave call (ECALL) will happen here.
	foo(eid, buffer, MAX_BUF_LEN);
	printf("%s", buffer);
	cout << endl;
	printAndChooseCommand();
	//ethcontract测试
	/*
	char transaction_account[] = "0x701E6978C946698a0E67CEd4f334f07C864d43db";
	char receiving_account[] = "0x0c683e9122aa7a43e7844b13f898A17198FfE7CE";
	char transaction_private_key[] = "0b3a159c5f437c3ce65c1682071888c169c9fadf1bd6ca9f0b5d399c68f97f69";
	Py_Initialize();
	char* result = eth_transaction(transaction_account, receiving_account, transaction_private_key, 1);
	cout << result << endl;
	char txhash[] = "0x676280e8fb2bf73d893876a76f2bdb5f04f5abd18d80819d19cb4a4e62e566c0";
	int a = eth_query_transaction(txhash);
	cout << a << endl;
	*/
	
	//Py_Finalize();
	// Destroy the enclave when all Enclave calls finished.


	if (SGX_SUCCESS != sgx_destroy_enclave(eid))
		return -1;
	return 0;
	
	
	
	


	
	
	
	
	
	
}

