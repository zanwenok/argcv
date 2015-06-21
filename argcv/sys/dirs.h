#ifndef ARGCV_SYS_DIRS_H
#define ARGCV_SYS_DIRS_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus


int dir_trav(const char* path, int recu, int (*file_handle)(const char* file_name, int is_dir, void* user),
             void* user);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  //  ARGCV_SYS_SYS_H