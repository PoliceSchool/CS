package pool8_0809_version2;

import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class PoolManager {
	private static Map<Class<?>, Pool> maps = new HashMap<>();

	// 静态方法，根据key来获得对应的对象，若在maps中该key对应的pool为空，则新建一个与该key对应的pool再put进maps，最后返回对象。
	@SuppressWarnings("unchecked")
	public static <T> T borrowObject(Class<T> key) throws InstantiationException, IllegalAccessException {
		if (maps.get(key) == null) {
			synchronized (maps) {
				if (maps.get(key) == null) {
					System.out.println("The first time create " + key + " pool in the maps!");
					Pool pool = PoolFactory.create(key);
					maps.put(key, pool);
				}
			}
		}
		return (T) maps.get(key).borrowObject();
	}

	public static /* synchronized */ void returnObject(Object object)
			throws InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException,
			NoSuchMethodException, SecurityException {
		maps.get(object.getClass()).returnObject(object);
	}

	
	
	
	
	/* 以下是输出PoolManager的基本信息，僅供測試使用 */
	// 输出maps中总共有多少种对象类型
	public static void printSizeOfKind() {
		System.out.println(maps.size());
	}

	// 打印maps中各种对象类型的名称
	public static void printKind() {
		Set<Class<?>> keySet = maps.keySet();
		for (Object keyName : keySet) {
			System.out.println(keyName);
		}
	}

	// 打印每种对象类型对应的pool中list的详细信息
	public static Map<String, Integer> printPerKindDetail() {
		Map<String, Integer> detailMap = new HashMap<String, Integer>();
		Set<Class<?>> keySet = maps.keySet();
		for (Object keyName : keySet) {
			detailMap.put(keyName.toString(), maps.get(keyName).getSize());
		}
		return detailMap;
	}

	/* 以下是一个静态类，是一个工厂，根据参数key来创建不同对象类型的对象池， */
	static class PoolFactory {
		public static Pool create(Class<?> key) throws InstantiationException, IllegalAccessException {
			return new Pool(key);
		}
	}

}
