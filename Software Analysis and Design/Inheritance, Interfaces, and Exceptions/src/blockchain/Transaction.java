package blockchain;

/**
 * Represents a transaction in the blockchain.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class Transaction {
	/**
	 * The id of the transaction.
	 */
	private final Integer id;

	/**
	 * The next id to be assigned to a transaction.
	 */
	private static Integer nextId = 0;

	/**
	 * The origin of the transaction.
	 */
	private String origin;

	/**
	 * The destination of the transaction.
	 */
	private String destination;

	/**
	 * The value of the transaction.
	 */
	private Integer value;

	/**
	 * Creates a new transaction given the origin and destination wallets.
	 * 
	 * @param origin      The origin of the transaction.
	 * @param destination The destination of the transaction.
	 * @param value       The value of the transaction.
	 */
	public Transaction(Wallet origin, Wallet destination, Integer value) {
		this.origin = origin.getPublicKey();
		this.destination = destination.getPublicKey();
		this.value = value;
		this.id = newId();
	}

	/**
	 * Creates a new transaction given the keys of the origin and destination.
	 * 
	 * @param keyOrigin      The key of the origin of the transaction.
	 * @param keyDestination The key of the destination of the transaction.
	 * @param value          The value of the transaction.
	 */
	public Transaction(String keyOrigin, String keyDestination, Integer value) {
		this.origin = keyOrigin;
		this.destination = keyDestination;
		this.value = value;
		this.id = newId();
	}

	/**
	 * Returns a new id for a new transaction.
	 * 
	 * @return The new id.
	 */
	private Integer newId() {
		return nextId++;
	}

	/**
	 * Returns the origin of the transaction.
	 * 
	 * @return The origin of the transaction.
	 */
	public String getOrigin() {
		return origin;
	}

	/**
	 * Returns the destination of the transaction.
	 * 
	 * @return The destination of the transaction.
	 */
	public String getDestination() {
		return destination;
	}

	/**
	 * Prints the transaction.
	 * 
	 * @return The node as a string
	 */
	@Override
	public String toString() {
		return "Transaction " + this.id + "| from: " + this.origin + ", to: " + this.destination + ", quantity: "
				+ this.value;
	}

	/**
	 * Returns the value of the transaction.
	 * 
	 * @return The value of the transaction.
	 */
	public Integer getValue() {
		return this.value;
	}

	/**
	 * Returns the id of the transaction.
	 * 
	 * @return The id of the transaction.
	 */
	public Integer getId() {
		return this.id;
	}

	/**
	 * Returns the details of the transaction.
	 * 
	 * @return The details of the transaction.
	 */
	public String details() {
		return " -> Tx details:" + this.toString();
	}
}
