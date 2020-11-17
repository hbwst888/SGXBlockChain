#pragma once
#include<Python.h> 
#include<iostream>
#include <direct.h>
#include <string.h>

using namespace std;

//调用python函数时先初始化，调用结束后结束初始化
//Py_Initialize(); Python接口初始化
//Py_Finalize(); 结束初始化

string getpath() {
	//设置路径
	string local_path;
	string path = "sys.path.append('";
	string a = "')";
	int p;
	local_path = _getcwd(NULL, 0);
	p = local_path.rfind("\\");
	local_path.replace(p, local_path.length() - p, "\\ethcontract");
	path.append(local_path).append(a);
	int position = path.find("\\");

	while (position > 0) {
		path.replace(position, 1, "/");
		position = path.find("\\");
	}
	cout << path << endl;
	return path;
}

//执行交易，判断余额是否充足，不充足返回0
//余额充足情况下，若上一笔交易未上链返回0
//交易成功返回交易哈希
char* eth_transaction(char* transaction_account, char* receiving_account, char* transaction_private_key, int amount) {


	PyObject* pModule = NULL;
	PyObject* pFunc = NULL;
	PyObject* pName = NULL;

	string path = getpath();
	
	PyRun_SimpleString("import os,sys");
	PyRun_SimpleString(path.data());
	

	//调用python文件名
	pModule = PyImport_ImportModule("ethcontract");

	//调用函数
	pFunc = PyObject_GetAttrString(pModule, "transaction");

	//给python传参数
	PyObject* pArgs = PyTuple_New(4);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", transaction_account)); 
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", receiving_account));
	PyTuple_SetItem(pArgs, 2, Py_BuildValue("s", transaction_private_key));
	PyTuple_SetItem(pArgs, 3, Py_BuildValue("i", amount)); 

	//调用该函数
	PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);

	//接收python计算好的返回值
	char* txhash;
	PyArg_Parse(pReturn, "s", &txhash);

	Py_DECREF(pArgs);
	return txhash;
}


//输入交易哈希判断交易是否成功上链，成功返回1，失败返回0
int eth_query_transaction(char* txhash) {

	PyObject* pModule = NULL;
	PyObject* pFunc = NULL;
	PyObject* pName = NULL;

	string path = getpath();

	PyRun_SimpleString("import os,sys");
	PyRun_SimpleString(path.data());
	
	//调用python文件名。
	pModule = PyImport_ImportModule("ethcontract");

	//调用函数名
	pFunc = PyObject_GetAttrString(pModule, "is_transaction_success");

	//给python传参数
	PyObject* pArgs = PyTuple_New(1);//参数个数
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", txhash)); //参数。

	//调用函数
	PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);
	
	//接收python计算好的返回值
	int result;
	PyArg_Parse(pReturn, "i", &result);//i表示转换成int型变量。在这里，最需要注意的是：PyArg_Parse的最后一个参数，必须加上“&”符号。
	cout << result << endl;

	Py_DECREF(pArgs);
	return result;
}

