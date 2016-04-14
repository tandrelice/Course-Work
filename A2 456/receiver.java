// This server is supposed to receive a sentence from the client, capitalizes it and sends it back to the client.

import java.io.*;
import java.net.*;

class UDPServer {

	InetAddress addrEmulator;
	int portToEmulator;
	int portFromEmulator;
	
	PrintWriter fileOut;
	DatagramSocket sockSend;
	DatagramSocket sockReceive;
	
	int windowSize;
	int expectSeqNum;
	int lastAck;
	
	// Logs
	PrintWriter arrivalLog;
	

	// Constructor
	UDPServer(String hostAddr, int portToEmu, int portFromEmu, String fileName) throws Exception {
		
		addrEmulator = InetAddress.getByName(hostAddr);
		portToEmulator = portToEmu;
		portFromEmulator = portFromEmu;
		
		windowSize = 10;
		expectSeqNum = 0; // first packet expected is 0
		
		fileOut = new PrintWriter(fileName);
		sockSend = new DatagramSocket();
		sockReceive = new DatagramSocket(portFromEmulator);

		arrivalLog = new PrintWriter("arrival.log");
	}
	
	void start() throws Exception {
		
		byte[] data = new byte[1024];
		
		boolean done = false;
		while (!done) {
			DatagramPacket receivePacket = new DatagramPacket(data, data.length);
			sockReceive.receive(receivePacket);
			packet p = packet.parseUDPdata(receivePacket.getData());
			
			arrivalLog.println(p.getSeqNum());
			//System.out.println("received: " + p.getSeqNum() + " expected: " + expectSeqNum); // DEBUG
			
			
			// Handle only expected packets
			if ( expectSeqNum == p.getSeqNum() ) {
				// If data packet
				if ( p.getType() == 1 ){
					lastAck = expectSeqNum;
					expectSeqNum++;
					expectSeqNum%=32;
					fileOut.print(new String(p.getData()));
				}
				// If EOT packet
				else if ( p.getType() == 2 ) {
					//System.out.println("EOT packet!"); // DEBUG
					lastAck = expectSeqNum;
					done = true;
					fileOut.close();
				}
			}
			
			// Send ACK
			packet ack;
			ack = packet.createACK(lastAck);
			//System.out.println("Send ACK: " + lastAck); // DEBUG
			sendPacket(ack);
		}
		
		
		
		arrivalLog.close();
		System.exit(0);
	}
	
	void sendPacket(packet p) throws Exception {
		byte[] data = p.getUDPdata();
		DatagramPacket sendPacket = new DatagramPacket(data, data.length, addrEmulator, portToEmulator);
		sockSend.send(sendPacket);
	}
	
	// Entry point
	public static void main(String[] args) {
		try {
			UDPServer s = new UDPServer(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]), args[3]);
			s.start();
		}
		catch (Exception e) {
			System.err.println("Input argument error.");
			System.exit(1);
		}
	}
	
}   

