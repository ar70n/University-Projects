package usuario;

import galeria.sala.*;
import galeria.obra.*;
import galeria.exposicion.*;
import descuento.*;
import galeria.*;
import sistema.*;
import entrada.Entrada;
import entrada.Visita;

import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.*;

/**
 * Clase que representa a un Gestor en el sistema.
 * Extiende de la clase UsuarioRegistrado.
 * 
 * 
 * @author Miguel Campo
 * @author Jorge Jiménez
 * @author Antonio Moroño
 * @author Javier Asensio
 */
public class Gestor extends UsuarioRegistrado {
	private static final long serialVersionUID = 1L;

	/**
	 * Constructor de la clase Gestor.
	 * 
	 * @param nif        el NIF del gestor
	 * @param nombre     el nombre del gestor
	 * @param contrasena la contraseña del gestor
	 */
	public Gestor(String nif, String nombre, String contrasena) {
		super(nif, nombre, contrasena);
	}

	/**
	 * Constructor vacío de la clase Gestor.
	 */
	public Gestor() {
		super();
	}

	/**
	 * Crea un nuevo SorteoActivo y lo agrega al sistema.
	 * 
	 * @param e             la exposición asociada al sorteo
	 * @param penalizacion  la penalización del sorteo
	 * @param entradas      el número de entradas del sorteo
	 * @param finSorteo     la fecha y hora de finalización del sorteo
	 * @param validezInicio la fecha y hora de inicio de validez del sorteo
	 * @param validezFinal  la fecha y hora de finalización de validez del sorteo
	 * @return el SorteoActivo creado
	 */
	public SorteoActivo crearSorteo(Exposicion e, int penalizacion, int entradas, LocalDateTime finSorteo,
			LocalDateTime validezInicio, LocalDateTime validezFinal) {
		SorteoActivo s = new SorteoActivo(penalizacion, entradas, finSorteo, validezInicio, validezFinal, e);
		Sistema.addSorteos(s);
		return s;
	}

	/**
	 * Realiza el sorteo de un SorteoActivo y entrega los regalos.
	 * 
	 * @param s el SorteoActivo a sortear
	 */
	public void sortear(SorteoActivo s) {
		s.darRegalos();
	}

	/**
	 * Crea una nueva ExposicionPermanente y la agrega al sistema.
	 * 
	 * @param nombre      el nombre de la exposición permanente
	 * @param descripcion la descripción de la exposición permanente
	 * @param apertura    la fecha y hora de apertura de la exposición permanente
	 * @return la ExposicionPermanente creada
	 */
	public Permanente crearExposicionPermanente(String nombre, String descripcion, LocalDateTime apertura) {
		
		if (nombre == null || nombre.isEmpty() || descripcion == null || descripcion.isEmpty()) {
			throw new IllegalArgumentException("El nombre de la exposición no puede ser nulo o vacío");
		}

		Permanente p = new Permanente(nombre, descripcion, apertura);
		Sistema.addExposiciones(p);
		return p;
	}

	/**
	 * Crea una nueva ExposicionTemporal y la agrega al sistema.
	 * 
	 * @param nombre      el nombre de la exposición temporal
	 * @param descripcion la descripción de la exposición temporal
	 * @param apertura    la fecha y hora de apertura de la exposición temporal
	 * @param cierre      la fecha y hora de cierre de la exposición temporal
	 * @return la ExposicionTemporal creada
	 */
	public Temporal crearExposicionTemporal(String nombre, String descripcion, LocalDateTime apertura,
			LocalDateTime cierre) {
		if (nombre == null || nombre.isEmpty() || descripcion == null || descripcion.isEmpty()) {
			throw new IllegalArgumentException("El nombre de la exposición no puede ser nulo o vacío");
		}
		if (cierre.isBefore(apertura)) {
			throw new IllegalArgumentException("Las fechas de apertura y cierre no pueden ser nulas");
		}
		Temporal t = new Temporal(nombre, descripcion, apertura, cierre);
		Sistema.addExposiciones(t);
		return t;
	}

	/**
	 * Registra un nuevo Cuadro y lo agrega al sistema.
	 * 
	 * @param nombre         el nombre del cuadro
	 * @param autor          el autor del cuadro
	 * @param fecha          la fecha del cuadro
	 * @param descripcion    la descripción del cuadro
	 * @param seguroCuantia  la cuantía del seguro del cuadro
	 * @param seguroPoliza   la póliza del seguro del cuadro
	 * @param enPropiedad    indica si el cuadro está en propiedad
	 * @param temperaturaMin la temperatura mínima recomendada para el cuadro
	 * @param temperaturaMax la temperatura máxima recomendada para el cuadro
	 * @param humedadMin     la humedad mínima recomendada para el cuadro
	 * @param humedadMax     la humedad máxima recomendada para el cuadro
	 * @param requiereTemp   indica si el cuadro requiere control de temperatura
	 * @param requiereHum    indica si el cuadro requiere control de humedad
	 * @param ancho          el ancho del cuadro
	 * @param alto           el alto del cuadro
	 * @param largo          el largo del cuadro
	 * @param tecnica        la técnica utilizada en el cuadro
	 * @return el Cuadro registrado
	 */
	public Cuadro registrarCuadro(String nombre, String autor, int fecha, String descripcion, double seguroCuantia,
			String seguroPoliza, boolean enPropiedad, double temperaturaMin, double temperaturaMax, double humedadMin,
			double humedadMax, boolean requiereTemp, boolean requiereHum, double ancho, double alto, double largo,
			String tecnica) {
		Cuadro c = new Cuadro(nombre, autor, fecha, descripcion, seguroCuantia, seguroPoliza, enPropiedad,
				temperaturaMin, temperaturaMax, humedadMin, humedadMax, requiereTemp, requiereHum, ancho, alto, largo,
				tecnica);
		Sistema.addObras(c);
		return c;
	}

	/**
	 * Registra una nueva Escultura y la agrega al sistema.
	 * 
	 * @param nombre         el nombre de la escultura
	 * @param autor          el autor de la escultura
	 * @param fecha          la fecha de la escultura
	 * @param descripcion    la descripción de la escultura
	 * @param seguroCuantia  la cuantía del seguro de la escultura
	 * @param seguroPoliza   la póliza del seguro de la escultura
	 * @param enPropiedad    indica si la escultura está en propiedad
	 * @param temperaturaMin la temperatura mínima recomendada para la escultura
	 * @param temperaturaMax la temperatura máxima recomendada para la escultura
	 * @param humedadMin     la humedad mínima recomendada para la escultura
	 * @param humedadMax     la humedad máxima recomendada para la escultura
	 * @param requiereTemp   indica si la escultura requiere control de temperatura
	 * @param requiereHum    indica si la escultura requiere control de humedad
	 * @param ancho          el ancho de la escultura
	 * @param alto           el alto de la escultura
	 * @param largo          el largo de la escultura
	 * @param material       el material utilizado en la escultura
	 * @return la Escultura registrada
	 */
	public Escultura registrarEscultura(String nombre, String autor, int fecha, String descripcion,
			double seguroCuantia, String seguroPoliza, boolean enPropiedad, double temperaturaMin,
			double temperaturaMax, double humedadMin, double humedadMax, boolean requiereTemp, boolean requiereHum,
			double ancho, double alto, double largo, String material) {
		Escultura e = new Escultura(nombre, autor, fecha, descripcion, seguroCuantia, seguroPoliza, enPropiedad,
				temperaturaMin, temperaturaMax, humedadMin, humedadMax, requiereTemp, requiereHum, ancho, alto, largo,
				material);
		Sistema.addObras(e);
		return e;
	}

	/**
	 * Registra una nueva Fotografia y la agrega al sistema.
	 * 
	 * @param nombre         el nombre de la fotografía
	 * @param autor          el autor de la fotografía
	 * @param fecha          la fecha de la fotografía
	 * @param descripcion    la descripción de la fotografía
	 * @param seguroCuantia  la cuantía del seguro de la fotografía
	 * @param seguroPoliza   la póliza del seguro de la fotografía
	 * @param enPropiedad    indica si la fotografía está en propiedad
	 * @param temperaturaMin la temperatura mínima recomendada para la fotografía
	 * @param temperaturaMax la temperatura máxima recomendada para la fotografía
	 * @param humedadMin     la humedad mínima recomendada para la fotografía
	 * @param humedadMax     la humedad máxima recomendada para la fotografía
	 * @param requiereTemp   indica si la fotografía requiere control de temperatura
	 * @param requiereHum    indica si la fotografía requiere control de humedad
	 * @param ancho          el ancho de la fotografía
	 * @param alto           el alto de la fotografía
	 * @param largo          el largo de la fotografía
	 * @param color          indica si la fotografía es en color
	 * @return la Fotografia registrada
	 */
	public Fotografia registrarFotografia(String nombre, String autor, int fecha, String descripcion,
			double seguroCuantia, String seguroPoliza, boolean enPropiedad, double temperaturaMin,
			double temperaturaMax, double humedadMin, double humedadMax, boolean requiereTemp, boolean requiereHum,
			double ancho, double alto, double largo, boolean color) {
		Fotografia f = new Fotografia(nombre, autor, fecha, descripcion, seguroCuantia, seguroPoliza, enPropiedad,
				temperaturaMin, temperaturaMax, humedadMin, humedadMax, requiereTemp, requiereHum, ancho, alto, largo,
				color);
		Sistema.addObras(f);
		return f;
	}

	/**
	 * Registra un nuevo audiovisual en el sistema.
	 * 
	 * @param nombre        el nombre del audiovisual
	 * @param autor         el autor del audiovisual
	 * @param fecha         la fecha de creación del audiovisual
	 * @param descripcion   la descripción del audiovisual
	 * @param seguroCuantia la cuantía del seguro del audiovisual
	 * @param seguroPoliza  la póliza del seguro del audiovisual
	 * @param enPropiedad   indica si el audiovisual está en propiedad
	 * @param duracion      la duración del audiovisual en minutos
	 * @param idioma        el idioma del audiovisual
	 * @return el objeto Audiovisual registrado
	 * @throws IllegalArgumentException si alguno de los parámetros es inválido
	 */
	public Audiovisual registrarAudiovisual(String nombre, String autor, int fecha, String descripcion,
			double seguroCuantia, String seguroPoliza, boolean enPropiedad, int duracion, String idioma) {
		Audiovisual a = new Audiovisual(nombre, autor, fecha, descripcion, seguroCuantia, seguroPoliza, enPropiedad,
				duracion, idioma);
		Sistema.addObras(a);
		return a;
	}

	/**
	 * Publica una exposición.
	 * 
	 * @param exp la exposición a publicar
	 * @throws IllegalArgumentException si no se puede publicar la exposición
	 */
	public void publicarExp(Exposicion exp) {
		try {
			exp.publicar();
		} catch (IllegalArgumentException e) {
			System.out.println("No se puede publicar la exposición");
		}
	}

	// FUNCIONES RELACIONADAS CON OBRAS

	/**
	 * Añade una obra a una sala.
	 * 
	 * @param obra la obra a añadir a la sala
	 * @param sala la sala en la que se añadirá la obra
	 * 
	 */
	public void addObraToSala(Obra obra, Sala sala) {

		try {

			if (!sala.addObraExpoCheck(obra.getPropiedad())) {
				System.out.println("La Exposicion no cumple las condiciones para añadir la obra");
				return;
			}

			sala.addObra(obra);
			obra.exponerEn(sala);

		} catch (SalaExceptions exSala) {
			System.out.println(exSala.toString());

		} catch (ObraExceptions exObra) {
			System.out.println(exObra.toString());
			sala.removeObra(obra);
		}

		System.out.println("Obra añadida a la sala correctamente");

	}

	/**
	 * Elimina una obra de una sala.
	 * 
	 * @param obra la obra a eliminar de la sala
	 */
	public void removeObraFromSala(Obra obra) {
		try {
			obra.removeFromSala();
		}

		catch (ObraExceptions e) {
			System.out.println(e.toString());
		}
	}

	/**
	 * Envia una obra al almacen.
	 * 
	 * @param obra la obra a enviar al almacen
	 */
	public void enviarObraAlmacen(Obra obra) {
		try {
			obra.enviarAlmacen();
		} catch (ObraExceptions e) {
			System.out.println(e.toString());
		}
	}

	/**
	 * Restaura una obra.
	 * 
	 * @param obra la obra a restaurar
	 */
	public void restaurarObra(Obra obra) {
		try {
			obra.restaurar();
		} catch (ObraExceptions e) {
			System.out.println(e.toString());

		}
	}

	/**
	 * Presta una obra.
	 * 
	 * @param obra la obra a prestar
	 */
	public void prestarObra(Obra obra) {
		try {
			obra.prestar();
		} catch (ObraExceptions e) {
			System.out.println(e.toString());
		}
	}

	/**
	 * Retira una obra.
	 * 
	 * @param obra la obra a retirar
	 */
	public void retirarObra(Obra obra) {
		try {
			obra.retirar();
		} catch (ObraExceptions e) {
			System.out.println(e.toString());
		}
	}

	// FUNCIONES RELACIONADAS CON EXPOSICIONES

	/**
	 * Configura una exposición.
	 * 
	 * @param nombre
	 * @param apertura
	 * @param precio
	 * @param exp
	 * @param d
	 * @param ent
	 * @param est
	 * @param salas
	 */
	public void configurarExposicion(String nombre, LocalDateTime apertura, double precio, Exposicion exp,
			List<Descuento> d, List<Entrada> ent, EstadoExp est, List<Sala> salas) {
		exp.setNombre(nombre);
		exp.setApertura(apertura);
		exp.setPrecioEntrada(precio);
		exp.setDescuentos(d);

		if (ent != null) {
			for (Entrada e : ent) {
				exp.addVisita(e.getVisita());
			}
		}
		exp.setEstado(est);
		for (Sala s : salas) {
			exp.addSala(s);
			try {
				s.setExposicion(exp);
			} catch (Exception e) {
				System.out.println(e);
			}
		}
	}

	/**
	 * Fija el precio de una exposición.
	 * 
	 * @param e
	 * @param precio
	 * @throws IllegalArgumentException
	 */
	public void fijarPrecioExposicion(Exposicion e, double precio) throws IllegalArgumentException {
		try {
			e.setPrecioEntrada(precio);
		} catch (IllegalArgumentException ex) {
			throw ex;
		}
	}

	/**
	 * Añade un descuento a una exposición.
	 * 
	 * @param e la exposición a la que añadir el descuento
	 * @param d los descuentos a añadir
	 */
	public void addDescuentoExposicion(Exposicion e, Descuento... d) {
		for (Descuento descuento : d) {
			e.addDescuento(descuento);
			if (e.getEstado() == EstadoExp.PUBLICADA || e.getEstado() == EstadoExp.COMENZADA) {
				for (UsuarioRegistrado u : Sistema.getUsuarios()) {
					if (u.getTipoUsuario().equals("Cliente")) {
						Sistema.enviarMensaje("Nuevo Descuento", "Se ha añadido a la exposición " + e.getNombre()
								+ " el descuento " + descuento.getMensaje(), u);
					}
				}

			}
		}
	}

	/**
	 * Añade una sala a una exposición.
	 * 
	 * @param e     la exposición a la que añadir las salas
	 * @param salas las salas a añadir
	 * @throws IllegalArgumentException
	 */
	public void addSalaExposicion(Exposicion e, Sala... salas) throws IllegalArgumentException {
		for (Sala sala : salas) {
			try {
				e.addSala(sala);
			} catch (IllegalArgumentException ex) {
				throw ex;
			}
		}
	}

	/**
	 * Cancela una exposición.
	 * 
	 * @param e la exposición a cancelar
	 */
	public static void cancelarExposicion(Exposicion e) {
		e = null;
	}

	/**
	 * Cambia la contraseña de los empleados.
	 * 
	 * @param contrasenaEmpleados la nueva contraseña de los empleados
	 */
	public void setContrasenaEmpleados(String contrasenaEmpleados) {
		Empleado.setContrasenaEmpleados(contrasenaEmpleados);
	}

	/**
	 * Cambia el horario de apertura y cierre del centro.
	 * 
	 * @param apertura
	 * @param cierre
	 */
	public void setHorarioCentro(LocalTime apertura, LocalTime cierre) {
		Sistema.setApertura(apertura);
		Sistema.SetCierre(cierre);
	}

	/**
	 * Da de alta a un empleado.
	 * 
	 * @param nombre          nombre del empleado
	 * @param nif             nif del empleado
	 * @param cuenta          cuenta del empleado
	 * @param direccion       dirección del empleado
	 * @param seguridadSocial número de seguridad social del empleado
	 * @return el empleado dado de alta
	 */
	public Empleado darDeAlta(String nombre, String nif, String cuenta, String direccion, String seguridadSocial) {
		Empleado e = new Empleado(nif, nombre, cuenta, direccion, seguridadSocial, false, false, false);
		Sistema.addEmpleado(e);
		return e;
	}

	/**
	 * Cambia el permiso de venta de un empleado.
	 * 
	 * @param e
	 * @param permisoVenta
	 */
	public void setPermisoVenta(Empleado e, boolean permisoVenta) {
		e.setPermisoVenta(permisoVenta);
	}

	/**
	 * Cambia el permiso de mensajes de un empleado.
	 * 
	 * @param e               el empleado al que cambiar el permiso
	 * @param permisoMensajes el nuevo permiso de mensajes
	 */
	public void setPermisoMensajes(Empleado e, boolean permisoMensajes) {
		e.setPermisoMensajes(permisoMensajes);
	}

	/**
	 * Cambia el permiso de regulación de un empleado.
	 * 
	 * @param e                 el empleado al que cambiar el permiso
	 * @param permisoRegulacion el nuevo permiso de regulación
	 */
	public void setPermisoRegulacion(Empleado e, boolean permisoRegulacion) {
		e.setPermisoRegulacion(permisoRegulacion);
	}

	/**
	 * Configura una sala.
	 * 
	 * @param s           la sala a configurar
	 * @param enchufes    el número de enchufes
	 * @param aforo       el aforo
	 * @param dimensiones las dimensiones de la sala
	 */
	public void configurarSala(Subsala s, int enchufes, int aforo, Vector3 dimensiones) {
		s.setEnchufes(enchufes);
		s.setAforo(aforo);
		s.setDimensiones(dimensiones);
	}

	/**
	 * Configura una sala raíz.
	 * 
	 * @param s           la sala raíz a configurar
	 * @param enchufes    el número de enchufes
	 * @param aforo       el aforo
	 * @param dimensiones las dimensiones de la sala
	 * @param regulable   si la sala es regulable
	 */
	public void configurarSala(SalaRaiz s, int enchufes, int aforo, Vector3 dimensiones, boolean regulable) {
		s.setEnchufes(enchufes);
		s.setAforo(aforo);
		s.setDimensiones(dimensiones);
		s.setRegulable(regulable);
	}

	/**
	 * Devuelve el tipo de usuario.
	 * 
	 * @return una cadena que representa el tipo de usuario
	 */
	public String getTipoUsuario() {
		return "Gestor";
	}

	/**
	 * Divide una sala en varias subsalas.
	 * 
	 * @param s        la sala a dividir
	 * @param enchufes la lista de enchufes para cada subsala
	 * @param aforo    la lista de aforo para cada subsala
	 * @param cortes   los cortes para dividir la sala
	 */
	public void dividirSala(Sala s, List<Integer> enchufes, List<Integer> aforo, double... cortes) {
		double largo = Math.max(s.getDimensiones().getX(), s.getDimensiones().getZ());
		double ancho = Math.min(s.getDimensiones().getX(), s.getDimensiones().getZ());
		List<Double> cortesList = new ArrayList<>();
		for (double corte : cortes) {
			cortesList.add(corte);
		}
		cortesList.add(0.0);
		cortesList.add(largo);
		Collections.sort(cortesList);
		cortes = cortesList.stream().mapToDouble(Double::doubleValue).toArray();
		double alto = s.getDimensiones().getY();
		List<Vector3> subsalas = new ArrayList<>();

		int totalEnchufes = 0;
		for (Integer i : enchufes) {
			if (i < 0) {
				System.out.println("Error: Número de enchufes no válido");
				return;
			}
			totalEnchufes += i;
		}
		if (totalEnchufes != s.getEnchufes()) {
			System.out.println("Error: Número de enchufes no válido");
			return;
		}
		int totalAforo = 0;
		for (Integer i : aforo) {
			if (i < 0) {
				System.out.println("Error: Número de aforo no válido");
				return;
			}
			totalAforo += i;
		}
		if (totalAforo != s.getAforo()) {
			System.out.println("Error: Número de aforo no válido");
			return;
		}
		Arrays.sort(cortes);

		if (cortes[0] != 0 || cortes[cortes.length - 1] != largo) {
			System.out.println("Error: Los cortes no son válidos");
			return;
		}
		for (int i = 0; i < cortes.length - 2; i++) {
			subsalas.add(new Vector3(ancho, alto, cortes[i + 1] - cortes[i]));
		}
		try {
			s.dividir(subsalas, enchufes, aforo);
		} catch (Exception e) {
			System.out.println(e);
		}
	}

	/**
	 * Añade una visita a una exposición.
	 * 
	 * @param fecha la fecha de la visita
	 * @param e     la exposición a visitar
	 * @return la visita añadida
	 */
	public Visita addVisita(LocalDateTime fecha, Exposicion e) {
		Visita v = new Visita(fecha, e);
		return v;
	}

	/**
	 * Añade un descuento.
	 * 
	 * @param porcentaje el porcentaje del descuento
	 * @param fidelidad  si el descuento es por fidelidad
	 * @param tiempo     el tiempo del descuento
	 * @return el descuento añadido
	 */
	public Descuento addDescuento(double porcentaje, boolean fidelidad, int tiempo) {
		if (fidelidad) {
			return new Fidelidad(porcentaje, tiempo);
		} else {
			return new Antelacion(porcentaje, tiempo);
		}
	}

	/**
	 * Devuelve una representación en cadena del gestor.
	 * 
	 * @return una cadena que representa al gestor
	 */
	@Override
	public String toString() {
		return "Gestor [nif=" + nif + ", nombre=" + nombre + ", contrasena=" + contrasena + "]";
	}
}
