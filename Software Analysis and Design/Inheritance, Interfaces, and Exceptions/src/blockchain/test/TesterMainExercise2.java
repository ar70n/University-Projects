package blockchain.test;

import blockchain.*;
import blockchain.message.TransactionNotification;
import exceptionbc.*;

/**
 * Tester for the second exercise.
 * 
 * @author eps
 * @version 1.0
 */
public class TesterMainExercise2 extends TesterMainExercise1 {
	/**
	 * Default constructor.
	 */
	TesterMainExercise2() {
		super();
	}

	/**
	 * Builds a faulty network.
	 */
	public void buildFaultyNetwork() {
		super.buildNetwork();
		try {
			this.network.connect(this.node); // cannot connect: node already in the network
		} catch (ConnectionException e) {
			System.err.println(e);
		} catch (Exception e) {
			System.err.println(e);
		}
		try {
			this.network.connect(this.miningNode2); // cannot connect: miningNode in a subnet
		} catch (DuplicateConnectionException e) {
			System.err.println(e);
		} catch (Exception e) {
			System.err.println(e);
		}
	}

	/**
	 * Creates transactions.
	 */
	public void createTransactions() {
		try {
			Transaction tr1 = node.createTransaction(wallet2, 10);
			network.broadcast(new TransactionNotification(tr1));
			Transaction tr2 = miningNode.createTransaction(wallet1.getPublicKey(), -1);// negative fails
			network.broadcast(new TransactionNotification(tr2));
		} catch (TransactionException e) {
			System.err.println(e);
		}
	}

	/**
	 * Main method.
	 * 
	 * @param args The arguments.
	 */
	public static void main(String[] args) {
		TesterMainExercise2 tme = new TesterMainExercise2();
		tme.buildFaultyNetwork();
		tme.createTransactions();
	}
}