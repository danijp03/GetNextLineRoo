/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:56:42 by roo               #+#    #+#             */
/*   Updated: 2024/12/10 20:59:30 by dajose-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_find_line(char *buffer)
{
	int		i;
	char	*line;
	static int		line_len = 0;

	buffer += line_len;
	if (buffer[0] == '\0')
		return (NULL);
	if (ft_strchr(buffer, '\n'))
		line_len += ft_strchr(buffer, '\n') + 1 - buffer;
	else
		line_len += ft_strchr(buffer, '\0') - buffer;
	line = malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
    static char     *buffer;
    char            *temp_buffer;
    char            *line;
    static ssize_t         readed = 1;
    unsigned int    aux;

    if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    if (!buffer)
    	buffer = ft_calloc(1, BUFFER_SIZE + 1);
    while (readed > 0)
    {
        temp_buffer = ft_calloc(1, BUFFER_SIZE + 1);
        readed = read(fd, temp_buffer, BUFFER_SIZE);
       /* if (readed <= 0)
            break;*/
        buffer = ft_strjoin(buffer, temp_buffer);
        free(temp_buffer);
    }
    line = ft_find_line(buffer);
    //aux = ft_strlen(line);
    //buffer = ft_substr(buffer, aux, ft_strlen(buffer));
    //printf("%s", buffer);
    return(line);
}

#include <fcntl.h>
int main(void)
{
    char *line;
    int fd = open("patata.txt", O_RDONLY);
    line = "a";
    while (line != NULL)
    {
	    line = get_next_line(fd);
	    printf("%s", line);
	    if (!line)
		    return (0);
	    free(line);
    }
    close(fd);
    return(0);
}
