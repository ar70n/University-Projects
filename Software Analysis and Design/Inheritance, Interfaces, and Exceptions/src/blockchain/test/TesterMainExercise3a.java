package blockchain.test;

import blockchain.*;
import blockchain.message.TransactionNotification;
import blockchain.method.SimpleMining;
import blockchain.method.SimpleValidate;
import exceptionbc.TransactionException;
import blockchain.utils.CommonUtils;

/**
 * Tester for the third exercise that extends the previous one to test the new
 * elements of the network.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class TesterMainExercise3a extends TesterMainExercise3 {
    /**
     * Default constructor.
     */
    TesterMainExercise3a() {
        super();
    }

    /**
     * The new nodes to test.
     */
    protected Node node2, node3;

    /**
     * The new mining nodes to test.
     */
    protected MiningNode miningNode3, miningNode4;

    /**
     * The new wallet to test.
     */
    protected Wallet wallet3, wallet4, wallet5, wallet6;

    /**
     * Creates more transactions.
     */
    public void createMoreTransactions() {
        super.createTransactions();
        this.wallet3 = new Wallet("Paul", CommonUtils.sha1("PK-Pauk"), 777);
        this.wallet4 = new Wallet("Michael", CommonUtils.sha1("PK-Michael"), 300);
        this.wallet5 = new Wallet("Alexander", CommonUtils.sha1("PK-Alexander"), 1000);
        this.wallet6 = new Wallet("John", CommonUtils.sha1("PK-John"), 500);

        node2 = new Node(wallet3);
        node3 = new Node(wallet5);
        miningNode3 = new MiningNode(wallet4, 10000);
        miningNode4 = new MiningNode(wallet6, 10000);
        
        this.miningNode3.setMiningMethod(new SimpleMining());
        this.miningNode3.setValidationMethod(new SimpleValidate());
        this.miningNode4.setMiningMethod(new SimpleMining());
        this.miningNode4.setValidationMethod(new SimpleValidate());
        this.wallet4 = new Wallet("Alexander", CommonUtils.sha1("PK-Alexander"), 1000);
        try {
            network.broadcast(new TransactionNotification(node2.createTransaction(wallet3.getPublicKey(), 10)));
            network.broadcast(new TransactionNotification(node3.createTransaction(wallet4.getPublicKey(), 15)));
        } catch (TransactionException e) {
            e.toString();
        }
    }

    /**
     * Main method.
     * 
     * @param args The arguments of the program.
     */
    public static void main(String[] args) {
        TesterMainExercise3a tmea = new TesterMainExercise3a();
        tmea.buildNetwork();
        tmea.createMoreTransactions();
        System.out.println("End of party!");
    }
}