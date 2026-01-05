package interfacebc;

import blockchain.Node;

/**
 * Represents a message object.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public interface IMessage {
    /**
     * Returns the message.
     * 
     * @return The message.
     */
    public String getMessage();

    /**
     * Processes the message.
     * 
     * @param n The node that receives the message.
     */
    public default void process(Node n) {
        System.out.println("[" + n.fullName() + "]" +
                " - Received notification - Nex Tx: " +
                this.getMessage());
    }
}
