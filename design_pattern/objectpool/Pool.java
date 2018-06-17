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
	private final int poolIncrementSize = 1;   //池的增量大小
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
		return clazz + " 池初始大小：" + poolInitSize + " 池空闲对象" + poolIdleSize + " 池真实大小" + poolInFactSize + " 池最大数量：" + poolMaxSize;
	}
	
	@SuppressWarnings("finally")
	public Object borrowObject() throws InstantiationException,
			IllegalAccessException {
		PoolItem poolItem = null;
		this.lock.lock();
		try {
			while (this.poolIdleSize <= 0
					&& this.poolInFactSize >= this.poolMaxSize) {
				System.out.println("池对象不足，阻塞..." + Thread.currentThread().getName());
				this.empty.await(); // 池对象不足，阻塞
			}

			if (this.poolIdleSize <= 0) {
				addObject2Pool();
			}
			int size = this.list.size();
			for (int i = 0; i < size; i++) {
				if (this.list.get(i).isUse() == false) {
					this.list.get(i).setUse(true);
					// 将池的空闲对象数量减一
					--this.poolIdleSize;
					//System.out.println("借出类型：" + this.clazz + " 在池中的順序：" + i);
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
				System.out.println("线程：" + Thread.currentThread().getName() + "还对象的地址为：" + list.get(i).getPoolItem());
			}
		}
		if(flag == false){
			System.out.println("归还不成功");
		}
		
		// 唤醒其他线程
		empty.signal();
		// 释放锁
		lock.unlock();
	}

	// 重置对象的属性值，避免脏数据的残留
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
		System.out.println("线程:" + Thread.currentThread().getName() + "  the " + this.clazz + " 空池并且新建一个对象" + " 对象池大小：" + this.poolInFactSize);
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
