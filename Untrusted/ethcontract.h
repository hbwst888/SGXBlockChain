#pragma once
#include<Python.h> 
#include<iostream>
#include <direct.h>
#include <string.h>

using namespace std;

//����python����ʱ�ȳ�ʼ�������ý����������ʼ��
//Py_Initialize(); Python�ӿڳ�ʼ��
//Py_Finalize(); ������ʼ��

string getpath() {
	//����·��
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

//ִ�н��ף��ж�����Ƿ���㣬�����㷵��0
//����������£�����һ�ʽ���δ��������0
//���׳ɹ����ؽ��׹�ϣ
char* eth_transaction(char* transaction_account, char* receiving_account, char* transaction_private_key, int amount) {


	PyObject* pModule = NULL;
	PyObject* pFunc = NULL;
	PyObject* pName = NULL;

	string path = getpath();
	
	PyRun_SimpleString("import os,sys");
	PyRun_SimpleString(path.data());
	

	//����python�ļ���
	pModule = PyImport_ImportModule("ethcontract");

	//���ú���
	pFunc = PyObject_GetAttrString(pModule, "transaction");

	//��python������
	PyObject* pArgs = PyTuple_New(4);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", transaction_account)); 
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", receiving_account));
	PyTuple_SetItem(pArgs, 2, Py_BuildValue("s", transaction_private_key));
	PyTuple_SetItem(pArgs, 3, Py_BuildValue("i", amount)); 

	//���øú���
	PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);

	//����python����õķ���ֵ
	char* txhash;
	PyArg_Parse(pReturn, "s", &txhash);

	Py_DECREF(pArgs);
	return txhash;
}


//���뽻�׹�ϣ�жϽ����Ƿ�ɹ��������ɹ�����1��ʧ�ܷ���0
int eth_query_transaction(char* txhash) {

	PyObject* pModule = NULL;
	PyObject* pFunc = NULL;
	PyObject* pName = NULL;

	string path = getpath();

	PyRun_SimpleString("import os,sys");
	PyRun_SimpleString(path.data());
	
	//����python�ļ�����
	pModule = PyImport_ImportModule("ethcontract");

	//���ú�����
	pFunc = PyObject_GetAttrString(pModule, "is_transaction_success");

	//��python������
	PyObject* pArgs = PyTuple_New(1);//��������
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", txhash)); //������

	//���ú���
	PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);
	
	//����python����õķ���ֵ
	int result;
	PyArg_Parse(pReturn, "i", &result);//i��ʾת����int�ͱ��������������Ҫע����ǣ�PyArg_Parse�����һ��������������ϡ�&�����š�
	cout << result << endl;

	Py_DECREF(pArgs);
	return result;
}

