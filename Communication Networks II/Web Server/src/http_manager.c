#include "http_manager.h"

#define MAX_HEADERS 128
#define HEADERS_LENGTH 8192
#define LAST_MOD_LENGTH 4092
#define BUFF_LENGTH 8192
const char *HTTP_ERROR_RESPONSE = "<html><body><h1>500 Internal Server Error</h1></body></html>";
const char *HTTP_NOT_FOUND_RESPONSE = "<html><body><h1>404 Not Found</h1></body></html>";
const char *HTTP_BAD_REQUEST_RESPONSE = "<html><body><h1>400 Bad Request</h1></body></html>";

char *web_root;
char *server_signature;

struct _http_response {
    int length;
    unsigned char *body;
};

struct _http_args{
    char *key;
    char *value;
    http_verbs verb;
};

struct _http_parse{
    char *method;
    char *path;
    char *protocol;
    char *host;
    char *user_agent;
    char *accept;
    char *accept_encoding;
    char *accept_language;
    char *content_length;
    char *content_type;
    char *last_modified;
    char *date;
    char *server_name;
    char *connection;
    char *data;
    char *header[MAX_HEADERS];
    int num_headers;
};

/*******************************************************************************
 * FUNCIÓN: 	char *http_get_status(int code)
 *
 * ARGS_IN: 	int code: Código de estado HTTP
 *
 * DESCRIPCIÓN: Devuelve el mensaje de estado HTTP correspondiente al código
 *
 * ARGS_OUT: char *: Mensaje de estado HTTP
 * *****************************************************************************/
char *http_get_status(int code);

/*******************************************************************************
 * FUNCIÓN: 	http_file_extensions get_file_extension(const char *filename)
 *
 * ARGS_IN: 	const char *filename: Nombre del archivo
 *
 * DESCRIPCIÓN: Devuelve la extensión del archivo
 *
 * ARGS_OUT: http_file_extensions: Extensión del archivo
 * *****************************************************************************/
http_file_extensions get_file_extension(const char *filename);

/*******************************************************************************
 * FUNCIÓN: 	char *http_get_date()
 *
 * DESCRIPCIÓN: Devuelve la fecha actual en formato HTTP
 *
 * ARGS_OUT: char *: Fecha actual en formato HTTP
 * *****************************************************************************/
char *http_get_date();

/*******************************************************************************
 * FUNCIÓN: 	char *http_create_response(int code, char *last_modified, http_file_extensions content_type, unsigned char *body)
 *
 * ARGS_IN:     int code: Código de estado HTTP
 *			    char *last_modified: Fecha de última modificación
 *			    http_file_extensions content_type: Tipo de contenido
 *			    unsigned char *body: Cuerpo de la respuesta
 *
 * DESCRIPCIÓN: Crea una respuesta HTTP
 *
 * ARGS_OUT: char *: Respuesta HTTP
 * *****************************************************************************/
http_response* http_create_response(int code, char *last_modified, http_file_extensions content_type, unsigned char *body, unsigned long body_size);

/*******************************************************************************
 * FUNCIÓN: 	char* content_type_to_string(http_file_extensions c)
 *
 * ARGS_IN: 	http_file_extensions c: Extensión del archivo
 *
 * DESCRIPCIÓN: Devuelve el tipo de contenido en formato string
 *
 * ARGS_OUT: char *: Tipo de contenido en formato string
 * *****************************************************************************/
char* content_type_to_string(http_file_extensions c);

/*******************************************************************************
 * FUNCIÓN: 	unsigned char *get_file_content(char *path, int size)
 *
 * ARGS_IN: 	char *path: Ruta del archivo
 *              int size: Tamaño del archivo
 *
 * DESCRIPCIÓN: Devuelve el contenido de un archivo
 *
 * ARGS_OUT: unsigned char *: Contenido del archivo
 * *****************************************************************************/
unsigned char *get_file_content(char *path, int size);

/*******************************************************************************
 * FUNCIÓN: 	int exec_script(char *path, http_file_extensions extension, http_args **args, int n_args, unsigned char *buffer)
 *
 * ARGS_IN: 	char *path: Ruta del script
 *              http_file_extensions extension: Extensión del script
 *              http_args **args: Argumentos del script
 *              int n_args: Número de argumentos
 *              unsigned char *buffer: Buffer donde se almacenará la salida del script
 *
 * DESCRIPCIÓN: Ejecuta un script
 *
 * ARGS_OUT: int: Tamaño de la salida del script
 * *****************************************************************************/
int exec_script(char *path, http_file_extensions extension, http_args **args, int n_args, unsigned char *buffer);

/*******************************************************************************
 * FUNCIÓN: 	char **get_exec_args(char *path, http_file_extensions extension, http_args **args, int n_args)
 *
 * ARGS_IN: 	char *path: Ruta del script
 *              http_file_extensions extension: Extensión del script
 *              http_args **args: Argumentos del script
 *              int n_args: Número de argumentos
 *
 * DESCRIPCIÓN: Devuelve los argumentos para ejecutar un script
 *
 * ARGS_OUT: char **: Argumentos para ejecutar un script
 * *****************************************************************************/
char **get_exec_args(char *path, http_file_extensions extension, http_args **args, int n_args);

/*******************************************************************************
 * FUNCIÓN: 	char *get_interpreter(http_file_extensions extension)
 *
 * ARGS_IN: 	http_file_extensions extension: Extensión del script
 *
 * DESCRIPCIÓN: Devuelve el intérprete correspondiente a la extensión del script
 *
 * ARGS_OUT: char *: Intérprete
 * *****************************************************************************/
char *get_interpreter(http_file_extensions extension);

/*******************************************************************************
 * FUNCIÓN: 	http_response* http_process(char *path, char *data, http_verbs verb)
 *
 * ARGS_IN:     char *path: Ruta del archivo
 *              char *data: Datos
 *              http_verbs verb: Verbo HTTP
 *
 * DESCRIPCIÓN: Procesa una petición HTTP
 *
 * ARGS_OUT: int: Respuesta HTTP
 * *****************************************************************************/
http_response* http_process(char *path, char *data, http_verbs verb);

/*******************************************************************************
 * FUNCIÓN: 	void replace_char(char *str, char find, char replace)
 *
 * ARGS_IN: 	char *str: Cadena
 *              char find: Caracter a buscar
 *              char replace: Caracter de reemplazo
 *
 * DESCRIPCIÓN: Reemplaza un caracter por otro en una cadena
 *
 * ARGS_OUT: void
 * *****************************************************************************/
void replace_char(char *str, char find, char replace);

/*******************************************************************************
 * FUNCIÓN: 	http_response* http_respond_options(char* allow)
 *
 * ARGS_IN: 	char* allow: Métodos permitidos
 *
 * DESCRIPCIÓN: Responde a una petición OPTIONS
 *
 * ARGS_OUT: http_response*: Respuesta HTTP
 * *****************************************************************************/
http_response* http_respond_options(char* allow);

/*******************************************************************************
 * FUNCIÓN: 	int parse_args(http_args ***args, int n_args, char* data)
 *
 * ARGS_IN: 	http_args ***args: Punter al array de argumentos
 *              int n_args: Número de argumentos
 *              char* data: Datos
 *
 * DESCRIPCIÓN: Parsea los argumentos
 *
 * ARGS_OUT: int: Número de argumentos
 * *****************************************************************************/
int parse_args(http_args ***args, int n_args, char* data);


void init_http_manager(char *root, char *signature)
{
    web_root = root;
    server_signature = signature;
}

void close_http_manager()
{
    free(web_root);
    free(server_signature);
}

http_response* http_parse_petition(char *buff)
{
    struct _http_parse parse;
    char *header[MAX_HEADERS];
    int num_headers = 0, j;

    //Init fields to null
    parse.host = NULL;
    parse.user_agent = NULL;
    parse.accept = NULL;
    parse.accept_encoding = NULL;
    parse.accept_language = NULL;
    parse.content_length = NULL;
    parse.content_type = NULL;
    parse.last_modified = NULL;
    parse.date = NULL;
    parse.server_name = NULL;
    parse.connection = NULL;
    parse.data = NULL;

    parse.method = strtok(buff, " ");
    parse.path = strtok(NULL, " ");
    parse.protocol = strtok(NULL, "\r\n");

    // Leer todas las cabeceras de la petición HTTP
    while ((header[num_headers] = strtok(NULL, "\r\n")) != NULL)
        num_headers++;

    for (j = 0; j < num_headers; j++)
    {
        if (strstr(header[j], "Host: "))
            parse.host = header[j] + 6;
        else if (strstr(header[j], "User-Agent: "))
            parse.user_agent = header[j] + 12;
        else if (strstr(header[j], "Accept:"))
            parse.accept = header[j] + 8;
        else if (strstr(header[j], "Accept-Encoding: "))
            parse.accept_encoding = header[j] + 16;
        else if (strstr(header[j], "Accept-Language: "))
            parse.accept_language = header[j] + 16;
        else if (strstr(header[j], "Content-Length: "))
            parse.content_length = header[j] + 16;
        else if (strstr(header[j], "Content-Type: "))
            parse.content_type = header[j] + 14;
        else if (strstr(header[j], "Last-Modified: "))
            parse.last_modified = header[j] + 15;
        else if (strstr(header[j], "Date: "))
            parse.date = header[j] + 6;
        else if (strstr(header[j], "Server: "))
            parse.server_name = header[j] + 8;
        else if (strstr(header[j], "Connection: "))
            parse.connection = header[j] + 12;
        else
            parse.data = header[j];
    }


    if (parse.content_length == NULL || atoi(parse.content_length) != strlen(header[j - 1]))
    {
        parse.data = NULL;
    }

    if (strcmp(parse.method, "GET") == 0)
    {
        return http_process(parse.path, parse.data, GET);
    }
    else if (strcmp(parse.method, "POST") == 0)
    {
        return http_process(parse.path, parse.data, POST);
    }
    else if (strcmp(parse.method, "OPTIONS") == 0)
    {
        return http_process(parse.path, parse.data, OPTIONS);
    }

    return http_create_response(HTTP_BAD_REQUEST, "none", html, (unsigned char*)HTTP_BAD_REQUEST_RESPONSE, strlen(HTTP_BAD_REQUEST_RESPONSE));
}

unsigned char *get_file_content(char *path, int size)
{
    unsigned char *file_content;
    int fd;
    
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        log_message(ERROR, "Error opening file %s", path);
        return NULL;
    }

    file_content = malloc(size);
    if (file_content == NULL)
    {
        log_message(ERROR, "Malloc error");
        close(fd);
        return NULL;
    }

    if (read(fd, file_content, size) != size)
    {
        log_message(ERROR, "Error reading file %s", path);
        close(fd);
        free(file_content);
        return NULL;
    }

    close(fd);
    
    return file_content;
}

int exec_script(char *path, http_file_extensions extension, http_args **args, int n_args, unsigned char *buffer)
{
    char **exec_args;
    int child_to_parent[2];
    int parent_to_child[2];
    int count;
    int buffer_size = 0;
    pid_t pid;
    
    exec_args = get_exec_args(path, extension, args, n_args);
    if (exec_args == NULL)
    {
        log_message(ERROR, "Error getting exec args");
        return -1;
    }
    
    if (pipe(child_to_parent) == -1)
    {
        log_message(ERROR, "Error creating pipe");
        free(exec_args);   
        return -1;
    }    
    if (pipe(parent_to_child) == -1)
    {
        log_message(ERROR, "Error creating pipe");
        free(exec_args);
        return -1;
    }

    pid = fork();
    if (pid == -1)
    {
        log_message(ERROR, "Error forking");
        free(exec_args);
        return -1;
    }

    if (pid == 0) // Hijo
    {        
        close(child_to_parent[0]); // Cierra el extremo de lectura
        close(parent_to_child[1]); // Cierra el extremo de escritura

        /*Redirigir stderr al pipe de escritura, de modo que al
        acceder a STDOUT, realmente se esté escribiendo en el pipe*/
        if (dup2(child_to_parent[1], STDOUT_FILENO) == -1)
        {
            log_message(ERROR, "dup2 stdout");
            free(exec_args);
            exit(EXIT_FAILURE);
        }

        /*Redirigir stderr al pipe de escritura, de modo que al
        acceder a STDERR, realmente se esté escribiendo en el pipe*/
        if (dup2(child_to_parent[1], STDERR_FILENO) == -1)
        {
            log_message(ERROR, "dup2 stderr");
            free(exec_args);
            exit(EXIT_FAILURE);
        }

        /*Redirigir stdin al pipe de lectura, de modo que al 
        acceder a STDIN, realmente se esté leyendo del pipe*/
        if (dup2(parent_to_child[0], STDIN_FILENO) == -1)
        {
            log_message(ERROR, "dup2 stdin");
            free(exec_args);
            exit(EXIT_FAILURE);
        }

        close(parent_to_child[0]); // Cierra el extremo de lectura del pipe en el hijo después de redirigir
        close(child_to_parent[1]); // Cierra el extremo de escritura del pipe en el hijo después de redirigir

        //Si execvp se ejecuta correctamente, acaba aquí
        execvp(exec_args[0], exec_args);
        
        log_message(ERROR, "Error executing script %s", path);
        free(exec_args);
        exit(EXIT_FAILURE);
    }    
    else // Padre
    {
        close(child_to_parent[1]); // Cierra el extremo de escritura
        close(parent_to_child[0]); // Cierra el extremo de lectura

        // Escribir los argumentos en el pipe
        for (int i = 0; i < n_args; i++)
        {
            if (args[i]->verb == GET)
            {
                write(parent_to_child[1], args[i]->value, strlen(args[i]->value));
            }
        }

        close(parent_to_child[1]);

        while ((count = read(child_to_parent[0], buffer, BUFF_LENGTH)) > 0)
        {
            buffer_size += count;
        }

        close(child_to_parent[0]);
        waitpid(pid, NULL, 0); // Esperar a que el hijo termine
        free(exec_args);
    }

    return buffer_size;
}

char **get_exec_args(char *path, http_file_extensions extension, http_args **args, int n_args)
{
    char **exec_args;
    char *interpreter;
    int count = 0;
    int i,j;

    interpreter = get_interpreter(extension);
    if (interpreter == NULL)
    {
        return NULL;
    }

    for (i = 0; i < n_args; i++)
    {
        if (args[i]->verb == POST)
        {
            count++;
        }
    }

    exec_args = malloc((count + 3) * sizeof(char *));
    if (exec_args == NULL)
    {
        log_message(ERROR, "Malloc error");
        return NULL;
    }

    exec_args[0] = interpreter;
    exec_args[1] = path;

    for (i = 0, j = 0; i < n_args; i++)
    {
        if (args[i]->verb == POST)
        {
            exec_args[j + 2] = args[i]->value;
            j++;
        }
    }

    exec_args[count + 2] = NULL;

    return exec_args;
}

char *get_interpreter(http_file_extensions extension)
{
    switch (extension)
    {
        case py:
            return "python3";
        case php:
            return "php";
        default:
            return NULL;
    }
}

http_response* http_create_response(int code, char *last_modified, http_file_extensions content_type, unsigned char *body, unsigned long body_size)
{
    size_t size = body_size + HEADERS_LENGTH;
    int resp_length = 0;
    http_response *response;
    response = malloc(sizeof(http_response));

    if (response == NULL)
    {
        return NULL;
    }

    response->body = (unsigned char*) calloc(size, sizeof(unsigned char));
    if (response->body == NULL)
    {
        free(response);
        return NULL;
    }

    resp_length = snprintf((char*)response->body, size,
             "HTTP/1.1 %s\r\n"
             "Date: %s\r\n"
             "Server: %s\r\n"
             "Last-Modified: %s\r\n"
             "Content-Length: %ld\r\n"
             "Content-Type: %s\r\n"
             "\r\n",
             http_get_status(code), http_get_date(), server_signature, last_modified, body_size, content_type_to_string(content_type));

    if (resp_length < 0 || resp_length >= size)
    {
        free(response->body);
        free(response);
        return NULL;
    }

    if (body != NULL && body_size > 0)
    {
        memcpy(response->body + resp_length, body, body_size);
    }

    response->length = resp_length + body_size;

    return response;
}

void http_respond(int connection_socket, http_response *response)
{
    s_send(connection_socket, response->body, response->length);
    free(response->body);
    free(response);
}

char *http_get_date()
{
    static char date[100];
    time_t now = time(NULL);
    struct tm tm = *gmtime(&now);

    strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S %Z", &tm);
    return date;
}

http_file_extensions get_file_extension(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
    {
        return unrecognized;
    }
    if (strcmp(dot + 1, "html") == 0)
    {
        return html;
    }
    else if (strcmp(dot + 1, "gif") == 0)
    {
        return gif;
    }
    else if (strcmp(dot + 1, "jpeg") == 0)
    {
        return jpeg;
    }
    else if (strcmp(dot + 1, "png") == 0)
    {
        return png;
    }
    else if (strcmp(dot + 1, "css") == 0)
    {
        return css;
    }
    else if (strcmp(dot + 1, "js") == 0)
    {
        return js;
    }
    else if (strcmp(dot + 1, "py") == 0)
    {
        return py;
    }
    else if (strcmp(dot + 1, "php") == 0)
    {
        return php;
    }
    else if (strcmp(dot + 1, "txt") == 0)
    {
        return txt;
    }
    return unrecognized;
}

char* content_type_to_string(http_file_extensions c){
    switch (c)
    {
    case html:
        return "text/html";
    case gif:
        return "image/gif";
    case jpeg:
        return "image/jpeg";
    case png:
        return "image/png";
    case css:
        return "text/css";
    case js:
        return "application/javascript";
    case txt:
        return "text/plain";
    default:
        return "application/octet-stream";
    }
}

char *http_get_status(int code)
{
    switch (code)
    {
    case 200:
        return "200 OK";
    case 400:
        return "400 Bad Request";
    case 404:
        return "404 Not Found";
    default:
        return "500 Internal Server Error";
    }
}

int parse_args(http_args ***args, int n_args, char* data)
{
    char *aux;
    http_verbs verb = POST;
    if (data == NULL)
    {
        verb = GET;
    }
    while ((aux = strtok(data, "=")) != NULL)
    {
        *args = realloc(*args, (n_args + 1) * sizeof(http_args*)); // Reasigna memoria para args
        if (*args == NULL)
        {
            log_message(ERROR, "Realloc error");
            for (int i = 0; i < n_args; i++)
            {
                free((*args)[i]);
            }
            return -1;
        }

        (*args)[n_args] = malloc(sizeof(http_args));
        if ((*args)[n_args] == NULL)
        {
            log_message(ERROR, "Malloc error");
            for (int i = 0; i < n_args; i++)
            {
                free((*args)[i]);
            }
            return -1;
        }

        (*args)[n_args]->key = aux;
        (*args)[n_args]->value = strtok(NULL, "&");
        (*args)[n_args]->verb = verb;

        replace_char((*args)[n_args]->value, '+', ' ');

        n_args++;
        data = NULL;
    }
    return n_args;
}

void replace_char(char *str, char find, char replace) 
{
    char *current_pos = strchr(str, find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos + 1, find);
    }
}

http_response* http_process(char *path, char *data, http_verbs verb)
{
    // Inicialización
    char *real_path = NULL;
    http_args **args = NULL;
    struct stat file_stat;
    http_file_extensions content_type;
    struct tm *tm_info = NULL;
    int n_args = 0, buff_size = 0, i;
    unsigned char buffer[BUFF_LENGTH], *file_content = NULL;
    char last_mod[LAST_MOD_LENGTH];
    http_response* response = NULL;

    //Inicializar buffer
    memset(buffer, 0, BUFF_LENGTH);

    // Construir la ruta real del archivo
    real_path = malloc(strlen(web_root) + strlen(path) + 1);
    if (real_path == NULL)
    {
        log_message(ERROR, "Malloc error");
        return http_create_response(HTTP_SERVER_ERROR, "none", html, (unsigned char *)HTTP_ERROR_RESPONSE, strlen(HTTP_ERROR_RESPONSE));
    }

    // Obtenemos la ruta real del archivo, eliminando los parámetros
    strtok(path, "?");
    strcpy(real_path, web_root);
    strcat(real_path, path);

    // Obtenemos información sobre el archivo
    if (stat(real_path, &file_stat) == -1)
    {
        log_message(ERROR, "Error getting file info");
        free(real_path);
        return http_create_response(HTTP_NOT_FOUND, "none", html, (unsigned char*)HTTP_NOT_FOUND_RESPONSE, strlen(HTTP_NOT_FOUND_RESPONSE));
    }

    // Si no es un archivo regular, devolvemos un error
    if (!S_ISREG(file_stat.st_mode))
    {
        free(real_path);
        return http_create_response(HTTP_NOT_FOUND, "none", html, (unsigned char*)HTTP_NOT_FOUND_RESPONSE, strlen(HTTP_NOT_FOUND_RESPONSE));
    }

    // Obtenemos la fecha de la última modificación del archivo y su extensión
    content_type = get_file_extension(path);
    tm_info = gmtime(&file_stat.st_mtime);
    strftime(last_mod, sizeof(last_mod), "%a, %d %b %Y %H:%M:%S %Z", tm_info);

    if (verb == OPTIONS)
    {
        free(real_path);
        if (content_type == py || content_type == php)
        {
            // Allow POST y GET
            return http_respond_options("GET, POST");
        }
        else
        {
            return http_respond_options("GET");
        }
    }

    // Intentamos parsear el path
    n_args = parse_args(&args, n_args, NULL); // Pasa la dirección de args
    if (n_args == -1)
    {
        free(real_path);
        return http_create_response(HTTP_SERVER_ERROR, "none", html, (unsigned char *)HTTP_ERROR_RESPONSE, strlen(HTTP_ERROR_RESPONSE));
    }

    if (verb == POST)
    {
        n_args = parse_args(&args, n_args, data);
        if (n_args == -1)
        {
            free(args);
            free(real_path);
            return http_create_response(HTTP_SERVER_ERROR, "none", html, (unsigned char *)HTTP_ERROR_RESPONSE, strlen(HTTP_ERROR_RESPONSE));
        }
    }


    if (n_args > 0 || content_type == py || content_type == php)
    {
        // Ejecutar el script
        if ((buff_size = exec_script(real_path, content_type, args, n_args, buffer)) < 0)
        {
            for (int i = 0; i < n_args; i++)
            {
                free(args[i]);
            }
            free(args);
            free(real_path);
            return http_create_response(HTTP_SERVER_ERROR, "none", html, (unsigned char *)HTTP_ERROR_RESPONSE, strlen(HTTP_ERROR_RESPONSE));
        }

        response = http_create_response(HTTP_OK, last_mod, txt, buffer, buff_size);
    }
    else if (verb == GET && content_type != py && content_type != php)
    {
        file_content = get_file_content(real_path, file_stat.st_size);
        if (file_content == NULL)
        {
            free(args);
            return http_create_response(HTTP_SERVER_ERROR, "none", html, (unsigned char *)HTTP_ERROR_RESPONSE, strlen(HTTP_ERROR_RESPONSE));
        }

        response = http_create_response(HTTP_OK, last_mod, content_type, file_content, file_stat.st_size);
        free(file_content);
    }
    else
    {
        response = http_create_response(HTTP_BAD_REQUEST, "none", html, (unsigned char*)HTTP_BAD_REQUEST_RESPONSE, strlen(HTTP_BAD_REQUEST_RESPONSE));
    }

    for (i = 0; i < n_args; i++)
    {
        free(args[i]);
    }
    free(args);
    free(real_path);

    return response;
}

http_response* http_respond_options(char* allow)
{
    http_response *response = NULL;

    response = malloc(sizeof(http_response));
    if (response == NULL)
    {
        return NULL;
    }   

    response->body = (unsigned char*) calloc(HEADERS_LENGTH, sizeof(unsigned char));
    if (response->body == NULL)
    {
        free(response);
        return NULL;
    }

    response->length = snprintf((char*)response->body, HEADERS_LENGTH,
             "HTTP/1.1 200 OK\r\n"
             "Date: %s\r\n"
             "Server: %s\r\n"
             "Allow: %s\r\n"
             "Content-Length: 0\r\n"
             "\r\n",
             http_get_date(), server_signature, allow);
    
    if (response->length < 0 || response->length >= HEADERS_LENGTH)
    {
        free(response->body);
        free(response);
        return NULL;
    }
    return response;
}