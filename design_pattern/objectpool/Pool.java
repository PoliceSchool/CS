package pool8_0809_version2;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Pool {
	private List<PoolObject> list = new ArrayList<PoolObject>();
	private Class<?> clazz;
	private final int poolInitSize = 3;
	private int poolIdleSize = poolInitSize;
	private int poolInFactSize = poolInitSize;
	private final int poolMaxSize = 5;
	private final int poolIncrementSize = 1;   //�ص�������С
	private final ReentrantLock lock = new ReentrantLock();
	private final Condition empty = lock.newCondition();

	public <T> Pool(Class<T> clazz) throws InstantiationException,
			IllegalAccessException {
		this.clazz = clazz;
		for(int i=0; i<this.poolInitSize; i++){
			list.add(new PoolObject((PoolItem)clazz.newInstance()));
		}
	}

	public String toString(){
		return clazz + " �س�ʼ��С��" + poolInitSize + " �ؿ��ж���" + poolIdleSize + " ����ʵ��С" + poolInFactSize + " �����������" + poolMaxSize;
	}
	
	@SuppressWarnings("finally")
	public Object borrowObject() throws InstantiationException,
			IllegalAccessException {
		PoolItem poolItem = null;
		this.lock.lock();
		try {
			while (this.poolIdleSize <= 0
					&& this.poolInFactSize >= this.poolMaxSize) {
				System.out.println("�ض����㣬����..." + Thread.currentThread().getName());
				this.empty.await(); // �ض����㣬����
			}

			if (this.poolIdleSize <= 0) {
				addObject2Pool();
			}
			int size = this.list.size();
			for (int i = 0; i < size; i++) {
				if (this.list.get(i).isUse() == false) {
					this.list.get(i).setUse(true);
					// ���صĿ��ж���������һ
					--this.poolIdleSize;
					//System.out.println("������ͣ�" + this.clazz + " �ڳ��е����" + i);
					poolItem = list.get(i).getPoolItem();
					break;
				}
			}
			
		} catch (InterruptedException e) {
			e.printStackTrace();
		} finally {
			this.lock.unlock();
			return poolItem;
		}
	}

	public void returnObject(Object object) throws InstantiationException,
			IllegalAccessException, IllegalArgumentException,
			InvocationTargetException, NoSuchMethodException, SecurityException {
		this.lock.lock();
		int size = this.list.size();
		boolean flag = false;
		for (int i = 0; i < size; i++) {
			if (this.list.get(i).getPoolItem() == object) {
				flag = true;
				++this.poolIdleSize;
				resetObject(object);
				this.list.get(i).setUse(false);
				System.out.println("�̣߳�" + Thread.currentThread().getName() + "������ĵ�ַΪ��" + list.get(i).getPoolItem());
			}
		}
		if(flag == false){
			System.out.println("�黹���ɹ�");
		}
		
		// ���������߳�
		empty.signal();
		// �ͷ���
		lock.unlock();
	}

	// ���ö��������ֵ�����������ݵĲ���
	public void resetObject(Object object)
			throws IllegalArgumentException, IllegalAccessException,
			InvocationTargetException, NoSuchMethodException, SecurityException {
		Method method = this.clazz.getDeclaredMethod("reset");
		method.invoke(object);
	}

	public void addObject2Pool() throws InstantiationException, IllegalAccessException{
		for(int i=0; i<this.poolIncrementSize; i++){
			this.list.add(new PoolObject((PoolItem)this.clazz.newInstance()));
		}
		this.poolInFactSize += this.poolIncrementSize;
		this.poolIdleSize += this.poolIncrementSize;
		System.out.println("�߳�:" + Thread.currentThread().getName() + "  the " + this.clazz + " �ճز����½�һ������" + " ����ش�С��" + this.poolInFactSize);
		//this.empty.notify();
	}
	
	public int getSize(){
		return this.list.size();
	}


	class PoolObject {
		private PoolItem poolItem;
		private boolean isUse = false;

		public PoolObject(PoolItem poolItem) {
			this.poolItem = poolItem;
		}


		public PoolItem getPoolItem() {
			return poolItem;
		}

		public void setPoolItem(PoolItem poolItem) {
			this.poolItem = poolItem;
		}

		public boolean isUse() {
			return isUse;
		}

		public void setUse(boolean isUse) {
			this.isUse = isUse;
		}
	}
}
