/**********************************************************************

  ruby/vm.h -

  $Author$
  created at: Sat May 31 15:17:36 2008

  Copyright (C) 2008 Yukihiro Matsumoto

**********************************************************************/

#ifndef RUBY_VM_H
#define RUBY_VM_H 1
#define HAVE_MVM 1

/* VM type declaration */
typedef struct rb_vm_struct ruby_vm_t;

/* core API */
ruby_vm_t *ruby_vm_new(int argc, char *argv[]);
int ruby_vm_run(ruby_vm_t *vm);
int ruby_vm_start(ruby_vm_t *vm);
int ruby_vm_join(ruby_vm_t *vm);
int ruby_vm_destruct(ruby_vm_t *vm);

/* initialize API */
int ruby_vm_init_add_argv(ruby_vm_t *vm, const char *arg);
int ruby_vm_init_add_library(ruby_vm_t *vm, const char *lib);
int ruby_vm_init_add_library_path(ruby_vm_t *vm, const char *path);
int ruby_vm_init_add_expression(ruby_vm_t *vm, const char *expr);
int ruby_vm_init_script(ruby_vm_t *vm, const char *script);
int ruby_vm_init_verbose(ruby_vm_t *vm, int verbose_p);
int ruby_vm_init_debug(ruby_vm_t *vm, int debug);
int ruby_vm_init_add_initializer(ruby_vm_t *vm, void (*initializer)(ruby_vm_t *));
int ruby_vm_init_stdin(ruby_vm_t *vm, int fd);
int ruby_vm_init_stdout(ruby_vm_t *vm, int fd);
int ruby_vm_init_stderr(ruby_vm_t *vm, int fd);

/* other API */
void ruby_vm_foreach(int (*)(ruby_vm_t *, void *), void *); /* returning false stops iteration */
void *ruby_vm_specific_ptr(ruby_vm_t *, int);


/* system level initializer */

#if (defined(__APPLE__) || defined(__NeXT__)) && defined(__MACH__)
/* to link startup code with ObjC support */
#define RUBY_GLOBAL_SETUP static void objcdummyfunction(void) {objc_msgSend();}
#else
#define RUBY_GLOBAL_SETUP
#endif

void ruby_sysinit(int *, char ***);

#ifdef __ia64
void ruby_init_stack(void *, void *);
#define ruby_init_stack(addr) ruby_init_stack(addr, rb_ia64_bsp())
#else
void ruby_init_stack(void *);
#endif
#define RUBY_INIT_STACK \
    void *variable_in_this_stack_frame; \
    ruby_init_stack(&variable_in_this_stack_frame);

#endif /* RUBY_VM_H */
