#include "Teechaindemo_u.h"
#include <errno.h>

typedef struct ms_foo_t {
	char* ms_buf;
	size_t ms_len;
} ms_foo_t;

typedef struct ms_Ecall_SetupAccount_t {
	const char* ms_Public_Key;
	char* ms_Private_Key;
	unsigned long long ms_Deposit_Amount;
} ms_Ecall_SetupAccount_t;

typedef struct ms_Ecall_LaunchTransaction_t {
	int ms_retval;
	unsigned long long ms_Transaction_Amount;
} ms_Ecall_LaunchTransaction_t;

typedef struct ms_Ecall_ReceiveTransaction_t {
	int ms_retval;
	unsigned long long ms_Transaction_Amount;
} ms_Ecall_ReceiveTransaction_t;

typedef struct ms_ocall_print_string_t {
	const char* ms_str;
} ms_ocall_print_string_t;

typedef struct ms_sgx_oc_cpuidex_t {
	int* ms_cpuinfo;
	int ms_leaf;
	int ms_subleaf;
} ms_sgx_oc_cpuidex_t;

typedef struct ms_sgx_thread_wait_untrusted_event_ocall_t {
	int ms_retval;
	const void* ms_self;
} ms_sgx_thread_wait_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_set_untrusted_event_ocall_t {
	int ms_retval;
	const void* ms_waiter;
} ms_sgx_thread_set_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_setwait_untrusted_events_ocall_t {
	int ms_retval;
	const void* ms_waiter;
	const void* ms_self;
} ms_sgx_thread_setwait_untrusted_events_ocall_t;

typedef struct ms_sgx_thread_set_multiple_untrusted_events_ocall_t {
	int ms_retval;
	const void** ms_waiters;
	size_t ms_total;
} ms_sgx_thread_set_multiple_untrusted_events_ocall_t;

static sgx_status_t SGX_CDECL Teechaindemo_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string(ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Teechaindemo_sgx_oc_cpuidex(void* pms)
{
	ms_sgx_oc_cpuidex_t* ms = SGX_CAST(ms_sgx_oc_cpuidex_t*, pms);
	sgx_oc_cpuidex(ms->ms_cpuinfo, ms->ms_leaf, ms->ms_subleaf);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Teechaindemo_sgx_thread_wait_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_wait_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_wait_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_wait_untrusted_event_ocall(ms->ms_self);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Teechaindemo_sgx_thread_set_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_set_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_untrusted_event_ocall(ms->ms_waiter);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Teechaindemo_sgx_thread_setwait_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_setwait_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_setwait_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_setwait_untrusted_events_ocall(ms->ms_waiter, ms->ms_self);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Teechaindemo_sgx_thread_set_multiple_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_set_multiple_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_multiple_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_multiple_untrusted_events_ocall(ms->ms_waiters, ms->ms_total);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * func_addr[6];
} ocall_table_Teechaindemo = {
	6,
	{
		(void*)(uintptr_t)Teechaindemo_ocall_print_string,
		(void*)(uintptr_t)Teechaindemo_sgx_oc_cpuidex,
		(void*)(uintptr_t)Teechaindemo_sgx_thread_wait_untrusted_event_ocall,
		(void*)(uintptr_t)Teechaindemo_sgx_thread_set_untrusted_event_ocall,
		(void*)(uintptr_t)Teechaindemo_sgx_thread_setwait_untrusted_events_ocall,
		(void*)(uintptr_t)Teechaindemo_sgx_thread_set_multiple_untrusted_events_ocall,
	}
};

sgx_status_t foo(sgx_enclave_id_t eid, char* buf, size_t len)
{
	sgx_status_t status;
	ms_foo_t ms;
	ms.ms_buf = buf;
	ms.ms_len = len;
	status = sgx_ecall(eid, 0, &ocall_table_Teechaindemo, &ms);
	return status;
}

sgx_status_t Ecall_SetupAccount(sgx_enclave_id_t eid, const char* Public_Key, char* Private_Key, unsigned long long Deposit_Amount)
{
	sgx_status_t status;
	ms_Ecall_SetupAccount_t ms;
	ms.ms_Public_Key = Public_Key;
	ms.ms_Private_Key = Private_Key;
	ms.ms_Deposit_Amount = Deposit_Amount;
	status = sgx_ecall(eid, 1, &ocall_table_Teechaindemo, &ms);
	return status;
}

sgx_status_t Ecall_ShowAccount(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 2, &ocall_table_Teechaindemo, NULL);
	return status;
}

sgx_status_t Ecall_LaunchTransaction(sgx_enclave_id_t eid, int* retval, unsigned long long Transaction_Amount)
{
	sgx_status_t status;
	ms_Ecall_LaunchTransaction_t ms;
	ms.ms_Transaction_Amount = Transaction_Amount;
	status = sgx_ecall(eid, 3, &ocall_table_Teechaindemo, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t Ecall_ReceiveTransaction(sgx_enclave_id_t eid, int* retval, unsigned long long Transaction_Amount)
{
	sgx_status_t status;
	ms_Ecall_ReceiveTransaction_t ms;
	ms.ms_Transaction_Amount = Transaction_Amount;
	status = sgx_ecall(eid, 4, &ocall_table_Teechaindemo, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

