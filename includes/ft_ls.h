/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:04:45 by ksalmi            #+#    #+#             */
/*   Updated: 2020/07/24 21:05:43 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include "ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <sys/acl.h>
# define BASE_STR_LOW "0123456789abcdef"
# define MAX_BUF_SIZE 256

/*
** Struct to hold command line options **
*/
typedef struct		s_opts
{
	int				a_option;
	int				lower_r_option;
	int				upper_r_option;
	int				l_option;
	int				t_option;
	int				g_option;
	int				specify_dir_name;
}					t_opts;

typedef struct		s_btree
{
	struct stat		stats;
	char			name[MAX_BUF_SIZE];
	char			*path;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

typedef	struct		s_format
{
	int				hard_links;
	int				owner;
	int				group;
	int				size;
	int				maj_min[2];
}					t_format;

void				init_ls(t_opts *opts);
int					read_options(char **argv, int argc, t_opts *opts, int i);
t_btree				*build_btree_sort_print(char *arg, t_opts *opts);
t_btree				*btree_create_node(char *path, char *d_name);
void				btree_add_left(t_btree **begin, t_btree *node);
t_btree				*open_dir_make_btree(const char *path, t_opts *opts);
t_btree				*add_sub_dirs(t_btree *tree, t_opts *opts);
char				*create_new_path(const char *path_name, char *addition);
void				content_swap(t_btree **j, t_btree **i);
void				sort_branch(t_btree *tree, t_opts *opts);
void				error_check(int num, char *msg);
int					is_symlink(char *path);
void				print_directory(t_btree *tree, t_opts *opts);
int					sort_args_print_files(char **argv, \
						int argc, int i, t_opts *opts);
void				print_files(char **arr, int limit, t_opts *opts);
int					is_dir(char *file);
int					is_exec(struct stat info);
char				*check_dir_name(char *dir_name);
void				handle_long_format(t_btree *tree, t_opts *opts);
void				free_btree(t_btree *tree, t_opts *opts);
int					compare_time(struct stat info_i, struct stat info_j);
int					check_group_namelen(gid_t group_num);
int					check_owner_namelen(uid_t owner_num);
struct stat			get_struct_stat(char *path);
t_format			*add_buffers(t_format *format);
void				print_permissions(mode_t st_mode);
void				print_time(struct timespec st_mtimespec);
int					print_xattr_acl(char *path);
void				print_name_symlink(char *n, char *p, struct stat in, \
						t_opts *opts);
void				print_color(struct stat info, char *msg);
void				handle_long_format_file_array(char **arr, int limit, \
						t_opts *opts);
void				print_l_form_array(char **arr, \
						t_format *f, int lim, t_opts *opts);
void				print_owner_group(struct stat info, t_format *format);
char				check_type(mode_t st_mode);
void				print_device(struct stat info, int *maj_min);
int					*check_device_len(struct stat info, int *maj_min);
#endif
