/** @file paging.h
 * 
 * 
 *
 */
 
#ifndef PAGING_H
#define PAGING_H
#define PDE_NUM 3
#define PTE_NUM 1024

extern void load_page_directory();
extern void enable_paging();

extern unsigned int *page_directory;

void paging_init();
int create_page_entry( int, char, char, char, char, char, char, char, char );
#endif
