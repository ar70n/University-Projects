package blockchain.test;

import blockchain.*;
import blockchain.utils.*;

/**
 * Tester for the first exercise.
 * 
 * @author eps
 * @version 1.0
 */
public class TesterMainExercise1 {
	/**
	 * The wallets of the network.
	 */
	protected Wallet wallet1, wallet2, wallet3;

	/**
	 * The nodes of the network.
	 */
	protected MiningNode miningNode, miningNode2;

	/**
	 * The node of the network.
	 */
	protected Node node;

	/**
	 * The subnet of the network.
	 */
	protected Subnet subnet;

	/**
	 * The network.
	 */
	protected BlockchainNetwork network;

	/**
	 * Default constructor.
	 */
	public TesterMainExercise1() {
	}

	/**
	 * Builds the network.
	 */
	public void buildNetwork() {
		// Create the wallets
		this.wallet1 = new Wallet("Bob", CommonUtils.sha1("PK-Bob"), 10);
		this.wallet2 = new Wallet("Alice", CommonUtils.sha1("PK-Alice"), 100);
		this.wallet3 = new Wallet("Paul", CommonUtils.sha1("PK-Pauk"), 777);
		// Create the nodes with the wallets
		node = new Node(wallet1);
		miningNode = new MiningNode(wallet2, 10000);
		// Create a subnet inside a network
		miningNode2 = new MiningNode(wallet3, 10000);
		subnet = new Subnet(miningNode2); // we could pass more nodes here
		// Create the network and connect the elements
		this.network = new BlockchainNetwork("ADSOF blockchain");
		try {
			network.connect(node).connect(subnet).connect(miningNode);
		} // create example transaction, which transfers 10 coins from wallet1 to wallet2
		catch (Exception e) {
			e.printStackTrace();
		}
		new Transaction(wallet1, wallet2, 10);
	}

	/**
	 * Main test.
	 * 
	 * @param args The arguments.
	 */
	public static void main(String[] args) {
		TesterMainExercise1 tme = new TesterMainExercise1();
		tme.buildNetwork();
		System.out.println(tme.network);
		System.out.println(tme.node.fullName()); // prints the name of the node
		System.out.println("End of party!");
	}
}