package pool8_0809_version2;

import java.lang.reflect.InvocationTargetException;

public class runner2 extends Thread{
	private MyType myType;
	
	public void run(){
		try {
			myType = PoolManager.borrowObject(MyType.class);
			System.out.println("线程：" + this.getName() + "借到对象的地址为：" + myType);
			//myType.setName("myType" + i);
			sleep(5000);
			//System.out.println("returnObject: myClass" + i);
			PoolManager.returnObject(myType);
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
