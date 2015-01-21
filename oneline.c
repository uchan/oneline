#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define VERSION "0.8"
#define REPO "https://github.com/uchan/oneline"

// type define
#define byte unsigned char

// consts
enum LineBytes{
  CR = 0x0d,
  LF = 0x0a
};

const int ARG_COUNT = 3;
const int MAX_LEN_OUT = 4;
const size_t LARGE_SIZE = 100*1024*1024;

const char* OUTPUT_CRLF = "crlf";
const char* OUTPUT_CR = "cr";
const char* OUTPUT_LF = "lf";

//-----------------------------------
// global vars
static FILE* input_file = NULL;
enum LineType 
{
  TYPE_INVALID = -1,
  TYPE_CRLF = 0,
  TYPE_CR = 1,
  TYPE_LF = 2
};
static enum LineType output_type = TYPE_INVALID;
static size_t output_size = 0;
static byte* input_buffer = NULL;
static byte* output_buffer = NULL;

//-----------------------------------
// help func

// print usage help
void print_help()
{
  printf("version:%s\n", VERSION);
  printf("repo:%s\n", REPO);
  printf("\noneline <filename> <output-format>\n");
  printf("output-format:crlf/cr/lf\n");
}

// store parameters
bool set_parameter(const char* filename, const char* output)
{
  // check file
  FILE* test_file = fopen(filename, "r+b");
  if (NULL == test_file)
  {
    perror(filename);
    return false;
  }
  else
  {
    input_file = test_file;
  }

  // check output
  int length = strlen(output); 
  if (MAX_LEN_OUT < length)
  {
    printf("output format error:%s\n", output);
    return false;
  }

  char* lower = (char*) calloc(length, 1);
  if (NULL == lower)
  {
    printf("can not allocate memory\n");
    return false;
  }
  for (int i = 0; i < length; i++)
  {
    lower[i] = tolower(output[i]);
  }

  if (0 == strcmp(lower, OUTPUT_CRLF))
  {
    output_type = TYPE_CRLF;
  }
  else if (0 == strcmp(lower, OUTPUT_CR))
  {
    output_type = TYPE_CR;
  }
  else if (0 == strcmp(lower, OUTPUT_LF))
  {
    output_type = TYPE_LF;
  }
  else
  {
    printf("output format error:%s\n", output);
    return false;
  }

  return true;
}

void put_output()
{
  byte* buffer = output_buffer + output_size;

  assert(NULL != buffer);

  switch(output_type)
  {
    case TYPE_CRLF:
      *buffer = CR;
      *(buffer + 1) = LF;
      output_size = output_size + 2;
      break;
    case TYPE_CR:
      *buffer = CR;
      output_size++;
      break;
    case TYPE_LF:
      *buffer = LF;
      output_size++;
      break;
    default:
      assert(0);
      break;
  }
}

// clean resource
void cleanup()
{
  if (NULL != input_file)
  {
    fclose(input_file);
  }
  if (NULL != input_buffer)
  {
    free(input_buffer);
  }
  if (NULL != output_buffer)
  {
    free(output_buffer);
  }
}
//-----------------------------------
// main func

void transform()
{
  // get file size
  if (0 != fseek(input_file, 0, SEEK_END))
  {
    printf("can not seek\n");
    return;
  }
  size_t size = ftell(input_file);
  rewind(input_file);
  if (LARGE_SIZE < size)
  {
    printf("large file:%lu, may take sometime or outof memory\n", size);
  }

  // make buffer
  input_buffer = (byte*)calloc(size, 1);
  if (NULL == input_buffer)
  {
    printf("can not allocate memory\n");
    return;
  }

  // read to buffer
  size_t result = fread(input_buffer, 1, size, input_file);
  if (result != size)
  {
    printf("read error:%lu", result);
    return;
  }

  // make output buffer
  output_buffer = (byte*)calloc(size * 2, 1);
  if (NULL == output_buffer)
  {
    printf("can not allocate memory\n");
    return;
  }

  // copy input to output
  size_t i = 0;
  while(i < size)
  {
    switch(input_buffer[i])
    {
      case CR:
        put_output();
        if (LF == input_buffer[i + 1]){
          i = i + 2;
        }else{
          i++;
        }
        break;
      case LF:
        put_output();
        i++;
        break;
      default:
        output_buffer[output_size] = input_buffer[i];
        output_size++;
        i++;
        break;
    }
  }   

  // write data to file
  rewind(input_file);
  result = fwrite(output_buffer, 1, output_size, input_file);
}

int main(int argc, char** argv)
{
  // check args
  if (ARG_COUNT != argc)
  {
    print_help();
    return 0;
  }
  else
  {
    bool result = set_parameter(argv[1], argv[2]);
    if (false == result)
    {
      cleanup();
      return -1;
    } 
  }

  // process
  transform();

  // clean up on exit
  cleanup();

  return 0;
}
