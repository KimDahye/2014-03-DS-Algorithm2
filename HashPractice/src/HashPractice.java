import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class HashPractice {

	public static void main(String[] args) {
		@SuppressWarnings("resource")
		Scanner keyboard = new Scanner(System.in);
		System.out.print("your text: ");
		String inputString = keyboard.nextLine();
		System.out.println("Input String: " + inputString);

        String md5Hash = hashString(inputString, "MD5");
        System.out.println("MD5 Hash: " + md5Hash);

        String sha1Hash = hashString(inputString, "SHA-1");
        System.out.println("SHA-1 Hash: " + sha1Hash);

        String sha256Hash = hashString(inputString, "SHA-256");
        System.out.println("SHA-256 Hash: " + sha256Hash);
	}

	private static String hashString(String message, String algorithm) {
			MessageDigest md;
			try {
				md = MessageDigest.getInstance(algorithm);
				byte[] hashedBytes = md.digest(message.getBytes("UTF-8"));
				return convertByteArrayToHexString(hashedBytes);

			} catch (NoSuchAlgorithmException | UnsupportedEncodingException e) {
				System.out.println("Could not generate hash from String.");
				e.printStackTrace();
			}
			return null;
	}

	private static String convertByteArrayToHexString(byte[] arrayBytes) {
		StringBuffer stringBuffer = new StringBuffer();
		for (int i = 0; i < arrayBytes.length; i++) {
			stringBuffer.append(Integer.toString((arrayBytes[i] & 0xff) + 0x100, 16).substring(1));
		}
		return stringBuffer.toString();
	}

}
