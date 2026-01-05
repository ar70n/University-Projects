package exceptionbc;

import blockchain.Node;

/**
 * Represents an exception that is thrown when a node is already connected to a subnet.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
@SuppressWarnings("serial")
public class DuplicateConnectionException extends Exception {
	/**
	 * Id of the node that is already connected to a subnet.
	 */
	private Integer nodeId;
	
	/**
	 * Creates a new ConnectionException.
	 * 
	 * @param id Id of the node that is already connected to a subnet.
	 */
	public DuplicateConnectionException(Node id) {
		this.nodeId = id.getId();
	}

	/**
	 * Prints the exception message.
	 * 
	 * @return The exception message.
	 */
	@Override 
	public String toString() {
		return String.format("Connection exception: Node %03d is connected to a different network",this.nodeId);
	}
}
