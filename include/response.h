/**
 * @brief Wrapper for fopen() to read the contents of a file. 
 *
 * @param The file path, relative to the directory containing the file where this method is executed.
 * @return The file contents as a string, or NULL if the read failed.
 */
char* readFile(char *fileName);
