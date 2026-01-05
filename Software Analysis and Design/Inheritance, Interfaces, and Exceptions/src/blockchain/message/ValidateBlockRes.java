package blockchain.message;

import blockchain.Block;
import blockchain.Node;
import interfacebc.IMessage;

/**
 * Represents a validate block response.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class ValidateBlockRes implements IMessage {
	/**
	 * Block to validate.
	 */
	private Block block;

	/**
	 * Flag to validate the block.
	 */
	private boolean flag;

	/**
	 * Mining id.
	 */
	private Integer miningId;

	/**
	 * Creates a validate block response.
	 * 
	 * @param block    Block to validate.
	 * @param flag     Flag to validate the block.
	 * @param miningId Mining id.
	 */
	public ValidateBlockRes(Block block, boolean flag, Integer miningId) {
		this.block = block;
		this.flag = flag;
		this.miningId = miningId;
		System.out.println(this.getMessage() + ": <b:" + this.block.getId() + ", res:" + this.flag
				+ String.format(", src:%03d>", this.miningId));
	}

	/**
	 * Returns the message.
	 * 
	 * @return The message.
	 */
	@Override
	public String getMessage() {
		return "ValidateBlockRes";
	}

	/**
	 * Processes the message.
	 * 
	 * @param n The node that receives the message.
	 */
	@Override
	public void process(Node n) {
		System.out.println("[" + n.fullName() + "] Recieved Task: " + this.getMessage() + ": <b:" + this.block.getId()
				+ ", res:" + this.flag + String.format(", src:%03d>", this.miningId));
		n.commitTransaction(block.getTransaction());
	}
}
