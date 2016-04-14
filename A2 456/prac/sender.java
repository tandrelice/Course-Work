// This client is supposed to send a sentence to the server, and then print the sentence received by the server. 

import java.io.*;  
import java.net.*;
import java.util.LinkedList;
//import java.util.Timer;
import javax.swing.Timer;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
//import java.lang.Math.*;

class sender {
	
	BufferedReader input_file; // the input file
	InetAddress NE_name; // the host name for the Network Emulator
	int data_portno, ACK_portno; // the two different port numbers
	
	DatagramSocket data_EOT_socket, ACK_socket; // two sockets
	

	// the list containing the queued/sent packets status
	// will be refined
	LinkedList<packet> packets;
	int total_packets_number;
	
	// this list is to track the packets being sent or not
	LinkedList<Boolean> sent_or_not;
	int number_in_queue;
	
	// the remaining window size is set to 10 in the constructor in the beginning
	int first_of_the_10_sent_packet;
	int remaining_window_size;
	int remaining_packets_to_send;
	int seq;
	
	// Logs
	PrintWriter seqnumLog;
	PrintWriter ackLog;
	
	
	
	// Constructor
	sender(String NE_addr, int port_to_NE, int port_from_NE, String fileName) throws Exception {
		
		NE_name = InetAddress.getByName(NE_addr);
		data_portno = port_to_NE;
		ACK_portno = port_from_NE;

		first_of_the_10_sent_packet = 0; // packets firmed with ACK
		remaining_window_size = 10;
		
		
		packets = new LinkedList<packet>();
		sent_or_not = new LinkedList<Boolean>();
		
		input_file = new BufferedReader(new FileReader(fileName));
		
		// the socket for sending data
		data_EOT_socket = new DatagramSocket();
		
		// the socket for receiving the ACKs
		ACK_socket = new DatagramSocket(ACK_portno);

		seqnumLog = new PrintWriter("seqnum.log");
		ackLog = new PrintWriter("ack.log");
		
		// sequence number starts at 0
		seq = 0;
	}
	
	void execute() throws Exception {
		
		// Start to Read File
		char[] rdbuffer = new char[500];
		int count = input_file.read(rdbuffer, 0, 500);
		while (count == 500) {
			
			packet new_packet = packet.createPacket(seq, new String(rdbuffer));
			packets.add(new_packet);
			sent_or_not.add(false);
			seq++; // the sequence number, will be mod 32 in the packet
			
			count = input_file.read(rdbuffer, 0, 500);
		}
		
		if (count < 500 && count > 0) {
			packet last_packet = packet.createPacket(seq, new String(rdbuffer));
			packets.add(last_packet);
			sent_or_not.add(false);
			seq++;
		}
		remaining_packets_to_send = packets.size();
		
		// End of Read File
		input_file.close();
		
		total_packets_number = packets.size();
		
		// execute thread for receiving ACKs
	    Thread threadReceiveACK = new Thread() {
	    	public void run() {
	    		try {
	    			byte[] data = new byte[512];
	    			DatagramPacket ACK_packet = new DatagramPacket(data, 512);
	    			
	    			while (packets.size() != 0) {
	    				// Get packets
	    				ACK_socket.receive(ACK_packet);
	    				packet parsed_packet = packet.parseUDPdata(ACK_packet.getData());
	    				
	    				// Only handle ACK packets
	    				if ( parsed_packet.getType() == 0 ) {
	    					// print the log for ACK
	    					ackLog.println(parsed_packet.getSeqNum());
	    					
	    						
	    					if ( ((first_of_the_10_sent_packet - parsed_packet.getSeqNum()) >= 0) 
	    							&& ((first_of_the_10_sent_packet - parsed_packet.getSeqNum()) < 10) 
	    							|| ((first_of_the_10_sent_packet - parsed_packet.getSeqNum()) < (-22 ) ) ) {
	    						if ( packets.size() > 0 ) {
	    							for (int n = 0; n < 9; n++){
	    								if ( packets.get(n).getSeqNum() == parsed_packet.getSeqNum() ){
	    									packets.remove(n);
	    									sent_or_not.remove(n);
	    									remaining_window_size++;
	    								}
	    							}
	    							if ( (( packets.get(0).getSeqNum() - parsed_packet.getSeqNum()) >= 0)
	    									&& (( packets.get(0).getSeqNum() - parsed_packet.getSeqNum()) < 10)
	    									|| (( packets.get(0).getSeqNum() - parsed_packet.getSeqNum()) < (-22 ) ) ){
	    								
	    							first_of_the_10_sent_packet = packets.get(0).getSeqNum(); 
	    							// confirm a successfully transferred packet
	    							
	    							// remaining_window_size++;
	    							}
	    							//System.out.println(packets.size() + " ACKed: " + first_of_the_10_sent_packet + " remaining_window_size: " + remaining_window_size);
	    							if ( first_of_the_10_sent_packet == 32 ) { 
	    								first_of_the_10_sent_packet = 0;
	    							}
	    						}
	    					}	
	    				}
	    			}
	            }
	    		catch (Exception e) {
					e.printStackTrace();
	            }
	    	}
	    };
	    threadReceiveACK.start();
		
	    while (packets.size() != 0) {
	    	int difference;
	    	System.out.println(remaining_window_size);
	    	System.out.println("reamining packets to send:");
	    	System.out.println(remaining_packets_to_send);
	    	for (int n = 0; n < 10 && n < remaining_packets_to_send ; n++){
//	    		System.out.println("before send");
	    		difference = packets.get(n).getSeqNum() - first_of_the_10_sent_packet;
/*	    		System.out.println("the value of n is:");
	    		System.out.println(n);
	    		System.out.println("the value of difference is:");
	    		System.out.println(difference);
	    		System.out.println(packets.get(n).getSeqNum()); */
	    		if (difference < 0) difference = difference + 32;
	    		if (sent_or_not.get(n) == false && difference < 10 && remaining_window_size > 0){
	    			sent_or_not.set(n, true);
	    			sendPacket(packets.get(n), n);
	    			remaining_window_size--;
	    			remaining_packets_to_send--;
	    			System.out.println ("success send");
	    			n++;
	    			break;
	    		} 
	    	}
	    }
	    
		// Send final EOT packet
		if ( packets.size() == 0 ) {
			//System.out.println("FINAL ACK!");
			packet EOT = packet.createEOT(seq);
			sendPacket(EOT, 0);
		}
		

		ackLog.close();
		seqnumLog.close();
		threadReceiveACK.interrupt();
		System.exit(0);
	}
	
	
	void sendPacket(packet p, int n) throws Exception {
		byte[] data = new byte[512];
		data = p.getUDPdata();
		DatagramPacket sendPacket = new DatagramPacket(data, data.length, NE_name, data_portno);
		data_EOT_socket.send(sendPacket);
		final int seqNum = p.getSeqNum();
		final int index = n;
		seqnumLog.println(seqNum); // Log
		
		Timer timer= new Timer(180, new ActionListener() { 
		    public void actionPerformed(ActionEvent e) {
		    	if (sent_or_not.size() != 0)
		    		sent_or_not.set(index, true);
		    		remaining_packets_to_send++;
		    } 
		});
		timer.setRepeats(false);
		timer.start();
	}
	
	// Entry point
	public static void main(String[] args) {
		try {
			sender exe = new sender(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]), args[3]);
			exe.execute();
		}
		catch (Exception e) {
			new Exception().printStackTrace();
			System.err.println("Error in input");
			System.exit(1);
		}
	}
	
}

