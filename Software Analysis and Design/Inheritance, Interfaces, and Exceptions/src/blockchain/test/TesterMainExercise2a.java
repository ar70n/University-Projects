package blockchain.test;

import blockchain.*;
import blockchain.message.TransactionNotification;
import exceptionbc.*;
import blockchain.utils.*;

/**
 * Tester for the second exercise that extends the previous one to test the new
 * elements of the network.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class TesterMainExercise2a extends TesterMainExercise2 {
    /**
     * Default constructor.
     */
    TesterMainExercise2a() {
        super();
    }

    /**
     * The new node to test.
     */
    protected Node node2;

    /**
     * The new wallet to test.
     */
    protected Wallet wallet3, wallet4;

    /**
     * The new mining node to test.
     */
    protected MiningNode miningNode3;

    /**
     * Builds a faulty network.
     */
    public void buildMoreFaultyNetwork() {
        super.buildFaultyNetwork();
        this.wallet3 = new Wallet("Paul", CommonUtils.sha1("PK-Pauk"), 777);
        this.wallet4 = new Wallet("Michael", CommonUtils.sha1("PK-Michael"), 300);
        node2 = new Node(wallet3);
        miningNode3 = new MiningNode(wallet4, 10000);
        try {
            this.network.connect(this.node2); // cannot connect: node already in the network
        } catch (ConnectionException e) {
            System.err.println(e);
        } catch (Exception e) {
            System.err.println(e);
        }
        try {
            this.network.connect(this.miningNode3); // cannot connect: miningNode in a subnet
        } catch (DuplicateConnectionException e) {
            System.err.println(e);
        } catch (Exception e) {
            System.err.println(e);
        }
    }

    /**
     * Creates more transactions.
     */
    public void createMoreTransactions() {
        super.createTransactions();
        try {
            Transaction tr3 = node2.createTransaction(wallet3, 20);
            network.broadcast(new TransactionNotification(tr3));
            Transaction tr4 = miningNode2.createTransaction(wallet1.getPublicKey(), -2);// negative fails
            network.broadcast(new TransactionNotification(tr4));
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
        TesterMainExercise2a tmea = new TesterMainExercise2a();
        tmea.buildMoreFaultyNetwork();
        tmea.createMoreTransactions();
    }
}
