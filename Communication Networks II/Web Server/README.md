# Guía de Ejecución  

## Requisitos Previos  

Antes de ejecutar el proyecto, asegúrese de contar con las siguientes dependencias instaladas:  

- Un compilador y enlazador de C  
- Intérpretes de Python 3 y PHP  

Además, verifique que ha descargado correctamente todos los archivos y que ha incluido en la carpeta `www` los archivos del front-end accesibles a través del servidor. Estos archivos no se proporcionan en este repositorio.  

## Compilación y Ejecución  

Para compilar tanto las bibliotecas estáticas como el servidor, ejecute los siguientes comandos desde la raíz del repositorio:  

```sh
make liblog.a libsocket_manager.a
make server
./server
```

Si desea compilar y ejecutar el servidor en un solo paso, puede utilizar:  

```sh
make run
```

A la hora de acceder al servidor a través de un navegador o al realizar peticiones con curl tenga en cuenta que no se ha implementado un sistema de redireccionamiento permanente (status 301). Por lo que si simplemente intenta acceder a `http://localhost:8080/` recibirá un **error 404** por lo que debe acceder a `index.html`.

## Configuración  

El archivo `server.conf` permite modificar diversos parámetros del servidor, entre ellos:  

- **Ruta del directorio accesible** desde el servidor web  
- **Puerto** en el que se ejecutará el servidor (por defecto 8080)
- **Firma del servidor**  
- **Número máximo de conexiones simultáneas**  

## Pruebas  

El archivo `index.html` incluye diversas pruebas para verificar la funcionalidad del servidor. Entre ellas, se ha agregado una prueba de denegación de servicio. Puede acceder a estas pruebas directamente desde su navegador.  

Además, para comprobar la correcta gestión de memoria, puede ejecutar el servidor con Valgrind usando el siguiente comando:  

```sh
make valgrind
```

## Arquitectura  

Este servidor es **concurrente y reactivo**, y está gestionado mediante hilos para optimizar su rendimiento.  

---