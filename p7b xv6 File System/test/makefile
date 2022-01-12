make:
	gcc -o fscheck fscheck.c -Wall -Werror
clean:
	rm -rf fscheck
test0:
	./fscheck good.img
test1:	
	@echo 'ERROR: bad inode.'
	./fscheck inode_1_badinode.img
test2:
	@echo 'ERROR: bad size in inode.'
	./fscheck inode_2_badsize.img
test3:
	@echo 'ERROR: root directory does not exist.'
	./fscheck dircheck_1_badroot.img
test4:
	@echo 'ERROR: current directory mismatch.'
	./fscheck dircheck_2_currdir.img
test5:
	@echo 'ERROR: bitmap marks data free but data block used by inode.'
	./fscheck bmapcheck_1_unmarked.img 
test6:	
	@echo 'ERROR: bitmap marks data block in use but not used.'
	./fscheck bmapcheck_2_marked.img
test7:
	@echo 'ERROR: inode marked free but referred to in directory.'
	./fscheck multistruct_1_freeinode.img
test8:
	@echo 'ERROR: inode marked in use but not found in a directory.'
	./fscheck multistruct_2_inuseInode.img
	
