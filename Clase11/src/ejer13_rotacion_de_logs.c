#include <sys/stat.h>  // Para stat() en Unix/Linux

void log_rotar_si_necesario(size_t max_bytes) {
    if (!logger.archivo) return;
    
    // Obtener tamaño actual
    fflush(logger.archivo);
    struct stat st;
    if (fstat(fileno(logger.archivo), &st) == 0) {
        if (st.st_size > max_bytes) {
            // Cerrar archivo actual
            fclose(logger.archivo);
            
            // Rotar: app.log -> app.log.1, app.log.1 -> app.log.2, etc.
            char old_name[256], new_name[256];
            for (int i = 9; i > 0; i--) {
                snprintf(old_name, sizeof(old_name), "app.log.%d", i-1);
                snprintf(new_name, sizeof(new_name), "app.log.%d", i);
                rename(old_name, new_name);
            }
            rename("app.log", "app.log.1");
            
            // Abrir nuevo archivo
            logger.archivo = fopen("app.log", "a");
            LOG_INFO("System", "Log rotado (tamaño alcanzó %ld bytes)", st.st_size);
        }
    }
}