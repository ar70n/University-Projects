# Proyecto de Análisis de Software - Galería de Exposición de Arte

## Visión General

La Galería de Exposición de Arte es un proyecto orientado a objetos en Java que busca proporcionar una interfaz atractiva y funcional para la gestión de un centro de exposiciones de arte. Se distinguen tres tipos de usuarios: gestor del centro, empleados del centro y clientes.

## Usuarios

- **Gestor del Centro:**
  - Vende entradas y puede actuar como cliente.
  - Configura horarios de apertura.
  - Aplica descuentos para usuarios registrados.
  - Configura permisos y contraseñas.

- **Empleados del Centro:**
  - Venden entradas.
  - Configuran temperatura y humedad de las salas.
  - Envían mensajes a clientes.

- **Clientes:**
  - Compran entradas a través de la aplicación.
  - Pueden registrarse en sorteos activos.
  - Reciben notificaciones y mensajes si están registrados.

## Funcionalidades Principales

- **Venta de Entradas:**
  - Diferentes tipos de entradas según sala y exposición.
  - Compra en efectivo o tarjeta (requiere registro).
  - Descuentos aplicados por el gestor.

- **Salas y Exposiciones:**
  - Salas físicas y subsalas con aforo.
  - Configuración de dimensiones, tomas de electricidad, temperatura y humedad.
  - División de salas y subsalas.

- **Obras de Arte:**
  - Tipos: cuadros, esculturas, fotos y audiovisuales.
  - Atributos específicos para cada tipo.
  - Registro a través de formulario o fichero de texto.

- **Ciclo de Vida de Exposiciones:**
  - Creación, configuración y asignación de obras.
  - Verificación de condiciones y compatibilidad de obras.
  - Publicación de la exposición.
  - Modificación de estado y cancelación con antelación.

- **Sorteos:**
  - Realizados gratuitamente para exposiciones.
  - Asignación aleatoria de entradas.
  - Penalización por no recoger entradas.

## Interfaz y Usabilidad

- **Portabilidad:**
  - Interfaz de usuario simple y fácil de usar.
  - Permisos específicos para empleados.

- **Gestión de Usuarios:**
  - Gestor gestiona contraseñas y altas de empleados.
  - Empleados gestionan sus datos personales.
  - Clientes se registran con NIF y contraseña.

- **Notificaciones:**
  - Clientes deciden recibir o no publicidad.
  - Empleados pueden enviar mensajes a clientes.

## Estadísticas y Configuraciones

- **Estadísticas:**
  - Sistema ofrece al gestor estadísticas de ventas y beneficios.
  - Consulta de estadísticas globalmente y por exposición.

- **Configuraciones:**
  - Gestor configura horas de apertura y meses de penalización.
  - Configura permisos y contraseñas de empleados.

Este proyecto proporciona una plataforma completa y eficiente para la gestión integral de una galería de exposición de arte, cumpliendo con las necesidades de gestores, empleados y clientes.

## Notas Raw
-Galeria de exposicionm de arte
-interfaz guay
-3 tipos de usuario: gestor del centro, empleados del centro, clientes
-En la galeria dfe arte hay obras que no siempre son nuestras
-Vendemos entradas (los empleados) los clientes pueden comprar emntradas en la app
-(El gestor como tal puede vender entradas y hacer de cliente)
-Salas y exposiciones tiene aforo
-Hay distitnos tipo de entrada (dependiendo de la sala y eso) 
-Las entradas se compran y la compra de entradas es para una exposicion concreta en una fecha y hora conmcreta y un numero de entradas concreta
-El empleado vende entradas y muy poco mas
-La galera de arte tiene3 salas fisicas que se pueden sudividir en salas mas pequeñas pq puede haber muchas exposiciones una misma sala
-Las subsalas tambien se pueden dividir en mas salas y asi hasta bueno hasta siempre
-El aforo es por exposicion
-Las entradas se pueden pagar en efectivo para ese mismo dia
-Se puede pagar con tarjeta de credito pero te tienes que registrar
-El gestor configura horarios de apertura
-Toda las exposiciones abren a la vez
-El gestor puede hacer descuentos para ciertos horarios,exposiciones… SOLO para usuarios registrados
-El aforo de la exposicion es el aforo de las salas que ocupa la exposicion
-Las salas tienen nombre, aforo, dimesniosnes: ancho largo y alto; numero de tomas de electricidad, si la sala permite controlar la temperatura y humedad. (cuidado al hacer subsalas pq hay que recalcular estos datos)
-las subsalas no se pueden destruir mientras hay una exposicion activa
-Hay dos tipos de descuentos: haber acudido a x expos en x meses, haber comprado las entradas con x dias de antelacion.
-Dos sistemas externos uno pa pagar con tarjeto y otro que generara un pdf de las entrada (Osea esto pasa al comnprar entradas)
-El empleado siempre paga en efectivo cuando un cliejte compra entradas en efectivo
-Hay obras de arte que les gestiona el gestor, pueden ser del centro o externas 
-Las obras de arte son cuadors esculturas fotos y audiovisuales
 cada una con sus atributis flow material , tecnica, foto:color, audiovisuales duracion e idioma
-Todas las obras tienen autor, año descricion y seguro con su poliza y cuantia
-Los cuadros, esculturas y fotos tienen un tamaño y pueden requierir humedad y temperatura (un rango determiando)
-Las obras se dan de alta con un formulario
-Tmbien se pueden meter a través de un fichero de texto conm ciuerto formato
-Las obras tienen un estoado: almacen, en expo, prestadas, en restauracion o retiradas
-Por defecto las obras estan en el almacen cuando se dan de alta
-Las que estan prestadas o en restauracion tienen que pasar por el almacen antes de ir a expo
-SI una obra esta reirada no se ùede cambiar su estado.
-Cualquier obra que quitas de una expo tiene que pasar por el almacen
-No puedes ni restaurar ni retirar ni prestar las obras que no son tuyas
-Trabajamos en dos dimensiones, los cuadros/fotos en la pared y las esculturas en el suelo
-Se tiene que poder buscvar fechas segun distiuntos filtros de exposicion para las que aun quedan entradas, fecha , tipo de exposicion, tipo de obra
-El gestor puede hacer login con una contraseña, puede configurar la contraseña para el susario empleado
-Puede configurar la hora de apertura del centro
-Puede configuar los meses de penalizacion por no recoger la entrada de un sorteo
-Dar de alta al empleado y configurar los permisos, configurar las salas y las subsalas, añadir obras de arte, editar el estado de una obra de arte, crear una exposicion y añadir obras de arte asi como la sala, fijar el precio de las entradas,  cerrar temporalmente una exposcicion permanente, configura los descuentos, programa y realiza los sorteos  y puede consutar las estadisticas, puede alterar el tiempo de una exposicion temporal.
-El gestor hace sorteos gratis para exposiciones: numero de entradas, condiciones, plazo de inscrippcion, periodo de uso... El limite de ntradas son 2
-Si las entradas son para un dia y una hora no saldran a la venta se reservan para el sorteo.
-Los clientes se pueden registrar en sorteos activos
-El gestor activa el sorteo pulsando un boton
-El sistema asigna las entradas aleatoriamente y notifica a los clientes dandoles un codigo unico de premio respetando el numero de entradas.
-Para reclamarlas al pagar por las entradas introduce el codigo y se le descuenta el precio de las entradas.
-SI alguien no recoge su entrada queda poenalizado de participar en los osrteos X meses (los que ponga el gestor)
-Aunque te toque una entrada tienes que decir a que hora vas. (Entonces has reservado mas de las que son tienes que liberar las que el cliente no pilla)
-Pa implementar un sorteo: realizas un sorteo entre todos si ole toca a algfuien que quieres dos le das las dos.
-cuando se publica una esposcinion o sale un descuento a se hace un sorteo se notifica a los clientes registrados.
-Los clientes pueden hacer que no reciban la publicidad esta de polla
-Les obligamos a registrarse si quieren recibir notificaciones y por defectio no recivben
-Los empleados si tienen permiso pueden enviar ,ensajes a los cluentes registrados o clientes especificos
-Estadisrica el sistema debe ofrecer al gestor estadisticas del numero de entradas vendidas y de los beneficiocs obtenidos entre dos fechas, tanto globalmente como por exposicion.
-Los cleitnes no registrados pueden registrarsem, pueden buscar expos.
-los empleados pueden loguearse , editar datos personales  suyos (y de clientws si queremos), ùeden vender entyradas, enviar mensajes a los clientes , pueden configurar la tewmperatura y humedad de las salas. (Ojo el empleado no puede cargarse una obra si ahy una que requiere cierta temp o humedad) 
-Portablidad interfaz de ususario sencialla y facil de usar, los empleaddos tienen permisos y eso.
-El gestor, Aceede al sistema con una contraseña predeterminada, da de altal a empleados (todos tienen la misma contraseña), los datos de los empleados son: nombre, nif, num seg social.
-El empleado accede al sistema con su nif y la contraseña uncia de empleado, puede editar su direccion, nunm seg social (12 nums) y numero de cuenta bancaria. 
-Los clientes ser registran con un nif y una contrseña. No puede haber dos empleados con el mismo niuf ni dos clientes con el mismo nif
-Un empleado no piuede ser un cliente.
-El gestor puede gestionar los permoispos de los empleados
-La lista de permisos: vender entradas, modifiucar temp y humedad y enviar mensajes. 
-LAS EXPOSISCIONES TIENE NOMBRES DESCRIPCION, tep o perm y fecha
-cICLO DE VIDA DE LA SEXPOS:
-Da de altal la expo con sus datos_ titulo, desc, fecha de incicio...
-La expo pasa a estar en creaciopnm unicamente ña puede ver el gestor
-mientras erzta en creacion: fija el precio de entradas, las obras, sala  se muestra cada sala de arte, cuando se asigna una obra a una sala tiene quie cunmpliar las condiciones: cosas triviales, si la expo es temporal la obra NO puede ser nuestras. si es permanente la obra puede ser tanto permanente como temporal.
-las audiovisuales deben mostrarse en sals copn tomas de electricidd,
-los cuadors, escurlturas y fotos nmo pueden superar el tmaa,ño de la sala y si tienen copndiciones de tewmmp y humedad tien que poder controlarse en esa sala.
-No pueden estar en la misma sala obras con cosas incompaltiuvles.
-UNA sala no puede tener opbras de expos diferentes
-La sala de be estar libre durante todo el tienmpo de la expo (al crearla el sistema te avisa).
-Dividir una sala que este vacia o no se puede dividir.
-Cuando el ggestor quiera poublica la expo habiuendo configurado el precio de las entradas incluisive sio el precio es 0.
-a partir de ese momento la expo se peude buscar.
-Unas expo se puede borrar antes de publicarse pero no depues.
 -Tras publicar una expo las obras no se pueden añadir ni quitar pero se puede modificar su estado
 -Cundo se publica una expo esta "comenzada"
 -Ls expos se pueden cancelar cpn 7 dias de antelacion
 -Se puede volver el dinero
 -Las expos permanentes pueden cerrar temporalmente por renovacion o mierdas.
