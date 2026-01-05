/**
* Esta aplicación muestra las palabras introducidas en la terminal junto con sus longitudes y la frecuencia de cada longitud
*
* @author Antonio Moroño Moreno y Pedro Ismael Haddou Acosta
*
*/
public class FrecuenciaPalabras {

/**
* Este método imprime las frecuencias de longitudes de palabras proporcionadas por la línea de
* comandos
* 
* @param args Los argumentos de la línea de comando. Se esperan palabras, como
*             cadenas
*/
public static void main(String[] args) {

    if (args.length == 0)
        System.err.println("Se espera al menos una palabra como parametro.");
    else {
        LongitudPalabras palabras = new LongitudPalabras(args);
    
        System.out.println(palabras);
        System.out.println("Palabras almacenadas: " + palabras.getPalabras());
    
        imprimeFrecuencias(palabras);
    }   
}

/**
* Imprime por pantalla las frecuencias de longitudes de palabras
* 
* @param palabras
*/
private static void imprimeFrecuencias(LongitudPalabras palabras) {
    System.out.println(palabras);
    for(int longitud : palabras.getLongitudesUnicas())
        System.out.println("Hay "+palabras.getFrecuencia(longitud)+" palabras de "+longitud+" letras.");
}
}
