package blockchain;

import java.util.ArrayList;
import interfacebc.*;
import java.util.List;

import blockchain.message.ValidateBlockRes;
import blockchain.message.ValidateBlockRq;
import blockchain.method.*;

/**
 * Represents a mining node in the blockchain.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public class MiningNode extends Node {
	/**
	 * The computational capacity of the node.
	 */
	@SuppressWarnings("unused")
	private Integer ComputacionalCapacity;

	/**
	 * The list of blocks mined by the node.
	 */
	private List<Block> blocks = new ArrayList<Block>();

	/**
	 * The mining method of the node.
	 */
	private IMiningMethod miningMethod = null;

	/**
	 * The validation method of the node.
	 */
	private IValidateMethod validateMethod = null;

	/**
	 * Creates a new mining node.
	 * 
	 * @param w The wallet of the node.
	 * @param c The computational capacity of the node.
	 */
	public MiningNode(Wallet w, Integer c) {
		super(w);
		this.ComputacionalCapacity = c;
	}

	/**
	 * Returns the name of the node.
	 * 
	 * @return The name of the node.
	 */
	public String fullName() {
		return String.format("MiningNode#%03d", this.id);
	}

	/**
	 * Returns the last block mined by the node.
	 * 
	 * @return The last block mined by the node.
	 */
	public Block getLastBlock() {
		return this.blocks.size() > 0 ? this.blocks.get(this.blocks.size() - 1) : null;
	}

	/**
	 * Sets the mining method of the node.
	 * 
	 * @param simpleMining The mining method of the node.
	 */
	public void setMiningMethod(SimpleMining simpleMining) {
		this.miningMethod = simpleMining;
	}

	/**
	 * Sets the validation method of the node.
	 * 
	 * @param simpleValidate The validation method of the node.
	 */
	public void setValidationMethod(SimpleValidate simpleValidate) {
		this.validateMethod = simpleValidate;

	}

	/**
	 * Returns the mining method of the node.
	 * 
	 * @return The mining method of the node.
	 */
	@Override
	public IMiningMethod getMiningMethod() {
		return this.miningMethod;
	}

	/**
	 * Returns the validation method of the node.
	 * 
	 * @return The validation method of the node.
	 */
	@Override
	public IValidateMethod getValidateMethod() {
		return this.validateMethod;
	}

	/**
	 * Mines a new block.
	 * 
	 * @param tr The transaction to mine.
	 */
	@Override
	public void mine(Transaction tr) {
		if (this.miningMethod == null) {
			return;
		}
		System.out.print("[" + this.fullName() + "] Mined block: ");
		Block mined;
		mined = this.miningMethod.mineBlock(tr, this.getLastBlock(), this.getPublicKey());
		this.addBlock(mined);
		this.addTransaction(tr);
		this.getTopParent().broadcast(new ValidateBlockRq(mined, this)); // Enviar mensaje a la red

	}

	/**
	 * Validates a block.
	 * 
	 * @param block The block to validate.
	 */
	@Override
	public void validate(Block block) {
		Boolean flag;
		if (this.blocks.contains(block)) {
			System.out.println("[" + this.fullName() + "] You cannot validate your own block");
			return;
		}
		flag = validateMethod.validate(miningMethod, block);
		System.out.print("[" + this.fullName() + "] Emitted Task: ");
		this.getTopParent().broadcast(new ValidateBlockRes(block, flag, this.getId())); // Enviar mensaje a la red

	}

	/**
	 * Adds a block to the list of mined blocks.
	 * 
	 * @param mined The block to add.
	 */
	private void addBlock(Block mined) {
		this.blocks.add(mined);
	}
}
