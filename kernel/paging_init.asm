extern page_directory

global load_page_directory
global enable_paging

bits 32
load_page_directory:
	mov eax, [page_directory]
	mov cr3, eax
	
	ret
	
enable_paging:
	mov eax, cr0
	or eax, 80000000h
	mov cr0, eax
	
	ret
