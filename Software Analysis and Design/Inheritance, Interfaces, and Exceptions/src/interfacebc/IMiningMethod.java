package interfacebc;

import blockchain.Block;
import blockchain.Transaction;

/**
 * Represents a mining method that can be used to mine a block.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public interface IMiningMethod {
	/**
	 * Creates a hash for a block.
	 * 
	 * @param block The block to create the hash for.
	 * 
	 * @return The hash for the block.
	 */
	String createHash(Block block);

	/**
	 * Mines a block.
	 * 
	 * @param transaction The transaction to include in the block.
	 * @param previousConfirmedBlock The previous confirmed block.
	 * @param minerKey The key of the miner.
	 * 
	 * @return The mined block.
	 */
	Block mineBlock(Transaction transaction, Block previousConfirmedBlock, String minerKey);
}
