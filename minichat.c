#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define PORT 8080

// Variables globales
SOCKET sockfd = INVALID_SOCKET;
char ultimo_recibido[BUFFER_SIZE] = "";
char ultimo_enviado[BUFFER_SIZE] = "";
HANDLE mutex = NULL;
int running = 1;

// Función para limpiar la pantalla
void limpiar_pantalla() {
    system("cls");
}

// Función para mostrar la interfaz
void mostrar_interfaz() {
    limpiar_pantalla();
    printf("========== MINICHAT TCP/IP ==========\n");
    printf("Para salir: escribir 'exit' o presionar Ctrl+C\n");
    printf("-------------------------------------\n");
    
    WaitForSingleObject(mutex, INFINITE);
    printf("ULTIMO MENSAJE RECIBIDO: %s\n", strlen(ultimo_recibido) > 0 ? ultimo_recibido : "(ninguno)");
    printf("ULTIMO MENSAJE ENVIADO: %s\n", strlen(ultimo_enviado) > 0 ? ultimo_enviado : "(ninguno)");
    ReleaseMutex(mutex);
    
    printf("-------------------------------------\n");
    printf("Escribe tu mensaje: ");
    fflush(stdout);
}

// Función para recibir mensajes (hilo)
unsigned int __stdcall recibir_mensajes(void *arg) {
    char buffer[BUFFER_SIZE];
    int n;
    
    while (running) {
        memset(buffer, 0, BUFFER_SIZE);
        n = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
        
        if (n <= 0) {
            if (running) {
                printf("\n[!] Conexion perdida con el servidor\n");
            }
            break;
        }
        
        buffer[n] = '\0';
        
        WaitForSingleObject(mutex, INFINITE);
        strncpy(ultimo_recibido, buffer, BUFFER_SIZE - 1);
        ReleaseMutex(mutex);
        
        // Mostrar el mensaje recibido sin interrumpir la entrada
        printf("\n\033[1A\033[2K"); // Borrar línea actual
        mostrar_interfaz();
    }
    return 0;
}

// Función para enviar mensajes
void enviar_mensaje(const char *mensaje) {
    if (sockfd == INVALID_SOCKET) return;
    
    if (send(sockfd, mensaje, (int)strlen(mensaje), 0) == SOCKET_ERROR) {
        printf("\n[!] Error al enviar mensaje\n");
        return;
    }
    
    WaitForSingleObject(mutex, INFINITE);
    strncpy(ultimo_enviado, mensaje, BUFFER_SIZE - 1);
    ReleaseMutex(mutex);
}

// Función para manejar Ctrl+C
BOOL WINAPI console_handler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        printf("\n[!] Cerrando conexion...\n");
        running = 0;
        if (sockfd != INVALID_SOCKET) {
            closesocket(sockfd);
            sockfd = INVALID_SOCKET;
        }
        WSACleanup();
        exit(0);
    }
    return TRUE;
}

// Función para validar dirección IP
int validar_ip(const char *ip) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1;
}

// Función para obtener la IP local
void obtener_ip_local() {
    char hostname[256];
    struct hostent *host_entry;
    
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        host_entry = gethostbyname(hostname);
        if (host_entry != NULL) {
            struct in_addr addr;
            addr.s_addr = *(u_long *)host_entry->h_addr_list[0];
            printf("[*] Tu IP local es: %s\n", inet_ntoa(addr));
        }
    }
}

int main() {
    WSADATA wsaData;
    char ip_destino[16];
    char mensaje[BUFFER_SIZE];
    struct sockaddr_in serv_addr;
    HANDLE hilo_recepcion;
    int opcion;
    
    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("[!] Error al inicializar Winsock\n");
        return 1;
    }
    
    // Crear mutex para sincronización
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) {
        printf("[!] Error al crear mutex\n");
        WSACleanup();
        return 1;
    }
    
    // Configurar manejador de Ctrl+C
    SetConsoleCtrlHandler(console_handler, TRUE);
    
    // Solicitar IP de destino
    limpiar_pantalla();
    printf("========== MINICHAT TCP/IP ==========\n\n");
    printf("1. Conectar como cliente (conectar a IP)\n");
    printf("2. Esperar como servidor (esperar conexion)\n");
    printf("3. Ver mi IP local\n");
    printf("Selecciona una opcion (1, 2 o 3): ");
    scanf("%d", &opcion);
    getchar(); // Limpiar buffer
    
    if (opcion == 3) {
        obtener_ip_local();
        printf("\nPresiona Enter para continuar...");
        getchar();
        limpiar_pantalla();
        printf("========== MINICHAT TCP/IP ==========\n\n");
        printf("1. Conectar como cliente (conectar a IP)\n");
        printf("2. Esperar como servidor (esperar conexion)\n");
        printf("Selecciona una opcion (1 o 2): ");
        scanf("%d", &opcion);
        getchar();
    }
    
    if (opcion == 1) {
        // Modo cliente - conectar a IP específica
        do {
            printf("Ingresa la direccion IP de destino: ");
            fgets(ip_destino, sizeof(ip_destino), stdin);
            ip_destino[strcspn(ip_destino, "\n")] = '\0';
            
            if (!validar_ip(ip_destino)) {
                printf("[!] IP invalida. Intenta nuevamente.\n");
            }
        } while (!validar_ip(ip_destino));
        
        // Crear socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == INVALID_SOCKET) {
            printf("[!] Error al crear socket\n");
            WSACleanup();
            return 1;
        }
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        
        if (inet_pton(AF_INET, ip_destino, &serv_addr.sin_addr) <= 0) {
            printf("[!] Direccion IP invalida\n");
            closesocket(sockfd);
            WSACleanup();
            return 1;
        }
        
        // Conectar al servidor
        printf("[*] Conectando a %s:%d...\n", ip_destino, PORT);
        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
            printf("[!] Error al conectar: %d\n", WSAGetLastError());
            closesocket(sockfd);
            WSACleanup();
            return 1;
        }
        printf("[+] Conectado a %s:%d\n", ip_destino, PORT);
        
    } else if (opcion == 2) {
        // Modo servidor - esperar conexión
        struct sockaddr_in direccion;
        int addr_len = sizeof(direccion);
        SOCKET socket_escucha;
        
        // Mostrar IP local
        obtener_ip_local();
        
        // Crear socket
        socket_escucha = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_escucha == INVALID_SOCKET) {
            printf("[!] Error al crear socket\n");
            WSACleanup();
            return 1;
        }
        
        direccion.sin_family = AF_INET;
        direccion.sin_addr.s_addr = INADDR_ANY;
        direccion.sin_port = htons(PORT);
        
        // Bind
        if (bind(socket_escucha, (struct sockaddr *)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
            printf("[!] Error al bind: %d\n", WSAGetLastError());
            closesocket(socket_escucha);
            WSACleanup();
            return 1;
        }
        
        // Escuchar
        if (listen(socket_escucha, 1) == SOCKET_ERROR) {
            printf("[!] Error al escuchar\n");
            closesocket(socket_escucha);
            WSACleanup();
            return 1;
        }
        
        printf("[*] Esperando conexion en el puerto %d...\n", PORT);
        sockfd = accept(socket_escucha, (struct sockaddr *)&direccion, &addr_len);
        if (sockfd == INVALID_SOCKET) {
            printf("[!] Error al aceptar conexion\n");
            closesocket(socket_escucha);
            WSACleanup();
            return 1;
        }
        
        // Obtener IP del cliente
        char ip_cliente[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &direccion.sin_addr, ip_cliente, sizeof(ip_cliente));
        printf("[+] Cliente conectado desde %s:%d\n", ip_cliente, ntohs(direccion.sin_port));
        closesocket(socket_escucha);
        
    } else {
        printf("[!] Opcion invalida\n");
        WSACleanup();
        return 1;
    }
    
    // Crear hilo para recibir mensajes
    unsigned int hilo_id;
    hilo_recepcion = (HANDLE)_beginthreadex(NULL, 0, recibir_mensajes, NULL, 0, &hilo_id);
    if (hilo_recepcion == NULL) {
        printf("[!] Error al crear hilo de recepcion\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    
    // Mostrar interfaz inicial
    Sleep(1000);
    mostrar_interfaz();
    
    // Bucle principal para enviar mensajes
    while (running) {
        memset(mensaje, 0, BUFFER_SIZE);
        
        if (fgets(mensaje, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        
        mensaje[strcspn(mensaje, "\n")] = '\0';
        
        // Verificar si es el comando de salida
        if (strcmp(mensaje, "exit") == 0) {
            printf("[*] Cerrando chat...\n");
            break;
        }
        
        // Enviar mensaje
        enviar_mensaje(mensaje);
        
        // Actualizar interfaz
        mostrar_interfaz();
    }
    
    // Limpiar
    running = 0;
    if (hilo_recepcion != NULL) {
        TerminateThread(hilo_recepcion, 0);
        CloseHandle(hilo_recepcion);
    }
    if (sockfd != INVALID_SOCKET) {
        closesocket(sockfd);
    }
    if (mutex != NULL) {
        CloseHandle(mutex);
    }
    WSACleanup();
    
    printf("[*] Chat cerrado\n");
    return 0;
}