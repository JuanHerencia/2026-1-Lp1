#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

// Niveles de log
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
} LogLevel;

const char *niveles_texto[] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR",
    "CRITICAL"
};

// Configuración global
typedef struct {
    FILE *archivo;
    LogLevel nivel_minimo;
    int escribir_consola;
} Logger;

Logger logger = {NULL, LOG_INFO, 1};

// Inicializar logger
void log_init(const char *nombre_archivo, LogLevel nivel_minimo) {
    logger.archivo = fopen(nombre_archivo, "a");
    logger.nivel_minimo = nivel_minimo;
    logger.escribir_consola = 1;
    
    if (logger.archivo == NULL) {
        perror("Error abriendo archivo de log");
    }
}

// Obtener timestamp formateado
void obtener_timestamp(char *buffer, size_t size) {
    time_t ahora = time(NULL);
    struct tm *info = localtime(&ahora);
    
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", info);
}

// Función principal de logging
void log_message(LogLevel nivel, const char *modulo, const char *formato, ...) {
    if (nivel < logger.nivel_minimo) return;
    if (!logger.archivo && !logger.escribir_consola) return;
    
    char timestamp[64];
    obtener_timestamp(timestamp, sizeof(timestamp));
    
    // Formatear mensaje del usuario
    char mensaje[1024];
    va_list args;
    va_start(args, formato);
    vsnprintf(mensaje, sizeof(mensaje), formato, args);
    va_end(args);
    
    // Línea completa de log
    char linea_log[2048];
    snprintf(linea_log, sizeof(linea_log),
             "[%s] %-8s [%s] %s\n",
             timestamp, niveles_texto[nivel], modulo, mensaje);
    
    // Escribir a archivo
    if (logger.archivo) {
        fputs(linea_log, logger.archivo);
        fflush(logger.archivo);  // Forzar escritura inmediata
    }
    
    // Escribir a consola (con colores opcionales)
    if (logger.escribir_consola) {
        // Códigos ANSI para colores en terminal
        const char *color = "";
        switch (nivel) {
            case LOG_DEBUG:   color = "\033[36m"; break;  // Cyan
            case LOG_INFO:    color = "\033[32m"; break;  // Verde
            case LOG_WARNING: color = "\033[33m"; break;  // Amarillo
            case LOG_ERROR:   color = "\033[31m"; break;  // Rojo
            case LOG_CRITICAL:color = "\033[35m\033[1m"; break;  // Magenta + bold
        }
        
        printf("%s%s\033[0m", color, linea_log);
    }
}

// Macros para facilidad de uso
#define LOG_DEBUG(mod, ...)   log_message(LOG_DEBUG, mod, __VA_ARGS__)
#define LOG_INFO(mod, ...)    log_message(LOG_INFO, mod, __VA_ARGS__)
#define LOG_WARN(mod, ...)    log_message(LOG_WARNING, mod, __VA_ARGS__)
#define LOG_ERROR(mod, ...)   log_message(LOG_ERROR, mod, __VA_ARGS__)
#define LOG_CRITICAL(mod, ...) log_message(LOG_CRITICAL, mod, __VA_ARGS__)

// Cerrar logger
void log_cerrar() {
    if (logger.archivo) {
        LOG_INFO("System", "Logger cerrado correctamente");
        fclose(logger.archivo);
        logger.archivo = NULL;
    }
}

// EJEMPLO DE USO
int main() {
    // Inicializar
    log_init("aplicacion.log", LOG_DEBUG);
    
    // Simular operaciones
    LOG_INFO("Database", "Conectando a la base de datos...");
    LOG_DEBUG("Database", "Usuario: %s, Host: %s", "admin", "localhost");
    
    // Simular advertencia
    LOG_WARN("Network", "Timeout en conexión, reintentando (%d/3)", 1);
    
    // Simular error
    LOG_ERROR("FileSystem", "No se pudo abrir archivo: %s", "config.ini");
    
    // Simular situación crítica
    if (1) {  // Condición hipotética
        LOG_CRITICAL("Security", "Buffer overflow detectado en función %s", "parse_input");
    }
    
    LOG_INFO("System", "Aplicación finalizada normalmente");
    
    log_cerrar();
    
    return 0;
}