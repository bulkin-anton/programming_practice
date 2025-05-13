#ifndef __SPLITTER_H__
#define __SPLITTER_H__

void set_delimiter(const char *str);

void set_array(int parc, const char *parms[]);

void free_splitter(void);

int next_block(int *begin, int *end);

#endif
