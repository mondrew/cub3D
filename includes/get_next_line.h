#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 32

typedef struct		s_list
{
	char			*data;
	char			*fd;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
int					foo(char **temp_str, t_list **stack, int fd);
char				*ft_cut_line(char *str, t_list **stack, int fd);
t_list				*ft_lstnew_addback(t_list **stack, int fd, char *to_stack);
int					ft_lst_del_clear(t_list **stack, t_list *node, int n);

size_t				ft_strlen_checknl(const char *s, int n);
char				*ft_strjoin_m(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_itoa_m(int n, int num);
int					ft_atoi(const char *nptr);

#endif
