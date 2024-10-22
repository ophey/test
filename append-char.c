#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char *arg) {
  fprintf(stderr,
	  "Append contents of one character stream to another, using one of 3 different methods\n\n"
	  "Usage: %s ( 'c' | 'l' | 'b' ) "
	  "[ ('-' | from-file ) [to-file] ]\n"
	  "\n"
	  "      'c' : copy characters with getc/putc\n"
	  "      'l' : copy lines with fgets/fputs\n"
	  "      'b' : copy bytes with fread/fwrite\n"
	  "\n"
	  "from-file : existing file opened for reading (if ommitted, read from stdin)\n"
	  "      '-' : read from stdin instead\n"
	  "  to-file : file opened or created for appending (if ommitted, write to stdout)\n\n"
	  "(Ref. David A. Curry : \"Using C on the UNIX System\", Examples 2-1, 2-2 and 2-3)\n"
	  , arg);
}

void fail_with_usage(char *arg) {
  usage(arg);
  exit(1);
}


FILE* try_open(char* file_name, char* mode) {
  FILE* result = fopen(file_name, mode);
  if(result == NULL) {
    perror(file_name);
    exit(1);
  } else {
    return result;
  }
}

void copy_chars_from_to(FILE* from, FILE* to) {
  int c;
  while((c = getc(from)) != EOF) {
    putc(c, to);
  }
}

void copy_lines_from_to(FILE* from, FILE* to) {
  char line[BUFSIZ];
  while(fgets(line, BUFSIZ, from) != NULL) {
    fputs(line, to);
  }
}

void copy_bytes_from_to(FILE* from, FILE* to) {
  char buf[BUFSIZ];
  int n;
  while((n = fread(buf, sizeof(char), BUFSIZ, from)) > 0) {
    fwrite(buf, sizeof(char), n, to);
  }
}


int main (int argc, char **argv) {
  FILE *from = stdin ,*to = stdout; // default to stdin and stdout
    
  if(argc < 2 || argc > 4) { // check argument count
    fail_with_usage(*argv);
  }
    
  // at this point at least one arg is given

  // first arg is mandatory and determines copy mode
  void (*copy_proc)(FILE*, FILE*) = NULL;
  if(!strcmp("c", argv[1])) {
    copy_proc = &copy_chars_from_to;
  } else if(!strcmp("l", argv[1])) {
    copy_proc = &copy_lines_from_to;
  } else if(!strcmp("b", argv[1])) {
    copy_proc = &copy_bytes_from_to;
  } else {
    fail_with_usage(*argv);
  }

  // handle optional file arguments
  if(argc > 2) {
    
    if(strcmp("-", argv[2])) { // arg as '-' leaves stdin
      from = try_open(argv[2], "r"); // or open file for reading
    }
    
    if(argc == 4) { // if second arg is given
      to = try_open(argv[3], "a"); // create/open file for appending
    }
  }
  copy_proc(from, to);
  fclose(from);
  fclose(to);
  exit(0);
}
