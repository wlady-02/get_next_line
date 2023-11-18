#include <unistd.h>  // per la chiamata di sistema read
#include <stdio.h>

int main() {
    char buffer[100];
    int file_descriptor = 0;  // 0 è il file descriptor di stdin

    // Utilizzo della chiamata di sistema read per leggere da stdin
    ssize_t bytesRead = read(file_descriptor, buffer, sizeof(buffer));

    if (bytesRead > 0) {
        printf("Hai inserito: %.*s\n", (int)bytesRead, buffer);
    } else {
        perror("Errore nella lettura");
    }

    return 0;
}

// dio cane, mi gira il cazzo! Oggi ho pure voglia di morire : ) 
// Detto questo tu come stai?
// Bene, grazie della domanda!
// Prego a differenza tua io non sono maleducato e ringrazio.
// Sparati tipo questa cosa sta degenrando!
