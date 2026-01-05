package blockchain;

import java.util.*;

import exceptionbc.TransactionException;
import interfacebc.IMessage;
import interfacebc.IMiningMethod;
import interfacebc.IValidateMethod;

/**
 * Represents a node in a blockchain network.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class Node extends Net {
	/**
	 * The wallet of the node.
	 */
	private Wallet wallet;

	/**
	 * The list of transactions of the node.
	 */
	private List<Transaction> transactions = new LinkedList<Transaction>();

	/**
	 * Creates a new node.
	 * 
	 * @param w The wallet of the node.
	 */
	public Node(Wallet w) {
		super();
		this.wallet = w;
	}

	/**
	 * Returns the name of the node.
	 * 
	 * @return The name of the node.
	 */
	public String fullName() {

		return String.format("Node#%03d", this.id);
	}

	/**
	 * Processes a message.
	 * 
	 * @param msg The message to process.
	 */
	@Override
	public void broadcast(IMessage msg) {
		msg.process(this);
	}

	/**
	 * Adds a transaction to the node.
	 * 
	 * @param t The transaction to add.
	 * 
	 */
	public void addTransaction(Transaction t) {
		transactions.add(t);
	}

	/**
	 * Checks if the node contains a transaction.
	 * 
	 * @param t The transaction to check.
	 * 
	 * @return The transaction to check.
	 */
	public boolean containsTransaction(Transaction t) {
		return transactions.contains(t);
	}

	/**
	 * Returns the public key of the wallet of the node.
	 * 
	 * @return The public key of the wallet of the node.
	 */
	public String getPublicKey() {
		return this.wallet.getPublicKey();
	}

	/**
	 * Returns the id of the node.
	 * 
	 * @return The id of the node.
	 */
	public Integer getId() {
		return this.id;
	}

	/**
	 * Checks if the node has mined a block.
	 * 
	 * @param block The block to check.
	 * 
	 * @return True if the node has mined a block, false otherwise.
	 */
	public boolean minedBlock(Block block) {
		return true;
	}

	/**
	 * Checks if the node contains a node.
	 */
	public boolean contains(Node n) {
		return false;
	}

	/**
	 * Prints the node.
	 * 
	 * @return The node as a string.
	 */
	@Override
	public String toString() {
		return "u: " + this.wallet.getUsername() + ", PK:" + this.wallet.getPublicKey() + ", balance: "
				+ this.wallet.getBalance() + " | @" + this.fullName();
	}

	/**
	 * Creates a transaction given a wallet and a value.
	 * 
	 * @param wallet2 The wallet to send the transaction to.
	 * @param value   The value of the transaction.
	 * 
	 * @return The transaction created.
	 * @throws TransactionException If the value is less than or equal to 0 or if
	 *                              the
	 */
	public Transaction createTransaction(Wallet wallet2, Integer value) throws TransactionException {
		if (value <= 0 || this.wallet.getBalance() - value < 0) {
			throw new TransactionException(this.wallet.getPublicKey(), wallet2.getPublicKey(), value);
		}
		Transaction t = new Transaction(this.wallet.getPublicKey(), wallet2.getPublicKey(), value);
		return t;
	}

	/**
	 * Creates a transaction given a key and a value.
	 * 
	 * @param key   The key of the wallet to send the transaction to.
	 * @param value The value of the transaction.
	 * 
	 * @return The transaction created.
	 * @throws TransactionException If the value is less than or equal to 0 or if
	 *                              the
	 */
	public Transaction createTransaction(String key, Integer value) throws TransactionException {
		if (value <= 0 || this.wallet.getBalance() - value < 0) {
			throw new TransactionException(this.wallet.getPublicKey(), key, value);
		}
		Transaction t = new Transaction(this.wallet.getPublicKey(), key, value);
		return t;
	}

	/**
	 * Returns the mining method: in this case, null.
	 * 
	 * @return Null.
	 */
	public IMiningMethod getMiningMethod() {
		return null;
	}

	/**
	 * Returns the last block mined by the node: in this case, null.
	 * 
	 * @return Null.
	 */
	public Block getLastBlock() {
		return null;
	}

	/**
	 * Returns the validation method: in this case, null.
	 * 
	 * @return Null.
	 */
	public IValidateMethod getValidateMethod() {
		return null;
	}

	/**
	 * Mines a new block.
	 * 
	 * @param transaction The transaction to mine.
	 */
	public void mine(Transaction transaction) {
		return;
	}

	/**
	 * Validates a block.
	 * 
	 * @param block The block to validate.
	 */
	public void validate(Block block) {
		return;
	}

	/**
	 * Commits a transaction.
	 * 
	 * @param tr The transaction to commit.
	 */
	public void commitTransaction(Transaction tr) {
		System.out.println(
				"[" + this.fullName() + "] Commiting transaction : Tx-" + tr.getId() + " in " + this.fullName());
		System.out.println("[" + this.fullName() + "]" + tr.details());
		this.transactions.add(tr);
		if (tr.getOrigin().equals(this.wallet.getPublicKey())) {
			this.wallet.updateBalance(-tr.getValue());
			System.out.println("[" + this.fullName() + "] Applied Transaction: " + tr.toString());
			System.out.println("[" + this.fullName() + "] New wallet value: " + this.wallet.toString());
		} else if (tr.getDestination().equals(this.wallet.getPublicKey())) {
			this.wallet.updateBalance(tr.getValue());
			System.out.println("[" + this.fullName() + "] Applied Transaction: " + tr.toString());
			System.out.println("[" + this.fullName() + "] New wallet value: " + this.wallet.toString());
		}
	}
}
