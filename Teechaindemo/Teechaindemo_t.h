#ifndef TEECHAINDEMO_T_H__
#define TEECHAINDEMO_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void foo(char* buf, size_t len);
void Ecall_SetupAccount(const char* Public_Key, char* Private_Key, unsigned long long Deposit_Amount);
void Ecall_ShowAccount(void);
int Ecall_LaunchTransaction(unsigned long long Transaction_Amount);
int Ecall_ReceiveTransaction(unsigned long long Transaction_Amount);
void Ecall_release_deposit(unsigned long long amount);

sgx_status_t SGX_CDECL ocall_print_string(const char* str);
sgx_status_t SGX_CDECL ocall_eth_transaction(char* account, int amount);
sgx_status_t SGX_CDECL sgx_oc_cpuidex(int cpuinfo[4], int leaf, int subleaf);
sgx_status_t SGX_CDECL sgx_thread_wait_untrusted_event_ocall(int* retval, const void* self);
sgx_status_t SGX_CDECL sgx_thread_set_untrusted_event_ocall(int* retval, const void* waiter);
sgx_status_t SGX_CDECL sgx_thread_setwait_untrusted_events_ocall(int* retval, const void* waiter, const void* self);
sgx_status_t SGX_CDECL sgx_thread_set_multiple_untrusted_events_ocall(int* retval, const void** waiters, size_t total);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
