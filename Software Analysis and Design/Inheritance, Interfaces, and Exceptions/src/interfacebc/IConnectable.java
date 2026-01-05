package interfacebc;

/**
 * Represents a connectable object.
 * 
 * @author Antonio Moroño and Pedro Ismael Haddou
 * @version 1.0
 */
public interface IConnectable {
    /**
     * Processes a message.
     * 
     * @param msg The message to process.
     */
    public void broadcast(IMessage msg);

    /**
     * Returns the parent of the connectable object.
     * 
     * @return The parent of the connectable object.
     */
    public IConnectable getParent();

    /**
     * Returns the top parent of the connectable object.
     * 
     * @return The top parent of the connectable object.
     */
    public default IConnectable getTopParent() {
        IConnectable parent = getParent();
        while (parent != null) {
            if (parent.getParent() == null)
                return parent;
            parent = parent.getParent();
        }
        return parent;
    }
}
