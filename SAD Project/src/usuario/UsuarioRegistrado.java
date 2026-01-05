package usuario;

import java.io.Serializable;
import java.util.Set;
import java.util.HashSet;
import mensaje.*;

public abstract class UsuarioRegistrado implements Serializable {
    protected String nif;
    protected String nombre;
    protected String contrasena;
    private static final long serialVersionUID = 1L;

    private Set<Notificacion> notificaciones;

    public UsuarioRegistrado(String nif, String nombre, String contrasena) {
        this.nif = nif;
        this.nombre = nombre;
        this.contrasena = contrasena;
        this.notificaciones = new HashSet<Notificacion>();
    }

    protected UsuarioRegistrado() {
    }

    public void recibirNotificacion(Notificacion n) {
        notificaciones.add(n);
    }

    public String getNif() {
        return nif;
    }

    public String getContrasena() {
        return contrasena;
    }

    public String getNombre() {
        return nombre;
    }

    public Set<Notificacion> getNotificaciones() {
        return notificaciones;
    }

    public abstract String getTipoUsuario();

}
