package blockchain.message;

import blockchain.*;
import interfacebc.IMessage;

/**
 * Represents a transaction notification.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class TransactionNotification implements IMessage {
	/**
	 * The transaction of the notification.
	 */
	private Transaction transaction;

	/**
	 * Creates a transaction notification.
	 * 
	 * @param transaction The transaction of the notification.
	 */
	public TransactionNotification(Transaction transaction) {
		this.transaction = transaction;
	}

	/**
	 * Processes the message.
	 * 
	 * @param n The node that receives the message.
	 */
	@Override
	public void process(Node n) {
		IMessage.super.process(n);
		if (!n.containsTransaction(transaction)) {
			n.mine(this.transaction);
		} else {
			System.out.println("[" + n.fullName() + "] Transaction already confirmed: Tx-" + transaction.getId());
		}
	}

	/**
	 * Returns the message.
	 * 
	 * @return The message.
	 */
	@Override
	public String getMessage() {
		return transaction.toString();
	}
}
