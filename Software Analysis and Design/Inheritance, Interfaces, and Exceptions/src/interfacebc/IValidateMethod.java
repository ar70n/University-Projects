package interfacebc;

import blockchain.Block;

/**
 * Represents a method that validates a block.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public interface IValidateMethod {
	/**
	 * Validates a block.
	 * 
	 * @param miningMethod The mining method used to mine the block.
	 * @param block        The block to validate.
	 * 
	 * @return True if the block is valid, false otherwise.
	 */
	public boolean validate(IMiningMethod miningMethod, Block block);
}
