package blockchain;

import java.util.*;

import exceptionbc.*;
import interfacebc.IConnectable;
import interfacebc.IMessage;

/**
 * Represents a blockchain network.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class BlockchainNetwork implements IConnectable {
	/**
	 * The name of the network.
	 */
	private String name;

	/**
	 * The list of peers in the network.
	 */
	private List<Net> lista = new LinkedList<>();

	/**
	 * Creates a new blockchain network.
	 * 
	 * @param name The name of the network.
	 */
	public BlockchainNetwork(String name) {
		this.name = name;
	}

	/**
	 * Connects a new peer to the network.
	 * 
	 * @param n The peer to connect.
	 * 
	 * @throws DuplicateConnectionException If the peer is already connected to another subnet in the network.
	 * @throws ConnectionException If the peer is already connected to the network. 			
	 * 
	 * @return The network itself.
	 */
	public BlockchainNetwork connect(Node n) throws DuplicateConnectionException, ConnectionException {
		if(this.lista.contains(n)) {
			throw new ConnectionException(n);
		}
		for(Net net : this.lista) {
			if(net.contains(n)){
				throw new DuplicateConnectionException(n);
			}
		}
		return this.checkedconnect(n);
	}

	/**
	 * Connects a new subnet to the network.
	 * 
	 * @param sub The subnet to connect.
	 * 
	 * @throws DuplicateConnectionException If the peer is already connected to another subnet in the network.
	 * @throws ConnectionException If the peer is already connected to the network. 	
	 * 
	 * @return The network itself.
	 */
	public BlockchainNetwork connect(Subnet sub) throws DuplicateConnectionException, ConnectionException {
		for(Node n : sub.getNodes()) {
			if(this.lista.contains(n)) {
				throw new ConnectionException(n);
			}
			for(Net net : this.lista) {
				if(net.contains(n)){
					throw new DuplicateConnectionException(n);
				}
			}
		}	
		return this.checkedconnect(sub);
	}
	
	/**
	 * Completes the connection of a new net to the network.
	 * 
	 * @param n The net to connect.
	 * 
	 * @return The network itself.
	 */
	private BlockchainNetwork checkedconnect(Net n) {
		this.lista.add(n);
		n.setParent(this);
		System.out.println(this.name + " - new peer connected: " + n);
		return this;
	}
	
	/**
	 * Sends a message to all the peers in the network.
	 * 
	 * @param msg The message to send.
	 */
	@Override
	public void broadcast(IMessage msg){
		for (Net n : lista) {
			n.broadcast(msg);
		}
	}

	/**
	 * Returns the father of the network: in this case, null.
	 * 
	 * @return null.
	 */
	@Override
	public IConnectable getParent(){
		return null;
	}

	/**
	 * Prints the network.
	 * 
	 * @return The network as a string.
	 */
	@Override
	public String toString() {
		String inicio = this.name + " consists of " + this.lista.size() + " elements\n";
		for (Net n : lista) {
			inicio += "* " + n.toString() + "\n";
		}
		return inicio;
	}
}
