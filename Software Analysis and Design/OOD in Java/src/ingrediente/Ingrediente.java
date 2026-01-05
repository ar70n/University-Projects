package ingrediente;

import java.util.*;
import infoNutricional.*;

/**
 * La clase Ingrediente representa un ingrediente utilizado en una receta.
 * Contiene información sobre el nombre, tipo, información nutricional y alérgenos del ingrediente.
 * 
 * @author Antonio Moroño y Pedro Ismael Haddou
 * 
 */
public class Ingrediente{

    private String nombre;
    private String tipo;
    private InfoNutricional info;
    private Set<Alergeno> alergenos;

    /**
     * Constructor de la clase Ingrediente
     * 
     * @param nombre    el nombre del ingrediente,
     * @param tipo      el tipo de ingrediente,
     * @param info  la informacion nutricional del ingrediente,
     */
    public Ingrediente(String nombre, TipoIngrediente tipo, InfoNutricional info) {
        this.nombre = nombre;
        this.info = info;
        this.alergenos = new HashSet<Alergeno>();

        if (tipo != null) {
            this.tipo = tipo.getNombre();
        } else {
            this.tipo = "Sin tipo";
        }
    }

    
    /**
     * Constructor de la clase Ingrediente
     * 
     * @param nombre    el nombre del ingrediente,
     * @param tipo      el tipo de ingrediente,
     * @param info  la informacion nutricional del ingrediente,
     */
    public Ingrediente(String nombre, String tipo, InfoNutricional info) {
        this.nombre = nombre;
        this.tipo = tipo;
        this.info = info;
        this.alergenos = new HashSet<Alergeno>();
    }

    /**
     * Añade los alergenos del ingrediente.
     * 
     * @param alergenos los alergenos del ingrediente.
     * @return el ingrediente
     */
    public Ingrediente tieneAlergenos(Alergeno... alergenos) {
        for (Alergeno alergeno : alergenos) {
            this.alergenos.add(alergeno);
        }
        return this;
    }

    /* Getters */

    /**
     * Devuelve el nombre del ingrediente.
     * @return El nombre.
     */
    public String getNombre() {
        return this.nombre;
    }

    /**
     * Devuelve el tipo del ingrediente.
     * @return el tipo
     */
    public String getTipo() {
        return this.tipo;
    }

    /**
     * Devuelve la informacion nutricional del ingrediente.
     * @return la informacion nutricional
     */
    public InfoNutricional getInfo() {
        return this.info;
    }

    /**
     * Devuelve los alergenos del ingrediente.
     * @return los alergenos
     */
    public Set<Alergeno> getAlergenos() {
        return this.alergenos;
    }

    @Override
    public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("[").append(this.tipo).append("] ").append(this.nombre).append(": ").append(this.info.toString());
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
     * Devuelve el tipo de ingrediente en mayúsculas según los siguientes valores:
     * - "Carne" se convierte en "CARNE"
     * - "Pescado" se convierte en "PESCADO"
     * - "Fruta y verduras" se convierte en "FRUTA_VERDURA"
     * - "Legumbre" se convierte en "LEGUMBRE"
     * - "Cereal" se convierte en "CEREAL"
     * - "Huevo" se convierte en "HUEVO"
     * - "Lacteo" se convierte en "LACTEO"
     * Si el tipo de ingrediente no coincide con ninguno de los valores anteriores,
     * se devuelve el tipo de ingrediente sin modificar.
     *
     * @return el tipo de ingrediente en mayúsculas o el tipo de ingrediente sin modificar
     */
    public String printTipo(){
        switch (this.tipo) {
            case "Carne":
                return "CARNE";
            case "Pescado":
                return "PESCADO";
            case "Fruta y verduras":
                return "FRUTA_VERDURA";
            case "Legumbre":
                return "LEGUMBRE";  
            case "Cereal":
                return "CEREAL";   
            case "Huevo":
                return "HUEVO";
            case "Lacteo":
                return "LACTEO";
            default:
                return this.tipo;
        }
    }

    /**
     * Devuelve una cadena de texto que representa los alérgenos del ingrediente.
     * 
     * @return una cadena de texto que contiene "S" si el ingrediente contiene el alérgeno correspondiente, o "N" si no lo contiene.
     */
    public String printAlergenos(){
        String alergenos = "";
        if(this.alergenos.contains(Alergeno.GLUTEN)){
            alergenos += "S;";
        }
        else{
            alergenos += "N;";
        }

        if(this.alergenos.contains(Alergeno.LACTOSA)){
            alergenos += "S;";
        }
        else{
            alergenos += "N;";
        }

        if(this.alergenos.contains(Alergeno.FRUTOS_SECOS)){
            alergenos += "S;";
        }
        else{
            alergenos += "N;";
        }

        if(this.alergenos.contains(Alergeno.HUEVO)){
            alergenos += "S";
        }
        else{
            alergenos += "N";
        }


        return alergenos;
    }
}