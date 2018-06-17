package pool8_0809_version2;

import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class PoolManager {
	private static Map<Class<?>, Pool> maps = new HashMap<>();

	// ��̬����������key����ö�Ӧ�Ķ�������maps�и�key��Ӧ��poolΪ�գ����½�һ�����key��Ӧ��pool��put��maps����󷵻ض���
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

	
	
	
	
	/* ���������PoolManager�Ļ�����Ϣ���H���yԇʹ�� */
	// ���maps���ܹ��ж����ֶ�������
	public static void printSizeOfKind() {
		System.out.println(maps.size());
	}

	// ��ӡmaps�и��ֶ������͵�����
	public static void printKind() {
		Set<Class<?>> keySet = maps.keySet();
		for (Object keyName : keySet) {
			System.out.println(keyName);
		}
	}

	// ��ӡÿ�ֶ������Ͷ�Ӧ��pool��list����ϸ��Ϣ
	public static Map<String, Integer> printPerKindDetail() {
		Map<String, Integer> detailMap = new HashMap<String, Integer>();
		Set<Class<?>> keySet = maps.keySet();
		for (Object keyName : keySet) {
			detailMap.put(keyName.toString(), maps.get(keyName).getSize());
		}
		return detailMap;
	}

	/* ������һ����̬�࣬��һ�����������ݲ���key��������ͬ�������͵Ķ���أ� */
	static class PoolFactory {
		public static Pool create(Class<?> key) throws InstantiationException, IllegalAccessException {
			return new Pool(key);
		}
	}

}
