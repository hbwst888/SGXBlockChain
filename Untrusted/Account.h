#pragma once
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include "sgx_urts.h"
#include "Teechaindemo_u.h"
#include "ethcontract.h"

using namespace std;

sgx_enclave_id_t Eid;


char* Public_Key = new char[200];
char* Private_Key = new char[200];
unsigned long long amount;

void SetupAccount() {
	cout << "Public key:" << endl;
	cin >> Public_Key;
	//const char* a = Public_Key;
	cout << "Private key:" << endl;
	cin >> Private_Key;
	cout << "Amount:" << endl;
	cin >> amount;
	Py_Initialize();
	char receiving_account[] = "0xA28e0005420eA9CeA80aF42841351B1549679D02";
	char* isaccount = eth_verify_account(Public_Key, amount);
	while (strcmp("right", isaccount) != 0) {
		if (strcmp("wrong1", isaccount) == 0) {
			cout << "余额不足请重新输入" << endl;
			cout << "Amount:" << endl;
			cin >> amount;
		}
		else if (strcmp("wrong2", isaccount) == 0) {
			cout << "账户地址不存在,请重新输入" << endl;
			cout << "Public key:" << endl;
			cin >> Public_Key;
		}
		isaccount = eth_verify_account(Public_Key, amount);
	}
	char* result = eth_transaction(Public_Key, receiving_account, Private_Key, amount);
	if (strcmp("wrong", result) == 0) {
		cout << "存在交易未执行" << endl;
	}
	else {
		cout << "存款成功" << endl;
	}
	
	Ecall_SetupAccount(Eid, Public_Key, Private_Key, amount);
}