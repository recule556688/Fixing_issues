/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-iuliia.dabizha
** File description:
** Utility functions for corewar
*/

#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/corewar.h"

uint32_t convert_endian(uint32_t value)
{
    return ((value >> 24) & 0xFF) |
        ((value >> 8) & 0xFF00) |
        ((value << 8) & 0xFF0000) |
        ((value << 24) & 0xFF000000);
}

int read_magic_and_name(int fd, header_t *header,
    unsigned char *magic_buf, char *name_buf)
{
    if (read(fd, magic_buf, 4) != 4)
        return -1;
    if (read(fd, name_buf, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
        return -1;
    name_buf[PROG_NAME_LENGTH] = '\0';
    lseek(fd, 4, SEEK_CUR);
    header->magic = (magic_buf[0] << 24) | (magic_buf[1] << 16) |
        (magic_buf[2] << 8) | magic_buf[3];
    for (int i = 0; i < PROG_NAME_LENGTH; i++)
        header->prog_name[i] = name_buf[i];
    header->prog_name[PROG_NAME_LENGTH] = '\0';
    return 0;
}

int read_size_and_comment(int fd, header_t *header,
    unsigned char *size_buf, char *comment_buf)
{
    if (read(fd, size_buf, 4) != 4)
        return -1;
    if (read(fd, comment_buf, COMMENT_LENGTH) != COMMENT_LENGTH)
        return -1;
    comment_buf[COMMENT_LENGTH] = '\0';
    lseek(fd, 4, SEEK_CUR);
    header->prog_size = (size_buf[0] << 24) | (size_buf[1] << 16) |
        (size_buf[2] << 8) | size_buf[3];
    for (int i = 0; i < COMMENT_LENGTH; i++)
        header->comment[i] = comment_buf[i];
    header->comment[COMMENT_LENGTH] = '\0';
    return 0;
}

int read_champion_header(int fd, header_t *header)
{
    unsigned char magic_buf[4];
    unsigned char size_buf[4];
    char name_buf[PROG_NAME_LENGTH + 1];
    char comment_buf[COMMENT_LENGTH + 1];

    if (read_magic_and_name(fd, header, magic_buf, name_buf) == -1)
        return -1;
    if (read_size_and_comment(fd, header, size_buf, comment_buf) == -1)
        return -1;
    return 0;
}
