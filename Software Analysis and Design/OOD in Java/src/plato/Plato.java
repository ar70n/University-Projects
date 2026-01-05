package plato;

import java.util.*;
import ingrediente.*;
import infoNutricional.*;
import planificador.ElementoNutricional;

/**
 * La clase Plato representa un plato de comida con su nombre, ingredientes, información nutricional, alérgenos y otros platos relacionados.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public class Plato{

    private String nombre;
    Map<Ingrediente, Integer> ingredientes = new HashMap<Ingrediente, Integer>();
    private Set<Plato> platos;
    private InfoNutricionalPlato info;
    private Set<Alergeno> alergenos;

    /**
     * Constructor de la clase Plato.
     * 
     * @param nombre el nombre del plato
     */
    public Plato(String nombre) {
        this.nombre = nombre;
        this.platos = new HashSet<Plato>();
        this.info = new InfoNutricionalPlato();
        this.alergenos = new HashSet<Alergeno>();
    }

    /**
     * Añade un ingrediente a la lista de ingredientes del plato.
     * 
     * @param ingrediente el ingrediente a añadir
     * @param cantidad la cantidad del ingrediente a añadir
     * @return true si el ingrediente ya existe en la lista, false si se añade correctamente
     */
    public boolean addIngrediente(Ingrediente ingrediente, int cantidad) {
        if (this.ingredientes.containsKey(ingrediente)){
            return true;
        }
        this.ingredientes.put(ingrediente, cantidad);
        this.info.sumarInfo(ingrediente.getInfo(), cantidad);
        this.alergenos.addAll(ingrediente.getAlergenos());

        return false;
    }

    /**
     * Añade un plato a la lista de platos relacionados.
     * 
     * @param plato el plato a añadir
     * @return true si el plato ya existe en la lista, false si se añade correctamente
     */
    public boolean addPlato(Plato plato) {
        if (this.platos.contains(plato)) {
            return true;
        }

        this.info.sumarInfo(plato.getInfo());

        this.alergenos.addAll(plato.getAlergenos());
        this.platos.add(plato);
        return false;
    }

    /* Getters */

    /**
     * Devuelve la información nutricional del plato.
     * 
     * @return la información nutricional del plato
     */
    public InfoNutricionalPlato getInfo() {
        return this.info;
    }
    
    /**
     * Devuelve el nombre del plato.
     * 
     * @return el nombre del plato
     */
    public String getNombre() {
    	return this.nombre;
    }
    
    /**
     * Devuelve los ingredientes del plato.
     * 
     * @return los ingredientes del plato
     */
    public Set<Ingrediente> getIngredientes(){
    	return this.ingredientes.keySet();
    }

    /**
     * Devuelve los alérgenos del plato.
     * 
     * @return los alérgenos del plato
     */
    public Set<Alergeno> getAlergenos() {
        return this.alergenos;
    }
    
    /**
     * Devuelve los platos relacionados.
     * 
     * @return los platos relacionados
     */
    public Set<Plato> getPlatos() {
    	return this.platos;
    }
    
    /**
     * Verifica si el plato contiene un plato específico.
     * 
     * @param plato el plato a verificar
     * @return true si el plato está contenido, false si no
     */
    public boolean contienePlato(Plato plato) {
    	return this.platos.contains(plato);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("[Plato] ").append(this.nombre).append(": INFORMACION NUTRICIONAL DEL PLATO ").append(this.info.toString());
        if (!this.alergenos.isEmpty()) {
            sb.append("\nCONTIENE: ");
            for (Alergeno alergeno : this.alergenos) {
                sb.append(alergeno.getNombre()).append(", ");
            }
            // Remove the trailing comma and space
            sb.setLength(sb.length() - 2);
        }
        return sb.toString();
    }

    /**
     * Imprime los ingredientes del plato.
     * 
     * @return una cadena de texto con los ingredientes del plato
     */
    public String printIngredientes(){
        String texto="";
        for (Ingrediente ingrediente : this.ingredientes.keySet()) {
            texto+=";INGREDIENTE "+ingrediente.getNombre()+":"+this.ingredientes.get(ingrediente);
        }
        return texto;
    }

    /**
     * Imprime los platos relacionados.
     * 
     * @return una cadena de texto con los platos relacionados
     */
    public String printPlatos(){
        String texto="";
        for (Plato plato : this.platos) {
            texto+=";PLATO "+plato.getNombre();
        }
        return texto;
    }
    
    /**
     * Devuelve el total de calorías del plato.
     * 
     * @return el total de calorías del plato
     */
    public double getCalorias() {
    	return this.info.getCalorias();
    }
    
    /**
     * Verifica si el plato contiene todos los alérgenos especificados.
     * 
     * @param alergenos los alérgenos a verificar
     * @return true si el plato contiene todos los alérgenos, false si no
     */
    public boolean contieneAlergenos(Set<Alergeno> alergenos) {
    	return this.alergenos.containsAll(alergenos);
    } 	

    /**
     * Devuelve el valor nutricional del plato para un nutriente específico.
     * 
     * @param nutriente el nutriente para el cual se desea obtener el valor nutricional
     * @return el valor nutricional del plato para el nutriente especificado
     * @throws IllegalArgumentException si el nutriente no es válido
     */
    public double getValorNutricional(ElementoNutricional nutriente) {
        switch (nutriente) {
            case CALORIAS:
                return this.info.getCalorias();
            case PROTEINAS:
                return this.info.getProteinas();
            case GRASAS:
                return this.info.getGrasas();
            case HIDRATOS_CARBONO:
                return this.info.getHidratosDeCarbono();
            case FIBRA:
                return this.info.getFibra();
            case SODIO:
                return this.info.getSodio();
            case AZUCARES:
                return this.info.getAzucares();
            case GRASA_SATURADA:
                return this.info.getGrasasSaturadas();
            default:
                throw new IllegalArgumentException("Nutriente no válido");
        }
    }
}