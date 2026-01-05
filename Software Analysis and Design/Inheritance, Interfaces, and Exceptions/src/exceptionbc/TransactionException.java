package exceptionbc;

/**
 * Represents an exception that is thrown when a new transaction is invalid.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
@SuppressWarnings("serial")
public class TransactionException extends BlockchainException {
	/**
	 * The wallet that is the source of the transaction.
	 */
	private String source;

	/**
	 * The wallet that is the receiver of the transaction.
	 */
	private String receiver;

	/**
	 * The amount of the transaction.
	 */
	private Integer amount;

	/**
	 * Creates a new TransactionException.
	 * 
	 * @param source   The wallet that is the source of the transaction.
	 * @param receiver The wallet that is the receiver of the transaction.
	 * @param amount   The amount of the transaction.
	 */
	public TransactionException(String source, String receiver, Integer amount) {
		this.source = source;
		this.receiver = receiver;
		this.amount = amount;
	}

	/**
	 * Prints the exception message.
	 * 
	 * @return The exception message.
	 */
	@Override
	public String toString() {
		return "Negative transfer attempt: source: " + this.source + ", receiver: " + this.receiver + ", amount: "
				+ this.amount;
	}
}
