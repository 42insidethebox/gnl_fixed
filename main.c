/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedroribeiro <pedroribeiro@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:40:50 by pedroribeir       #+#    #+#             */
/*   Updated: 2024/12/10 16:53:27 by pedroribeir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    char    *line;
    int     fd;

    fd = open("tests/empty_file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open empty_file");
        return (1);
    }
    printf("=== Test Empty File ===\n");
    line = get_next_line(fd);
    if (!line)
        printf("No line returned, correct for empty file.\n");
    else
    {
        printf("Unexpected line: %s\n", line);
        free(line);
    }
    close(fd);
    printf("\n");

    fd = open("tests/no_newline_at_end.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open no_newline_at_end");
        return (1);
    }
    printf("=== Test No Newline at End ===\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);
    }
    close(fd);
    printf("\n");

    fd = open("tests/multiple_lines.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open multiple_lines");
        return (1);
    }
    printf("=== Test Multiple Lines ===\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);
    }
    close(fd);
    printf("\n");

    fd = open("tests/large_file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open large_file");
        return (1);
    }
    printf("=== Test Large File ===\n");
    int count = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (count < 3)
            printf("Line %d: %s", count + 1, line);
        free(line);
        count++;
    }
    printf("Total lines read: %d\n", count);
    close(fd);

    return 0;
}