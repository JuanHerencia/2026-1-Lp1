// gcc miniservidor.c -lws2_32 -o miniservidor.exe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 8192
#define PORT 80
#define MAX_CLIENTS 10

// Función para obtener la fecha y hora actual
void obtener_timestamp(char *buffer, size_t size) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, size, "[%Y-%m-%d %H:%M:%S]", timeinfo);
}

// Función para extraer el método HTTP (GET/POST)
void extraer_metodo(const char *peticion, char *metodo, size_t size) {
    char temp[BUFFER_SIZE];
    strncpy(temp, peticion, BUFFER_SIZE - 1);
    temp[BUFFER_SIZE - 1] = '\0';
    
    char *token = strtok(temp, " ");
    if (token) {
        strncpy(metodo, token, size - 1);
        metodo[size - 1] = '\0';
    } else {
        strcpy(metodo, "DESCONOCIDO");
    }
}

// Función para extraer la URL solicitada
void extraer_url(const char *peticion, char *url, size_t size) {
    char temp[BUFFER_SIZE];
    strncpy(temp, peticion, BUFFER_SIZE - 1);
    temp[BUFFER_SIZE - 1] = '\0';
    
    char *token = strtok(temp, " ");
    if (token) {
        token = strtok(NULL, " ");
        if (token) {
            strncpy(url, token, size - 1);
            url[size - 1] = '\0';
        } else {
            strcpy(url, "/");
        }
    } else {
        strcpy(url, "/");
    }
}

// Función para extraer el body de una petición POST
void extraer_body(const char *peticion, char *body, size_t size) {
    char *pos = strstr(peticion, "\r\n\r\n");
    if (pos) {
        pos += 4; // Saltar los \r\n\r\n
        strncpy(body, pos, size - 1);
        body[size - 1] = '\0';
    } else {
        body[0] = '\0';
    }
}

// Función para extraer parámetros del POST
void extraer_parametros(const char *body, char *usuario, char *clave) {
    char temp[BUFFER_SIZE];
    strncpy(temp, body, BUFFER_SIZE - 1);
    temp[BUFFER_SIZE - 1] = '\0';
    
    // Buscar usuario
    char *user_pos = strstr(temp, "usuario=");
    if (user_pos) {
        user_pos += 8; // Saltar "usuario="
        char *end = strchr(user_pos, '&');
        if (end) {
            int len = end - user_pos;
            strncpy(usuario, user_pos, len);
            usuario[len] = '\0';
        } else {
            strcpy(usuario, user_pos);
        }
    } else {
        strcpy(usuario, "No especificado");
    }
    
    // Buscar clave
    char *pass_pos = strstr(temp, "clave=");
    if (pass_pos) {
        pass_pos += 6; // Saltar "clave="
        strcpy(clave, pass_pos);
        // Eliminar posibles saltos de línea
        char *newline = strchr(clave, '\r');
        if (newline) *newline = '\0';
        newline = strchr(clave, '\n');
        if (newline) *newline = '\0';
    } else {
        strcpy(clave, "No especificada");
    }
}

// Función para servir el archivo login.html
void servir_login_html(SOCKET client_socket) {
    FILE *file;
    char buffer[BUFFER_SIZE];
    char contenido[BUFFER_SIZE * 2];
    int bytes_read;
    long file_size;
    
    file = fopen("login.html", "rb");
    if (file == NULL) {
        // Si no existe, crearlo automáticamente con los dos botones
        const char *html_default = 
            "<!DOCTYPE html>\n"
            "<html>\n"
            "<head>\n"
            "    <meta charset='UTF-8'>\n"
            "    <title>Login</title>\n"
            "    <style>\n"
            "        body {\n"
            "            font-family: Arial, sans-serif;\n"
            "            margin: 0;\n"
            "            padding: 0;\n"
            "            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);\n"
            "            height: 100vh;\n"
            "            display: flex;\n"
            "            justify-content: center;\n"
            "            align-items: center;\n"
            "        }\n"
            "        .container {\n"
            "            background: white;\n"
            "            padding: 40px;\n"
            "            border-radius: 10px;\n"
            "            box-shadow: 0 10px 30px rgba(0,0,0,0.3);\n"
            "            width: 350px;\n"
            "        }\n"
            "        h2 {\n"
            "            text-align: center;\n"
            "            color: #333;\n"
            "            margin-bottom: 30px;\n"
            "        }\n"
            "        .form-group {\n"
            "            margin-bottom: 20px;\n"
            "        }\n"
            "        label {\n"
            "            display: block;\n"
            "            margin-bottom: 5px;\n"
            "            color: #555;\n"
            "            font-weight: bold;\n"
            "        }\n"
            "        input[type='text'],\n"
            "        input[type='password'] {\n"
            "            width: 100%;\n"
            "            padding: 10px;\n"
            "            border: 2px solid #ddd;\n"
            "            border-radius: 5px;\n"
            "            font-size: 16px;\n"
            "            box-sizing: border-box;\n"
            "            transition: border-color 0.3s;\n"
            "        }\n"
            "        input[type='text']:focus,\n"
            "        input[type='password']:focus {\n"
            "            outline: none;\n"
            "            border-color: #667eea;\n"
            "        }\n"
            "        .botones {\n"
            "            display: flex;\n"
            "            gap: 10px;\n"
            "            margin-top: 10px;\n"
            "        }\n"
            "        .btn-aceptar {\n"
            "            flex: 1;\n"
            "            padding: 12px;\n"
            "            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);\n"
            "            color: white;\n"
            "            border: none;\n"
            "            border-radius: 5px;\n"
            "            font-size: 16px;\n"
            "            font-weight: bold;\n"
            "            cursor: pointer;\n"
            "            transition: transform 0.2s;\n"
            "        }\n"
            "        .btn-aceptar:hover {\n"
            "            transform: scale(1.02);\n"
            "        }\n"
            "        .btn-cancelar {\n"
            "            flex: 1;\n"
            "            padding: 12px;\n"
            "            background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);\n"
            "            color: white;\n"
            "            border: none;\n"
            "            border-radius: 5px;\n"
            "            font-size: 16px;\n"
            "            font-weight: bold;\n"
            "            cursor: pointer;\n"
            "            transition: transform 0.2s;\n"
            "        }\n"
            "        .btn-cancelar:hover {\n"
            "            transform: scale(1.02);\n"
            "        }\n"
            "        .info {\n"
            "            text-align: center;\n"
            "            margin-top: 20px;\n"
            "            color: #888;\n"
            "            font-size: 12px;\n"
            "        }\n"
            "    </style>\n"
            "</head>\n"
            "<body>\n"
            "    <div class='container'>\n"
            "        <h2>🔐 Iniciar Sesión</h2>\n"
            "        <form method='POST' action='/login'>\n"
            "            <div class='form-group'>\n"
            "                <label>Usuario</label>\n"
            "                <input type='text' name='usuario' placeholder='Ingresa tu usuario' required>\n"
            "            </div>\n"
            "            <div class='form-group'>\n"
            "                <label>Clave</label>\n"
            "                <input type='password' name='clave' placeholder='Ingresa tu clave' required>\n"
            "            </div>\n"
            "            <div class='botones'>\n"
            "                <input type='submit' class='btn-aceptar' value='✅ Aceptar'>\n"
            "                <input type='button' class='btn-cancelar' value='❌ Cancelar' onclick='cancelar()'>\n"
            "            </div>\n"
            "        </form>\n"
            "        <div class='info'>\n"
            "            Mini Servidor Web - Prueba POST/GET\n"
            "        </div>\n"
            "    </div>\n"
            "    <script>\n"
            "        function cancelar() {\n"
            "            window.location.href = 'https://www.google.com/search?q=fundamentos+de+TCP%2FIP';\n"
            "        }\n"
            "    </script>\n"
            "</body>\n"
            "</html>";
        
        sprintf(contenido, 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %d\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s",
            (int)strlen(html_default), html_default);
        
        send(client_socket, contenido, strlen(contenido), 0);
        return;
    }
    
    // Obtener tamaño del archivo
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Leer el archivo
    memset(contenido, 0, sizeof(contenido));
    bytes_read = fread(contenido, 1, sizeof(contenido) - 1, file);
    fclose(file);
    
    // Enviar respuesta HTTP
    sprintf(buffer, 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        bytes_read, contenido);
    
    send(client_socket, buffer, strlen(buffer), 0);
}

// Función para procesar la petición y mostrar logs
void procesar_peticion(const char *peticion, SOCKET client_socket) {
    char metodo[20];
    char url[256];
    char body[BUFFER_SIZE];
    char timestamp[30];
    char usuario[100];
    char clave[100];
    
    extraer_metodo(peticion, metodo, sizeof(metodo));
    extraer_url(peticion, url, sizeof(url));
    extraer_body(peticion, body, sizeof(body));
    obtener_timestamp(timestamp, sizeof(timestamp));
    
    // Mostrar log
    printf("\n%s ========================================\n", timestamp);
    printf("PETICION RECIBIDA:\n");
    printf("  Metodo: %s\n", metodo);
    printf("  URL: %s\n", url);
    
    if (strcmp(metodo, "POST") == 0) {
        printf("  Body: %s\n", body);
        extraer_parametros(body, usuario, clave);
        printf("  Usuario: %s\n", usuario);
        printf("  Clave: %s\n", clave);
        
        // Responder con confirmación
        char respuesta[BUFFER_SIZE];
        sprintf(respuesta,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<!DOCTYPE html>\n"
            "<html>\n"
            "<head><meta charset='UTF-8'><title>Datos Recibidos</title>\n"
            "<style>\n"
            "body { font-family: Arial; margin: 50px; background: #f0f0f0; }\n"
            ".container { max-width: 600px; margin: auto; background: white; padding: 30px; border-radius: 10px; }\n"
            "h2 { color: #4CAF50; }\n"
            "p { padding: 10px; background: #f9f9f9; border-left: 4px solid #4CAF50; }\n"
            ".botones { display: flex; gap: 10px; margin-top: 20px; }\n"
            "a { display: inline-block; padding: 10px 20px; background: #4CAF50; color: white; text-decoration: none; border-radius: 5px; }\n"
            ".btn-volver { background: #667eea; }\n"
            "</style>\n"
            "</head>\n"
            "<body>\n"
            "    <div class='container'>\n"
            "        <h2>✅ Datos Recibidos Correctamente</h2>\n"
            "        <p><strong>Usuario:</strong> %s</p>\n"
            "        <p><strong>Clave:</strong> %s</p>\n"
            "        <div class='botones'>\n"
            "            <a href='/login.html' class='btn-volver'>← Volver al Login</a>\n"
            "        </div>\n"
            "    </div>\n"
            "</body>\n"
            "</html>\n",
            usuario, clave);
        
        send(client_socket, respuesta, strlen(respuesta), 0);
        
    } else if (strcmp(metodo, "GET") == 0) {
        // Para GET, servir el archivo login.html
        if (strcmp(url, "/") == 0 || strcmp(url, "/login.html") == 0) {
            servir_login_html(client_socket);
        } else {
            // Para otras URLs, mostrar error 404
            const char *not_found = 
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n"
                "<html><body><h1>404 - Archivo no encontrado</h1></body></html>";
            send(client_socket, not_found, strlen(not_found), 0);
        }
    }
    
    printf("========================================\n");
}

// Función para manejar clientes
void manejar_cliente(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_recibidos;
    
    memset(buffer, 0, sizeof(buffer));
    bytes_recibidos = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_recibidos > 0) {
        buffer[bytes_recibidos] = '\0';
        procesar_peticion(buffer, client_socket);
    }
    
    closesocket(client_socket);
}

// Función para mostrar la IP local
void obtener_ip_local() {
    char hostname[256];
    struct hostent *host_entry;
    WSADATA wsaData;
    
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        host_entry = gethostbyname(hostname);
        if (host_entry != NULL) {
            struct in_addr addr;
            addr.s_addr = *(u_long *)host_entry->h_addr_list[0];
            printf("IP Local: %s\n", inet_ntoa(addr));
        }
    }
    WSACleanup();
}

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    char timestamp[30];
    
    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error al inicializar Winsock\n");
        return 1;
    }
    
    // Mostrar información del servidor
    system("cls");
    printf("========================================\n");
    printf("    SERVIDOR WEB MINI - v2.0\n");
    printf("========================================\n");
    printf("Puerto: %d\n", PORT);
    obtener_ip_local();
    printf("\nPara usar el servidor:\n");
    printf("  - Abre un navegador y visita: http://localhost/login.html\n");
    printf("  - O usa la IP: http://IP_LOCAL/login.html\n");
    printf("\nCaracteristicas:\n");
    printf("  ✅ Boton Aceptar: Envia usuario/clave via POST\n");
    printf("  ❌ Boton Cancelar: Redirige a Google (TCP/IP)\n");
    printf("\nPresiona Ctrl+C para detener el servidor\n");
    printf("========================================\n\n");
    printf("Servidor iniciado. Esperando peticiones...\n");
    printf("----------------------------------------\n");
    
    // Crear socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Error al crear socket\n");
        WSACleanup();
        return 1;
    }
    
    // Configurar dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Bind
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Error al bind: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    
    // Escuchar
    if (listen(server_socket, MAX_CLIENTS) == SOCKET_ERROR) {
        printf("Error al escuchar\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    
    // Bucle principal
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket == INVALID_SOCKET) {
            printf("Error al aceptar conexión\n");
            continue;
        }
        
        // Mostrar IP del cliente
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
        obtener_timestamp(timestamp, sizeof(timestamp));
        printf("%s Conexión desde: %s:%d\n", timestamp, client_ip, ntohs(client_addr.sin_port));
        
        // Manejar cliente
        manejar_cliente(client_socket);
    }
    
    // Limpiar (nunca se alcanza en este bucle infinito)
    closesocket(server_socket);
    WSACleanup();
    return 0;
}