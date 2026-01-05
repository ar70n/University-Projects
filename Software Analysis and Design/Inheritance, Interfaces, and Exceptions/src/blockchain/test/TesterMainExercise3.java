package blockchain.test;

import blockchain.*;
import blockchain.message.TransactionNotification;
import blockchain.method.SimpleMining;
import blockchain.method.SimpleValidate;
import exceptionbc.TransactionException;

@SuppressWarnings("unused")

/**
 * Tester for the third exercise.
 * 
 * @author eps
 * @version 1.0
 */
public class TesterMainExercise3 extends TesterMainExercise2 {
	/**
	 * Default constructor.
	 */
	public TesterMainExercise3() {
		super();
	}

	/**
	 * Creates transactions.
	 */
	public void createTransactions() {
		// create a transaction and send it to the network
		this.miningNode.setMiningMethod(new SimpleMining());
		this.miningNode.setValidationMethod(new SimpleValidate());
		this.miningNode2.setMiningMethod(new SimpleMining());
		this.miningNode2.setValidationMethod(new SimpleValidate());
		try {
			network.broadcast(new TransactionNotification(node.createTransaction(wallet2.getPublicKey(), 5)));
		} catch (TransactionException e) {
			e.toString();
		}
	}

	/**
	 * Main method.
	 * 
	 * @param args The arguments.
	 */
	public static void main(String[] args) {
		TesterMainExercise3 tme = new TesterMainExercise3();
		tme.buildNetwork();
		tme.createTransactions();
		System.out.println("End of party!");
	}
}