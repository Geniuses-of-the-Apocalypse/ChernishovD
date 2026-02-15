package ru.guu_labs;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        Vector3D v1 = new Vector3D();
        Vector3D v2 = new Vector3D();

        System.out.println("Ввод первого вектора:");
        v1.read();

        System.out.println("\nВвод второго вектора:");
        v2.read();

        System.out.print("\nv1 = ");
        v1.display();
        System.out.print("v2 = ");
        v2.display();

        Vector3D sum = v1.add(v2);
        System.out.print("\nСумма v1 + v2 = ");
        sum.display();

        Vector3D diff = v1.sub(v2);
        System.out.print("Разность v1 - v2 = ");
        diff.display();

        double dot = v1.dotProduct(v2);
        System.out.println("Скалярное произведение v1·v2 = " + dot);

        System.out.print("\nВведите скаляр для умножения на v1: ");
        double scalar = scanner.nextDouble();
        Vector3D scaled = v1.mul(scalar);
        System.out.print("Результат умножения v1 на " + scalar + " = ");
        scaled.display();

        System.out.println("\nv1 равен v2? " + v1.equ(v2));

        System.out.println("Длина v1 = " + v1.length());
        System.out.println("Длина v2 = " + v2.length());

        int comparison = v1.compareLength(v2);
        System.out.print("Сравнение длин: ");
        if (comparison > 0) {
            System.out.println("v1 Длинее v2");
        } else if (comparison < 0) {
            System.out.println("v1 короче v2");
        } else {
            System.out.println("длины равны");
        }
    }
}
