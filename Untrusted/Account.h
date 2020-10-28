#pragma once
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include "sgx_urts.h"
#include "Teechaindemo_u.h"

using namespace std;

sgx_enclave_id_t Eid;


char* Public_Key = new char[20];
char* Private_Key = new char[20];
unsigned long long amount;

void SetupAccount() {
	cout << "Public key:" << endl;

	cin >> Public_Key;
	cout << "Private key:" << endl;
	cin >> Private_Key;
	cout << "Amount:" << endl;
	cin >> amount;
	Ecall_SetupAccount(Eid, Public_Key, Private_Key, amount);
}