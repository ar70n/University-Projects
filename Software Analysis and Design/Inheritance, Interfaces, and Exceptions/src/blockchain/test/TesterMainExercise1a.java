package blockchain.test;

import blockchain.*;
import blockchain.utils.*;

/**
 * Tester for the first exercise with connection exception.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class TesterMainExercise1a {
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
	protected Node node1, node2;

	/**
	 * The subnet of the network.
	 */
	protected Subnet subnet;

	/**
	 * The network.
	 */
	protected BlockchainNetwork network1, network2;

	/**
	 * Default constructor.
	 */
	public TesterMainExercise1a() {
	}

	/**
	 * Builds the network throwing a connection exception.
	 */
	public void buildNetworkConnectionException() {
		// Create the wallets
		this.wallet1 = new Wallet("Bob", CommonUtils.sha1("PK-Bob"), 10);
		this.wallet2 = new Wallet("Alice", CommonUtils.sha1("PK-Alice"), 100);
		this.wallet3 = new Wallet("Paul", CommonUtils.sha1("PK-Pauk"), 777);
		// Create the nodes with the wallets
		node1 = new Node(wallet1);
		miningNode = new MiningNode(wallet2, 10000);
		// Create a subnet inside a network
		miningNode2 = new MiningNode(wallet3, 10000);
		subnet = new Subnet(miningNode2);
		// Create the network and connect the elements
		this.network1 = new BlockchainNetwork("ADSOF blockchain");
		try {
			network1.connect(node1).connect(subnet).connect(miningNode).connect(node1);
		} catch (Exception e) {
			System.out.println(e);
		}
	}

	/**
	 * Main test.
	 * This test must throw a ConnectionException.
	 * 
	 * @param args The arguments.
	 */
	public static void main(String[] args) {
		TesterMainExercise1a tme1 = new TesterMainExercise1a();
		tme1.buildNetworkConnectionException();
	}
}