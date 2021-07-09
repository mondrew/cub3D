#include "cub3d.h"

static char	*ft_free_strings(char *s1, char *s2)
{
	if (s1 != NULL)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2 != NULL)
	{
		free(s2);
		s2 = NULL;
	}
	return (NULL);
}

char		*ft_strjoin_free_add_n(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (ft_free_strings(s1, s2));
	if (!(new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2))))
		return (ft_free_strings(s1, s2));
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new_str[i++] = s2[j++];
	new_str[i++] = '\n';
	new_str[i] = '\0';
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (new_str);
}
