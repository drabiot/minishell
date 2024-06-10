/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:05:39 by tchartie          #+#    #+#             */
/*   Updated: 2024/06/09 21:41:57 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef char	t_bool;

# define FALSE 0
# define TRUE 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ********************************************************** */
/*                                                            */
/*                  Part 1 : Libc functions                   */
/*                                                            */
/* ********************************************************** */

/* ****************************************** */
/*                ft_isalpha.c                */
/*   Checks  for  an  alphabetic character    */
/*      which are neither uppercase nor       */
/*                 lowercase                  */
/* ****************************************** */
int		ft_isalpha(int character);

/* ****************************************** */
/*                ft_isdigit.c                */
/*      Checks for a digit (0 through 9)      */
/* ****************************************** */
int		ft_isdigit(int character);

/* ****************************************** */
/*                ft_isalnum.c                */
/*   Checks for an alphanumeric character.    */
/*            It is equivalent to             */
/*         (isalpha(c) || isdigit(c))         */
/* ****************************************** */
int		ft_isalnum(int character);

/* ****************************************** */
/*                ft_isascii.c                */
/*     Checks whether c is a 7-bit value      */
/*   that fits into the ASCII character set   */
/* ****************************************** */
int		ft_isascii(int character);

/* ****************************************** */
/*                ft_isprint.c                */
/*    Checks for any printable character      */
/*              including space               */
/* ****************************************** */
int		ft_isprint(int character);

/* ****************************************** */
/*                ft_strlen.c                 */
/*    Calculates the length of the string     */
/*    excluding the terminating null byte     */
/* ****************************************** */
size_t	ft_strlen(const char *str);

/* ****************************************** */
/*                ft_memset.c                 */
/*   Fills the first n bytes of the memory    */
/*       area with the constant byte c        */
/* ****************************************** */
void	*ft_memset(void *s, int c, size_t n);

/* ****************************************** */
/*                 ft_bzero.c                 */
/*   Erases the data in the n bytes of the    */
/*  memory starting at the location pointed   */
/*   to by s, by writing zeros to that area   */
/* ****************************************** */
void	ft_bzero(void *s, size_t n);

/* ****************************************** */
/*                ft_memcpy.c                 */
/*      Copies n bytes from memory area       */
/*          src to memory area dest           */
/* ****************************************** */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/* ****************************************** */
/*                ft_memmove.c                */
/*      Copies n bytes from memory area       */
/*          src to memory area dest           */
/* ****************************************** */
void	*ft_memmove(void *dest, const void *src, size_t n);

/* ****************************************** */
/*                ft_strlcpy.c                */
/*     Copy strings. Take the full size       */
/*      of the buffer and guarantee to        */
/*          NUL-terminate the result          */
/* ****************************************** */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/* ****************************************** */
/*                ft_strcat.c                 */
/*       Concatenate two given strings        */
/* ****************************************** */
char	*ft_strcat(char const *s1, char const *s2, char *array);

/* ****************************************** */
/*                ft_strlcat.c                */
/*  Concatenate strings. Take the full size   */
/*      of the buffer and guarantee to        */
/*          NUL-terminate the result          */
/* ****************************************** */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* ****************************************** */
/*                ft_toupper.c                */
/*    If character is a lowercase letter,     */
/*      returns its uppercase equivalent      */
/* ****************************************** */
int		ft_toupper(int character);

/* ****************************************** */
/*                ft_tolower.c                */
/*    If character is a uppercase letter,     */
/*      returns its lowercase equivalent      */
/* ****************************************** */
int		ft_tolower(int character);

/* ****************************************** */
/*                ft_strchr.c                 */
/*      Returns  a  pointer to the first      */
/*       occurrence of the character c        */
/*              in the string s               */
/* ****************************************** */
char	*ft_strchr(const char *s, int c);
char	*ft_strmultichr(const char *s, char *c);

/* ****************************************** */
/*                ft_strrchr.c                */
/*      Returns  a  pointer to the last       */
/*       occurrence of the character c        */
/*              in the string s               */
/* ****************************************** */
char	*ft_strrchr(const char *s, int c);

/* ****************************************** */
/*               ft_str(n)cmp.c               */
/*          Compares the two strings          */
/* returns an integer indicating the result   */
/*             of the comparison:             */
/* •0, if the s1 and s2 are equal             */
/* •a negative value if s1 is less than s2    */
/* •a positive value if s1 is greater than s2 */
/* ****************************************** */
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* ****************************************** */
/*                ft_memchr.c                 */
/*  Scans  the initial n bytes of the memory  */
/*        area pointed to by s for the        */
/*            first instance of c             */
/* ****************************************** */
void	*ft_memchr(const void *s, int c, size_t n);

/* ****************************************** */
/*                ft_memcmp.c                 */
/*  Returns an integer less than, equal to,   */
/*      or  greater  than  zero  if  the      */
/*       first  n bytes of s1 is found        */
/* ****************************************** */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/* ****************************************** */
/*                ft_strnstr.c                */
/*    Locates the first occurrence of the     */
/*    null-terminated string little in the    */
/*    string big, where not more than len     */
/*          characters are searched.          */
/* ****************************************** */
char	*ft_strnstr(const char *s1, const char *s2, size_t len);

/* ****************************************** */
/*                 ft_atoi.c                  */
/*    Converts the initial portion of the     */
/*            string to an integer            */
/* ****************************************** */
int		ft_atoi(const char *str);

/* ****************************************** */
/*                 ft_atol.c                  */
/*    Converts the initial portion of the     */
/*              string to a long              */
/* ****************************************** */
long	ft_atol(const char *str);

/* ****************************************** */
/*                ft_calloc.c                 */
/* Allocates size bytes and returns a pointer */
/*          to the allocated memory           */
/* ****************************************** */
void	*ft_calloc(size_t nmemb, size_t size);

/* ****************************************** */
/*                ft_strdup.c                 */
/*  Returns a pointer to a new string which   */
/*       is a duplicate of the string s       */
/* ****************************************** */
char	*ft_strdup(const char *src);

/* ********************************************************** */
/*                                                            */
/*                Part 2 : Additional functions               */
/*                                                            */
/* ********************************************************** */

/* ****************************************** */
/*                ft_substr.c                 */
/*      Allocates & returns a substring       */
/*           from the given string.           */
/*       The substring begins at index        */
/*    ’start’ and is of maximum size ’len’    */
/* ****************************************** */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* ****************************************** */
/*                ft_strjoin.c                */
/*     Allocates & returns a new string,      */
/*  which is the result of the concatenation  */
/*            of two given strings            */
/* ****************************************** */
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnjoin(char *s1, char const *s2, size_t len);

/* ****************************************** */
/*                ft_strtrim.c                */
/*        Allocates& returns a copy of        */
/*     ’s1’ with the characters specified     */
/*         in ’set’ removed from the          */
/*    beginning and the end of the string     */
/* ****************************************** */
char	*ft_strtrim(char const *s1, char const *set);

/* ****************************************** */
/*                 ft_split.c                 */
/*        Allocates & returns an array        */
/*      of strings obtained by splitting      */
/*      the given string using the given      */
/*  character as a delimiter. The array must  */
/*          end with a NULL pointer           */
/* ****************************************** */
char	**ft_split(char const *s, char c);
char	**ft_multisplit(char const *s, char *sep);

/* ****************************************** */
/*                 ft_itoa.c                  */
/*        Allocates & returns a string        */
/*     representing the integer received      */
/*              as an argument.               */
/*      Negative numbers must be handled      */
/* ****************************************** */
char	*ft_itoa(int n);

/* ****************************************** */
/*                ft_strmapi.c                */
/* Applies the function ’f’ to each character */
/*      of the given string , & passing       */
/*   its index as first argument to create    */
/*           a new string resulting           */
/*    from successive applications of ’f’     */
/* ****************************************** */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* ****************************************** */
/*               ft_striteri.c                */
/* Applies the function ’f’ on each character */
/*     of the string passed as argument,      */
/*   passing its index as first argument.     */
/*        Each character is passed by         */
/* address to ’f’ to be modified if necessary */
/* ****************************************** */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* ****************************************** */
/*              ft_putchar_fd.c               */
/*       Outputs the given character to       */
/*         the given file descriptor          */
/* ****************************************** */
void	ft_putchar_fd(char c, int fd);

/* ****************************************** */
/*               ft_putstr_fd.c               */
/*        Outputs the given string to         */
/*         the given file descriptor          */
/* ****************************************** */
void	ft_putstr_fd(char *s, int fd);

/* ****************************************** */
/*               ft_putstr_fd.c               */
/*        Outputs the given string to         */
/*         the given file descriptor          */
/*           followed by a newline            */
/* ****************************************** */
void	ft_putendl_fd(char *s, int fd);

/* ****************************************** */
/*               ft_putstr_fd.c               */
/*        Outputs the given integer to        */
/*         the given file descriptor          */
/* ****************************************** */
void	ft_putnbr_fd(int n, int fd);

/* ********************************************************** */
/*                                                            */
/*                         Bonus part                         */
/*                                                            */
/* ********************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ****************************************** */
/*                ft_lstnew.c                 */
/*      Allocates & returns a new node.       */
/*      The member variable ’content’ is      */
/*     initialized with the value of the      */
/*            parameter ’content’.            */
/* The variable ’next’ is initialized to NULL */
/* ****************************************** */
t_list	*ft_lstnew(void *content);

/* ****************************************** */
/*             ft_lstadd_front.c              */
/*    Adds the node ’new’ at the beginning    */
/*                of the list                 */
/* ****************************************** */
void	ft_lstadd_front(t_list **lst, t_list *new);

/* ****************************************** */
/*                ft_lstsize.c                */
/*    Counts the number of nodes in a list    */
/* ****************************************** */
int		ft_lstsize(t_list *lst);

/* ****************************************** */
/*                ft_lstlast.c                */
/*     Returns the last node of the list      */
/* ****************************************** */
t_list	*ft_lstlast(t_list *lst);

/* ****************************************** */
/*              ft_lstadd_back.c              */
/*       Adds the node ’new’ at the end       */
/*                of the list                 */
/* ****************************************** */
void	ft_lstadd_back(t_list **lst, t_list *new);

/* ****************************************** */
/*               ft_lstdelone.c               */
/*   Takes as a parameter a node and frees    */
/*      the memory of the node’s content      */
/*    using the function ’del’ given as a     */
/*  parameter & free the node. The memory of  */
/*          ’next’ must not be freed          */
/* ****************************************** */
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/* ****************************************** */
/*               ft_lstclear.c                */
/* Deletes and frees the given node and every */
/*     successor of that node, using the      */
/*          function ’del’ and free.          */
/*   Finally, the pointer to the list must    */
/*               be set to NULL               */
/* ****************************************** */
void	ft_lstclear(t_list **lst, void (*del)(void*));

/* ****************************************** */
/*                ft_lstiter.c                */
/*  Iterates the list ’lst’ and applies the   */
/*  function ’f’ on the content of each node  */
/* ****************************************** */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/* ****************************************** */
/*                ft_lstmap.c                 */
/*  Iterates the list ’lst’ and applies the   */
/* function ’f’ on the content of each node.  */
/*    Creates a new list resulting of the     */
/*       successive applications of the       */
/*    function ’f’. The ’del’ function is     */
/*    used to delete the content of a node    */
/*                 if needed.                 */
/* ****************************************** */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ********************************************************** */
/*                                                            */
/*                        ft_random.c                         */
/*                                                            */
/* ********************************************************** */

/* ****************************************** */
/*                 ft_srand()                 */
/*         Initialize the given seed          */
/* ****************************************** */
void	ft_srand(unsigned int seed);

/* ****************************************** */
/*                 ft_rand()                  */
/*   Take two numbers and provide a random    */
/*            number between them             */
/* ****************************************** */
int		ft_rand(int a, int b);


/* ****************************************** */
/*                get_next_line               */
/*       Read first line not read in fd       */
/* ****************************************** */
char	*get_next_line(int fd);
char	*ft_substr_gnl(char *s, int start, int len, int clear);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_read_line(int fd);
char	ft_find_newline(char *last_line);
char	*ft_div_line(char *current_line, char *last_line, int i);
char	*ft_find_line(char *current_line, char **last_line, int fd);
char	*ft_find_readed_line(char **last_line);

#endif //LIBFT_H
