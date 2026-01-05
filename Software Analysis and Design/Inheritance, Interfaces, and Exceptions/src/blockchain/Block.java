package blockchain;

import java.util.Date;
import java.util.Random;

import blockchain.utils.BlockConfig;

/**
 * Represents a block in the blockchain.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class Block {
	/**
	 * The id of the block.
	 */
	private final Integer id;

	/**
	 * The version of the block.
	 */
	private int version = BlockConfig.VERSION;

	/**
	 * The nonce of the block.
	 */
	private int nonce = new Random().nextInt(1001);

	/**
	 * The timestamp of the block.
	 */
	private int timestamp;

	/**
	 * The difficulty of the block.
	 */
	private int difficulty = BlockConfig.DIFFICULTY;

	/**
	 * The transaction of the block.
	 */
	private Transaction origin;

	/**
	 * The flag of the block.
	 */
	@SuppressWarnings("unused")
	private boolean flag = false;

	/**
	 * The hash of the block.
	 */
	private String hash;

	/**
	 * The previous block.
	 */
	private Block previous = null;

	/**
	 * The next id.
	 */
	private static Integer nextId = 0;

	/**
	 * Creates a new block.
	 * 
	 * @param origin The transaction of the block.
	 */
	public Block(Transaction origin) {
		this.id = newId();
		this.timestamp = (int) (new Date().getTime() / 1000);
		this.origin = origin;
	}

	/**
	 * Sets the hash of the block.
	 * 
	 * @param hash The hash of the block.
	 */
	public void setHash(String hash) {
		this.hash = hash;
	}

	/**
	 * Returns a new id for a new block.
	 * 
	 * @return The new id.
	 */
	private Integer newId() {
		return nextId++;
	}

	/**
	 * Returns the version of the block.
	 * 
	 * @return The version of the block.
	 */
	public int getVersion() {
		return this.version;
	}

	/**
	 * Returns the transaction of the block.
	 * 
	 * @return The transaction of the block.
	 */
	public Transaction getTransaction() {
		return this.origin;
	}

	/**
	 * Generates the string to hash.
	 * 
	 * @return The string to hash.
	 */
	public String preHash() {
		String previousHash;
		if (previous == null) {
			previousHash = BlockConfig.GENESIS_BLOCK;
		} else {
			previousHash = this.previous.getHash();
		}
		return this.version + previousHash + timestamp + this.difficulty + this.nonce;
	}

	/**
	 * Returns the hash of the block.
	 * 
	 * @return The hash of the block.
	 */
	public String getHash() {
		return this.hash;
	}

	/**
	 * Sets the previous block.
	 * 
	 * @param previousConfirmedBlock The previous block.
	 */
	public void setPreviousBlock(Block previousConfirmedBlock) {
		this.previous = previousConfirmedBlock;
	}

	/**
	 * Sets the flag of the block.
	 * 
	 * @param b The flag of the block.
	 */
	public void setFlag(boolean b) {
		this.flag = b;
	}

	/**
	 * Prints the block.
	 * 
	 * @return The block as a string.
	 */
	@Override
	public String toString() {
		return "id:" + this.id + ", v:" + this.version + ", nonce:" + this.nonce + ", ts:" + this.timestamp + ", diff:"
				+ this.difficulty + ", hash:" + this.hash;
	}

	/**
	 * Returns the id of the block.
	 * 
	 * @return The id of the block.
	 */
	public Integer getId() {
		return this.id;
	}
}
