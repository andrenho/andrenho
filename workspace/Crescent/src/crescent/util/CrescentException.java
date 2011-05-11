package crescent.util;

@SuppressWarnings("serial")
public class CrescentException extends Exception {

	public CrescentException() {
		super();
	}

	public CrescentException(String message) {
		super(message);
	}

	public CrescentException(Throwable cause) {
		super(cause);
	}

	public CrescentException(String message, Throwable cause) {
		super(message, cause);
	}

}
