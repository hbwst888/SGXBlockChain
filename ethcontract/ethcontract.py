from web3 import Web3
import gc

infura_url = "http://127.0.0.1:7545"
web3 = Web3(Web3.HTTPProvider(infura_url))
# 检查账户余额是否充足
def is_money_enough(transaction_account, amount):
    balance = web3.fromWei(web3.eth.getBalance(transaction_account), 'ether')
    if balance >= amount:
        print("余额充足")
        return 1
    else:
        print("余额不足")
        return 0

# 执行以太坊交易
# 输入交易账户，接收账户，交易账户私钥，交易金额
def transaction(transaction_account, receiving_account, transaction_private_key, amount):
    is_enough = is_money_enough(transaction_account, amount)
    if(is_enough):
        nonce = web3.eth.getTransactionCount(transaction_account)
        tx = {
            'nonce': nonce,
            'to': receiving_account,
            'value': web3.toWei(amount, 'ether'),
            'gas': 2000000,
            'gasPrice': web3.toWei('50', 'gwei'),
        }
        # 私钥签署交易
        signed_tx = web3.eth.account.signTransaction(tx, transaction_private_key)
        # 交易哈希
        try:
            tx_hash = web3.toHex(web3.eth.sendRawTransaction(signed_tx.rawTransaction))
        except ValueError:
            print("上一笔交易未上链")
            gc.collect()
            return 0
        else:
            # 打印交易哈希
            print(tx_hash)
            gc.collect()
            return tx_hash
    else:
        print("余额不足无法进行交易")
        gc.collect()
        return 0

def is_transaction_success(tx_hash):
    try:
        web3.eth.getTransactionReceipt(tx_hash)
    except:
        print("交易未上链")
        gc.collect()
        return 0
    else:
        print("交易成功")
        gc.collect()
        return 1


if __name__ == '__main__':
    #infura_url = "http://127.0.0.1:7545"
    #web3 = Web3(Web3.HTTPProvider(infura_url))
    #practice()
    print(web3.isConnected())
    transaction_account = '0xb34A64432C6Eca44362E36f8dEa9e4f63D1b2508'
    receiving_account = '0x55161ff956E763759ffbbC35F110C71214a6F2f7'
    transaction_private_key = 'fce7b4aec5ed17877e890a7ce030a0abc6794d1f1853f17f3fd90a7ebd08ebf1'
    #print(is_money_enough(transaction_account, 10))

    tx_hash = transaction(transaction_account, receiving_account, transaction_private_key, 1)
    # print(web3.eth.getTransactionReceipt('0x43998e3ac5af6445d9382eaee543b0af4e5d61d2f0e844b0ebc049651c2ef197'))

    is_transaction_success(tx_hash)