package blockchain.message;

import blockchain.*;
import interfacebc.IMessage;

/**
 * Represents a validate block request.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class ValidateBlockRq implements IMessage {
	/**
	 * The block to validate.
	 */
	private Block block;

	/**
	 * The node that sends the request.
	 */
	@SuppressWarnings("unused")
	private Node node;

	/**
	 * The mining id.
	 */
	private final Integer MiningId;

	/**
	 * Creates a validate block request.
	 * 
	 * @param block The block to validate.
	 * @param n     The node that sends the request.
	 */
	public ValidateBlockRq(Block block, Node n) {
		this.block = block;
		this.node = n;
		this.MiningId = n.getId();
	}

	/**
	 * Returns the message.
	 * 
	 * @return The message.
	 */
	@Override
	public String getMessage() {
		return "ValidateBlockRq";
	}

	/**
	 * Processes the message.
	 * 
	 * @param n The node that receives the message.
	 */
	@Override
	public void process(Node n) {
		System.out.println("[" + n.fullName() + "] Recieved Task: " + this.getMessage() + ": <b:" + this.block.getId()
				+ String.format(", src:%03d>", this.MiningId));
		n.validate(this.block);
		// IMessage.super.process(n);

	}
}
