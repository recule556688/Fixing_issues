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

int read_magic_and_name(int fd, header_t *header,
    unsigned char *magic_buf, char *name_buf)
{
    if (read(fd, magic_buf, 4) != 4)
        return -1;
    if (read(fd, name_buf, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
        return -1;
    name_buf[PROG_NAME_LENGTH] = '\0';
    lseek(fd, 4, SEEK_CUR);
    header->magic = ((magic_buf[0] & 0xFF) << 24) |
        ((magic_buf[1] & 0xFF) << 16) |
        ((magic_buf[2] & 0xFF) << 8) |
        (magic_buf[3] & 0xFF);
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
    header->prog_size = ((size_buf[0] & 0xFF) << 24) |
        ((size_buf[1] & 0xFF) << 16) |
        ((size_buf[2] & 0xFF) << 8) |
        (size_buf[3] & 0xFF);
    my_printf("Debug: Raw size bytes: 0x%02x 0x%02x 0x%02x 0x%02x\n",
        size_buf[0], size_buf[1], size_buf[2], size_buf[3]);
    my_printf("Debug: Program size: %d\n", header->prog_size);
    for (int i = 0; i < COMMENT_LENGTH; i++)
        header->comment[i] = comment_buf[i];
    header->comment[COMMENT_LENGTH] = '\0';
    return 0;
}

int read_champion_header(int fd, header_t *header, char *filename)
{
    unsigned char magic_buf[4];
    unsigned char size_buf[4];
    char name_buf[PROG_NAME_LENGTH + 1];
    char comment_buf[COMMENT_LENGTH + 1];

    if (read_magic_and_name(fd, header, magic_buf, name_buf) == -1) {
        my_printf("Error: File %s is too small or corrupted\n", filename);
        return 84;
    }
    if (read_size_and_comment(fd, header, size_buf, comment_buf) == -1) {
        my_printf("Error: File %s is too small or corrupted\n", filename);
        return 84;
    }
    if (header->magic != COREWAR_EXEC_MAGIC) {
        my_printf("Error: %s has an invalid header"
            " (magic: 0x%x, expected: 0x%x)\n"
            , filename, header->magic, COREWAR_EXEC_MAGIC);
        return 84;
    }
    if (header->prog_size <= 0 || header->prog_size > MEM_SIZE) {
        my_printf("Error: %s has invalid program size: %d"
            " (must be > 0 and <= %d)\n",
            filename, header->prog_size, MEM_SIZE);
        return 84;
    }
    return 0;
}
