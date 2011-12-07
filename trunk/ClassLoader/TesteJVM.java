import java.util.Arrays;


public class TesteJVM {
	public double x = 12.23;
	public int h = 12;
	float y = 14.34f;
	int z = 10;
	
	public TesteJVM() {
		
	}
	public static void main(String[] args) {
		System.out.println(args[0]);
		System.out.println((Arrays.toString(args)));
		new TesteJVM();
	}
	
	private int multiplica() {
		int k = 10;
		k = z*k;
		return k;
	}
	
	private int soma(int argumento1, int argumento2) {
		return argumento1 + argumento2;
	}

}
