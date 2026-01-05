package blockchain.utils;

/**
 * Represents the configuration of a block.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class BlockConfig {
	/**
	 * Default constructor.
	 */
	public BlockConfig() {
	}

	/**
	 * The hash of the genesis block.
	 */
	public static String GENESIS_BLOCK = "0000000000000000000000000000000000000000000000000000000000000000";

	/**
	 * The difficulty of the block.
	 */
	public static int DIFFICULTY = 1;

	/**
	 * The number of blocks to mine before the reward is halved.
	 */
	public static int VERSION = 1;
}
