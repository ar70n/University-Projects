package galeria;

import java.io.Serializable;

/**
 * La clase Vector3 representa un vector tridimensional en un sistema de
 * coordenadas cartesianas.
 * Los atributos de la clase son el ancho, alto y largo del vector.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Vector3 implements Serializable {
    private double x; // ancho en cm
    private double y; // alto en cm
    private double z; // largo en cm
    private static final long serialVersionUID = 1L;

    /**
     * Constructor de la clase Vector3.
     * 
     * @param ancho el ancho del vector en cm
     * @param alto  el alto del vector en cm
     * @param largo el largo del vector en cm
     */
    public Vector3(double ancho, double alto, double largo) {
        this.x = ancho;
        this.y = alto;
        this.z = largo;
    }

    /**
     * Constructor vacío de la clase Vector3.
     */
    public Vector3() {
    }

    /**
     * Obtiene el valor del ancho del vector.
     * 
     * @return el valor del ancho del vector
     */
    public double getX() {
        return this.x;
    }

    /**
     * Obtiene el valor del alto del vector.
     * 
     * @return el valor del alto del vector
     */
    public double getY() {
        return this.y;
    }

    /**
     * Obtiene el valor del largo del vector.
     * 
     * @return el valor del largo del vector
     */
    public double getZ() {
        return this.z;
    }

    /**
     * Establece las dimensiones del vector.
     * 
     * @param ancho el nuevo valor del ancho del vector en cm
     * @param alto  el nuevo valor del alto del vector en cm
     * @param largo el nuevo valor del largo del vector en cm
     * @throws IllegalArgumentException si alguna de las dimensiones es negativa
     */
    public void setDimensiones(double ancho, double alto, double largo) throws IllegalArgumentException {
        if (ancho < 0 || alto < 0 || largo < 0) {
            throw new IllegalArgumentException("Las dimensiones no deben ser negativas");
        }
        this.x = ancho;
        this.y = alto;
        this.z = largo;
    }

    /**
     * Calcula el volumen del vector.
     * 
     * @return el volumen del vector
     */
    public double volumen() {
        return this.getX() * this.getY() * this.getZ();
    }

    /**
     * Devuelve una representación en forma de cadena del vector.
     * 
     * @return una cadena que representa el vector en el formato "Vector3
     *         [Ancho(X)=x, Alto(Y)=y, Largo(Z)=z]"
     */
    @Override
    public String toString() {
        return "Vector3 [Ancho(X)=" + x + ", Alto(Y)=" + y + ", Largo(Z)=" + z + "]";
    }
}