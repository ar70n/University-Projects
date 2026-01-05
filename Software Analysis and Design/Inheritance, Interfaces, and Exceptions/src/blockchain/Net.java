package blockchain;

import interfacebc.*;

/**
 * Represents a network.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public abstract class Net implements IConnectable {
	/**
	 * The id of the node.
	 */
	protected final Integer id;

	/**
	 * Integer that represents the next id to assign to a new node.
	 */
	private static Integer nextId = 0;

	/**
	 * The father of the node.
	 */
	private IConnectable father;

	/**
	 * Creates a new net.
	 */
	protected Net() {
		this.id = newId();
	}

	/**
	 * Returns a new id for a new node.
	 * 
	 * @return The new id.
	 */
	private Integer newId() {
		return nextId++;
	}

	/**
	 * Sets the father of the node.
	 * 
	 * @param father The father of the node.
	 */
	public void setParent(IConnectable father) {
		this.father = father;
	}

	/**
	 * Returns the father of the node.
	 */
	public IConnectable getParent() {
		return father;
	}

	/**
	 * Checks if the net contains a node.
	 * 
	 * @param n The node to check.
	 * 
	 * @return True if the net contains the node, false otherwise.
	 */
	protected abstract boolean contains(Node n);
}
