package blockchain.method;

import blockchain.Block;
import blockchain.Transaction;
import blockchain.utils.CommonUtils;
import interfacebc.IMiningMethod;

/**
 * Represents a simple mining method.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class SimpleMining implements IMiningMethod {
	/**
	 * Default constructor.
	 */
	public SimpleMining() {
	}

	/**
	 * Mines a block.
	 * 
	 * @param transaction            Transaction to mine.
	 * @param previousConfirmedBlock Previous confirmed block.
	 * @param minerKey               Miner key.
	 * 
	 * @return The mined block.
	 */
	public Block mineBlock(Transaction transaction, Block previousConfirmedBlock, String minerKey) {
		Block newBlock = new Block(transaction);
		newBlock.setPreviousBlock(previousConfirmedBlock);
		newBlock.setHash(createHash(newBlock));
		System.out.println(newBlock.toString() + ", minerK: " + minerKey);
		return newBlock;
	}

	/**
	 * Creates a hash.
	 * 
	 * @param block Block to hash.
	 * 
	 * @return The hash.
	 */
	public String createHash(Block block) {
		return CommonUtils.sha256(block.preHash());
	}
}
