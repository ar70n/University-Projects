package infoNutricional;
import java.util.Locale;

/**
 * La clase InfoNutricional representa la información nutricional de un ingrediente.
 * Contiene los valores de calorías, hidratos de carbono, grasas totales, grasas saturadas,
 * proteínas, azúcares, fibra y sodio.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public abstract class InfoNutricional{
    private double calorias;
    private double hidratos;
    private double grasasTotales;
    private double grasasSaturadas;
    private double proteinas;
    private double azucares;
    private double fibra;
    private double sodio;

    /**
     * Constructor de la clase InfoNutricional
     * 
     * @param calorias        las calorias del ingrediente
     * @param hidratos        los hidratos de carbono del ingrediente
     * @param grasasTotales   las grasas totales del ingrediente
     * @param grasasSaturadas las grasas saturadas del ingrediente
     * @param proteinas       las proteinas del ingrediente
     * @param azucares        los azucares del ingrediente
     * @param fibra           la fibra del ingrediente
     * @param sodio           el sodio del ingrediente
     * 
     */
    public InfoNutricional(double calorias, double hidratos, double grasasTotales, double grasasSaturadas,
            double proteinas, double azucares, double fibra, double sodio) {
        this.calorias = calorias;
        this.hidratos = hidratos;
        this.grasasTotales = grasasTotales;
        this.grasasSaturadas = grasasSaturadas;
        this.proteinas = proteinas;
        this.azucares = azucares;
        this.fibra = fibra;
        this.sodio = sodio;
    }

    public InfoNutricional() {
        this.calorias = 0;
        this.hidratos = 0;
        this.grasasTotales = 0;
        this.grasasSaturadas = 0;
        this.proteinas = 0;
        this.azucares = 0;
        this.fibra = 0;
        this.sodio = 0;
    }

    /* Getters */

    /*
     * Devuelve las calorias
     */
    public double getCalorias() {
        return this.calorias;
    }

    /*
     * Devuelve los hidratos de carbono
     */
    public double getHidratosDeCarbono() {
        return this.hidratos;
    }

    /*
     * Devuelve las grasas totales
     */
    public double getGrasas() {
        return this.grasasTotales;
    }

    /*
     * Devuelve las grasas saturadas
     */
    public double getGrasasSaturadas() {
        return this.grasasSaturadas;
    }

    /* 
     * Devuelve las proteinas
     */
    public double getProteinas() {
        return this.proteinas;
    }

    /* 
     * Devuelve los azucares
     */
    public double getAzucares() {
        return this.azucares;
    }

    /* 
     * Devuelve la fibra
     */
    public double getFibra() {
        return this.fibra;
    }

    /*
     * Devuelve el sodio
     */
    public double getSodio() {
        return this.sodio;
    }

    /* Setters */

    /*
     * Establece las calorias
     */
    public void setCalorias(double calorias) {
        this.calorias = calorias;
    }

    /*
     * Establece los hidratos de carbono
     */
    public void setHidratosDeCarbono(double hidratos) {
        this.hidratos = hidratos;
    }

    /*
     * Establece las grasas totales
     */
    public void setGrasas(double grasas) {
        this.grasasTotales = grasas;
    }   

    /* 
     * Establece las grasas saturadas
     */
    public void setGrasasSaturadas(double grasasSaturadas) {
        this.grasasSaturadas = grasasSaturadas;
    }

    /*
     * Establece las proteinas
     */
    public void setProteinas(double proteinas) {
        this.proteinas = proteinas;
    }

    /*
     * Establece los azucares
     */
    public void setAzucares(double azucares) {
        this.azucares = azucares;
    }

    /*
     * Establece la fibra
     */
    public void setFibra(double fibra) {
        this.fibra = fibra;
    }

    /*
     * Establece el sodio
     */
    public void setSodio(double sodio) {
        this.sodio = sodio;
    }

    /*
     * Devuelve el factor de conversion
     */
    public double factor(double cantidad){
        return cantidad;
    }

    @Override
    public String toString() {
        
        return String.format(Locale.US,"-> Valor Energetico: %.2f kcal, Hidratos de Carobono: %.2f g, Grasas: %.2f g, Saturadas: %.2f g, Proteinas: %.2f g, Azucares: %.2f g, Fibra: %.2f g, Sodio: %.2f mg.",this.calorias,this.hidratos,this.grasasTotales,this.grasasSaturadas,this.proteinas,this.azucares,this.fibra,this.sodio);    
    }

    public abstract String printInfo();
}
