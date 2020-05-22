/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamzil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:33:10 by aamzil            #+#    #+#             */
/*   Updated: 2019/10/30 14:41:42 by aamzil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# define BUFFER_SIZE 700


# include <stdlib.h>

# include <sys/types.h>

# include <sys/uio.h>

# include <unistd.h>

int		get_next_line(int fd, char **line);
char	*my_realloc(char *dst, char *src, int len);
int		has_nl(char *s, int new_line);
char	*my_free(char *buf, char *rest);
char	*sdp(char *s1, char *right_s);
char	*helper_fun(char **line, char *rest, char *buf);

#endif
