package blockchain.test;

import blockchain.*;
import blockchain.utils.*;

/**
 * Tester that extends the previous one to test the new elements of the network.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class TesterMainExercise1b extends TesterMainExercise1 {
    /**
     * The new wallets and nodes to test.
     */
    protected Wallet wallet4, wallet5;

    /**
     * The new mining node to test.
     */
    protected MiningNode miningNode3;

    /**
     * The new node to test.
     */
    protected Node node2;

    /**
     * The new subnet to test.
     */
    protected Subnet subnet2;

    /**
     * Default constructor.
     */
    public TesterMainExercise1b() {
        super();
    }

    /**
     * Builds the network with the new elements.
     */
    @Override
    public void buildNetwork() {
        super.buildNetwork();

        // Create more wallets
        this.wallet4 = new Wallet("John", CommonUtils.sha1("PK-John"), 50);
        this.wallet5 = new Wallet("Jane", CommonUtils.sha1("PK-Jane"), 200);

        // Create more nodes with the wallets
        node2 = new Node(wallet4);
        miningNode3 = new MiningNode(wallet5, 20000);

        // Create another subnet inside the network
        subnet2 = new Subnet(miningNode3); // we could pass more nodes here

        // Connect the new elements to the network
        try {
            network.connect(node2).connect(subnet2);
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Create more transactions
        new Transaction(wallet4, wallet5, 20);
    }

    /**
     * Main method.
     * 
     * @param args The arguments.
     */
    public static void main(String[] args) {
        TesterMainExercise1b tmeb = new TesterMainExercise1b();
        tmeb.buildNetwork();
        System.out.println(tmeb.network);
        System.out.println(tmeb.node.fullName());
        System.out.println(tmeb.node2.fullName()); // prints the name of the new node
        System.out.println("End of party!");
    }
}