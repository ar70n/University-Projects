package fichero;

import galeria.obra.*;
import sistema.Sistema;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.BufferedReader;

/**
 * Clase que maneja la lectura y escritura de archivos y la carga de obras.
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class ManejadorFicheros {

    /**
     * Guarda un objeto en un archivo.
     * 
     * @param obj      el objeto a guardar
     * @param filename el nombre del archivo
     * @throws IOException si ocurre un error de entrada/salida
     */
    public static void guardar(Object obj, String filename) throws IOException {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(obj);
        }
    }

    /**
     * Carga un objeto desde un archivo.
     * 
     * @param filename el nombre del archivo
     * @return el objeto cargado desde el archivo
     * @throws IOException            si ocurre un error de entrada/salida
     * @throws ClassNotFoundException si la clase del objeto no se encuentra
     */
    public static Object cargar(String filename) throws IOException, ClassNotFoundException {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename))) {
            return ois.readObject();
        }
    }

    /**
     * Lee las obras desde un archivo y las agrega al sistema.
     * 
     * @param fichero el nombre del archivo
     */
    public static void leerObras(String fichero) {
        String line = "";
        String separador = ";";
        String nombre;
        String autor;
        int fecha;
        String descripcion;
        double seguroCuantia;
        String seguroPoliza;
        boolean enPropiedad;

        try (BufferedReader br = new BufferedReader(new FileReader(fichero))) {

            br.readLine(); // Saltar la primera línea

            while ((line = br.readLine()) != null) {
                // Usa punto y coma como separador
                String[] fields = line.split(separador, -1);

                // Crea una obra con los campos leídos
                nombre = fields[2];
                autor = fields[3];
                fecha = Integer.parseInt(fields[4]);
                descripcion = fields[5];
                seguroCuantia = Double.parseDouble(fields[6]);
                seguroPoliza = fields[7];
                if ("CENTRO".equals(fields[1])) {
                    enPropiedad = true;
                } else {
                    enPropiedad = false;
                }

                if ("CUADRO".equals(fields[0]) || "ESCULTURA".equals(fields[0]) || "FOTOGRAFIA".equals(fields[0])) {
                    double temperaturaMin;
                    double temperaturaMax;
                    boolean requiereTemp;
                    double humedadMin;
                    double humedadMax;
                    boolean requiereHum;

                    if (!"".equals(fields[16].split("--")[0])) {
                        temperaturaMin = Double.parseDouble(fields[16].split("--")[0]);
                        temperaturaMax = Double.parseDouble(fields[16].split("--")[1]);
                        requiereTemp = true;
                    } else {
                        temperaturaMin = 0;
                        temperaturaMax = 0;
                        requiereTemp = false;
                    }
                    if (!"".equals(fields[17].split("--")[0])) {
                        humedadMin = Double.parseDouble(fields[17].split("--")[0]);
                        humedadMax = Double.parseDouble(fields[17].split("--")[1]);
                        requiereHum = true;
                    } else {
                        humedadMin = 0;
                        humedadMax = 0;
                        requiereHum = false;
                    }
                    double ancho = Double.parseDouble(fields[13]);
                    double alto = Double.parseDouble(fields[14]);
                    double largo = 0;
                    if (!"".equals(fields[15])) {
                        largo = Double.parseDouble(fields[15]);
                    }

                    if ("CUADRO".equals(fields[0])) {
                        String tecnica = fields[8];
                        Cuadro obra = new Cuadro(nombre, autor, fecha, descripcion, seguroCuantia, seguroPoliza,
                                enPropiedad, temperaturaMin, temperaturaMax, humedadMin, humedadMax, requiereTemp,
                                requiereHum, ancho, alto, largo, tecnica);
                        Sistema.addObras(obra);
                    }
                    if ("ESCULTURA".equals(fields[0])) {
                        String material = fields[9];
                        Escultura obra = new Escultura(nombre, autor, fecha, descripcion, seguroCuantia, seguroPoliza,
                                enPropiedad, temperaturaMin, temperaturaMax, humedadMin, humedadMax, requiereTemp,
                                requiereHum, ancho, alto, largo, material);
                        Sistema.addObras(obra);
                    }
                    if ("FOTOGRAFIA".equals(fields[0])) {
                        boolean color;
                        if ("Color".equals(fields[10])) {
                            color = true;
                        } else {
                            color = false;
                        }
                        Fotografia obra = new Fotografia(nombre, autor, fecha, descripcion, seguroCuantia,
                                seguroPoliza, enPropiedad, temperaturaMin, temperaturaMax, humedadMin, humedadMax,
                                requiereTemp, requiereHum, ancho, alto, largo, color);
                        Sistema.addObras(obra);
                    }
                } else {
                    String idioma = fields[12];
                    String[] partes = fields[11].split("\\D+");

                    int horas = Integer.parseInt(partes[0]);
                    int minutos = Integer.parseInt(partes[1]);
                    int segundos = Integer.parseInt(partes[2]);

                    int totalSegundos = horas * 3600 + minutos * 60 + segundos;

                    Audiovisual obra = new Audiovisual(nombre, autor, fecha, descripcion, seguroCuantia, seguroPoliza,
                            enPropiedad, totalSegundos, idioma);
                    Sistema.addObras(obra);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
