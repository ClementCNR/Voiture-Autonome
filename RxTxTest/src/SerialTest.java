import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import java.util.Enumeration;
public class SerialTest implements SerialPortEventListener {

SerialPort serialPort;
/** The port we�re normally going to use. */
private static final String PORT_NAMES[] = {
		" /dev/tty.usbserial-A9007UX1 ", // Mac OS X
		" /dev/ttyUSB0 ", // Linux
		"COM4", // Windows
};

private BufferedReader input;
private OutputStream output;
private static final int TIME_OUT = 2000;
private static final int DATA_RATE = 9600;
private float valeur1 = 0;
private float valeur2 = 0;
private int pos = 0;
private int type = 10;
private boolean nVal = false;

public int getType() {
	return this.type;
}

public float getValeur1() {
	return this.valeur1;
}

public float getValeur2() {
	return this.valeur2;
}

public int getPos() {
	return this.pos;
}
public void initialize() {
	CommPortIdentifier portId = null;
	Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

	//First, Find an instance of serial port as set in PORT_NAMES.
	while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
			for (String portName : PORT_NAMES) {
				if (currPortId.getName().equals(portName)) {
					portId = currPortId;
					break;
				}
			}
	}
	if (portId == null) {
		System.out.println(" Could not find COM port. ");
		return;
	}

	try {
		serialPort = (SerialPort) portId.open(this.getClass().getName(),
				TIME_OUT);
		serialPort.setSerialPortParams(DATA_RATE,
				SerialPort.DATABITS_8,
				SerialPort.STOPBITS_1,
				SerialPort.PARITY_NONE);

		// open the streams
		input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
		output = serialPort.getOutputStream();

		serialPort.addEventListener(this);
		serialPort.notifyOnDataAvailable(true);
	} catch (Exception e) {
		System.err.println(e.toString());
	}
	}
	public synchronized void close() {
		if (serialPort != null) {
			serialPort.removeEventListener();
			serialPort.close();
		}
	}

public synchronized void serialEvent(SerialPortEvent oEvent) {
	if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
		try {
			String inputLine=null;
			
			if (input.ready()) {
				
				inputLine = input.readLine();
				valeur1 = Float.parseFloat(inputLine);
				
				if (valeur1 <= 2 && valeur1 >= 0)
				{
					type = Integer.parseInt(inputLine);
					System.out.println("");
					System.out.println("");
					System.out.println("Type : " + type);
				}
				
				else
				{
					if (nVal == false)
					{
						valeur1 = Float.parseFloat(inputLine);
						System.out.println("Valeur 1 : " + valeur1);
						nVal = true;
					}
					
					else
					{
						valeur2 = Float.parseFloat(inputLine);
						System.out.println("Valeur 2 : " + valeur2);
						nVal = false;
					}
					
				}
				//inputLine = input.readLine();

				//String [] chunks = inputLine.split(" , ");

				//System.out.println(inputLine);
				//System.out.println("");
				/*try {
					System.out.println(chunks[0] +  " \t  " + chunks[1] +  " \t  " + chunks[2] +  " \t " );
				} catch (Exception e) {}*/

			}

		} catch (Exception e) {
			System.err.println(e.toString());
		}
	}
	// Ignore all the other eventTypes, but you should consider the other ones.
}

public static void main(String[] args) throws Exception {
	SerialTest main = new SerialTest();
	main.initialize();
	Thread t=new Thread() {
		public void run() {
			//the following line will keep this app alive for 1000 seconds,
			//waiting for events to occur and responding to them (printing incoming messages to console).
			try {Thread.sleep(1000000);} catch (InterruptedException ie) {}
		}
	};
	t.start();
	System.out.println(" Started ");
	}
}