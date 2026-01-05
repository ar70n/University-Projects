package blockchain;

import java.util.*;
import interfacebc.*;

/**
 * Represents a subnet in a blockchain network.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class Subnet extends Net {
	/**
	 * The nodes of the subnet.
	 */
	private Set<Node> nodes = new LinkedHashSet<>();

	/**
	 * Creates a new subnet.
	 * 
	 * @param n The nodes of the subnet.
	 */
	public Subnet(Node... n) {
		for (Node node : n) {
			node.setParent(this);
			this.nodes.add(node);
		}
	}

	/**
	 * Returns the nodes of the subnet.
	 * 
	 * @return The nodes of the subnet.
	 */
	public Set<Node> getNodes() {
		return Collections.unmodifiableSet(nodes);
	}
	
	/**
	 * Checks if the subnet contains a node.
	 * 
	 * @param n The node to check.
	 */
	public boolean contains(Node n) {
		return this.nodes.contains(n);
	}
	
	/**
	 * Returns the name of the subnet.
	 * 
	 * @return The name of the subnet.
	 */
	public String fullName() {
		return String.format("Subnet#%03d", this.id);
	}
	
	/**
	 * Sends a message to all the peers in the network.
	 * 
	 * @param msg The message to send.
	 */
	@Override
	public void broadcast(IMessage msg){
		System.out.println("["+this.fullName()+"] "+msg.getMessage());
		System.out.println("Broadcasting to "+this.nodes.size()+ " nodes:");
		for (Node n : nodes) {
			n.broadcast(msg);
		}
	}

	/**
	 * Prints the subnet.
	 * 
	 * @return The subnet as a string.
	 */
	@Override
	public String toString() {
		String inicio = "Node network of " + this.nodes.size() + " nodes: [";
		for (Node n : nodes) {
			inicio += n.toString();
		}
		return inicio + "]";
	}
}
