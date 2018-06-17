package pool8_0809_version2;

public class MyClass implements PoolItem{
	private String name = "asd";
	private int age = 1;
	
	public MyClass(){}
	
	public MyClass(String name){}
	
	public void reset(){
		this.name = null;
		this.age = 0;
	}
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}
}
