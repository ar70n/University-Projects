package blockchain.utils;

import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Common utilities.
 * 
 * @author eps
 */
@SuppressWarnings("unused")
public class CommonUtils {
	/**
	 * Default constructor.
	 */
	private CommonUtils() {
	}

	/**
	 * Converts a byte array to a long.
	 * 
	 * @param data         The byte array.
	 * @param shaAlgorithm The algorithm to use.
	 * 
	 * @return The long.
	 */
	private static String shaGeneral(String data, String shaAlgorithm) {
		MessageDigest digestInstance;
		String shaReturn;
		shaReturn = "";
		try {
			digestInstance = MessageDigest.getInstance(shaAlgorithm);
			digestInstance.update(data.getBytes("UTF-8"));

			StringBuilder result = new StringBuilder();
			for (byte byteIn : digestInstance.digest()) {
				result.append(String.format("%02x", byteIn));
			}
			shaReturn = result.toString();
		} catch (NoSuchAlgorithmException | UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		return shaReturn;
	}

	/**
	 * Converts a byte array to a long.
	 * 
	 * @param data The byte array.
	 * 
	 * @return The long.
	 */
	public static String sha256(String data) {
		String shaReturn;
		shaReturn = shaGeneral(data, "SHA-256");
		return shaReturn;
	}

	/**
	 * Converts a byte array to a long.
	 * 
	 * @param data The byte array.
	 * 
	 * @return The long.
	 */
	public static String sha1(String data) {
		String shaReturn;

		shaReturn = shaGeneral(data, "SHA-1");
		return shaReturn;
	}
}
