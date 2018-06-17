package pool8_0809_version2;

public class MyType implements PoolItem{
	private String password;
	private String name;
	
	
	public void reset(){
		this.name = null;
		this.password = null;
	}
	
	
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
}
