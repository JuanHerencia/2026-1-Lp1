void compactar_archivo(const char *original, const char *temp) {
    FILE *orig = fopen(original, "rb");
    FILE *tmp = fopen(temp, "wb");
    
    if (!orig || !tmp) return;
    
    Cliente c;
    int contador = 0;
    
    // Leer todos los registros activos
    while (fread(&c, sizeof(Cliente), 1, orig) == 1) {
        if (c.activo) {
            fwrite(&c, sizeof(Cliente), 1, tmp);
            contador++;
        }
    }
    
    fclose(orig);
    fclose(tmp);
    
    // Reemplazar archivo original
    remove(original);
    rename(temp, original);
    
    printf("Compactación completa: %d registros activos\n", contador);
}