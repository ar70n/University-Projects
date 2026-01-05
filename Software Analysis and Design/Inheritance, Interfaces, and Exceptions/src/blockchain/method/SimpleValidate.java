package blockchain.method;

import blockchain.Block;
import interfacebc.*;

/**
 * Represents a simple validate method.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class SimpleValidate implements IValidateMethod {

	/**
	 * Default constructor.
	 */
	public SimpleValidate() {
	}

	/**
	 * Validates a block.
	 * 
	 * @param miningMethod The mining method.
	 * @param block        The block to validate.
	 * 
	 * @return True if the block is valid, false otherwise.
	 */
	public boolean validate(IMiningMethod miningMethod, Block block) {
		if (miningMethod.createHash(block).equals(block.getHash())) {
			block.setFlag(true);
			return true;
		}
		return false;
	}
}
