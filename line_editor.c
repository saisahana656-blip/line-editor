/*
 * Build a Simple Line Editor in C
 * Commands: insert, delete, display, save, load, search, help, quit
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 500
#define MAX_LEN 256
#define FILE_NAME_LEN 256

static char lines[MAX_LINES][MAX_LEN];
static int line_count = 0;

static void trim_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) s[--n] = '\0';
}

static int read_int(const char *prompt, int *out) {
    char buffer[64], *end;
    long value;
    printf("%s", prompt);
    if (!fgets(buffer, sizeof buffer, stdin)) return 0;
    value = strtol(buffer, &end, 10);
    while (*end && isspace((unsigned char)*end)) end++;
    if (end == buffer || *end != '\0' || value < -2147483647L || value > 2147483647L) {
        puts("Please enter a valid whole number.");
        return -1;
    }
    *out = (int)value;
    return 1;
}

static void display(void) {
    int i;
    if (line_count == 0) { puts("(document is empty)"); return; }
    for (i = 0; i < line_count; i++) printf("%3d | %s\n", i + 1, lines[i]);
}

static void insert_line(void) {
    int pos, i, status;
    char text[MAX_LEN];
    if (line_count >= MAX_LINES) { puts("Document is full."); return; }
    status = read_int("Insert at line number (1 to end+1): ", &pos);
    if (status <= 0) return;
    if (pos < 1 || pos > line_count + 1) { puts("Line number out of range."); return; }
    printf("Text: ");
    if (!fgets(text, sizeof text, stdin)) return;
    trim_newline(text);
    for (i = line_count; i >= pos; i--) strcpy(lines[i], lines[i - 1]);
    strcpy(lines[pos - 1], text);
    line_count++;
    puts("Line inserted.");
}

static void delete_line(void) {
    int pos, i, status = read_int("Delete line number: ", &pos);
    if (status <= 0) return;
    if (pos < 1 || pos > line_count) { puts("Line number out of range."); return; }
    for (i = pos - 1; i < line_count - 1; i++) strcpy(lines[i], lines[i + 1]);
    line_count--;
    puts("Line deleted.");
}

static void save_file(void) {
    char filename[FILE_NAME_LEN];
    FILE *fp;
    printf("Filename to save (e.g. document.txt): ");
    if (!fgets(filename, sizeof filename, stdin)) return;
    trim_newline(filename);
    fp = fopen(filename, "w");
    if (!fp) { perror("Could not open file"); return; }
    for (int i = 0; i < line_count; i++) fprintf(fp, "%s\n", lines[i]);
    if (fclose(fp) != 0) { perror("Could not finish saving file"); return; }
    printf("Saved %d line(s) to %s.\n", line_count, filename);
}

static void load_file(void) {
    char filename[FILE_NAME_LEN], buffer[MAX_LEN];
    FILE *fp;
    int count = 0;
    printf("Filename to load: ");
    if (!fgets(filename, sizeof filename, stdin)) return;
    trim_newline(filename);
    fp = fopen(filename, "r");
    if (!fp) { perror("Could not open file"); return; }
    while (count < MAX_LINES && fgets(buffer, sizeof buffer, fp)) {
        trim_newline(buffer);
        strncpy(lines[count], buffer, MAX_LEN - 1);
        lines[count][MAX_LEN - 1] = '\0';
        count++;
    }
    if (ferror(fp)) { perror("Error reading file"); fclose(fp); return; }
    fclose(fp);
    line_count = count;
    printf("Loaded %d line(s) from %s.\n", line_count, filename);
    if (count == MAX_LINES) puts("Note: document capacity reached; any remaining file lines were not loaded.");
}

static void search_text(void) {
    char query[MAX_LEN];
    int found = 0;
    printf("Search for: ");
    if (!fgets(query, sizeof query, stdin)) return;
    trim_newline(query);
    if (query[0] == '\0') { puts("Search text cannot be empty."); return; }
    for (int i = 0; i < line_count; i++) {
        if (strstr(lines[i], query)) {
            printf("Found on line %d: %s\n", i + 1, lines[i]);
            found = 1;
        }
    }
    if (!found) puts("No matches found.");
}

static void help(void) {
    puts("\nCommands:");
    puts("  i  Insert a line at a line number");
    puts("  d  Delete a line by number");
    puts("  p  Print all lines");
    puts("  s  Save document to a text file");
    puts("  l  Load document from a text file (replaces current contents)");
    puts("  f  Find text and show matching line numbers");
    puts("  h  Show this help");
    puts("  q  Quit");
}

int main(void) {
    char command[32];
    puts("Simple Line Editor");
    help();
    for (;;) {
        printf("\nline-editor> ");
        if (!fgets(command, sizeof command, stdin)) break;
        trim_newline(command);
        if (strcmp(command, "i") == 0 || strcmp(command, "insert") == 0) insert_line();
        else if (strcmp(command, "d") == 0 || strcmp(command, "delete") == 0) delete_line();
        else if (strcmp(command, "p") == 0 || strcmp(command, "print") == 0 || strcmp(command, "display") == 0) display();
        else if (strcmp(command, "s") == 0 || strcmp(command, "save") == 0) save_file();
        else if (strcmp(command, "l") == 0 || strcmp(command, "load") == 0) load_file();
        else if (strcmp(command, "f") == 0 || strcmp(command, "find") == 0 || strcmp(command, "search") == 0) search_text();
        else if (strcmp(command, "h") == 0 || strcmp(command, "help") == 0) help();
        else if (strcmp(command, "q") == 0 || strcmp(command, "quit") == 0) { puts("Goodbye."); break; }
        else puts("Unknown command. Type h for help.");
    }
    return 0;
}
