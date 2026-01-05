package exceptionbc;

import blockchain.Node;

/**
 * Represents an exception that is thrown when a node is already connected to the network.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
@SuppressWarnings("serial")
public class ConnectionException extends BlockchainException {
	/**
	 * Id of the node that is already connected to the network.
	 */
	private Integer nodeId;
	
	/**
	 * Creates a new ConnectionException.
	 * 
	 * @param id Id of the node that is already connected to the network.
	 */
	public ConnectionException(Node id) {
		this.nodeId = id.getId();
	}

	/**
	 * Prints the exception message.
	 * 
	 * @return The exception message.
	 */
	@Override 
	public String toString() {
		return  String.format("Connection exception: Node %03d is already connected to the network",this.nodeId);
	}
}

