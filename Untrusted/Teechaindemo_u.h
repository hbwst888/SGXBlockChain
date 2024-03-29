#ifndef TEECHAINDEMO_U_H__
#define TEECHAINDEMO_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OCALL_PRINT_STRING_DEFINED__
#define OCALL_PRINT_STRING_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* str));
#endif
#ifndef OCALL_ETH_TRANSACTION_DEFINED__
#define OCALL_ETH_TRANSACTION_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_eth_transaction, (char* account, int amount));
#endif
#ifndef SGX_OC_CPUIDEX_DEFINED__
#define SGX_OC_CPUIDEX_DEFINED__
void SGX_UBRIDGE(SGX_CDECL, sgx_oc_cpuidex, (int cpuinfo[4], int leaf, int subleaf));
#endif
#ifndef SGX_THREAD_WAIT_UNTRUSTED_EVENT_OCALL_DEFINED__
#define SGX_THREAD_WAIT_UNTRUSTED_EVENT_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_wait_untrusted_event_ocall, (const void* self));
#endif
#ifndef SGX_THREAD_SET_UNTRUSTED_EVENT_OCALL_DEFINED__
#define SGX_THREAD_SET_UNTRUSTED_EVENT_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_untrusted_event_ocall, (const void* waiter));
#endif
#ifndef SGX_THREAD_SETWAIT_UNTRUSTED_EVENTS_OCALL_DEFINED__
#define SGX_THREAD_SETWAIT_UNTRUSTED_EVENTS_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_setwait_untrusted_events_ocall, (const void* waiter, const void* self));
#endif
#ifndef SGX_THREAD_SET_MULTIPLE_UNTRUSTED_EVENTS_OCALL_DEFINED__
#define SGX_THREAD_SET_MULTIPLE_UNTRUSTED_EVENTS_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_multiple_untrusted_events_ocall, (const void** waiters, size_t total));
#endif

sgx_status_t foo(sgx_enclave_id_t eid, char* buf, size_t len);
sgx_status_t Ecall_SetupAccount(sgx_enclave_id_t eid, const char* Public_Key, char* Private_Key, unsigned long long Deposit_Amount);
sgx_status_t Ecall_ShowAccount(sgx_enclave_id_t eid);
sgx_status_t Ecall_LaunchTransaction(sgx_enclave_id_t eid, int* retval, unsigned long long Transaction_Amount);
sgx_status_t Ecall_ReceiveTransaction(sgx_enclave_id_t eid, int* retval, unsigned long long Transaction_Amount);
sgx_status_t Ecall_release_deposit(sgx_enclave_id_t eid, unsigned long long amount);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
