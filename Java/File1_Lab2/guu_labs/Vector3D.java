package ru.guu_labs;
import java.util.Scanner;

public class Vector3D {
    private double x, y, z;

    public void init(double x_val, double y_val, double z_val) {
        x = x_val;
        y = y_val;
        z = z_val;
    }

    public void read() {
        Scanner in = new Scanner(System.in);
        System.out.print("Введите координату x: ");
        x = in.nextDouble();
        System.out.print("Введите координату y: ");
        y = in.nextDouble();
        System.out.print("Введите координату z: ");
        z = in.nextDouble();
    }

    public String toString() {
        return "(" + x + ", " + y + ", " + z + ")";
    }

    public void display() {
        System.out.println(toString());
    }

    public Vector3D add(Vector3D other) {
        Vector3D res = new Vector3D();
        res.x = x + other.x;
        res.y = y + other.y;
        res.z = z + other.z;
        return res;
    }

    public Vector3D sub(Vector3D other) {
        Vector3D res = new Vector3D();
        res.x = x - other.x;
        res.y = y - other.y;
        res.z = z - other.z;
        return res;
    }

    public double dotProduct(Vector3D other) {
        return x * other.x + y * other.y + z * other.z;
    }

    public Vector3D mul(double scalar) {
        Vector3D res = new Vector3D();
        res.x = x * scalar;
        res.y = y * scalar;
        res.z = z * scalar;
        return res;
    }

    public boolean equ(Vector3D other) {
        return this.x == other.x && this.y == other.y && this.z == other.z;
    }

    public double length() {
        return Math.sqrt(x * x + y * y + z * z);
    }

    public int compareLength(Vector3D other) {
        double thisLength = this.length();
        double otherLength = other.length();
        if (thisLength > otherLength) {
            return 1;
        } else if (thisLength < otherLength) {
            return -1;
        } else {
            return 0;
        }
    }
}
