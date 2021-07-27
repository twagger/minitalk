SRCSCLI		= srcs/client.c \
			  srcs/utils.c

SRCSSRV		= srcs/server.c \
			  srcs/utils.c

OBJSCLI		= $(SRCSCLI:.c=.o)

OBJSSRV		= $(SRCSSRV:.c=.o)

BSRCSCLI	= srcs/client_bonus.c \
			  srcs/utils.c

BSRCSSRV	= srcs/server_bonus.c \
			  srcs/utils.c

BOBJSCLI	= $(BSRCSCLI:.c=.o)

BOBJSSRV	= $(BSRCSSRV:.c=.o)

NAMECLI		= client

NAME		= server

HEADERS		= includes/

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

CC			= gcc

AR			= ar rcs

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(HEADERS)

$(NAME):	$(OBJSSRV) $(OBJSCLI)
			$(CC) $(CFLAGS) $(OBJSSRV) -o $(NAME) -I$(HEADERS)
			$(CC) $(CFLAGS) $(OBJSCLI) -o $(NAMECLI) -I$(HEADERS)

all:		$(NAME)

clean:
			$(RM) $(OBJSSRV) $(OBJSCLI) $(BOBJSSRV) $(BOBJSCLI)

fclean:		clean
			$(RM) $(NAME) $(NAMECLI)

bonus:		fclean $(BOBJSSRV) $(BOBJSCLI)
			$(CC) $(CFLAGS) $(BOBJSSRV) -o $(NAME) -I$(HEADERS)
			$(CC) $(CFLAGS) $(BOBJSCLI) -o $(NAMECLI) -I$(HEADERS)

re:			fclean all

bonus:		all

.PHONY:		all clean fclean c.o re bonus
