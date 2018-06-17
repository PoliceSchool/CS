package pool8_0809_version2;

import pool7_0809.runner1;
import pool7_0809.runner2;


public class Client3 {

	public static void main(String[] args) throws InterruptedException {
		int i;	
		for(i = 0; i<100; i++){
			new runner1(i).start();
			new runner2().start();
			Thread.sleep(100);
		}
	}
}
