/**
 * Author......: Jens Steube <jens.steube@gmail.com>
 * License.....: MIT
 */

#include "common.h"
#include "types_int.h"
#include "memory.h"
#include "filehandling.h"

uint count_lines (FILE *fd)
{
  uint cnt = 0;

  char *buf = (char *) mymalloc (HCBUFSIZ + 1);

  char prev = '\n';

  while (!feof (fd))
  {
    size_t nread = fread (buf, sizeof (char), HCBUFSIZ, fd);

    if (nread < 1) continue;

    size_t i;

    for (i = 0; i < nread; i++)
    {
      if (prev == '\n') cnt++;

      prev = buf[i];
    }
  }

  myfree (buf);

  return cnt;
}

int fgetl (FILE *fp, char *line_buf)
{
  int line_len = 0;

  while (!feof (fp))
  {
    const int c = fgetc (fp);

    if (c == EOF) break;

    line_buf[line_len] = (char) c;

    line_len++;

    if (line_len == HCBUFSIZ) line_len--;

    if (c == '\n') break;
  }

  if (line_len == 0) return 0;

  if (line_buf[line_len - 1] == '\n')
  {
    line_len--;

    line_buf[line_len] = 0;
  }

  if (line_len == 0) return 0;

  if (line_buf[line_len - 1] == '\r')
  {
    line_len--;

    line_buf[line_len] = 0;
  }

  return (line_len);
}

int in_superchop (char *buf)
{
  int len = strlen (buf);

  while (len)
  {
    if (buf[len - 1] == '\n')
    {
      len--;

      continue;
    }

    if (buf[len - 1] == '\r')
    {
      len--;

      continue;
    }

    break;
  }

  buf[len] = 0;

  return len;
}