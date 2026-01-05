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
