package blockchain;

/**
 * Represents a wallet in the blockchain.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class Wallet {
	/**
	 * The username of the wallet.
	 */
	private String username;

	/**
	 * The key of the wallet.
	 */
	private String key;

	/**
	 * The balance of the wallet.
	 */
	private Integer balance;

	/**
	 * Creates a new wallet.
	 * 
	 * @param username The username of the wallet.
	 * @param key      The key of the wallet.
	 * @param balance  The balance of the wallet.
	 */
	public Wallet(String username, String key, Integer balance) {
		this.username = username;
		this.key = key;
		this.balance = balance;
	}

	/**
	 * Returns the key of the wallet.
	 * 
	 * @return The key of the wallet.
	 */
	public String getPublicKey() {
		return this.key;
	}

	/**
	 * Returns the username of the wallet.
	 * 
	 * @return The username of the wallet.
	 */
	public String getUsername() {
		return this.username;
	}

	/**
	 * Returns the balance of the wallet.
	 * 
	 * @return The balance of the wallet.
	 */
	public Integer getBalance() {
		return this.balance;
	}

	/**
	 * Updates the balance of the wallet.
	 * 
	 * @param i The value to update the balance.
	 */
	public void updateBalance(Integer i)  {
		this.balance+=i;
	}
	
	/**
	 * Prints the wallet.
	 * 
	 * @return The wallet as a string.
	 */
	@Override
	public String toString() {
		return "u: "+this.username+", PK:"+this.key+", balance:"+this.balance;
	}
}
